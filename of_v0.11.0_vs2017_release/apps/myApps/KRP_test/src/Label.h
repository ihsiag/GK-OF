//
//  Label.h
//  KRP_test
//
//  Created by rs on 2020/12/24.
//

#pragma once
#include "ofMain.h"

class Label : public std::enable_shared_from_this<Label> {
public:
    using Ptr = shared_ptr<Label>;
    Label(const string & name, float x, float y)
    : name(name), x(x), y(y) {
    }
    
    void update() {
        auto p = shared_from_this();
        item = Collidable<shared_ptr<Label>>({x, y, 1, 1}, p);
    }
    
    string name;
    float x;
    float y;
    Collidable<shared_ptr<Label>> item;
};
