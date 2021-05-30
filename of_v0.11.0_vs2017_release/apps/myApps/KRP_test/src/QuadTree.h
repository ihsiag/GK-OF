#pragma once
#include <any>
#include <vector>
#include <algorithm>

template<class T>
class QuadTree;

struct Bound {
    Bound(const Bound& other) : Bound(other.x, other.y, other.width, other.height) {}
    Bound(float x = 0, float y = 0, float width = 0, float height = 0) : x(x), y(y), width(width), height(height) {}
    
    bool contains(const Bound &other) const {
        if (x > other.x) return false;
        if (y > other.y) return false;
        if (x + width  < other.x + other.width) return false;
        if (y + height < other.y + other.height) return false;
        return true;
    }
    
    bool intersects(const Bound &other) const {
        if (x > other.x + other.width)  return false;
        if (x + width < other.x)        return false;
        if (y > other.y + other.height) return false;
        if (y + height < other.y)       return false;
        return true;
    }
    
    float getLeft() const { return x - (width  * 0.5f); }
    float getTop() const { return y + (height * 0.5f); }
    float getRight() const { return x + (width  * 0.5f); }
    float getBottom() const { return y - (height * 0.5f); }
    
    float x, y, width, height;
};

template<class T>
struct Collidable {
    friend class QuadTree<T>;
public:
    Bound bound;
    T data;
    
    Collidable(const Bound & bound = {}, T data = {}) : bound(bound), data(data) {}
private:
    QuadTree<T> *qt = nullptr;
    Collidable(const Collidable&) = delete;
};

template<class T>
class QuadTree {
public:
    QuadTree(const Bound & bounds, unsigned capacity, unsigned maxLevel) : bounds(bounds), capacity(capacity), maxLevel(maxLevel) {
        objects.reserve(capacity);
        foundObjects.reserve(capacity);
    };
    QuadTree() : QuadTree({}, 0, 0) {}
    
    bool insert(Collidable<T> *obj) {
        if (obj->qt != nullptr) return false;
        
        if (!isLeaf) {
            // insert object into leaf
            if (QuadTree *child = getChild(obj->bound))
                return child->insert(obj);
        }
        objects.push_back(obj);
        obj->qt = this;
        
        // Subdivide if required
        if (isLeaf && level < maxLevel && objects.size() >= capacity) {
            subdivide();
            update(obj);
        }
        return true;
    }
    
    bool remove(Collidable<T> *obj) {
        if (obj->qt == nullptr) return false; // Cannot exist in vector
        if (obj->qt != this) return obj->qt->remove(obj);
        
        objects.erase(std::find(objects.begin(), objects.end(), obj));
        obj->qt = nullptr;
        discardEmptyBuckets();
        return true;
    }
    
    bool update(Collidable<T> *obj) {
        if (!remove(obj)) return false;
        
        // Not contained in this node -- insert into parent
        if (parent != nullptr && !bounds.contains(obj->bound))
            return parent->insert(obj);
        if (!isLeaf) {
            // Still within current node -- insert into leaf
            if (QuadTree *child = getChild(obj->bound))
                return child->insert(obj);
        }
        return insert(obj);
    }
    
    std::vector<Collidable<T>*> &getObjectsInBound(const Bound &bound) {
        foundObjects.clear();
        for (const auto &obj : objects) {
            // Only check for intersection with OTHER boundaries
            if (&obj->bound != &bound && obj->bound.intersects(bound))
                foundObjects.push_back(obj);
        }
        if (!isLeaf) {
            // Get objects from leaves
            if (QuadTree *child = getChild(bound)) {
                child->getObjectsInBound(bound);
                foundObjects.insert(foundObjects.end(), child->foundObjects.begin(), child->foundObjects.end());
            } else for (QuadTree *leaf : children) {
                if (leaf->bounds.intersects(bound)) {
                    leaf->getObjectsInBound(bound);
                    foundObjects.insert(foundObjects.end(), leaf->foundObjects.begin(), leaf->foundObjects.end());
                }
            }
        }
        return foundObjects;
    }
    
    unsigned totalChildren() const {
        unsigned total = 0;
        if (isLeaf) return total;
        for (QuadTree *child : children)
            total += child->totalChildren();
        return 4 + total;
    }
    
    unsigned totalObjects() const {
        unsigned total = (unsigned)objects.size();
        if (!isLeaf) {
            for (QuadTree *child : children)
                total += child->totalObjects();
        }
        return total;
    }
    
    void clear() {
        if (!objects.empty()) {
            for (auto&& obj : objects)
                obj->qt = nullptr;
            objects.clear();
        }
        if (!isLeaf) {
            for (QuadTree *child : children)
                child->clear();
            isLeaf = true;
        }
    }
    
    ~QuadTree() {
        clear();
        if (children[0]) delete children[0];
        if (children[1]) delete children[1];
        if (children[2]) delete children[2];
        if (children[3]) delete children[3];
    }
private:
    bool isLeaf = true;
    unsigned level  = 0;
    unsigned capacity;
    unsigned maxLevel;
    Bound bounds;
    QuadTree<T>* parent = nullptr;
    QuadTree<T>* children[4] = { nullptr, nullptr, nullptr, nullptr };
    std::vector<Collidable<T>*> objects, foundObjects;
    
    void subdivide() {
        float width = bounds.width  * 0.5f;
        float height = bounds.height * 0.5f;
        float x = 0, y = 0;
        for (unsigned i = 0; i < 4; ++i) {
            switch (i) {
                case 0: x = bounds.x + width; y = bounds.y; break; // Top right
                case 1: x = bounds.x;         y = bounds.y; break; // Top left
                case 2: x = bounds.x;         y = bounds.y + height; break; // Bottom left
                case 3: x = bounds.x + width; y = bounds.y + height; break; // Bottom right
            }
            children[i] = new QuadTree({ x, y, width, height }, capacity, maxLevel);
            children[i]->level  = level + 1;
            children[i]->parent = this;
        }
        isLeaf = false;
    }
    
    void discardEmptyBuckets() {
        if (!objects.empty()) return;
        if (!isLeaf) {
            for (QuadTree *child : children)
                if (!child->isLeaf || !child->objects.empty())
                    return;
        }
        if (clear(), parent != nullptr)
            parent->discardEmptyBuckets();
    }
    
    inline QuadTree *getChild(const Bound &bound) const {
        bool left  = bound.x + bound.width < bounds.getRight();
        bool right = bound.x > bounds.getRight();
        
        if (bound.y + bound.height < bounds.getTop()) {
            if (left)  return children[1]; // Top left
            if (right) return children[0]; // Top right
        } else if (bound.y > bounds.getTop()) {
            if (left)  return children[2]; // Bottom left
            if (right) return children[3]; // Bottom right
        }
        return nullptr; // Cannot contain boundary -- too large
    }
};


////
////  QuadTree.h
////  KRP_test
////
////  Created by rs on 2020/12/23.
////
//
//#pragma once
//#include "ofMain.h"
//
//template<class T>
//class QuadTree {
//public:
//    using Ptr = shared_ptr<QuadTree>;
//    QuadTree() {}
//    QuadTree(float x, float y, float w, float h, int capacity) {
//        setup(x, y, w, h, capacity);
//    }
//
//    void setup(float x, float y, float w, float h, int capacity) {
//        this->boundary = ofRectangle(x, y, w, h);
//        this->capacity = capacity;
//    }
//
//    void clear() {
//        points.clear();
//        nw = ne = se = sw = nullptr;
//    }
//
//    template<class U = T>
//    bool inside(const ofRectangle & b, U u, typename std::enable_if<std::is_pointer<U>::value >::type* = 0) {
//        return b.inside(u->x, u->y);
//    }
//
//    template<class U = T>
//    bool inside(const ofRectangle & b, U u, typename std::enable_if<!std::is_pointer<U>::value >::type* = 0) {
//        return b.inside(u.x, u.y);
//    }
//
//    template<class U = T>
//    bool inside(float x, float y, float radius, U u, typename std::enable_if<std::is_pointer<U>::value >::type* = 0) {
//        return ofDistSquared(x, y, u->x, u->y) < radius * radius;
//    }
//
//    template<class U = T>
//    bool inside(float x, float y, float radius, U u, typename std::enable_if<!std::is_pointer<U>::value >::type* = 0) {
//        return ofDistSquared(x, y, u.x, u.y) < radius * radius;
//    }
//
//    bool insert(const T & p) {
//        if (!inside(boundary, p)) return false;
//        if (points.size() < capacity && nw == nullptr) {
//            points.push_back(p);
//            return true;
//        }
//
//        if (nw == nullptr) subdivide();
//
//        if (nw->insert(p)) return true;;
//        if (ne->insert(p)) return true;;
//        if (sw->insert(p)) return true;;
//        if (se->insert(p)) return true;;
//
//        return false;
//    }
//
//    void subdivide() {
//        float x = boundary.x;
//        float y = boundary.y;
//        float w = boundary.width;
//        float h = boundary.height;
//
//        nw = make_shared<QuadTree>(x, y, w * 0.5, h * 0.5, capacity);
//        ne = make_shared<QuadTree>(x + w * 0.5, y, w * 0.5, h * 0.5, capacity);
//        sw = make_shared<QuadTree>(x, y + h * 0.5, w * 0.5, h * 0.5, capacity);
//        se = make_shared<QuadTree>(x + w * 0.5, y + h * 0.5, w * 0.5, h * 0.5, capacity);
//    }
//
//    vector<T> queryRange(const ofRectangle & range) {
//        vector<T> result;
//        if (!boundary.intersects(range)) return result;
//
//        for (auto & p : points) {
//            if (inside(range, p)) result.push_back(p);
//        }
//
//        if (nw == nullptr) return result;
//
//        auto nw_points = nw->queryRange(range);
//        auto ne_points = ne->queryRange(range);
//        auto sw_points = sw->queryRange(range);
//        auto se_points = se->queryRange(range);
//
//        std::copy(nw_points.begin(), nw_points.end(), std::back_inserter(result));
//        std::copy(ne_points.begin(), ne_points.end(), std::back_inserter(result));
//        std::copy(sw_points.begin(), sw_points.end(), std::back_inserter(result));
//        std::copy(se_points.begin(), se_points.end(), std::back_inserter(result));
//        return result;
//    }
//
//    vector<T> queryRange(float cx, float cy, float radius) {
//        vector<T> result;
//
//        for (auto & p : points) {
//            if (inside(cx, cy, radius, p)) result.push_back(p);
//        }
//
//        if (nw == nullptr) return result;
//
//        auto nw_points = nw->queryRange(cx, cy, radius);
//        auto ne_points = ne->queryRange(cx, cy, radius);
//        auto sw_points = sw->queryRange(cx, cy, radius);
//        auto se_points = se->queryRange(cx, cy, radius);
//
//        std::copy(nw_points.begin(), nw_points.end(), std::back_inserter(result));
//        std::copy(ne_points.begin(), ne_points.end(), std::back_inserter(result));
//        std::copy(sw_points.begin(), sw_points.end(), std::back_inserter(result));
//        std::copy(se_points.begin(), se_points.end(), std::back_inserter(result));
//        return result;
//    }
//
//    void show() {
//        ofPushStyle();
//        ofNoFill();
//        if (nw == nullptr) {
//            ofDrawRectangle(boundary);
//        } else {
//            nw->show();
//            ne->show();
//            sw->show();
//            se->show();
//        }
//        ofPopStyle();
//    }
//    QuadTree::Ptr nw, ne, sw, se;
//    int capacity;
//    ofRectangle boundary;
//    vector<T> points;
//
//    //private:
//    //    QuadTree() {}
//};
