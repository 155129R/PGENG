#include "Classes\Animator.h"

//Forward declaration for classes since we can't cross include
#include "Classes\Character.h"

void Animator::PlayAnimation(AnimationType animType, Character* character)
{
	switch (animType)
	{
		case PLAYERRUN:
		{
			character->getSprite()->stopAllActions();

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

			character->getSprite()->runAction(RepeatForever::create(animateIdle));
		}
		break;

		case PLAYERIDLE:
		{
			character->getSprite()->stopAllActions();

			Vector<SpriteFrame*> animFrames;
			animFrames.reserve(2);
			animFrames.pushBack(SpriteFrame::create("PlayerIdle/idle1.png", Rect(0, 0, 65, 81)));
			animFrames.pushBack(SpriteFrame::create("PlayerIdle/idle2.png", Rect(0, 0, 65, 81)));

			Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
			Animate* animateIdle = Animate::create(animation);

			character->getSprite()->runAction(RepeatForever::create(animateIdle));

		}
		break;

		case PLAYERJUMP:
		{
			character->getSprite()->stopAllActions();

			Vector<SpriteFrame*> animFrames;
			animFrames.reserve(3);
			animFrames.pushBack(SpriteFrame::create("PlayerJumping/jumping1.png", Rect(0, 0, 65, 81)));
			animFrames.pushBack(SpriteFrame::create("PlayerJumping/jumping2.png", Rect(0, 0, 65, 81)));
			animFrames.pushBack(SpriteFrame::create("PlayerJumping/jumping3.png", Rect(0, 0, 65, 81)));

			Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.35f);
			Animate* animationJump = Animate::create(animation);

			//  Play animation once using this code without the RepeatForever
			// 	character->getSprite()->runAction(animationRunning);
			character->getSprite()->runAction(animationJump);
		}
		break;
	}
}