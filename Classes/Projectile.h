#include "BaseEntity.h"

class Projectile : public BaseEntity
{
protected:

	// Remaining lifetime in seconds
	float m_Lifetime;

	// The direction of the projectile
	Vec2 m_ProjectileDirection;

	// The Damage of the projectile
	int m_Damage;

	float blastRadius;

public:
	Projectile(const char* _srcImg, float, Vec2, int);
	Projectile();
	virtual ~Projectile();

	//Get the status of the projectile
	void SetStatus(const bool status);
	bool GetStatus(void) const;

	// Set the direction of the projectile
	void SetDirection(Vec2 direction);
	// Get the direction of the projectile
	Vec2 GetDir(void);

	// Set the lifetime of the projectile
	void SetLifetime(const float lifeTime);
	// Get the lifetime of the projectile
	float GetLifetime(void) const;

	// Set the direction of the projectile
	void SetSpeed(float speed);
	// Get the direction of the projectile
	float GetProjectileSpeed(void) const;

	// Get the damage of the projectile
	int GetDamage();
	// Set the damage of the projectile
	void SetDamage(int );

	void SetBlastRadius(float radius);
	float GetBlastRadius();

	// Set the position of the projectile
	void SetPosition(Vec2);

	// Update the status of this projectile
	virtual void Update(double dt = 0.0333f);
	
};