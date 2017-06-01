#include "BaseEntity.h"
int BaseEntity::GetDirection()
{
	return m_dir;
}

float BaseEntity::GetSpeed()
{
	return m_speed;
}

void BaseEntity::SetDirection(int dir)
{
	m_dir = dir;
}

void BaseEntity::SetSpeed(float speed)
{
	m_speed = speed;
}

Animator BaseEntity::GetAnimator()
{
	return animator;
}

void BaseEntity::SetAnimator(Animator anim)
{
	animator = anim;
}

bool BaseEntity::GetAlive()
{
	return isAlive;
}

void BaseEntity::SetAlive(bool status)
{
	isAlive = status;
}