#pragma once
#include "ofMain.h"
#include <algorithm>

template<class T, int dim = 3>
class AABB {
//    static constexpr int LIM_MAX = std::numeric_limits<int>::max();
//    static constexpr int LIM_MIN = std::numeric_limits<int>::min();
public:
    AABB () { reset(); }
    
    T size() const { return max - min; }
    float getWidth() const { return abs(max[0] - min[0]); }
    float getHeight() const { return abs(max[1] - min[1]); }
    float getDepth() const { return dim > 2 ? abs(max[2] - min[2]) : 0; }
    float getVolume() const { return getWidth() * getHeight() * (dim > 2 ? getDepth() : 1); }
    T getMin() const { return min; }
    T getMax() const { return max; }
    T getCenter() const { return (min + max) * 0.5; }
    
    float x() const { return min[0]; }
    float y() const { return min[1]; }
    float z() const { return min[2]; }
    
    float volume() const {
        return getWidth() * getHeight() * getDepth();
    }
    
    void reset() {
        for (int i = 0; i < dim; i++) {
            min[i] = INT_MAX;
            max[i] = -INT_MAX;
        }
    }
    
    void add(const T & p) {
        for (int i = 0; i < dim; i++) {
            if (p[i] < min[i]) min[i] = p[i];
            if (p[i] > max[i]) max[i] = p[i];
        }
    }
    
    void add(const AABB<T, dim> & box) {
        for (int i = 0; i < dim; i++) {
            if (box.min[i] < min[i]) min[i] = box.min[i];
            if (box.max[i] > max[i]) max[i] = box.max[i];
        }
    }
    
    bool empty() const {
        for (int i = 0; i < dim; i++) {
            if (min[i] <= max[i]) return false;
        }
        return true;
    }
    
    bool isinside(const T & p) const {
        for (int i = 0; i < dim; i++) {
            if (p[i] < min[i] && p[i] > max[i]) return false;
        }
        return true;
    }
    
    bool isIntersected(const AABB<T, dim> & box, AABB * overlap = NULL) {
        for (int i = 0; i < dim; i++) {
            if (min[i] > box.min[i]) return false;
            if (max[i] < box.max[i]) return false;
        }
        
        if (overlap != NULL) {
            for (int i = 0; i < dim; i++) {
                overlap->min[i] = std::max(min[i], box.min[i]);
                overlap->max[i] = std::min(max[i], box.max[i]);
            }
        }
        
        return true;
    }
    
    void draw() const {
        
        float min_depth = dim > 2 ? min[2] : 0;
        float max_depth = dim > 2 ? max[2] : 0;
        
        glBegin(GL_LINE_LOOP);
        glVertex3f(min[0], min[1], min_depth);
        glVertex3f(max[0], min[1], min_depth);
        glVertex3f(max[0], min[1], max_depth);
        glVertex3f(min[0], min[1], max_depth);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex3f(min[0], max[1], min_depth);
        glVertex3f(max[0], max[1], min_depth);
        glVertex3f(max[0], max[1], max_depth);
        glVertex3f(min[0], max[1], max_depth);
        glEnd();
        
        glBegin(GL_LINES);
        glVertex3f(min[0], min[1], min_depth);
        glVertex3f(min[0], max[1], min_depth);
        
        glVertex3f(max[0], min[1], min_depth);
        glVertex3f(max[0], max[1], min_depth);
        
        
        glVertex3f(max[0], min[1], max_depth);
        glVertex3f(max[0], max[1], max_depth);
        
        glVertex3f(min[0], min[1], max_depth);
        glVertex3f(min[0], max[1], max_depth);
        glEnd();
    }
    
    T min;
    T max;
};
