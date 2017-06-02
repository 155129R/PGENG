#ifndef CHARACTER_H
#define CHARACTER_H

#include "Classes\Animator.h"
#include "BaseEntity.h"
#include "cocos2d.h"

using namespace cocos2d;

class Character : public BaseEntity
{
private:
	GLProgram *charEffect;

	Vec2 mLoc;
	Vec2 mLocInc;
	void MoveChar(int);

public:
	void Init(const char*, const char*, float, float);
	void MoveCharByCoord(float, float);
	void Stop(void);
	void Update(float);

	void MoveRight();
	void MoveLeft();
};

#endif // CHARACTER_H