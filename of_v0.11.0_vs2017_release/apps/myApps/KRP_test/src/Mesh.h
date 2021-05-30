//
//  Mesh.h
//  KRP_test
//
//  Created by rs on 2020/12/24.
//

#pragma once
#include "ofMain.h"
#include "AABB.hpp"
#include "QuadTree.h"
#include "Utils.h"
#include <boost/any.hpp>

using AABB2 = AABB<glm::vec2, 2>;

struct DrawParam {
    GLuint mode;
    GLfloat color[4];
    GLuint pointSize;
    GLuint lineWidth;
    GLfloat step[2];
    
    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
        color[0] = r;  color[1] = g;  color[2] = b;  color[3] = a; 
    }
    
    void setHatching(GLfloat x, GLfloat y) {
        step[0] = x; step[1] = y;
    }
};

struct Vertex {
    GLfloat pos[3];
    GLfloat color[4];
    
    bool operator == (const Vertex & rhs) const {
        return pos[0] == rhs.pos[0] && pos[1] == rhs.pos[1] && pos[2] == rhs.pos[2];
    }
};

class Mesh : public std::enable_shared_from_this<Mesh> {
public:
    using Ptr = shared_ptr<Mesh>;
    
    Mesh() : mode(GL_TRIANGLES) {}
    
    virtual ~Mesh() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);
        glDeleteVertexArrays(1, &vao);
    }
    
    void init() {        
        data.clear();
        indices.clear();
        
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
        
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ((Vertex *)0)->pos);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), ((Vertex *)0)->color);
        
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    void updateVbo() {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        int bufSize = 0;
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufSize);
        if (bufSize) glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * data.size(),&data[0]);
        else glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * data.size(), &data[0], GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void updateIBO() {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void updateCollider() {
        auto p = shared_from_this();
        item = Collidable<shared_ptr<Mesh>>({ aabb.x(), aabb.y(), aabb.getWidth(), aabb.getHeight() }, p);
    }
    
    void draw() {
        if (bUpdateVBO) {
            updateVbo();
            bUpdateVBO = false;
        }
        
        if (bUpdateIBO) {
            updateIBO();
            bUpdateIBO = false;
        }
        
        if (data.empty()) return;
        
        if (indices.size()) {
            glBindVertexArray(vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glDrawElements(mode, indices.size(), GL_UNSIGNED_SHORT, (void *)0);
            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        } else {
            glBindVertexArray(vao);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glDrawArrays(mode, 0, data.size());
            glBindVertexArray(0);
        }
    }
    
    void setMode(GLuint mode) {
        this->mode = mode;
    }
    
    int size() const {
        return data.size();
    }
    
    void addVertex(GLfloat x, GLfloat y, GLfloat z, GLfloat r = 0, GLfloat g = 0, GLfloat b = 0, GLfloat a = 1) {
        data.push_back({ { x,  y, z }, { r, g, b, a } });
        aabb.add(glm::vec2(x, y));
        bUpdateVBO = true;
    }
    
    void setVertex(int i, GLfloat x, GLfloat y, GLfloat z) {
        data[i].pos[0] = x;
        data[i].pos[1] = y;
        data[i].pos[2] = z;
        bUpdateVBO = true;
    }
    
    void setColor(int i, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
        data[i].color[0] = r;
        data[i].color[1] = g;
        data[i].color[2] = b;
        data[i].color[3] = a;
        bUpdateVBO = true;
    }
    
    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
        for (auto & d : data) {
            d.color[0] = r;
            d.color[1] = g;
            d.color[2] = b;
            d.color[3] = a;
        }
        bUpdateVBO = true;
    }
    
    void clearVertices() {
        data.clear();
        aabb.reset();
        bUpdateVBO = true;
    }
    
    void addIndex(GLushort i) {
        indices.push_back(i);
        bUpdateIBO = true;
    }
    
    void clearIndices() {
        indices.clear();
        bUpdateIBO = true;
    }
    
    Vertex & getVertex(int index) {
        return data[index];
    }
    
    vector<Vertex> & getVertices() {
        return data;
    }
    
    void getCentroid(float * x, float * y) {
        float cx = 0;
        float cy = 0;
        for (int i = 0; i < data.size(); i++) {
            cx += data[i].pos[0];
            cy += data[i].pos[1];
        }
        *x = cx / data.size();
        *y = cy / data.size();
    }
    
    int clockwise() {
        int a;
        double p1x = data[0].pos[0];
        double p1y = data[0].pos[1];
        double p2x = data[1].pos[0];
        double p2y = data[1].pos[1];
        double p3x = data[2].pos[0];
        double p3y = data[2].pos[1];
        
        double dx2, dy2, dx3, dy3;
        
        dx2 = p2x - p1x;
        dy2 = p2y - p1y;
        dx3 = p3x - p1x;
        dy3 = p3y - p1y;
        
        if ( ( dx2 * dy3 ) > ( dx3 * dy2 ) ) a = -1;
        else if ( ( dx2 * dy3 ) < ( dx3 * dy2 ) ) a = 1;
        else a = 0;
        
        return a;
    }
    
    Collidable<shared_ptr<Mesh>> item;
    AABB2 aabb;
    DrawParam param;
    
    vector<boost::any> props;
    
    template<class T>
    T getProp(int field) const {
        if (props[field].type() == typeid(T)) {
            return boost::any_cast<T>(props[field]);
        } else {
            throw "type mismatching";;
        }
    }
    
    void resample(float space) {
        ofPolyline line;
        for (auto v : data) {
            line.addVertex(v.pos[0], v.pos[1], v.pos[2]);
        }
        line = line.getResampledBySpacing(space);
        
        clearVertices();
        for (auto & v : line.getVertices()) {
            addVertex(v.x, v.y, v.z, 0, 0, 0, 1);
        }
    }
//    map<string, boost::any> props; //custom property
//    template<class T>
//    void set(const string & name, const T & prop) {
//        props.insert(make_pair(name, prop));
//    }
//
//    template<class T>
//    bool get(const string & name, T * prop) {
//        auto it = props.find(name);
//        if (it == props.end()) return false;
//        if ((it->second).type() != typeid(T)) return false;
//        *prop = boost::any_cast<T>(it->second);
//        return true;
//    }
    
protected:
    GLuint mode;
    GLuint vbo;
    GLuint ibo;
    GLuint vao;
    vector<Vertex> data;
    vector<GLushort> indices;
    bool bUpdateVBO = false;
    bool bUpdateIBO = false;
};

//class Mesh : public ofVboMesh , public std::enable_shared_from_this<Mesh> {
//public:
//    using Ptr = shared_ptr<Mesh>;
//    void addVertex(float x, float y) {
//        ofVboMesh::addVertex(glm::vec3(x, y, 0));
//        aabb.add(glm::vec2(x, y));
//    }
//
//    void update() {
//        auto p = shared_from_this();
//        item = Collidable<shared_ptr<Mesh>>({ aabb.x(), aabb.y(), aabb.getWidth(), aabb.getHeight() }, p);
//    }
//
//    AABB2 aabb;
//    ofFloatColor color;
//    Collidable<shared_ptr<Mesh>> item;
//};
