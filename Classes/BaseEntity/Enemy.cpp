	#include"Enemy.h"

void Enemy::Init(const char* _srcImg, const char* _name, float _x, float _y, float _dir)
{
	m_mainSprite = Sprite::create(_srcImg);
	m_mainSprite->setAnchorPoint(Vec2(0, 0));
	m_mainSprite->setPosition(_x, _y);
	m_mainSprite->setName(_name);
	m_dir = 0;
	m_speed = 0.1f;

	mLoc.set(.5f, .5f);
	mLocInc.set(.005f, .01f);

	entityType = EntityType::ENEMY;

	animator.animType = Animator::ENEMYRUN;
	
	animator.PlayAnimation(animator.animType, (BaseEntity*)this);
	
	m_speed = 1.f;

	m_dir = _dir;

	isAlive = false;

	charEffect = new GLProgram();
	charEffect->initWithFilenames("Basic.vsh", "CharEffect.fsh");
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	charEffect->link();
	charEffect->updateUniforms();

}

void Enemy::Update(float _delta, BaseEntity character)
{
	if (isAlive && character.GetAlive())
	{
		auto moveEvent = MoveBy::create(0.f, Vec2(m_dir, 0.f) * m_speed);
		m_mainSprite->runAction(moveEvent);

		m_mainSprite->setVisible(true);

		//Collision detection
		if (m_mainSprite->boundingBox().intersectsRect(character.getSprite()->getBoundingBox()) ||
			m_mainSprite->getPosition().x < -m_mainSprite->getContentSize().width)
		{
			isAlive = false;
			m_mainSprite->setVisible(false);
		}
	}
}

