#include "Rocket.h"

#include "../BaseEntity/Character.h"
#include "../scene/SceneManager.h"
#include "../scene/GameScene.h"
#include "../Projectile/Projectile.h"

Rocket::Rocket(BaseEntity* _character)
{
	setWielder(_character);
}

Rocket::~Rocket()
{

}

void Rocket::setWielder(BaseEntity* _wielder)
{
	wielder = _wielder;
	character = dynamic_cast<Character*>(_wielder);
}

void Rocket::use()
{
	
	if (character->getCharacterState() == CHARACTER_STATE::RUNNING)
	{
		fired = false;
		character->Jump();
	}
	else if (!fired)
	{
		Scene* scene = (CCDirector::getInstance()->getRunningScene());
		Node* node = scene->getChildByTag((int)SceneType::GAMEPLAY);
		GameScene* game = dynamic_cast<GameScene*>(node);

		if (game)
		{
			for (auto projectile : game->projectileList)
			{
				if (!projectile->GetAlive())
				{
					fired = true;
					Vec2 direction = Vec2(0.0f, -1.0f);
					projectile->SetPosition(character->getPosition());
					projectile->SetSpeed(1500.f);
					projectile->SetLifetime(1.f);
					projectile->SetBlastRadius(500.f);
					projectile->SetDamage(0.f);
					projectile->SetDirection(direction);
					projectile->SetAlive(true);
					break;
				}
			}
		}
	}

}