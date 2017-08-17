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

	void AddBackground(std::string name, int layers);
	void ChangeBackground(std::string name);
	void TransitionBackground(std::string name);
	void SetScrollSpeed(float _speed);

	inline void SetFadeTime(float _time){ fadeTime = _time; }
	inline float GetFadeTime(){ return fadeTime; }

private:
	struct BackgroundInfo
	{
		std::vector<Texture2D*> storage;
		int layers;
	};

	typedef enum FADE_STATES
	{
		FADE_OUT,
		FADE_IN,
		MAX,
	};

	std::map<std::string, BackgroundInfo> backgroundStorage;
	Sprite* transitionSprite;
	BackgroundInfo* targetBackground;

	std::string activeBackgroundName;

	float fadeTime;
	float scrollSpeed;
	FADE_STATES fadeState;
	bool transition;

	void(ParallaxBackground::*fadeFunc[MAX])(float);
	void FadeOut(float _deltaTime);
	void FadeIn(float _deltaTime);
	
	ScrollingBackground* backgrounds[MAX_LAYERS];
};


#endif // !__PARALLAX_BACKGROUND_H__


