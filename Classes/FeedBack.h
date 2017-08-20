#pragma once
#include "BaseEntity.h"
class FeedBack : public BaseEntity
{	
public:
	FeedBack();
	~FeedBack();
	void Init(const char*, const char*, float, float);
	void Update(float, BaseEntity*);
	void playerHeal();
	void playerTakeDamage();
};