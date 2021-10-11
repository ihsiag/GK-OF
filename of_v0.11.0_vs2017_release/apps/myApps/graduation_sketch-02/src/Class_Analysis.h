#pragma once

#include "ofMain.h"
#include "ofApp.h"


class Class_Analysis {
public:
	//using Ptr = shared_ptr<Class_Analysis>;
	vector < glm::vec3> listPosVertex;
	vector <glm::vec2> resultArr;
	bool calcEnd,displayEnd;
	int frame;
	float scl;

	Class_Analysis() {
		listPosVertex.clear();
		resultArr.clear();
		calcEnd = false;
		displayEnd = false;
		frame = 0;
		scl = 7.0;
	}

	void setup(vector<glm::vec3>& _data) {
		for (int i = 0; i < _data.size();i++) {
			listPosVertex.push_back(_data[i]);
		}
	}


	void run() {
		//update();
		//display();
	}

	void update() {
	}

	void display() {
		if (resultArr.size() > 1) {
			if (frame < resultArr.size()-1-1) {
				frame+=2;
			}
			else {
				displayEnd = true;
			}
			glLineWidth(2);
			glColor3f(1, 0, 0);
			glBegin(GL_LINES);
			for (int i = 0; i < frame; i++) {
				glVertex2f(i, ofGetHeight() / 2 + resultArr[i].y*scl);
				glVertex2f(i + 1, ofGetHeight() / 2 + resultArr[i+1].y*scl);
			}
			glEnd();
		}
		
	}
	
	vector<glm::vec2> calcLeastSquaresMethod() {

		int N = listPosVertex.size();
		const int M = 20;
		double a[M + 1][M + 2], s[2 * M + 1], t[M + 1];
		double p, d, px;

		//-----------prepairBEGIN
		for (int i = 0; i < 2 * M + 1; i++) {
			s[i] = 0;
		}
		for (int i = 0; i < M + 1; i++) {
			t[i] = 0;
		}

		for (int j = 0; j < N; j++) {
			for (int i = 0; i < 2 * M + 1; i++) {
				s[i] += pow(j, i);//今回はxはただのindex
			}
			for (int i = 0; i < M + 1; i++) {
				t[i] += pow(listPosVertex[j].z, i);
			}
		}
		//-----------prepairEND

		//-----------gaussianJordanBEGIN
		// a[][] に s[], t[] 代入
		for (int i = 0; i < M + 1; i++) {
			for (int j = 0; j < M + 1; j++) {
				a[i][j] = s[i + j];
			}
			a[i][M + 1] = t[i];
		}

		// 掃き出し
		for (int k = 0; k < M + 1; k++) {
			p = a[k][k];
			for (int j = k; j <= M + 1; j++) {
				a[k][j] /= p;
			}
			for (int i = 0; i < M + 1; i++) {
				if (i != k) {
					d = a[i][k];
					for (int j = k; j <= M + 1; j++) {
						a[i][j] -= d * a[k][j];
					}
				}
			}
		}

		// y 値計算＆結果出力
		for (int k = 0; k <= M; k++){
			printf("a%d = %10.6f\n", k, a[k][M + 1]);
			printf("    x    y\n");
			for (px = -3; px<3; px += .5) {
				p = 0;
				for (int k = 0; k <= M; k++)
					p += a[k][M + 1] * pow(px, k);
				printf("%5.1f%5.1f\n", px, p);
			}
		}

		// y 値計算＆結果出力
		/*
		vector<float> dist;
		vector<double> vSum;
		double sum = 0;
		int count = N - 1;
		double y;
		for(int i=0;i<N;i++){
			y = 0;
			//count = 0;
			for(int k=0; k<M+1;k++){
				y += a[i][M + 1] * pow(listPosVertex[k][2], k); //posXiにおけるyの値
				//count++;
			}
			sum += abs(y - i);
		}
		for (int i = 0; i < M + 1; i++) {
			cout << "a[" << i << "] = " << a[i][M + 1] << endl;		
		}
		*/
		float count = 0;
		for (double px = 0; px <= listPosVertex.size(); px += 0.75) {
			double py = 0;
			for(int k=0; k<M+1;k++){				
				py += a[k][M + 1] * pow(px, k)+ ofMap(ofNoise(px / 100, k / 100), 0, 1, -0.25, 0.25);
				count++;
			}
			//cout << "x:" << px << ",y:" << py << endl;
			//py *= scl;
			resultArr.push_back(glm::vec2(px, py));
		}

		//-----------gaussianJordanEND

		calcEnd = true;
		return resultArr;
	}

	float sq(glm::vec2 pos1, glm::vec2 pos2) {
		return glm::distance(pos1, pos2);
	}	
};