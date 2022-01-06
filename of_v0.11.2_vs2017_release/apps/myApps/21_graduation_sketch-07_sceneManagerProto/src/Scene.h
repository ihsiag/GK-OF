#pragma once

class CommonData;
class Scene {
protected:
    Scene(CommonData* const commonData) :
        commonData(commonData)
    {}


public:
    //�R�s�[�֎~
    Scene(const Scene&) = delete;
    //�R�s�[�֎~
    Scene& operator=(const Scene&) = delete;

    //���z�֐��������f�X�g���N�^
    virtual ~Scene() = default;

protected:
    //���L�f�[�^
    CommonData* const commonData;


public:
    virtual Scene* update() = 0;
    virtual void draw() const = 0;

protected:
    //���̐����p�֐�
    template<typename T>
    Scene* makeScene();
};