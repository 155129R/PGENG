#pragma once
#include "FeedBack.h"

class FeedBackManager
{
private:
	FeedBack* playerFeedBack;

public:
	FeedBackManager(Node*);
	~FeedBackManager();
	void HealPlayer();
	void Update(double dt, BaseEntity* character);
};