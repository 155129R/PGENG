#ifndef __PARALLAX_BACKGROUND_H__
#define __PARALLAX_BACKGROUND_H__

#include "ScrollingBackground.h"

#define MAX_LAYERS 8

class ParallaxBackground
{
public:
	cocos2d::Node* node;

	ParallaxBackground();
	~ParallaxBackground();

	void Init(float screenWidth, float screenHeight);
	void Update(float deltaTime);

	bool AddBackground(std::string name, std::string path);
	void SetStartingBackground(std::string name);
	void QueueBackground(std::string name);
	void SetScrollSpeed(float _speed);
	void SetScrollSpeedByTime(float _seconds);

private:
	std::vector<std::string> backgroundNames;

	float seconds;
	float scrollSpeed;
	ScrollingBackground* backgrounds[MAX_LAYERS];
};


#endif // !__PARALLAX_BACKGROUND_H__


