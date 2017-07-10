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

	groundHeight = _y;

	mLoc.set(.5f, .5f);
	mLocInc.set(.005f, .01f);

	entityType = EntityType::CHARACTER;

	isAlive = true;

	charEffect = new GLProgram();
	charEffect->initWithFilenames("Basic.vsh", "CharEffect.fsh");
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	charEffect->link();
	charEffect->updateUniforms();

	setWeapon(new Rocket(this));

	charState = CHARACTER_STATE::RUNNING;
	animator.animType = Animator::PLAYERRUN;
	animator.PlayAnimation(animator.animType, (BaseEntity*)this);
}

void Character::Update(float _dt)
{
	(this->*fncStates[charState])(_dt);

	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(charEffect);
	m_mainSprite->setGLProgram(charEffect);
	m_mainSprite->setGLProgramState(state);
	state->setUniformVec2("loc", mLoc);
}

void Character::Running(float _deltaTime)
{
	if (velocity.y != 0)
	{
		charState = CHARACTER_STATE::JUMPING;
	}
}

void Character::Jumping(float _deltaTime)
{
	velocity.y -= 9.8f;
	m_mainSprite->setPosition(m_mainSprite->getPosition() + velocity * _deltaTime);

	if (m_mainSprite->getPosition().y < groundHeight)
	{
		velocity.setZero();
		m_mainSprite->setPositionY(groundHeight);
		animator.animType = Animator::PLAYERRUN;
		animator.PlayAnimation(animator.animType, (BaseEntity*)this);
		charState = CHARACTER_STATE::RUNNING;
	}
}

void Character::Death(float _deltaTime)
{

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
	cocos2d::log(("Before: " + std::to_string(velocity.y)).c_str());
	velocity += dir * (force / mass);
	cocos2d::log(("After: " + std::to_string(velocity.y)).c_str());
}
