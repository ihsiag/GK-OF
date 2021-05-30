//
//  Utils.h
//  KRP_test
//
//  Created by rs on 2020/12/23.
//

#pragma once
#include "Constants.h"
#include "shapefil.h"
#include <iconv.h>
#include <errno.h>

#include <boost/any.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

#define ENC_SRC "SHIFT_JIS"
#define ENC_DST "UTF-8"
#define B_SIZE 1024 //Buffer size
#define DEG2RAD( a ) ( (a) * (PI/180.0) )

using BOOST_ESCAPED_LIST_SEP = boost::escaped_list_separator<char>;
using BOOST_TOKENIZER_ESCAPED_LIST = boost::tokenizer< boost::escaped_list_separator<char> >;

static inline void glBlendAlpha() { glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); }
static inline void glBlendAdd() { glBlendFunc(GL_SRC_ALPHA, GL_ONE); }
static inline void glBlendMulti() { glBlendFunc(GL_ZERO, GL_SRC_COLOR); }
static inline void glBlendScreen() { glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE); }
static inline void glBlendReverse() { glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO); }
static inline void glBlendReverse2() { glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO); }
static inline void glBlendSeparatedAlpha() { glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA,GL_ONE); }

static inline float cross(float x1, float y1, float x2, float y2) {
    return x1 * y2 - x2 * y1;
}

static inline bool ccw(float x1, float y1, float x2, float y2, float x3, float y3) {
    return cross(x2 - x1, y2 - y1, x3 - x2, y3 - y2) > 0;
}

static const GLuint toGLType(int nSHPType) {
    switch (nSHPType) {
        case SHPT_POINT:
        case SHPT_MULTIPOINT:
        case SHPT_POINTZ:
            return GL_POINTS;
        case SHPT_ARC:
        case SHPT_ARCZ:
            return GL_LINE_STRIP;
        case SHPT_POLYGON:
        case SHPT_POLYGONZ:
            return GL_TRIANGLES;
        default:
            cerr << SHPTypeName(nSHPType) << " is not supperted" << endl;
    }
    return GL_LINE_STRIP;
}

//referenced from https://www.kobiwa.jp/2017/03/22/post-286/
static void lonlat2xy(double Lon, double Lat, double Lon0, double Lat0, double * X, double * Y) {
    static const double daa = 6378137; //長半径
    static const double dF = 298.257222101; //逆扁平率
    static const double dM0 = 0.9999; //平面直角座標系のY軸上における縮尺係数(UTM座標系の場合→0.9996)

    double dn = 1. / (2. * dF - 1.);
    Lon = DEG2RAD(Lon);
    Lat = DEG2RAD(Lat);
    Lon0 = DEG2RAD(Lon0);
    Lat0 = DEG2RAD(Lat0);

    double dt = sinh(atanh(sin(Lat)) - (2 * sqrt(dn)) / (1 + dn) * atanh(2 * sqrt(dn) / (1 + dn) * sin(Lat)));
    double dtb = sqrt(1 + pow(dt, 2));
    double dLmc = cos(Lon - Lon0);
    double dLms = sin(Lon - Lon0);
    double dXi = atan(dt / dLmc);
    double dEt = atanh(dLms / dtb);

    //α1→0～α5→4
    double dal[6];
    dal[0] = 0;
    dal[1] = 1. / 2. * dn - 2. / 3. * pow(dn, 2) + 5. / 16. * pow(dn, 3) + 41. / 180. * pow(dn, 4) - 127. / 288. * pow(dn, 5);
    dal[2] = 13. / 48. * pow(dn, 2) - 3. / 5. * pow(dn, 3) + 557. / 1440. * pow(dn, 4) + 281. / 630. * pow(dn, 5);
    dal[3] = 61. / 240. * pow(dn, 3) - 103. / 140. * pow(dn, 4) + 15061. / 26880. * pow(dn, 5);
    dal[4] = 49561. / 161280. * pow(dn, 4) - 179. / 168. * pow(dn, 5);
    dal[5] = 34729. / 80640. * pow(dn, 5);
    double dSg = 0; double dTu = 0;
    for (int j = 1; j <= 5; j++) {
        dSg = dSg + 2 * j * dal[j] * cos(2 * j * dXi) * cosh(2 * j * dEt);
        dTu = dTu + 2 * j * dal[j] * sin(2 * j * dXi) * sinh(2 * j * dEt);
    }
    dSg = 1 + dSg;

    //A0-A5
    double dA[6];
    dA[0] = 1 + pow(dn, 2) / 4 + pow(dn, 4) / 64;
    dA[1] = -3. / 2. * (dn - pow(dn, 3) / 8 - pow(dn, 5) / 64.);
    dA[2] = 15. / 16. * (pow(dn, 2) - pow(dn, 4) / 4.);
    dA[3] = -35. / 48. * (pow(dn, 3) - 5. / 16. * pow(dn, 5));
    dA[4] = 315. / 512. * pow(dn, 4);
    dA[5] = -693. / 1280. * pow(dn, 5);
    double dAb = dM0 * daa / (1 + dn) * dA[0];
    double dSb = 0;
    for (int j = 1; j <= 5; j++) {
        dSb = dSb + dA[j] * sin(2 * j * Lat0);
    }
    dSb = dM0 * daa / (1 + dn) * (dA[0] * Lat0 + dSb);
    
    *Y = 0; *X = 0;
    for (int j = 1; j <= 5; j++) {
        *Y = *Y + dal[j] * sin(2 * j * dXi) * cosh(2 * j * dEt);
        *X = *X + dal[j] * cos(2 * j * dXi) * sinh(2 * j * dEt);
    }
    *Y = dAb * (dXi + *Y) - dSb;
    *X = dAb * (dEt + *X);
}

//SHIFT_JIS to UTF-8
static string encode(const char * val) {
    iconv_t ic;
    
    char s_src[B_SIZE], s_dst[B_SIZE];
    size_t n_src, n_dst;
    char *p_src, *p_dst;
    
    strcpy(s_src, val);
    p_src = s_src;
    p_dst = s_dst;
    n_src = strlen(s_src);
    n_dst = B_SIZE - 1;
    
    errno = 0;
    ic = iconv_open(ENC_DST, ENC_SRC);
    
    int cnt = 0;
    while (0 < n_src) {
        iconv(ic, &p_src, &n_src, &p_dst, &n_dst);
        if (cnt++ > B_SIZE) break;
    }
    *p_dst = '\0';
    
    iconv_close(ic);
    
    if(errno) return "";
    return s_dst;
}

static void loadCsv(const string & filepath, vector<vector<string>> & data) {
    std::ifstream ifs;
    try {
        ifs.open(ofToDataPath(filepath).c_str());
        std::string line;
        while (getline(ifs, line) ) {
            BOOST_TOKENIZER_ESCAPED_LIST tokens(line);
            vector<string > row;
            for (const auto & token : tokens) {
                row.push_back(token);
            }
            data.push_back(row);
        }
        ifs.close();
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}
    
template <typename T, typename F>
static void loadSHP(const string & filepath, vector<vector<T>> & polygons, F functor) {
    try {
        SHPHandle hSHP = SHPOpen(filepath.c_str(), "rb");
        if (hSHP == nullptr) {
            throw string("cannot open " + filepath);
        }
        
        int nEntities;
        int nShapeType;
        double adfMinBound[4];
        double adfMaxBound[4];
        SHPGetInfo(hSHP, &nEntities, &nShapeType, adfMinBound, adfMaxBound);
        
        for (int i = 0; i < nEntities; i++) {
            SHPObject * psShape = SHPReadObject(hSHP, i);

            vector<T> cur_polygons;
            functor(psShape, cur_polygons);
            //std::copy(cur_polygons.begin(), cur_polygons.end(), std::back_inserter(polygons));
            polygons.push_back(cur_polygons);
            
            SHPDestroyObject(psShape);
        }
        
        SHPClose(hSHP);
    } catch (const string & e) {
        throw e;
    } catch (...) {
        throw std::string("Other exception");
    }
}

static void loadDBF(const string & filepath, vector<vector<boost::any>> & records) {
    try {
        DBFHandle hDBF = DBFOpen(filepath.c_str(), "rb");
        if (hDBF == nullptr) {
            throw string("cannot open " + filepath);
        }
        
        int nField = DBFGetFieldCount(hDBF);
        int nRecord = DBFGetRecordCount(hDBF);
                
        iconv_t icd;
        icd = iconv_open(ENC_DST, ENC_SRC);
        char s_src[B_SIZE], s_dst[B_SIZE];
        char *p_src, *p_dst;
        size_t n_src, n_dst;
        
        DBFFieldType eType;
        char szTitle[32];
        int nWidth, nDecimals;
        for (int i = 0; i < nRecord; i++) {
            vector<boost::any> record;
            for (int j = 0; j < nField; j++) {
                eType = DBFGetFieldInfo(hDBF, j, szTitle, &nWidth, &nDecimals);
                //printf("Field %d: Title = %s, Width = %d, Decimals = %d\n", i, szTitle, nWidth, nDecimals );
                switch (eType) {
                    case FTString:
                    {
                        const char * v = DBFReadStringAttribute(hDBF, i, j);
                        string val = encode(v);
//                        cout << "FTString: " << val << endl;
                        record.push_back(val);
                        break;
                    }
                    case FTInteger:
                    {
                        int val = DBFReadIntegerAttribute( hDBF, i, j );
//                        cout << "FTInteger: " << val << endl;
                        record.push_back(val);
                        break;
                    }
                    case FTDouble:
                    {
                        double val = DBFReadDoubleAttribute(hDBF, i, j);
//                        cout << "FTDouble: " << val << endl;
                        record.push_back(val);
                        break;
                    }
                    case FTLogical:
                    {
                        const char *val = DBFReadLogicalAttribute(hDBF, i, j);
//                        cout << "FTLogical: " << val << endl;
                        record.push_back(val);
                        break;
                    }
                    case FTInvalid:
//                        record.push_back("?");
                        break;
                    default:
//                        cout << "mmm" << endl;
                        break;
                }
            }
            records.push_back(record);
        }
        iconv_close(icd);
        DBFClose(hDBF);
    } catch (const string & e) {
        throw e;
    } catch (char * e) { //iconv exception
        throw e;
    } catch (...) {
        throw std::string("Other exception");
    }
}
