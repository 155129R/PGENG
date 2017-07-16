#include "Character.h"
#include "scene\\HelloWorldScene.h"

#include "Weapon\Rocket.h"


Character::Character()
{
	fncStates[CHARACTER_STATE::RUNNING] = &Character::Running;
	fncStates[CHARACTER_STATE::JUMPING] = &Character::Jumping;
	fncStates[CHARACTER_STATE::DEATH] = &Character::Death;
}

Character::~Character()
{
	if (weapon)
	{
		delete weapon;
		weapon = nullptr;
	}
}

void Character::Init(const char* _srcImg, const char* _name, float _x, float _y)
{
	m_mainSprite = Sprite::create(_srcImg);
	m_mainSprite->setAnchorPoint(Vec2(0, 0));
	m_mainSprite->setPosition(_x, _y);
	m_mainSprite->setName(_name);

	physics = PhysicsBody::createBox(m_mainSprite->getContentSize(), PhysicsMaterial(0.f, 0.f, 0.f));
	physics->addMass(mass);
	physics->setRotationEnable(false);
	m_mainSprite->addComponent(physics);

	groundHeight = _y;
	visible = true;
	score = 0;

	health = hits;

	invulTimer = invulDuration;
	invulFlag = false;

	entityType = EntityType::CHARACTER;

	isAlive = true;

	setWeapon(new Rocket(this));

	charState = CHARACTER_STATE::RUNNING;
	animator.animType = Animator::PLAYERRUN;
	animator.PlayAnimation(animator.animType, (BaseEntity*)this);
}

void Character::Update(float _dt)
{
	(this->*fncStates[charState])(_dt);
	Invulerable(_dt);
}

void Character::Running(float _deltaTime)
{
	physics->setGravityEnable(false);
	if (physics->getVelocity().y != 0.f)
	{
		charState = CHARACTER_STATE::JUMPING;
	}
}

void Character::Jumping(float _deltaTime)
{
	physics->setGravityEnable(true);
	if (m_mainSprite->getPosition().y < groundHeight)
	{
		physics->setGravityEnable(false);
		physics->setVelocity(Vec2::ZERO);
		m_mainSprite->setPositionY(groundHeight);
		animator.animType = Animator::PLAYERRUN;
		animator.PlayAnimation(animator.animType, (BaseEntity*)this);
		charState = CHARACTER_STATE::RUNNING;
	}
}

void Character::Death(float _deltaTime)
{

}

void Character::Invulerable(float dt)
{
	if (invulFlag)
	{
		invulTimer -= dt;
		visible = !visible;
		m_mainSprite->setVisible(visible);

		if (invulTimer < 0)
		{
			visible = true;
			m_mainSprite->setVisible(visible);
			invulTimer = invulDuration;
			invulFlag = false;
		}
	}
}

void Character::Jump()
{
	if (charState != CHARACTER_STATE::JUMPING)
	{
		charState = CHARACTER_STATE::JUMPING;
		animator.animType = Animator::PLAYERJUMP;
		animator.PlayAnimation(animator.animType, (BaseEntity*)this);
		ApplyForce(Vec2(0.f, 1.f), jumpForce);
	}
}

CHARACTER_STATE Character::getCharacterState()
{
	return charState;
}

void Character::setWeapon(BaseWeapon* _weapon)
{
	weapon = _weapon;
	weapon->setWielder(this);
}

BaseWeapon* Character::getWeapon()
{
	return weapon;
}

void Character::ApplyForce(const Vec2& dir, const float& force)
{ 
	physics->setVelocity(physics->getVelocity() + dir * force);
}

void Character::TakeDamage()
{
	if (!invulFlag)
	{
		health -= 1;
		invulFlag = true;
	}
}

bool Character::isDead()
{
	return health <= 0;
}