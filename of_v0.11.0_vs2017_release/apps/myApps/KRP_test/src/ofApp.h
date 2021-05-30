#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "QuadTree.h"
#include "Mesh.h"
#include "Label.h"
#include "Utils.h"

#include "ofxSyphon.h"

#include <earcut.hpp>

static void convertToMesh(SHPObject* psShape, vector<Mesh::Ptr> & polygons) {
    double* x = psShape->padfX;
    double* y = psShape->padfY;
    
    int type = psShape->nSHPType;
    int nParts = psShape->nParts;
    int nVertices = psShape->nVertices;
    if (type == SHPT_POINT) {
        Mesh::Ptr polygon = make_shared<Mesh>();
        polygon->init();
        polygon->setMode(toGLType(type));
        for (int v = 0; v < nVertices; v++) {
            double x2, y2;
            lonlat2xy(x[v], y[v], MID_LON, MID_LAT, &x2, &y2);
            polygon->addVertex(x2 * 0.1, y2 * 0.1, 0);
        }
        polygons.push_back(polygon);
    } else {
        int glType = toGLType(type);
        for (int j = 0; j < nParts; j++) {
            int counts = 0;
            if (j != (nParts - 1)) counts = psShape->panPartStart[j + 1] - psShape->panPartStart[j];
            else counts = nVertices - psShape->panPartStart[j];
            Mesh::Ptr polygon = make_shared<Mesh>();
            polygon->init();
            polygon->setMode(glType);
            for (int k = 0; k < counts; k++) {
                int v = k + psShape->panPartStart[j];
                double x2, y2;
                lonlat2xy(x[v], y[v], MID_LON, MID_LAT, &x2, &y2);
                polygon->addVertex(x2 * 0.1, y2 * 0.1, 0);
            }
            polygons.push_back(polygon);
        }
    }
}

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void drawLabel();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);

    void loadTown();
    void loadGaiku();

    void loadWaterArea();
    void loadGeometry();
    void loadLand();
    void loadAdminArea();
    void loadDisaster();
    void loadFacility();
    void loadTourism();
    void loadTraffic();

    void setParam(vector<vector<Mesh::Ptr>> & meshes, const DrawParam & param) {
        for (auto & mesh : meshes) {
            if (param.mode == GL_POINTS || param.mode == GL_LINES || param.mode == GL_LINE_STRIP) {
                for (auto & m : mesh) m->setMode(param.mode);
                if (param.mode == GL_LINES) for (auto & m : mesh) m->resample(2);
            } else if (param.mode == GL_TRIANGLES) {
                using Coord = double;
                using N = uint32_t;
                using Point = std::array<Coord, 2>;
                
                for (auto & m : mesh) {
                    m->setMode(param.mode);
                    vector<vector<Point>> polygon2;
                    vector<Point> points;
                    vector<Point> holes;

//                    auto & v1 = m->getVertex(0);
//                    auto & v2 = m->getVertex(1);
//                    auto & v3 = m->getVertex(2);
//                    if (ccw(v1.pos[0], v1.pos[1], v2.pos[0], v2.pos[1], v3.pos[0], v3.pos[1])) {
//                        for (auto & data : m->getVertices()) {
//                            holes.push_back({data.pos[0], data.pos[1]});
//                        }
//                    } else {
//                        for (auto & data : m->getVertices()) {
//                            points.push_back({data.pos[0], data.pos[1]});
//                        }
//                    }

                    for (auto & data : m->getVertices()) {
                        points.push_back({data.pos[0], data.pos[1]});
                    }
                    
                    polygon2.push_back(points);
                    polygon2.push_back(holes);
                    std::vector<N> indices = mapbox::earcut<N>(polygon2);
                    for (int i = 0; i < indices.size(); i += 3) {
                        m->addIndex(indices[i]);
                        m->addIndex(indices[i + 1]);
                        m->addIndex(indices[i + 2]);
                    }
                }
            } 
        }

        for (auto & mesh : meshes) {
            for (auto & m : mesh) m->param = param;
            for (auto & m : mesh) {
                for (int i = 0; i < m->size(); i++) m->setColor(i, param.color[0], param.color[1], param.color[2], param.color[3]);
                m->updateCollider();
                quadtree.insert(&m->item);
            }
        }
    }
    
    void loadShape(const string & filepath, vector<vector<Mesh::Ptr>> & polygons, bool bLoadDBF = true) {
        for (const auto & file : boost::filesystem::directory_iterator(ofToDataPath(filepath))) {
            if (file.path().extension() == ".shp") {
                cout << file.path().stem() << endl;
                vector<vector<Mesh::Ptr>> cur_polygons;
                try {
                    loadSHP(file.path().string(), cur_polygons, convertToMesh);
                } catch (string & e) {
                    cerr << "ERROR: " << e << endl;
                }

                std::copy(cur_polygons.begin(), cur_polygons.end(), std::back_inserter(polygons));
                
                if (bLoadDBF) {
                    auto filepath2 = file.path().parent_path().string() + "/" + file.path().stem().string() + ".dbf";
                    vector<vector<boost::any>> records;
                    try {
                        loadDBF(filepath2, records);
                    } catch (string & e) {
                        cerr << "ERROR: " << e << endl;
                    }
                 
                    if (cur_polygons.size() == records.size()) {
                        for (int i = 0; i < cur_polygons.size(); i++) {
                            auto & poly = cur_polygons[i];
                            auto & record = records[i];
                            for (auto & part : poly) {
                                part->props = record;
                            }
                        }
                    } else {
                        cerr << "record size is miss mathing" << endl;
                    }
                }
            }
        }
    }
    
    void addLabel(const string & name, float x, float y) {
        Label::Ptr label = make_shared<Label>(name, x, y);
        label->update();
        labels.push_back(label);
        quadtree2.insert(&label->item);
    }
    
    ofEasyCam cam;
    ofTrueTypeFont font;
    QuadTree<Mesh::Ptr> quadtree;
    QuadTree<Label::Ptr> quadtree2; //for label
    ofFbo fbo;
    Mesh grid;
    ofShader shader;
    ofxSyphonServer server;
    bool bDrawFull = false;
    int screenOffset = 0;

    //ラベル
    vector<Label::Ptr> labels;

    //行政地域
    vector<vector<Mesh::Ptr>> districts;
    vector<vector<Mesh::Ptr>> keikan_keikaku_kuiki;
    vector<vector<Mesh::Ptr>> keikan_chiku;
    vector<vector<Mesh::Ptr>> keikan_kenzobutsu;
    vector<vector<Mesh::Ptr>> dento_hozon_chiku;
    vector<vector<Mesh::Ptr>> hudo_hozon_kuiki;
    //水域
    vector<vector<Mesh::Ptr>> coastline; //line
    vector<vector<Mesh::Ptr>> coast_preserve; //line
    vector<vector<Mesh::Ptr>> rivers; //line
    vector<vector<Mesh::Ptr>> lakes; //polygon
    vector<vector<Mesh::Ptr>> dams; //points

    //地形
    vector<vector<Mesh::Ptr>> hyoko_mesh; //mesh
    vector<vector<Mesh::Ptr>> teii_chitai; //polygon

    //土地利用
    vector<vector<Mesh::Ptr>> tochi_mesh; //mesh
    vector<vector<Mesh::Ptr>> forests; //polygon
    vector<vector<Mesh::Ptr>> woods; //polygon
    vector<vector<Mesh::Ptr>> cities; //polygon
    vector<vector<Mesh::Ptr>> agri_lands; //polygon
    vector<vector<Mesh::Ptr>> district_use; //polygon

    //施設
    vector<vector<Mesh::Ptr>> factories; //polygon
    vector<vector<Mesh::Ptr>> water_supply; //polygon

    //地域資源・観光
    vector<vector<Mesh::Ptr>> bunkazai; //points
    vector<vector<Mesh::Ptr>> bunka_isan; //line
    vector<vector<Mesh::Ptr>> shizen_isan; //polygon
    vector<vector<Mesh::Ptr>> kanko_shigen; //polygon
    vector<vector<Mesh::Ptr>> tiiki_shigen; //points

    //交通
    vector<vector<Mesh::Ptr>> highways; //line
    vector<vector<Mesh::Ptr>> trains; //line
    vector<vector<Mesh::Ptr>> buses; //line
    vector<vector<Mesh::Ptr>> kinkyu_yuso; //line
};
