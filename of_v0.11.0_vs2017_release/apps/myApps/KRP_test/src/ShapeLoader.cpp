#include "ofApp.h"

static const bool getCentroid(vector<Mesh::Ptr> & poly, float * cx, float * cy) {
    auto it = max_element(begin(poly), end(poly), [](Mesh::Ptr & a, Mesh::Ptr & b) { return a->aabb.getVolume() < b->aabb.getVolume(); });
    if (it != end(poly)) {
        (*it)->getCentroid(cx, cy);
        return true;
    }
    return false;
}

void ofApp::loadTown() {
    vector<vector<string>> data;
    loadCsv("./大字・町丁目レベル位置参照情報/26_2019.csv", data);
    for (auto & row : data) {
        string name = row[3];
        float ido = stof(row[6]);
        float keido = stof(row[7]);
        double x, y;
        lonlat2xy(keido, ido, MID_LON, MID_LAT, &x, &y);
        addLabel(name, x * 0.1, y * 0.1);
    }
}

void ofApp::loadGaiku() {
    vector<vector<string>> data;
    loadCsv("./街区レベル位置参照情報/26_2019.csv", data);
    for (auto & row : data) {
        string name = row[2] + row[3] + row[4];
        float ido = stof(row[8]);
        float keido = stof(row[9]);
        double x, y;
        lonlat2xy(keido, ido, MID_LON, MID_LAT, &x, &y);
        addLabel(name, x * 0.1, y * 0.1);
    }
}

void ofApp::loadWaterArea() {
    DrawParam param = {GL_LINE_STRIP, {0.0, 0.0, 0.0, 1}, 1, 1, 0, 0};
    
    loadShape("水域/海岸線", coastline);
    param.lineWidth = 2;
    param.setColor(1, 0, 0, 1);
    param.setHatching(0, 0);
    setParam(coastline, param);
    try {
        for (auto & poly : coastline) {
            for (auto & part : poly) {
                auto name = part->getProp<string>(3);
                if (name.size()) {
                    auto & v = part->getVertex(part->size() * 0.5);
                    addLabel(name, v.pos[0], v.pos[1]);
                }
            }
        }
    } catch(const boost::bad_any_cast& e) {
        cout << e.what() << endl;
    }
    
    loadShape("水域/海岸保全施設", coast_preserve);
    param.mode = GL_AUTO;
    param.lineWidth = 2;
    param.pointSize = 4;
    param.setColor(1, 0, 0, 1);
    param.setHatching(0, 0);
    setParam(coast_preserve, param);
    try {
        //        for (auto & poly : coastline) {
        //            for (auto & part : poly) {
        //                auto name = part->getProp<string>(3);
        //                if (name.size()) {
        //                    auto & v = part->getVertex(part->size() * 0.5);
        //                    addLabel(name, v.pos[0], v.pos[1]);
        //                }
        //            }
        //        }
    } catch(const boost::bad_any_cast& e) {
        cout << e.what() << endl;
    }
    
    loadShape("水域/河川データ", rivers);
    param.mode = GL_AUTO;
    param.pointSize = 5;
    param.lineWidth = 2;
    param.setColor(0, 0, 1, 1);
    param.setHatching(0, 0);
    setParam(rivers, param);
    try {
        for (auto & poly : rivers) {
            for (auto & part : poly) {
                if (part->props.size() == 10) {
                    auto type = part->getProp<string>(2);
                    auto name = part->getProp<string>(3);
                    if (name.size() && name != "名称不明") {
                        auto & v = part->getVertex(part->size() * 0.5);
                        addLabel(name, v.pos[0], v.pos[1]);
                    }

                    part->setColor(0, 0, 1.0, 1.0);
                }
            }
        }
    } catch(const boost::bad_any_cast& e) {
        cout << e.what() << endl;
    }
    
    loadShape("水域/湖沼データ", lakes);
    param.mode = GL_TRIANGLES;
    param.setColor(0, 0, 1, 0.5);
    param.setHatching(0, 0);
    setParam(lakes, param);
    try {
        for (auto & poly : lakes) {
            auto name = poly[0]->getProp<string>(0);
            if (name.size()) {
                float cx, cy;
                if (getCentroid(poly, &cx, &cy)) addLabel(name, cx, cy);
            }
        }
    } catch(const boost::bad_any_cast& e) {
        cout << e.what() << endl;
    }
    
//    loadShape("水域/ダムデータ", dams);
//    param.mode = GL_POINTS;
//    param.setColor(0, 0, 1, 1);
//    param.pointSize = 3;
//    param.setHatching(0, 0);
//    setParam(dams, param);
//    try {
//        for (auto & poly : dams) {
//            for (auto & part : poly) {
//                auto name = part->getProp<string>(0);
//                if (name.size()) {
//                    auto & v = part->getVertex(0);
//                    addLabel(name, v.pos[0], v.pos[1]);
//                }
//            }
//        }
//    } catch(const boost::bad_any_cast& e) {
//        cout << e.what() << endl;
//    }
}

void ofApp::loadGeometry() {
    DrawParam param = {GL_LINE_STRIP, {0.0, 0.0, 0.0, 1}, 1, 1, 0, 0};
    //    loadShape("地形/標高・傾斜度5次メッシュデータ", hyoko_mesh);
    //    setParam(hyoko_mesh, {GL_POINTS, {0, 0, 0, 1}, 1, 1});
    
    loadShape("地形/低位地帯", teii_chitai);
    param.mode = GL_TRIANGLES;
    param.setColor(0.5, 0.5, 0.5, 0.75);
    param.setHatching(2, 2);
    setParam(teii_chitai, param);
}

void ofApp::loadLand() {
    DrawParam param = {GL_LINE_STRIP, {0.0, 0.0, 0.0, 1}, 1, 1, 0, 0};

//    loadShape("土地利用/土地利用3次メッシュ", tochi_mesh);
//    setParam(tochi_mesh, GL_POINTS);//GL_TRIANGLES);
//
    loadShape("土地利用/森林地域", forests);
    param.mode = GL_TRIANGLES;
    param.setColor(0, 1, 0, 1);
    param.setHatching(2, 2);
    setParam(forests, param);
//    try {
//        for (auto & poly : forests) {
//            for (auto & part : poly) {
//                auto layer = part->getProp<int>(6);
//                float col = ofMap(layer, 7, 10, 0.25, 1);
////                part->setColor(0, col, 0, 0.8);
//                if (part->clockwise() == 1) part->setColor(0, 0, 0, 0.8);
//                else part->setColor(1, 0, 0, 0.8);
//            }
//        }
    try {
        for (int i = 0; i < forests.size(); i++) {
            auto & poly = forests[i];
            
            float hue = ofMap(i, 0, forests.size(), 0.0, 1.0, true);
            ofFloatColor col = ofFloatColor::fromHsb(hue, 0.8, 1.0);
            
            for (int i = 0; i < poly.size(); i++) {
                poly[i]->setColor(col.r, col.g, col.b, 1);
            }
        }
    } catch(const boost::bad_any_cast& e) {
        cout << e.what() << endl;
    }

    loadShape("土地利用/国有林野", woods);
    param.mode = GL_LINE_STRIP;
    param.setColor(0, 0.5, 0, 1);
    param.setHatching(0, 0);
    setParam(woods, param);
    try {
        for (auto & poly : woods) {
            auto name = poly[0]->getProp<string>(12);
            if (name.size()) {
                float cx, cy;
                if (getCentroid(poly, &cx, &cy)) addLabel(name, cx, cy);
            }
        }
    } catch(const boost::bad_any_cast& e) {
        cout << e.what() << endl;
    }
    
    loadShape("土地利用/都市地域/shp_file", cities);
    param.mode = GL_TRIANGLES;
    param.setColor(1, 0, 0, 0.5);
    param.setHatching(4, 4);
    setParam(cities, param);
    for (int i = 0; i < cities.size(); i++) {
        auto & poly = cities[i];
        ofFloatColor col = ofFloatColor::fromHsb(ofMap(i, 0, cities.size(), 0.0, 0.15), 0.5, 1.0);
        for (auto & part : poly) {
            part->setColor(col.r, col.g, col.b, 1);
        }
    }

    loadShape("土地利用/農業地域", agri_lands);
    param.mode = GL_TRIANGLES;
    param.setColor(0, 1, 0, 1);
    param.setHatching(4, 4);
    setParam(agri_lands, param);
    try {
        for (auto & poly : agri_lands) {
            string name = poly[0]->getProp<string>(3);
            if (name.size()) {
                float cx, cy;
                if (getCentroid(poly, &cx, &cy)) addLabel(name, cx, cy);
            }
            
            auto layer = poly[0]->getProp<int>(6);
            for (auto & part : poly) {
                if (layer == 5) {
                    part->setColor(0, 0.5, 0, 0.5);
                } else {
                    part->setColor(0, 1, 0, 0.5);
                }
            }
        }
    } catch(const boost::bad_any_cast& e) {
        cout << e.what() << endl;
    }
    
//    loadShape("土地利用/用途地域/01-01_シェープファイル形式", district_use);
//    param.mode = GL_TRIANGLES;
//    param.setColor(0, 1, 1, 1);
//    param.setHatching(2, 2);
//    setParam(district_use, param);
//    try {
//        for (auto & poly : district_use) {
//            for (auto & part : poly) {
//                int code = part->getProp<int>(3);
//                string name = part->getProp<string>(4);
//
//                float hue = ofMap(code, 1, 21, 0.0, 1.0, true);
//                ofFloatColor col = ofFloatColor::fromHsb(hue, 0.8, 1.0);
//                part->setColor(col.r, col.g, col.b, 1);
//                if (name.size()) {
//                    auto v = part->aabb.getCenter();
//                    addLabel(name, v.x, v.y);
//                }
//            }
//        }
//    } catch(const boost::bad_any_cast& e) {
//        cout << e.what() << endl;
//    }
}

void ofApp::loadAdminArea() {
    DrawParam param = {GL_LINE_STRIP, {0.0, 0.0, 0.0, 1}, 1, 1, 0, 0};
    
    loadShape("行政地域/行政地域", districts);
    param.mode = GL_LINE_STRIP;
    param.setColor(0, 0, 0, 1);
    param.setHatching(0, 0);
    setParam(districts, param);
//    try {
//        for (auto & poly : districts) {
//            string name = poly[0]->getProp<string>(2) + poly[0]->getProp<string>(3);
//            glm::vec2 center;
//            for (int i = 0; i < poly.size(); i++) {
//                if (poly[i]->clockwise()) poly[i]->setColor(0, 0, 0, 1);
//                else poly[i]->setColor(1, 0, 0, 1);
//                center += poly[i]->aabb.getCenter();
//            }
//            center /= poly.size();
//            addLabel(name, center.x, center.y);
//        }
//    } catch(const boost::bad_any_cast& e) {
//        cout << e.what() << endl;
//    }

    //    load("行政地域/景観重要建造物", keikan_kenzobutsu);
    //    setParam(keikan_kenzobutsu, GL_POINTS);
    //    loadShape("行政地域/景観地区", keikan_chiku);
    //    setParam(keikan_chiku, {GL_TRIANGLES, {1, 0, 0, 1}, 1, 1});
    //    load("行政地域/景観計画区域", keikan_keikaku_kuiki);
    //    setParam(keikan_keikaku_kuiki, GL_TRIANGLES);
    
    //    load("行政地域/伝統的建造物群保存地区", dento_hozon_chiku);
    //    setParam(dento_hozon_chiku, GL_LINE_STRIP);
    //    load("行政地域/歴史的風土保存区域", hudo_hozon_kuiki);
    //    setParam(dento_hozon_chiku, GL_LINE_STRIP);
}

void ofApp::loadDisaster() {
}

void ofApp::loadFacility() {
    DrawParam param = {GL_LINE_STRIP, {0.0, 0.0, 0.0, 1}, 1, 1, 0, 0};
    loadShape("施設/工業用地", factories);
    param.mode = GL_TRIANGLES;
    param.setColor(0.2, 0.2, 0.2, 1);
    param.setHatching(4, 4);
    setParam(factories, param);

    loadShape("施設/上水道関連施設", water_supply);
    param.mode = GL_TRIANGLES;
    param.setColor(0.2, 0.2, 0.2, 1);
    param.setHatching(4, 4);
    setParam(water_supply, param);
}

void ofApp::loadTourism() {
    //    loadShape("地域資源・観光/都道府県指定文化財データ", bunkazai);
    //    setParam(bunkazai, GL_POINTS);
    //    loadShape("地域資源・観光/世界自然遺産データ", shizen_isan);
    //    setParam(shizen_isan, GL_TRIANGLES);
    //    loadShape("地域資源・観光/世界文化遺産データ", bunka_isan);
    //    setParam(bunka_isan, GL_LINE_STRIP); //auto
    //    loadShape("地域資源・観光/観光資源データ", kanko_shigen);
    //    setParam(kanko_shigen, GL_LINE_STRIP); //auto
    //    loadShape("地域資源・観光/地域資源データ", tiiki_shigen);
    //    setParam(tiiki_shigen, GL_POINTS);
}

void ofApp::loadTraffic() {
    DrawParam param = {GL_LINE_STRIP, {0.0, 0.0, 0.0, 1}, 1, 1, 0, 0};
    loadShape("交通/高速道路時系列", highways);
    param.mode = GL_LINE_STRIP;
    param.setColor(1, 1, 0, 1);
    param.setHatching(0, 0);
    setParam(highways, param);
    
    
    loadShape("交通/鉄道データ", trains);
    param.mode = GL_LINE_STRIP;
    param.setColor(1, 0, 0, 1);
    param.setHatching(0, 0);
    setParam(trains, param);
    
    loadShape("交通/バスルート", buses);
    param.mode = GL_LINE_STRIP;
    param.setColor(0, 1, 1, 1);
    param.setHatching(0, 0);
    setParam(buses, param);
    
    loadShape("交通/緊急輸送道路", kinkyu_yuso);
    param.mode = GL_LINE_STRIP;
    param.setColor(1, 0, 1, 1);
    param.setHatching(0, 0);
    setParam(kinkyu_yuso, param);
}
