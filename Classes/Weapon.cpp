#include "Weapon.h"
Weapon::Weapon(int bulletCap,int bulletPerMag, bool reload)
{
	bulletLeft = bulletCap;
	magazineSize = bulletPerMag;
	bullet = magazineSize;
	ableToReload = reload;
	weaponFired = false;
	coolDownPerShot = 1.0f;
	coolDownTimer = coolDownPerShot;
}
Weapon::~Weapon()
{
}
void Weapon::Reload()
{
	if (ableToReload)
	{
		if (bulletLeft != 0)
		{
			if (bulletLeft > magazineSize)
			{
				bullet = magazineSize;
				bulletLeft -= magazineSize;
			}
			else if (bulletLeft < magazineSize)
			{
				bullet = bulletLeft;
				bulletLeft = 0;
			}
		}
		else
		{
			//NO bullet left to reload, although the gun is reloadable
		}
	}
}
void Weapon::Fire(vector<Projectile*> projectilePool, BaseEntity owner)
{
	if (bullet > 0)
	{
		for (auto projectile : projectilePool)
		{
			if (!weaponFired)
			{
				if (!projectile->GetAlive())
				{
					Vec2 direction = Vec2(1.0f, 0.0f);
					projectile->SetPosition(owner.getPosition());
					projectile->SetSpeed(projectile->GetSpeed());
					projectile->SetLifetime(projectile->GetLifetime());
					projectile->SetDamage(projectile->GetDamage());
					projectile->SetDirection(projectile->GetDir());
					projectile->SetAlive(true);
			
					bullet -= 1;
					weaponFired = true;
				}
			}
		}
		
	}
	else
	{
		Reload();
	}
}
void Weapon::Update(float dt)
{
	if (weaponFired)
	{
		coolDownTimer -= dt;
		if (coolDownTimer <= 0.0f)
		{
			weaponFired = false;
			coolDownTimer = coolDownPerShot;
		}
	}
}