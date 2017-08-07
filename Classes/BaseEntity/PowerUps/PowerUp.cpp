#include "PowerUp.h"
#include "../Character.h"


PowerUp::PowerUp()
{

}

PowerUp::~PowerUp()
{

}

void PowerUp::Init(const char* _srcImg, const char* _name, float _x, float _y)
{
	m_mainSprite = Sprite::create(_srcImg);
	m_mainSprite->setAnchorPoint(Vec2(0, 0));
	m_mainSprite->setPosition(_x, _y);
	m_mainSprite->setName(_name);

	groundHeight = _y;
	visible = true;

	m_dir = -1;
	entityType = EntityType::POWERUP_LIFE;

	isAlive = true;
}

void PowerUp::Update(float _delta, BaseEntity* character)
{
	if (isAlive && character->GetAlive())
	{
		cocos2d::log(std::to_string(m_mainSprite->getPosition().x).c_str());
		auto moveEvent = MoveBy::create(0.f, Vec2(m_dir, 0.f) * m_speed);
		m_mainSprite->runAction(moveEvent);
		m_mainSprite->setVisible(true);
		
		if (m_mainSprite->boundingBox().intersectsRect(character->getSprite()->getBoundingBox()))
		{
			Character* player = (Character*)character;
			if (player)
			{
				player->Heal();
				isAlive = false;
				m_mainSprite->setVisible(false);
			}
		}
	}
}

BaseEntity::EntityType PowerUp::GetPowerUpType()
{
	return entityType;
}