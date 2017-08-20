//#include "/Animator.h"
#include "Animator.h"
//Forward declaration for classes since we can't cross include
//#include "/BaseEntity/Character.h"
#include "Character.h"

void Animator::Init()
{
	animation = new Animation();
	animate = new Animate();
}


void Animator::PlayAnimation(AnimationType animType, BaseEntity* entity)
{
	if (entity->GetAlive())
	{
		switch (entity->entityType)
		{
		case BaseEntity::CHARACTER:
			switch (animType)
			{
			case PLAYERRUN:
			{
				entity->getSprite()->stopAllActions();

				Vector<SpriteFrame*> animFrames;
				animFrames.reserve(8);
				animFrames.pushBack(SpriteFrame::create("PlayerRunning/running1.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("PlayerRunning/running2.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("PlayerRunning/running3.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("PlayerRunning/running4.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("PlayerRunning/running5.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("PlayerRunning/running6.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("PlayerRunning/running7.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("PlayerRunning/running8.png", Rect(0, 0, 65, 81)));

				animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
				animate = Animate::create(animation);

				entity->getSprite()->runAction(RepeatForever::create(animate));
			}
			break;

			case PLAYERIDLE:
			{
				entity->getSprite()->stopAllActions();

				Vector<SpriteFrame*> animFrames;
				animFrames.reserve(2);
				animFrames.pushBack(SpriteFrame::create("PlayerIdle/idle1.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("PlayerIdle/idle2.png", Rect(0, 0, 65, 81)));

				animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
				animate = Animate::create(animation);

				entity->getSprite()->runAction(RepeatForever::create(animate));

			}
			break;

			case PLAYERJUMP:
			{
				entity->getSprite()->stopAllActions();

				Vector<SpriteFrame*> animFrames;
				animFrames.reserve(3);
				animFrames.pushBack(SpriteFrame::create("PlayerJumping/jumping1.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("PlayerJumping/jumping2.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("PlayerJumping/jumping3.png", Rect(0, 0, 65, 81)));

				animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
				animate = Animate::create(animation);

				//  Play animation once using this code without the RepeatForever
				// 	character->getSprite()->runAction(animationRunning);
				entity->getSprite()->runAction(animate);
			}
			break;
			}
			break;

		case BaseEntity::ENEMY:
			switch (animType)
			{

			case ENEMYRUN:
			{
				entity->getSprite()->stopAllActions();

				Vector<SpriteFrame*> animFrames;
				animFrames.reserve(4);
				animFrames.pushBack(SpriteFrame::create("Attack/Attack1.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("Attack/Attack2.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("Attack/Attack3.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("Attack/Attack4.png", Rect(0, 0, 65, 81)));

				animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
				animate = Animate::create(animation);

				//  Play animation once using this code without the RepeatForever
				// 	character->getSprite()->runAction(animationRunning);
				entity->getSprite()->runAction(RepeatForever::create(animate));
			}
			break;
			}
			break;
		}
	}
}

void Animator::SetAnimType(AnimationType newType)
{
	animType = newType;
}
Animator::AnimationType Animator::GetAnimType()
{
	return animType;
}

void Animator::PowerUpAnimationFinish(BaseEntity* entity)
{
	entity->getSprite()->setVisible(false);
}
void Animator::PlayFeedBackAnimation(AnimationType animType, BaseEntity* entity)
{
	switch (animType)
	{
	case PLAYERHEAL:
	{
		entity->getSprite()->stopAllActions();

		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(5);
		animFrames.pushBack(SpriteFrame::create("Heal/Heal1.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Heal/Heal2.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Heal/Heal3.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Heal/Heal4.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Heal/Heal5.png", Rect(0, 0, 65, 81)));

		animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
		animate = Animate::create(animation);

		entity->getSprite()->runAction(animate);
	}
	break;
	case PLAYERTAKEDAMAGE:
	{
		entity->getSprite()->stopAllActions();

		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(6);
		animFrames.pushBack(SpriteFrame::create("Damage/damage1.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Damage/damage2.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Damage/damage3.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Damage/damage4.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Damage/damage5.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Damage/damage6.png", Rect(0, 0, 65, 81)));

		animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
		animate = Animate::create(animation);

		entity->getSprite()->runAction(animate);
	}
	break;
	}
}