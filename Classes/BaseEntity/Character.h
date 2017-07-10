#ifndef CHARACTER_H
#define CHARACTER_H

#include "Classes\Animator.h"
#include "BaseEntity.h"
#include "cocos2d.h"

class BaseWeapon;

using namespace cocos2d;

typedef enum CHARACTER_STATE
{
	RUNNING,
	JUMPING,
	DEATH,
	MAX,
};


class Character : public BaseEntity
{
private:
	GLProgram *charEffect;
	cocos2d::Node* node;

	Vec2 mLoc;
	Vec2 mLocInc;

	Vec2 velocity;
	const float mass = 5.f;
	const float jumpForce = 2000.f;

	float groundHeight;
	CHARACTER_STATE charState;
	BaseWeapon* weapon;

	void(Character::*fncStates[CHARACTER_STATE::MAX])(float);
	void Running(float _deltaTime);
	void Jumping(float _deltaTime);
	void Death(float _deltaTime);

public:
	Character();
	virtual ~Character();

	void Init(const char* _srcImg, const char* _name, float _x, float _y);
	void Update(float);
	void Jump();

	CHARACTER_STATE getCharacterState();
	
	void setWeapon(BaseWeapon* _weapon);
	BaseWeapon* getWeapon();
	
	void ApplyForce(const Vec2& dir, const float& force);
};

#endif // CHARACTER_H