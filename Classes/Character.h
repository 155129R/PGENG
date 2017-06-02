#ifndef CHARACTER_H
#define CHARACTER_H

#include "cocos2d.h"

using namespace cocos2d;

class Character
{
private:
	GLProgram *charEffect;
	Sprite* m_mainSprite;

	Vec2 mLoc;
	Vec2 mLocInc;

	int m_dir;
	float m_speed;

public:
	void Init(const char*, const char*, float, float);
	void MoveChar(int);
	void MoveRight();
	void MoveCharByCoord(float, float);
	void Stop(void);
	void Update(float);

	Sprite* getSprite(void) { return m_mainSprite; }
	Vec2 getPosition() { return m_mainSprite->getPosition(); }
};

#endif // CHARACTER_H