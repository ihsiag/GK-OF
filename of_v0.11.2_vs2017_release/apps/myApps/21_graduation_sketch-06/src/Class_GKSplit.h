#pragma once

#ifndef GK_SPLIT_H  
#define GK_SPLIT_H  

#include "ofMain.h"
#include "ofxGKUtils.h"



class GKSplit {
public:
	GKPlane mainPlane;
	set<GKPlane> cutterPlanesSet;
    vector<GKPlane> cutterPlanes;
    vector<GKLineSimple> intersectLines;

	GKSplit(){}
    GKSplit(const GKPlane& _mainPlane) {
        mainPlane = _mainPlane;
        scaleMainPlane();
    }
	~GKSplit(){}

    void addCutterPlane(const GKPlane& _cutterPlane) {
        if (_cutterPlane.state != mainPlane.state) {
            cutterPlanesSet.insert(_cutterPlane);
        }
    };
    void splitExcute(vector<GKPlane>* _gkPlanesNew, vector<GKLineSimple>* _intersectLines) {
        sortCutterPlanes();
        intersectLines.erase(intersectLines.begin(), intersectLines.end());
        for (auto& cutterPlane : cutterPlanes) {
            vector<glm::vec3> _intersectPoints = getPlaneIntersection(cutterPlane, mainPlane);
            if (_intersectPoints.size() == 2) {
                GKLineSimple _intersectLine = GKLineSimple(_intersectPoints[0], _intersectPoints[1]);
                intersectLines.push_back(_intersectLine);
                GKPlane _gkPlaneNew = splitPlaneWithIntersectLine(mainPlane, _intersectLine);
                mainPlane = _gkPlaneNew;
                               
            }
        }
        _gkPlanesNew->push_back(mainPlane);
        for (auto& il : intersectLines) {
            _intersectLines->push_back(il);
        }

    };

    //-----------OPERATOR-----------//
    bool operator == (const GKSplit& _gks) const {
        return mainPlane.state == _gks.mainPlane.state;
    }
    bool operator < (const GKSplit& _gks) const {
        return mainPlane.state < _gks.mainPlane.state;
    };
    

private:
    ofxGKUtils gk;

    void sortCutterPlanes() {
        cutterPlanes.erase(cutterPlanes.begin(), cutterPlanes.end());
        for (auto& cps : cutterPlanesSet) {
            if (glm::distance(cps.centroid, mainPlane.centroid) < 40) {
                cutterPlanes.push_back(cps);
            }
        }
        for (int i = 0; i < cutterPlanes.size(); i++) {
            for (int j = 0; j < cutterPlanes.size(); j++) {
                    if (glm::angle(cutterPlanes[i].normal, mainPlane.normal) < glm::angle(cutterPlanes[i].normal, mainPlane.normal)) {
                        swap(cutterPlanes[i], cutterPlanes[j]);
                    }              
            }
        }
    }
    void scaleMainPlane() {
        for (auto& e : mainPlane.edges) {
            scalePlaneEdge(&e, mainPlane.centroid, 50);
        }
    }

    void scalePlaneEdge(GKLineSimple* _edge, const glm::vec3& _scaleCenter, const float& _scaleFactor) {
        _edge->a = glm::normalize(_edge->a - _scaleCenter) * _scaleFactor + _scaleCenter;
        _edge->b = glm::normalize(_edge->b - _scaleCenter) * _scaleFactor + _scaleCenter;
    }
    vector<glm::vec3> getPlaneIntersection(const GKPlane& _gkPlaneCutter, const GKPlane& _gkPlane) {
        int _lengthMax = 100;
        vector<glm::vec3>  _intersectPoints;
        vector<GKLineSimple> _edges = _gkPlane.edges;
        for (auto& _edge : _edges) {
            glm::vec3 _intersectPoint;
            //scalePlaneEdge(&_edge, _gkPlaneActive.centroid, _lengthMax);
            float _innerA = glm::dot(_gkPlaneCutter.normal, _edge.a - _gkPlaneCutter.centroid);
            float _innerB = glm::dot(_gkPlaneCutter.normal, _edge.b - _gkPlaneCutter.centroid);
            if (abs(_innerA) < 0.000001) { _innerA = 0.0; }
            if (abs(_innerB) < 0.000001) { _innerB = 0.0; }
            if ((_innerA > 0 && _innerB < 0) || (_innerA < 0 && _innerB > 0)) {
                // _bIntersect = true;
                _intersectPoint = (_edge.b - _edge.a) * abs(_innerA) / (abs(_innerA) + abs(_innerB)) + _edge.a;
                _intersectPoints.push_back(_intersectPoint);
            }
        }
        return _intersectPoints;
    }
    GKPlane splitPlaneWithIntersectLine(const GKPlane& _gkPlane, const GKLineSimple& _gkLine) {
        vector<GKPoint> _gkPointsPolar;
        vector<glm::vec3> _onPlaneGKPlaneVertices = gk.getOnPlaneVertices(_gkPlane.vertices, _gkPlane.modifyInfo);
        for (auto& v : _onPlaneGKPlaneVertices) {
            _gkPointsPolar.push_back(GKPoint(gk.getPolarFromRectangular(v), 0)); //0 means pts from GKPlane
        }
        vector<glm::vec3> _onPlaneGKLineVertices = gk.getOnPlaneVertices({ _gkLine.a,_gkLine.b }, _gkPlane.modifyInfo);
        for (auto& v : _onPlaneGKLineVertices) {
            _gkPointsPolar.push_back(GKPoint(gk.getPolarFromRectangular(v), 1)); //1 means pts from GKLine
        }
        gk.sortPolars(&_gkPointsPolar);
        vector<glm::vec3> _verticesForA, _verticesForB;
        bool bFaceBBegin = false;
        for (auto& gkPoint : _gkPointsPolar) {
            if (gkPoint.state == 1) {
                _verticesForA.push_back(gkPoint.pos);
                _verticesForB.push_back(gkPoint.pos);
                bFaceBBegin = !bFaceBBegin;
            }
            else {
                if (bFaceBBegin)_verticesForB.push_back(gkPoint.pos);
                else _verticesForA.push_back(gkPoint.pos);
            }
        }
        for (auto& v : _verticesForA) {
            v = gk.getRectangularFromPolar(v);
        }
        for (auto& v : _verticesForB) {
            v = gk.getRectangularFromPolar(v);
        }
        GKPlane _splittedFaceA, _splittedFaceB;
        _verticesForA = gk.getModifiedVertices(_verticesForA, _gkPlane.modifyInfo);
        _verticesForB = gk.getModifiedVertices(_verticesForB, _gkPlane.modifyInfo);
        _splittedFaceA.setup(_verticesForA, 1);
        _splittedFaceB.setup(_verticesForB, 1);
        if (_splittedFaceA.hasInside(_gkPlane.centroid)) {
            return _splittedFaceA;
        }
        else if (_splittedFaceB.hasInside(_gkPlane.centroid)) {
            return _splittedFaceB;
        }
        else {
            return GKPlane();
        }
    }
};
#endif