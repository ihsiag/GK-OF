#pragma once

#include "ofMain.h"
#include "ofApp.h"


class Class_AnalyseModel {
public:
	//using Ptr = shared_ptr<Class_Analysis>;
	ofMesh* mesh;
	vector <glm::vec3>* resultArr;
	bool bFirst,bSecond;
	int frame;
	float scl;

	Class_AnalyseModel() {
	}
	~Class_AnalyseModel() {
	}

	void setup(ofMesh* _mesh,vector<glm::vec3>* _resultArr) {
		mesh = _mesh;
		resultArr = _resultArr;
		bFirst = true;
		bSecond = false;
		frame = 0;
		scl = 7.0;
	}


	bool run() {
		//if (bFirst)calcLeastSquaresMethod();
		if (bFirst)myCalc();
		if (bSecond)display();
		if (!bFirst && !bSecond) { return true; }else {return false;}
	}

	void update() {
	}

	void display() {
		if (frame < resultArr->size()-1) {
			frame+=1;
		}
		else {
			bSecond = false;
		}
		if (frame - 1 > 0) {
			glLineWidth(2);
			glColor3f(1, 0, 0);
			glBegin(GL_LINES);
			for (int i = 0; i < frame - 1; i++) {
				glVertex2f(i, ofGetHeight() / 2 + resultArr->at(i).y*scl);
				glVertex2f(i + 1, ofGetHeight() / 2 + resultArr->at(i).y * scl);
			}
			glEnd();
		}	
	}
	
	void calcLeastSquaresMethod() {

		int N = mesh->getNumVertices();
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
				t[i] += pow(mesh->getVertex(i).z, i);
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
		
		/*
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
		*/

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
		
		for (double px = 0; px <= mesh->getNumVertices(); px += 0.75) {
			double py = 0;
			for(int k=0; k<M+1;k++){				
				py += a[k][M + 1] * pow(px, k)+ ofMap(ofNoise(px / 100, k / 100), 0, 1, -0.25, 0.25);
				count++;
			}
			//py *= scl;
			resultArr->push_back(glm::vec3(px, py,0));
		}

		//-----------gaussianJordanEND

		//-----------BoolsBEGIN
		bFirst = false;
		bSecond = true;
		//-----------BoolsBEGIN
	}



	void myCalc() {
		int N = mesh->getNumVertices();
		for (int i = 0; i < N-1; i++) {
			glm::vec3 diff = mesh->getVertex(i + 1) - mesh->getVertex(i);
			resultArr->push_back(diff);
		}

		//-----------BoolsBEGIN
		bFirst = false;
		//bSecond = true;
		//-----------BoolsBEGIN
	}

	float sq(glm::vec2 pos1, glm::vec2 pos2) {
		return glm::distance(pos1, pos2);
	}	
};