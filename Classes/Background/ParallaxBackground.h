#ifndef __PARALLAX_BACKGROUND_H__
#define __PARALLAX_BACKGROUND_H__

#include "ScrollingBackground.h"

#define MAX_LAYERS 5

class ParallaxBackground
{
public:
	cocos2d::Node* node;

	ParallaxBackground();
	~ParallaxBackground();

	void Init(float _seconds);
	void Update(float deltaTime);

	bool AddBackground(int layer, ScrollingBackground* background);
	void RemoveBackground(int layer);
	ScrollingBackground& GetBackground(int layer);
	void SetScrollSpeedByTime(float _seconds);

private:
	float seconds;

	ScrollingBackground* backgrounds[MAX_LAYERS];
};


#endif // !__PARALLAX_BACKGROUND_H__


