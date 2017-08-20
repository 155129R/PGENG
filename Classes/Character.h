#ifndef CHARACTER_H
#define CHARACTER_H

#include "Animator.h"
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
	cocos2d::Node* node;
	const float mass = 10.f;
	const float jumpForce = 700.f;
	const float invulDuration = 2.f;
	const int hits = 3;
	
	int health;

	float groundHeight;
	CHARACTER_STATE charState;
	BaseWeapon* weapon;
	PhysicsBody* physics;

	void(Character::*fncStates[CHARACTER_STATE::MAX])(float);
	void Running(float _deltaTime);
	void Jumping(float _deltaTime);


	bool invulFlag;
	float invulTimer;
	bool visible;

public:
	int score;

	Character();
	virtual ~Character();

	void Init(const char* _srcImg, const char* _name, float _x, float _y);
	void Update(float);
	void Jump();
	void Invulerable(float dt);
	void Heal();
	void Death();

	CHARACTER_STATE getCharacterState();
	
	void setWeapon(BaseWeapon* _weapon);
	BaseWeapon* getWeapon();
	
	void ApplyForce(const Vec2& dir, const float& force);
	void TakeDamage();
	bool isDead();

	int GetHits();
	int GetHealth();
};

#endif // CHARACTER_H