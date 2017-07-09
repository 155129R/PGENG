#include "Projectile\Projectile.h"
#include "BaseEntity\BaseEntity.h"
#include "cocos2d.h"
using std::vector;
class Weapon : public BaseEntity
{
protected:
	float firstRate;
	int bulletLeft;
	int magazineSize;
	int bullet;
	bool ableToReload;
	bool weaponFired;
	float coolDownPerShot;
	float coolDownTimer;

public:
	Weapon(int, int, bool);
	~Weapon();
	void Reload();
	void Fire(vector<Projectile*>, BaseEntity);
	virtual void Update(float dt);
};