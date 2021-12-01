#pragma once

#ifndef GK_DELAUNAY3D_H  
#define GK_DELAUNAY3D_H  

#include "ofMain.h"
#include "ofxGKUtils.h"


namespace GKDelaunay{

    class PtrComp {
    public:
        template <class Type>
        bool operator()(const Type* a, const Type* b) const
        {
            return *a < *b;
        }
    };

    struct Circle {
        glm::vec3 center;  // 中心座標  
        double radius;  // 半径  
    };


    class Triangle {
    public:
        const static size_t NUM_VERTICES = 3;
        const GKPoint vertices[NUM_VERTICES];  // 頂点座標  // <-おそらくこれをGKPlaneに帰る
    };


    class Tetrahedron {
    public:
        const static size_t NUM_VERTICES = 4;
        const GKPoint vertices[NUM_VERTICES];

        // ======================================    
        // 他の四面体と共有点を持つか    
        // ======================================   
        bool hasCommonPoints(const Tetrahedron& _tet) const {
            for (int i = 0; i < NUM_VERTICES; ++i)
                for (int j = 0; j < NUM_VERTICES; ++j)
                    if (vertices[i].pos == _tet.vertices[j].pos) return true;
            return false;
        }
    };

    class Delaunay3d{
    public:
        static void getDelaunayTriangles(vector<GKPlane>& _gkPlanes, set<Triangle> *_triangles) {
            set<Tetrahedron> tetras;
            glm::vec3 p0, p1, p2, p3;
            Tetrahedron hugeTetrahedron = { p0, p1, p2, p3 };
            {              
                double maxX, maxY, maxZ;
                double minX, minY, minZ;
                maxX = maxY = maxZ = DBL_MIN;
                minX = minY = minZ = DBL_MAX;
                for (auto& gp : _gkPlanes) {
                    if (maxX < gp.centroid.x)maxX = gp.centroid.x;
                    if (gp.centroid.x < minX)minX = gp.centroid.x;
                    if (maxY < gp.centroid.y)maxY = gp.centroid.y;
                    if (gp.centroid.y < minY)minY = gp.centroid.y;
                    if (maxZ < gp.centroid.z)maxZ = gp.centroid.z;
                    if (gp.centroid.z < minZ)minZ = gp.centroid.z;
                }
                glm::vec3 center = glm::vec3(0.5 * (maxX - minX), 0.5 * (maxY - minY), 0.5 * (maxZ - minZ));
                double radius = sqrt(pow((center.x - minX), 2.) + pow((center.y - minY), 2.) + pow((center.z - minZ), 2.)) + 0.1;

                // 4つの頂点
                p0 = glm::vec3(center.x, center.y + 3. * radius, center.z);
                p1 = glm::vec3(center.x - 2.0 * sqrt(2.0) * radius, center.y - radius, center.z);
                p2 = glm::vec3(center.x + sqrt(2.0) * radius, center.y - radius, center.z + sqrt(6.0) * radius);
                p3 = glm::vec3(center.x + sqrt(2.0) * radius, center.y - radius, center.z - sqrt(6.0) * radius);              
            }
            tetras.insert(hugeTetrahedron);
             
            for (auto gpItr = _gkPlanes.begin(); gpItr != _gkPlanes.end();){ // 点を逐次追加...

                GKPoint gp = GKPoint(gpItr->centroid,gpItr->state);
                map<Tetrahedron,bool> tmpMapForCheck; // 追加候補の四面体を保持する一時マップ

                for (auto tetItr = tetras.begin(); tetItr != tetras.end();) { // 四面体セットから要素を取りだして…  
                      
                    Tetrahedron tet = *tetItr; 
                    Circle c = getCircumcircle(tet);
                    double dist = glm::distance(c.center, gp.pos);

                    //内部にあった場合四面体を再分割し一時保持マップに追加し自身は消える
                    if (dist < c.radius) {
                        Tetrahedron t0 = { gp, tet.vertices[0], tet.vertices[1], tet.vertices[2] };
                        addElementToRedundanciesMap(&tmpMapForCheck, t0);

                        Tetrahedron t1 = { gp, tet.vertices[0], tet.vertices[2], tet.vertices[3] };
                        addElementToRedundanciesMap(&tmpMapForCheck, t1);

                        Tetrahedron t2 = { gp, tet.vertices[0], tet.vertices[3], tet.vertices[1] };
                        addElementToRedundanciesMap(&tmpMapForCheck, t2);

                        Tetrahedron t3 = { gp, tet.vertices[1], tet.vertices[2], tet.vertices[3] };
                        addElementToRedundanciesMap(&tmpMapForCheck, t3);

                        tetras.erase(tetItr);
                    }
                    else ++tetItr;
                }

                //一時保持マップで重複チェックし、問題のないものだけ四面体セットに追加
                for (auto mapItr = tmpMapForCheck.begin(); mapItr != tmpMapForCheck.end(); ++mapItr) {
                    if (mapItr->second) tetras.insert(mapItr->first);
                }
            }
   
            // 最後に、外部三角形の頂点を削除       
            for (auto tetItr = tetras.begin(); tetItr != tetras.end(); ) {
                if (hugeTetrahedron.hasCommonPoints(*tetItr))
                    tetras.erase(tetItr++);
                else ++tetItr;
            }

            // そして、伝説へ…  (triangleに返していく)
            for (auto tetItr = tetras.begin(); tetItr != tetras.end(); ++tetItr) {
                Tetrahedron tetra = *tetItr;
                Triangle t0 = { tetra.vertices[0], tetra.vertices[1], tetra.vertices[2] };
                _triangles->insert(t0);
                Triangle t1 = { tetra.vertices[0], tetra.vertices[2], tetra.vertices[3] };
                _triangles->insert(t1);
                Triangle t2 = { tetra.vertices[0], tetra.vertices[3], tetra.vertices[1] };
                _triangles->insert(t2);
                Triangle t3 = { tetra.vertices[1], tetra.vertices[2], tetra.vertices[3] };
                _triangles->insert(t3);
            }
        };
    private:
        // ======================================    
        // LU分解による三元一次連立方程式の解法  
        // ======================================  
        static double lu(double a[3][3], int ip[3])
        {
            const int n = 3;
            double weight[n];

            for (int k = 0; k < n; ++k)
            {
                ip[k] = k;
                double u = 0;
                for (int j = 0; j < n; ++j)
                {
                    double t = fabs(a[k][j]);
                    if (t > u) u = t;
                }
                if (u == 0) return 0;
                weight[k] = 1 / u;
            }
            double det = 1;
            for (int k = 0; k < n; ++k)
            {
                double u = -1;
                int m = 0;
                for (int i = k; i < n; ++i)
                {
                    int ii = ip[i];
                    double t = fabs(a[ii][k]) * weight[ii];
                    if (t > u)
                    {
                        u = t;
                        m = i;
                    }
                }
                int ik = ip[m];
                if (m != k)
                {
                    ip[m] = ip[k]; ip[k] = ik;
                    det = -det;
                }
                u = a[ik][k]; det *= u;
                if (u == 0) return 0;
                for (int i = k + 1; i < n; ++i)
                {
                    int ii = ip[i];
                    double t = (a[ii][k] /= u);
                    for (int j = k + 1; j < n; ++j)
                        a[ii][j] -= t * a[ik][j];
                }
            }
            return det;
        }
        static void solve(double a[3][3], double b[3], int ip[3], double x[3])
        {
            const int n = 3;

            for (int i = 0; i < n; ++i)
            {
                int ii = ip[i];
                double t = b[ii];
                for (int j = 0; j < i; ++j)
                    t -= a[ii][j] * x[j];
                x[i] = t;
            }

            for (int i = n - 1; i >= 0; --i)
            {
                double t = x[i];
                int ii = ip[i];
                for (int j = i + 1; j < n; ++j)
                    t -= a[ii][j] * x[j];
                x[i] = t / a[ii][i];
            }
        }
        static double gauss(double a[3][3], double b[3], double x[3])
        {
            const int n = 3;
            int ip[n];
            double det = lu(a, ip);

            if (det != 0) solve(a, b, ip, x);
            return det;
        }

        // ======================================    
        // 与えられた四面体の外接球を求める  
        // ======================================  
        static Circle getCircumcircle(const Tetrahedron& _tetra) {
            const glm::vec3 p0 = _tetra.vertices[0].pos;
            const glm::vec3 p1 = _tetra.vertices[1].pos;
            const glm::vec3 p2 = _tetra.vertices[2].pos;
            const glm::vec3 p3 = _tetra.vertices[3].pos;
            Circle _circle;

            double A[3][3] = {
              {p1.x - p0.x, p1.y - p0.y, p1.z - p0.z},
              {p2.x - p0.x, p2.y - p0.y, p2.z - p0.z},
              {p3.x - p0.x, p3.y - p0.y, p3.z - p0.z}
            };

            double b[3] = {
              0.5 * (p1.x * p1.x - p0.x * p0.x + p1.y * p1.y - p0.y * p0.y + p1.z * p1.z - p0.z * p0.z),
              0.5 * (p2.x * p2.x - p0.x * p0.x + p2.y * p2.y - p0.y * p0.y + p2.z * p2.z - p0.z * p0.z),
              0.5 * (p3.x * p3.x - p0.x * p0.x + p3.y * p3.y - p0.y * p0.y + p3.z * p3.z - p0.z * p0.z)
            };

            double x[3] = { 0.0, 0.0, 0.0 };

            if (gauss(A, b, x) == 0)
            {
                _circle.center = glm::vec3(0);
                _circle.radius = -1;
            }
            else
            {
                _circle.center = glm::vec3(x[0], x[1], x[2]);
                _circle.radius = sqrt(pow((x[0] - p0.x), 2.) + pow((x[1] - p0.y), 2.) + pow((x[2] - p0.z), 2.)) + 0.1;
            }
            return _circle;
        }

        // ======================================    
        // 四面体の重複管理  
        // ======================================  
        static inline void addElementToRedundanciesMap(map<Tetrahedron, bool>* _tmpMapForCheck, const Tetrahedron& _tet) {
            auto mapItr = _tmpMapForCheck->find(_tet);
            if (mapItr != _tmpMapForCheck->end() && mapItr->second)
            {
                // 値を (t, true) から (t, false) に置換    
                _tmpMapForCheck->erase(mapItr);
                _tmpMapForCheck->insert(map<Tetrahedron, bool>::value_type(_tet, false));
            }
            else
                _tmpMapForCheck->insert(map<Tetrahedron, bool>::value_type(_tet, true));
        }
    };
}
#endif  
