#include"Projectile\Projectile.h"

#include "../scene/SceneManager.h"
#include "../scene/GameScene.h"

Projectile::Projectile(const char* _srcImg, float lifetime, Vec2 direction, int damage)
{
	m_mainSprite = Sprite::create(_srcImg);
	m_Lifetime = lifetime;
	m_ProjectileDirection = direction;
	m_Damage = damage;
	m_speed = 1.f;
	//isAlive = false;
	m_mainSprite->setVisible(false);
}

Projectile::Projectile()
{
	m_Lifetime = 1.0f;
	m_Damage = 1.0f;
	m_ProjectileDirection = Vec2(1.0f, 0.0f);
	//isAlive = false;
	m_mainSprite->setVisible(false);
}

Projectile::~Projectile()
{

}

// Update the status of this projectile
void Projectile::Update(double dt)
{
	if (isAlive)
	{
		auto moveEvent = MoveBy::create(0.0f, m_ProjectileDirection * m_speed * dt);
		m_mainSprite->runAction(moveEvent);
		m_mainSprite->setVisible(true);

		if (m_mainSprite->getPosition().y <= 150.f)
		{
			SetAlive(false);
			m_mainSprite->setVisible(false);

			Scene* scene = (CCDirector::getInstance()->getRunningScene());
			Node* node = scene->getChildByTag((int)SceneType::GAMEPLAY);
			GameScene* game = dynamic_cast<GameScene*>(node);

			if (game)
			{
				game->mainChar.ApplyForce(Vec2(0.f, 1.f), 2000.f);
			}
		}
	}
}

void Projectile::SetPosition(Vec2 newPos)
{
	m_mainSprite->setPosition(newPos);
}
//Get the status of the projectile
void Projectile::SetStatus(const bool status)
{
	isAlive = status;
}

bool Projectile::GetStatus(void) const
{
	return isAlive;
}

// Set the damage of the projectile
void Projectile::SetDamage(int newDamage)
{
	m_Damage = newDamage;
}

// Set the damage of the projectile
int Projectile::GetDamage()
{
	return m_Damage;
}

// Set the direction of the projectile
void Projectile::SetDirection(Vec2 direction)
{
	m_ProjectileDirection = direction;
}

// Get the direction of the projectile
Vec2 Projectile::GetDir(void)
{
	return m_ProjectileDirection;
}

// Set the lifetime of the projectile
void Projectile::SetLifetime(const float lifeTime)
{
	m_Lifetime = lifeTime;
}

// Get the lifetime of the projectile
float Projectile::GetLifetime(void) const
{
	return m_Lifetime;
}
// Set the speed of the projectile
void Projectile::SetSpeed(const float m_fSpeed)
{
	m_speed = m_fSpeed;
}

// Get the speed of the projectile
float Projectile::GetProjectileSpeed(void) const
{
	return m_speed;
}

