#pragma once

#include "ofMain.h"
#include "ofApp.h"

#define M_PI 3.141592

class Class_DelaPoint {
private:
	glm::vec2 vel;
	double speed;
	double circleR;
	double globalR;
public:
	glm::vec2 pos;
	Class_DelaPoint() {};
	~Class_DelaPoint() {};

	void setup(double& _globalR, double& _speed, double& _size) {
		double r = ofRandom(0, _globalR);
		double theta = ofRandom(0, 2 * M_PI);
		double rad = -theta + M_PI / 2 - ofRandom(-70, 70) / 180 * M_PI;

		pos = glm::vec2(ofGetWidth() / 2 + r * cos(theta), ofGetHeight() / 2 + r * sin(theta));
		speed = ofRandom(_speed / 5, _speed);	
		vel = glm::vec2(speed * sin(rad), speed * cos(rad));

		circleR = _size;
		globalR = _globalR;
	};
	
	void run() {
		update();
		display();
	};
	
	void update() {
		pos -= vel;
		glm::vec2 _pos = pos - glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2);
		if (_pos.length() > globalR)
		{
			vel = speed * glm::rotate(glm::normalize(_pos),ofRandom(-70, 70));
		}
	};

	void display() {
		ofFill();
		glColor3f(1, 1, 0);
		ofDrawCircle(pos, circleR);	
	};

	void setGlobalR(double& _globalR) {
		globalR = _globalR;
	}
};

class Class_DelaCircle{
private:
	float r;

public:
	vector<Class_DelaPoint> elements;
	glm::vec2 center;
	int shareside[3]; //01:0 12:1 20:2
	int sharepoint[3];

	Class_DelaCircle() {};
	~Class_DelaCircle() {};
	
	void setup(vector<Class_DelaPoint> _elements) {
		//free
		vector<Class_DelaPoint>().swap(elements);
		//外接円のパラメータの計算(３つの点から中心を求める)
		elements = _elements;
		double c = 2 * ((elements[1].pos.x - elements[0].pos.x) * (elements[2].pos.y - elements[0].pos.y) - (elements[1].pos.y - elements[0].pos.y) * (elements[2].pos.x - elements[0].pos.x));
		double x1, x2, y1, y2, xy1, xy2;
		x1 = (elements[2].pos.y - elements[0].pos.y);
		x2 = (elements[0].pos.y - elements[1].pos.y);
		y1 = (elements[0].pos.x - elements[2].pos.x);
		y2 = (elements[1].pos.x - elements[0].pos.x);
		xy1 = (pow(elements[1].pos.x, 2) - pow(elements[0].pos.x, 2) + pow(elements[1].pos.y, 2) - pow(elements[0].pos.y, 2));
		xy2 = (pow(elements[2].pos.x, 2) - pow(elements[0].pos.x, 2) + pow(elements[2].pos.y, 2) - pow(elements[0].pos.y, 2));
		
		center.x = (x1 * xy1 + x2 * xy2) / c;
		center.y = (y1 * xy1 + y2 * xy2) / c;
		r = glm::vec2(center - elements[0].pos).length();

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
		ofDrawCircle(center, 6);
	};
	
	void drawCircle() {
		glLineWidth(0.3);
		ofNoFill();
		glColor3f(0, 0, 0);
		ofDrawCircle(center, r);
	};
	
	void drawTriangle() {
		ofMesh mesh;
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		mesh.addVertex(ofPoint(elements[0].pos));
		mesh.addVertex(ofPoint(elements[1].pos));
		mesh.addVertex(ofPoint(elements[2].pos));
		mesh.addVertex(ofPoint(elements[0].pos)); //2
		
		glColor3f(1, 1, 1);
		mesh.draw();
		glColor3f(1, 0, 0);
		glLineWidth(0.2);
		mesh.drawWireframe();
	};
	
	bool check(vector<Class_DelaPoint> _points) {
		bool result = true;
		for (int i = 0; i < _points.size(); i++){
			float length = glm::vec2(center - _points[i].pos).length();
			if (length < r - 0.01){
				result = false;
			}
		}
		return result;
	};
};

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
		if ((point[0] - center).length() - globalR < 0 && (point[1] - center).length() - globalR < 0) {
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
			if (((point[0] - center).length() - globalR) > 0)
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

#pragma mark Class_Delaunay
class Class_Delaunay {
public:

	bool bStageEnd;
	vector<glm::vec3>* vertexArr;

	vector<Class_DelaPoint> points;
	vector<Class_DelaCircle> circles;
	vector<Class_DelaVoronoi> voronois;

	double dynamic_GLOBAL_RADIUS;
	int GenNum;
	int POINT_NUM = 10;
	double GLOBAL_RADIUS = 230;
	double POINT_RADIUS = 5;
	double POINT_SPEED = 10;

	Class_Delaunay() {}
	~Class_Delaunay() {}

	void setup(vector<glm::vec3>* _vertexArr) {
		vertexArr = _vertexArr;
		
		//free
		vector<Class_DelaPoint>().swap(points);
		vector<Class_DelaCircle>().swap(circles);
		vector<Class_DelaVoronoi>().swap(voronois);


		for (int i = 0; i < POINT_NUM; i++) {
			Class_DelaPoint _delaPoint;
			double rad = ofRandom(0, 360) / 180 * M_PI;
			_delaPoint.setup(GLOBAL_RADIUS, POINT_SPEED, POINT_RADIUS);
			points.push_back(_delaPoint);
		}
	}
	bool run() {
		update();
		display();
		return bStageEnd;
	}

	void update() {
		dynamic_GLOBAL_RADIUS = GLOBAL_RADIUS + GLOBAL_RADIUS / 4 * sin(ofGetElapsedTimef() / 2);
		for (int i = 0; i < points.size(); i++)
		{
			points[i].setGlobalR(dynamic_GLOBAL_RADIUS);
			points[i].update();
		}
		if (points.size() > 2)
		{
			circles = getCircles();
			voronois = getVoronois();
			vector<Class_DelaVoronoi> _additionalVoronoi = getOutlierVoronois();
			voronois.insert(voronois.end(), _additionalVoronoi.begin(), _additionalVoronoi.end());
		}
	}

	void display() {
		glClearColor(1, 1, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		//外周円の描画
		glColor3f(0, 0, 0);
		ofNoFill();
		glLineWidth(1);
		ofDrawCircle(glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2), dynamic_GLOBAL_RADIUS);

		//動きまわる赤色の点の描画
		for (int i = 0; i < points.size(); i++)
		{
			points[i].display();
		}

		//ボロノイの描画
		for (int i = 0; i < voronois.size(); i++)
		{
			voronois[i].display();
		}

		//ドロネーの描画
		for (int i = 0; i < circles.size(); i++)
		{
			circles[i].drawTriangle();
			circles[i].drawCircle();
			circles[i].drawCenter();
		}

	}

	void makeCircumcircle() {

	}
	vector<Class_DelaCircle> getCircles() {
		//外接円の中に他のpointが存在しないpointの組み合わせを全探索
		vector<Class_DelaCircle> _circles;
		for (int i = 0; i < points.size() - 2; i++)
		{
			for (int j = i + 1; j < points.size() - 1; j++)
			{
				for (int k = j + 1; k < points.size(); k++)
				{
					vector <Class_DelaPoint>elements;
					elements.push_back(points[i]);
					elements.push_back(points[j]);
					elements.push_back(points[k]);

					Class_DelaCircle delaCircle;
					delaCircle.setup(elements);
					//外接円内に他のpointがないか確認
					if (delaCircle.check(points))
					{
						_circles.push_back(delaCircle);
					}
				}
			}
		}
		return _circles;
	};
	vector<Class_DelaVoronoi> getVoronois() {
		vector<Class_DelaVoronoi> _voronois;
		for (int i = 0; i < circles.size() - 1; i++) {
			for (int j = i + 1; j < circles.size(); j++) {
				int sharepoint = 0;
				for (int k = 0; k < 3; k++) {
					circles[i].sharepoint[k] = 0;
					circles[j].sharepoint[k] = 0;
				}

				//ドロネーで分割した三角形の中で頂点を共有しているものの洗い出し
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						if (ofVec2f(circles[i].elements[k].pos).match(ofVec2f(circles[j].elements[l].pos))) {
							circles[i].sharepoint[k]++;
							circles[j].sharepoint[l]++;
							sharepoint++;
						}
					}
				}

				//頂点を２つ共有している場合ひとつの辺を共有していることになる
				//辺を共有している場合はボロノイの線で繋がれる
				if (sharepoint == 2) {
					if (circles[i].sharepoint[0] > 0) {
						if (circles[i].sharepoint[1] > 0) {
							circles[i].shareside[0]++;
						}
						if (circles[i].sharepoint[2] > 0) {
							circles[i].shareside[2]++;
						}
					}
					else {
						if (circles[i].sharepoint[1] > 0 && circles[i].sharepoint[2] > 0) {
							circles[i].shareside[1]++;
						}
					}
					if (circles[j].sharepoint[0] > 0) {
						if (circles[j].sharepoint[1] > 0) {
							circles[j].shareside[0]++;
						}
						if (circles[j].sharepoint[2] > 0) {
							circles[j].shareside[2]++;
						}
					}
					else {
						if (circles[j].sharepoint[1] > 0 && circles[j].sharepoint[2] > 0) {
							circles[j].shareside[1]++;
						}
					}

					Class_DelaVoronoi _voronoi;
					_voronoi.setup(dynamic_GLOBAL_RADIUS, POINT_RADIUS, circles[i].center, circles[j].center);
					_voronois.push_back(_voronoi);
				}
			}
		}
		return _voronois;
	};
	vector<Class_DelaVoronoi> getOutlierVoronois() {
		vector<Class_DelaVoronoi> _voronois;
		for (int i = 0; i < circles.size(); i++)
		{
			//移動点の外枠の探索
			int share = 0;
			for (int j = 0; j < 3; j++)
			{
				if (circles[i].shareside[j] > 0)
				{
					share++;
				}
			}
			if (share < 3)
			{
				for (int j = 0; j < 3; j++)
				{
					if (circles[i].shareside[j] == 0)
					{
						glm::vec2 p1, p2;
						p1 = circles[i].center;
						double dig1 = ofVec2f(circles[i].center - circles[i].elements[0].pos).angleRad(ofVec2f(circles[i].elements[1].pos - circles[i].elements[0].pos));
						double dig2 = ofVec2f(circles[i].center - circles[i].elements[1].pos).angleRad(ofVec2f(circles[i].elements[2].pos - circles[i].elements[1].pos));
						double dig3 = ofVec2f(circles[i].center - circles[i].elements[2].pos).angleRad(ofVec2f(circles[i].elements[0].pos - circles[i].elements[2].pos));

						glm::vec2 direct = (circles[i].elements[j].pos + circles[i].elements[(j + 1) % 3].pos) / 2 - circles[i].center;
						direct = glm::normalize(direct);

						if (j == 0)
						{
							if ((dig1 < 0 && dig2 > 0 && dig3 > 0) || (dig1 > 0 && dig2 < 0 && dig3 < 0))
							{
								p2 = circles[i].center - direct * 1000;
							}
							else
							{
								p2 = circles[i].center + direct * 1000;
							}
						}
						else if (j == 1)
						{
							if ((dig1 > 0 && dig2 < 0 && dig3 >0) || (dig1 < 0 && dig2 > 0 && dig3 < 0))
							{
								p2 = circles[i].center - direct * 1000;
							}
							else
							{
								p2 = circles[i].center + direct * 1000;
							}
						}
						else if (j == 2)
						{
							if ((dig1 > 0 && dig2 > 0 && dig3 < 0) || (dig1 < 0 && dig2 < 0 && dig3 > 0))
							{
								p2 = circles[i].center - direct * 10000;
							}
							else
							{
								p2 = circles[i].center + direct * 10000;
							}
						}

						Class_DelaVoronoi _voronoi;
						_voronoi.setup(dynamic_GLOBAL_RADIUS, POINT_RADIUS, p1, p2);
						_voronois.push_back(_voronoi);
					}
				}
			}
		}
		return _voronois;
	};
};