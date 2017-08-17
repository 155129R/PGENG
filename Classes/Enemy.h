#pragma once
#include "BaseEntity.h"

class Enemy : public BaseEntity
{
	private:
		Vec2 mLoc;
		Vec2 mLocInc;
		GLProgram *charEffect;

	public:
		void Init(const char*, const char*, float, float, float);
		void Update(float, BaseEntity*);


};