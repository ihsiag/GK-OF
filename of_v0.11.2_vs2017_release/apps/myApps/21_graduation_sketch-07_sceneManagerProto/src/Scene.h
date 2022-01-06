#pragma once

class CommonData;
class Scene {
protected:
    Scene(CommonData* const commonData) :
        commonData(commonData)
    {}


public:
    //コピー禁止
    Scene(const Scene&) = delete;
    //コピー禁止
    Scene& operator=(const Scene&) = delete;

    //仮想関数化したデストラクタ
    virtual ~Scene() = default;

protected:
    //共有データ
    CommonData* const commonData;


public:
    virtual Scene* update() = 0;
    virtual void draw() const = 0;

protected:
    //実体生成用関数
    template<typename T>
    Scene* makeScene();
};