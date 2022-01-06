#pragma once
#include "Scene.h"
#include "CommonData.h"

class SceneManager :public Scene{
public:	
	class Title;

	SceneManager():
		Scene(new CommonData()),
		mScene(makeScene<Title>())
	{}
	~SceneManager() {
		if (mScene != nullptr) delete mScene;
		delete commonData;
	}
private:
	Scene* mScene;
public:
	void update() {
		Scene* p = mScene->update();
		if (p != mScene) {
			delete mScene;
			mScene = p;
		};
	}
	void draw() const {
		mScene->draw();
	};
};
