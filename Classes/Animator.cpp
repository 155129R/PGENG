#include "Classes\Animator.h"

//Forward declaration for classes since we can't cross include
#include "Classes\BaseEntity\Character.h"

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

				Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
				Animate* animateIdle = Animate::create(animation);

				entity->getSprite()->runAction(RepeatForever::create(animateIdle));
			}
			break;

			case PLAYERIDLE:
			{
				entity->getSprite()->stopAllActions();

				Vector<SpriteFrame*> animFrames;
				animFrames.reserve(2);
				animFrames.pushBack(SpriteFrame::create("PlayerIdle/idle1.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("PlayerIdle/idle2.png", Rect(0, 0, 65, 81)));

				Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
				Animate* animateIdle = Animate::create(animation);

				entity->getSprite()->runAction(RepeatForever::create(animateIdle));

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

				Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.35f);
				Animate* animationJump = Animate::create(animation);

				//  Play animation once using this code without the RepeatForever
				// 	character->getSprite()->runAction(animationRunning);
				entity->getSprite()->runAction(animationJump);
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
				animFrames.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 65, 81)));
				animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));

				Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.35f);
				Animate* animationRun = Animate::create(animation);

				//  Play animation once using this code without the RepeatForever
				// 	character->getSprite()->runAction(animationRunning);
				entity->getSprite()->runAction(RepeatForever::create(animationRun));
			}
			break;
			}
			break;
		}
	}
}