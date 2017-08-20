#include "FeedBack.h"

void FeedBack::Init(const char* _srcImg, const char* _name, float _x, float _y)
{
	m_mainSprite = Sprite::create(_srcImg);
	m_mainSprite->setAnchorPoint(Vec2(0, 0));
	m_mainSprite->setPosition(_x, _y);
	m_mainSprite->setName(_name);
	animator.Init();
	animator.animType = Animator::PLAYERHEAL;



}
FeedBack::FeedBack()
{
}
FeedBack::~FeedBack()
{
}
void FeedBack::Update(float dt, BaseEntity* character)
{
	m_mainSprite->setPosition(character->getSprite()->getPosition().x, character->getSprite()->getPosition().y);
	int temp = m_mainSprite->getNumberOfRunningActions();
	if (m_mainSprite->getNumberOfRunningActions() == 0)
	{
		this->SetAlive(false);
		m_mainSprite->setVisible(false);
	}
}

void FeedBack::playerHeal()
{
	m_mainSprite->setVisible(true);
	animator.animType = Animator::PLAYERHEAL;
	animator.PlayFeedBackAnimation(animator.animType, this);
}

void FeedBack::playerTakeDamage()
{
	m_mainSprite->setVisible(true);
	animator.animType = Animator::PLAYERTAKEDAMAGE;
	animator.PlayFeedBackAnimation(animator.animType, this);
}