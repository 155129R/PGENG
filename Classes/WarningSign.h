#pragma once
#include "BaseEntity.h"

class WarningSign : public BaseEntity
{
private:
	Vec2 mLoc;
	Vec2 mLocInc;
	GLProgram *charEffect;

	float warningScale;
	float scaleLimit;
	bool scaleUp;
	bool scaleDown;


public:
	enum WarningType
	{
		NIL = 0,
		POWERUP,
		ENEMEY,
		MAX
	}warningType;
	
	void Init(const char*, const char*, float, float);
	void SetType(WarningType);
	WarningType WarningSign::GetType();
	void Update(float);
};