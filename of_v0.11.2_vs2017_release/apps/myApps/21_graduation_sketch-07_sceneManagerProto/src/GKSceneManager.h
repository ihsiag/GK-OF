#pragma once

#include <vector>
#include "GKScene.h"

class GKSceneManager {
public:
	std:: vector<GKScene *> gkScenes;
	void addScene(GKScene* _gkScene) {
		gkScenes.push_back(_gkScene);
	};
private:
};
