#ifndef __BASE_WEAPON_H__
#define __BASE_WEAPON_H__

class BaseEntity;

class BaseWeapon
{
protected:
	BaseEntity* wielder;

public:
	BaseWeapon(BaseEntity* _wielder = nullptr){}
	virtual ~BaseWeapon(){}
	virtual void setWielder(BaseEntity* _wielder){ wielder = _wielder; }
	virtual void use() = 0;
};

#endif // !__BASE_WEAPON_H__



