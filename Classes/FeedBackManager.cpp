#include "FeedBackManager.h"

FeedBackManager::FeedBackManager(Node* scene)
{

}
FeedBackManager::~FeedBackManager()
{

}

void FeedBackManager::HealPlayer() 
{

}

void FeedBackManager::Update(double dt, BaseEntity* character)
{
	playerFeedBack->getSprite()->setPosition(character->getSprite()->getPosition().x, character->getSprite()->getPosition().y);
}