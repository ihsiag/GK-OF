#pragma once

#include "ofMain.h"
#include "ofApp.h"

#define M_PI 3.141592

//====================================================================================================================================
//====================================================================================================================================
//====================================================================================================================================
class Class_DelaPoint {
private:
	glm::vec2 vel;
	double speed;
	double circleR;
	double edgeR;
public:
	glm::vec2 pos;
	Class_DelaPoint() {};
	~Class_DelaPoint() {};

	void setup(double _edgeR, double _speed, double _size) {
		double r = ofRandom(0, _edgeR);
		double theta = ofRandom(0, 2 * M_PI);
		double rad = -theta + M_PI / 2 - ofRandom(-70, 70) / 180 * M_PI;

		pos = glm::vec2(ofGetWidth() / 2 + r * cos(theta), ofGetHeight() / 2 + r * sin(theta));
		speed = ofRandom(_speed / 5, _speed);	
		vel = glm::vec2(speed * cos(rad), speed * sin(rad));

		circleR = _size;
		edgeR = _edgeR;
	};
	
	void run() {
		update();
		display();
	};
	
	void update() {
		pos += vel;
		glm::vec2 _pos = pos - glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2);
		if (ofVec2f(_pos).length() > edgeR){
			vel = speed * glm::rotate(glm::normalize(_pos),ofRandom(-70, 70));
			//glm::rotate(vel, ofRandom(-70, 70));
			//vel = speed * ofVec2f(_pos).getNormalized().rotate(ofRandom(-70, 70));
		}
	};

	void display() {
		ofFill();
		glColor3f(0, 1, 0);
		ofDrawCircle(pos, circleR);	
	};

	void setEdgeR(double _edgeR) {
		edgeR = _edgeR;
	}
};


//====================================================================================================================================
//====================================================================================================================================
//====================================================================================================================================
class Class_DelaCircle{
private:
	float triR;

public:
	vector<Class_DelaPoint> triVertices;
	glm::vec2 triCenter;
	int shareside[3]; //01:0 12:1 20:2
	int sharepoint[3];

	Class_DelaCircle() {};
	~Class_DelaCircle() {};
	
	void setup(vector<Class_DelaPoint> _triVertices) {
		//free
		vector<Class_DelaPoint>().swap(triVertices);
		//外接円のパラメータの計算(３つの点から中心を求める)
		triVertices = _triVertices;
		double c = 2 * ((triVertices[1].pos.x - triVertices[0].pos.x) * (triVertices[2].pos.y - triVertices[0].pos.y) - (triVertices[1].pos.y - triVertices[0].pos.y) * (triVertices[2].pos.x - triVertices[0].pos.x));
		double x1, x2, y1, y2, xy1, xy2;
		x1 = (triVertices[2].pos.y - triVertices[0].pos.y);
		x2 = (triVertices[0].pos.y - triVertices[1].pos.y);
		y1 = (triVertices[0].pos.x - triVertices[2].pos.x);
		y2 = (triVertices[1].pos.x - triVertices[0].pos.x);
		xy1 = (pow(triVertices[1].pos.x, 2) - pow(triVertices[0].pos.x, 2) + pow(triVertices[1].pos.y, 2) - pow(triVertices[0].pos.y, 2));
		xy2 = (pow(triVertices[2].pos.x, 2) - pow(triVertices[0].pos.x, 2) + pow(triVertices[2].pos.y, 2) - pow(triVertices[0].pos.y, 2));
		
		triCenter = glm::vec2((x1 * xy1 + x2 * xy2) / c, (y1 * xy1 + y2 * xy2) / c);
		triR = glm::distance(triCenter,triVertices[0].pos);

		shareside[0] = 0;
		shareside[1] = 0;
		shareside[2] = 0;
	};
	void run() {
		update();
		display();
	};
	void update() {
	};
	void display() {
		drawTriangle();
		drawCircle();
		drawCenter();
	};

	void drawCenter() {
		ofFill();
		glColor3f(1, 0, 1);
		ofDrawCircle(triCenter, 6);
	};
	
	void drawCircle() {
		glLineWidth(0.3);
		ofNoFill();
		glColor3f(0, 0, 0);
		ofDrawCircle(triCenter, triR);
	};
	
	void drawTriangle() {
		ofMesh mesh;
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		mesh.addVertex(ofPoint(triVertices[0].pos));
		mesh.addVertex(ofPoint(triVertices[1].pos));
		mesh.addVertex(ofPoint(triVertices[2].pos));
		//mesh.addVertex(ofPoint(triVertices[0].pos)); //2
		
		glColor3f(1, 1, 1);
		//mesh.draw();
		glColor3f(1, 0, 0);
		glLineWidth(0.2);
		mesh.drawWireframe();
	};
	
	bool check(vector<Class_DelaPoint> _points) {
		bool result = false;
		for (int i = 0; i < _points.size(); i++){
			float length = glm::distance(triCenter,_points[i].pos);
			
			if (length < triR-0.01){
				result = true;
			}
		}
		return result;
	};
};

//====================================================================================================================================
//====================================================================================================================================
//====================================================================================================================================
class Class_DelaVoronoi {
private:
	double globalR;
	double pointR;
	glm::vec2 point[2];
public:
	Class_DelaVoronoi() {};
	~Class_DelaVoronoi() {};

	void setup(double& _globalR, double& _pointR, glm::vec2& _start, glm::vec2& _end) {
		globalR = _globalR;
		pointR = _pointR;
		point[0] = _start;
		point[1] = _end;
	};
	void run() {
		update();
		display();
	};
	void update() {};
	void display() {
		glLineWidth(1);
		double Ax, Ay, Bx, By;
		glm::vec2 center(ofGetWidth() / 2, ofGetHeight() / 2);
		ofFill();
		if (glm::distance(point[0],center) - globalR < 0 && glm::distance(point[1],center) - globalR < 0) {
			glColor3f(0, 0, 1);
			glBegin(GL_LINES);
			glVertex2f(point[0].x, point[0].y);
			glVertex2f(point[1].x, point[1].y);
			glEnd();
		} else { //if((point[0] - center).length() - globalRadius<0 || (point[1] - center).length() - globalRadius<0)
			Ax = point[1].x - ofGetWidth() / 2;
			Ay = point[1].y - ofGetHeight() / 2;
			Bx = point[0].x - point[1].x;
			By = point[0].y - point[1].y;

			double t = 0;
			double t1, t2;
			t1 = (-(Ax * Bx + Ay * By) + sqrt(pow((Ax * Bx + Ay * By), 2) - (Bx * Bx + By * By) * (Ax * Ax + Ay * Ay - globalR * globalR))) / (Bx * Bx + By * By);
			t2 = (-(Ax * Bx + Ay * By) - sqrt(pow((Ax * Bx + Ay * By), 2) - (Bx * Bx + By * By) * (Ax * Ax + Ay * Ay - globalR * globalR))) / (Bx * Bx + By * By);
			if (t1 > 0 && t1 < 1)
			{
				t = t1;
			}
			else if (t2 > 0 && t2 < 1)
			{
				t = t2;
			}

			glm::vec2 start, end;
			if ((glm::distance(point[0],center) - globalR) > 0)
			{
				start = point[1];
			}
			else
			{
				start = point[0];
			}
			end = point[1] + t * (point[0] - point[1]);

			ofSetColor(0, 0, 255);
			ofDrawLine(start, end);

			ofSetColor(0, 255, 0);
			ofDrawCircle(end, pointR);
		}
	};
};

//====================================================================================================================================
//====================================================================================================================================
//====================================================================================================================================
class Class_DelaTriangle {
public:
	Class_DelaTriangle() {};
	~Class_DelaTriangle() {};
	void setup() {
	};
	void run() {
		update();
		display();
	};
	void update() {
	};
	void display() {
	};
};


//====================================================================================================================================
//====================================================================================================================================
//====================================================================================================================================
#pragma mark Class_Delaunay
class Class_Delaunay {
public:

	bool bStageEnd;
	vector<glm::vec3>* vertexArr;

	vector<Class_DelaPoint> points;
	vector<Class_DelaCircle> triCircles;
	vector<Class_DelaVoronoi> voronois;

	double edgeR;
	int GenNum;
	int POINT_NUM = 10;
	double initialEdgeR = 230;
	double POINT_RADIUS = 2;
	double POINT_SPEED = 5;

	Class_Delaunay() {}
	~Class_Delaunay() {}

	void setup(vector<glm::vec3>* _vertexArr) {
		ofSetCircleResolution(36);
		vertexArr = _vertexArr;
		edgeR = initialEdgeR;
		//free
		vector<Class_DelaPoint>().swap(points);
		vector<Class_DelaCircle>().swap(triCircles);
		vector<Class_DelaVoronoi>().swap(voronois);

		//create & init points
		for (int i = 0; i < POINT_NUM; i++) {
			Class_DelaPoint _delaPoint;
			double rad = ofRandom(0, 360) / 180 * M_PI;
			_delaPoint.setup(initialEdgeR, POINT_SPEED, POINT_RADIUS);
			points.push_back(_delaPoint);
		}
		/*
		for (int i = 0; i < vertexArr->size(); i++) {
			Class_DelaPoint _delaPoint;
			double rad = ofRandom(0, 360) / 180 * M_PI;
			_delaPoint.setup(initialEdgeR, vertexArr->at(i));
			points.push_back(_delaPoint);
		}*/
	}
	bool run() {
		update();
		display();
		return bStageEnd;
	}

	void update() {
		//point moving
		edgeR = initialEdgeR + initialEdgeR / 4 * sin(ofGetElapsedTimef() / 2);
		for (int i = 0; i < points.size(); i++){
			points[i].setEdgeR(edgeR);
			points[i].update();
		}

		//init triCircles & voronois
		if (points.size() > 2){
			triCircles = getTriCircles();
			/*
			voronois = getVoronois();
			vector<Class_DelaVoronoi> _additionalVoronoi = getOutlierVoronois();
			voronois.insert(voronois.end(), _additionalVoronoi.begin(), _additionalVoronoi.end());
			*/
		}
	}

	void display() {
		glClearColor(1, 1, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		//外周円の描画
		glColor3f(0, 0, 0);
		ofNoFill();
		glLineWidth(1);
		ofDrawCircle(glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2), edgeR);

		//ボロノイの描画
		
		for (int i = 0; i < voronois.size(); i++){
			//voronois[i].display();
		}
		

		//ドロネーの描画
		for (int i = 0; i < triCircles.size(); i++)
		{
			triCircles[i].drawTriangle();
			//triCircles[i].drawCircle();
			//triCircles[i].drawCenter();
		}

		//動きまわる赤色の点の描画
		for (int i = 0; i < points.size(); i++) {
			//points[i].display();
		}

	};

	vector<Class_DelaCircle> getTriCircles() {
		//外接円の中に他のpointが存在しないpointの組み合わせを全探索
		vector<Class_DelaCircle> _triCircles;
		for (int i = 0; i < points.size() - 2; i++){
			for (int j = i + 1; j < points.size() - 1; j++){
				for (int k = j + 1; k < points.size(); k++){
					vector<Class_DelaPoint> _triVertices;
					_triVertices.push_back(points[i]);
					_triVertices.push_back(points[j]);
					_triVertices.push_back(points[k]);

					Class_DelaCircle _triCircle;
					_triCircle.setup(_triVertices);
					//外接円内に他のpointがないか確認
					if (!_triCircle.check(points)){
						_triCircles.push_back(_triCircle);
					}
				}
			}
		}
		return _triCircles;
	};
	vector<Class_DelaVoronoi> getVoronois() {
		vector<Class_DelaVoronoi> _voronois;
		for (int i = 0; i < triCircles.size() - 1; i++) {
			for (int j = i + 1; j < triCircles.size(); j++) {
				int sharepoint = 0;
				for (int k = 0; k < 3; k++) {
					triCircles[i].sharepoint[k] = 0;
					triCircles[j].sharepoint[k] = 0;
				}

				//ドロネーで分割した三角形の中で頂点を共有しているものの洗い出し
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						if (ofVec2f(triCircles[i].triVertices[k].pos).match(ofVec2f(triCircles[j].triVertices[l].pos))) {
							triCircles[i].sharepoint[k]++;
							triCircles[j].sharepoint[l]++;
							sharepoint++;
						}
					}
				}

				//頂点を２つ共有している場合ひとつの辺を共有していることになる
				//辺を共有している場合はボロノイの線で繋がれる
				if (sharepoint == 2) {
					if (triCircles[i].sharepoint[0] > 0) {
						if (triCircles[i].sharepoint[1] > 0) {
							triCircles[i].shareside[0]++;
						}
						if (triCircles[i].sharepoint[2] > 0) {
							triCircles[i].shareside[2]++;
						}
					}
					else {
						if (triCircles[i].sharepoint[1] > 0 && triCircles[i].sharepoint[2] > 0) {
							triCircles[i].shareside[1]++;
						}
					}
					if (triCircles[j].sharepoint[0] > 0) {
						if (triCircles[j].sharepoint[1] > 0) {
							triCircles[j].shareside[0]++;
						}
						if (triCircles[j].sharepoint[2] > 0) {
							triCircles[j].shareside[2]++;
						}
					}
					else {
						if (triCircles[j].sharepoint[1] > 0 && triCircles[j].sharepoint[2] > 0) {
							triCircles[j].shareside[1]++;
						}
					}

					Class_DelaVoronoi _voronoi;
					_voronoi.setup(edgeR, POINT_RADIUS, triCircles[i].triCenter, triCircles[j].triCenter);
					_voronois.push_back(_voronoi);
				}
			}
		}
		return _voronois;
	};
	vector<Class_DelaVoronoi> getOutlierVoronois() {
		vector<Class_DelaVoronoi> _voronois;
		for (int i = 0; i < triCircles.size(); i++)
		{
			//移動点の外枠の探索
			int share = 0;
			for (int j = 0; j < 3; j++)
			{
				if (triCircles[i].shareside[j] > 0)
				{
					share++;
				}
			}
			if (share < 3)
			{
				for (int j = 0; j < 3; j++)
				{
					if (triCircles[i].shareside[j] == 0)
					{
						glm::vec2 p1, p2;
						p1 = triCircles[i].triCenter;
						double dig1 = ofVec2f(triCircles[i].triCenter - triCircles[i].triVertices[0].pos).angleRad(ofVec2f(triCircles[i].triVertices[1].pos - triCircles[i].triVertices[0].pos));
						double dig2 = ofVec2f(triCircles[i].triCenter - triCircles[i].triVertices[1].pos).angleRad(ofVec2f(triCircles[i].triVertices[2].pos - triCircles[i].triVertices[1].pos));
						double dig3 = ofVec2f(triCircles[i].triCenter - triCircles[i].triVertices[2].pos).angleRad(ofVec2f(triCircles[i].triVertices[0].pos - triCircles[i].triVertices[2].pos));

						glm::vec2 direct = (triCircles[i].triVertices[j].pos + triCircles[i].triVertices[(j + 1) % 3].pos) / 2 - triCircles[i].triCenter;
						direct = glm::normalize(direct);

						if (j == 0)
						{
							if ((dig1 < 0 && dig2 > 0 && dig3 > 0) || (dig1 > 0 && dig2 < 0 && dig3 < 0))
							{
								p2 = triCircles[i].triCenter - direct * 1000;
							}
							else
							{
								p2 = triCircles[i].triCenter + direct * 1000;
							}
						}
						else if (j == 1)
						{
							if ((dig1 > 0 && dig2 < 0 && dig3 >0) || (dig1 < 0 && dig2 > 0 && dig3 < 0))
							{
								p2 = triCircles[i].triCenter - direct * 1000;
							}
							else
							{
								p2 = triCircles[i].triCenter + direct * 1000;
							}
						}
						else if (j == 2)
						{
							if ((dig1 > 0 && dig2 > 0 && dig3 < 0) || (dig1 < 0 && dig2 < 0 && dig3 > 0))
							{
								p2 = triCircles[i].triCenter - direct * 10000;
							}
							else
							{
								p2 = triCircles[i].triCenter + direct * 10000;
							}
						}

						Class_DelaVoronoi _voronoi;
						_voronoi.setup(edgeR, POINT_RADIUS, p1, p2);
						_voronois.push_back(_voronoi);
					}
				}
			}
		}
		return _voronois;
	};
};