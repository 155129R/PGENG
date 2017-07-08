#ifndef __SCROLLING_BACKGROUND_H__
#define __SCROLLING_BACKGROUND_H__

#include <vector>
#include <queue>
#include <map>
#include <string>

#include "cocos2d.h"

using namespace cocos2d;

class ScrollingBackground
{
public:
	Node* node[2];

	ScrollingBackground();
	~ScrollingBackground();

	void Init(int _screenWidth, int _screenHeight);
	void Update(float _deltaTime);
	
	void SetScreenSize(int _screenWidth, int _screenHeight);
	void SetStartingBackground(std::string name);
	void SetScrollSpeed(float _scrollSpeed);
	void SetScrollSpeedByTime(float seconds);
	bool AddImage(std::string name, std::string fileLocation);
	bool QueueNextBackground(std::string name);
	
	void StopBackground();
private:
	enum STATE
	{
		RUN,
		PRE_STOP,
		STOP,
		MAX,
	} state;

	std::map<std::string, Texture2D*> imageMap;
	std::queue<std::map<std::string, Texture2D*>::iterator> imageQueue;
	Sprite* buffers[2];

	float time;

	void(ScrollingBackground::*stateFunc[MAX])(float);

	std::string currentActiveName;
	Size imageSize;
	float screenWidth;
	float screenHeight;
	float scrollSpeed;
	int currIndex;
	int nextIndex;

	void ScrollBackgrounds(float _deltaTime);
	bool CheckScrollLimit();
	void SwapIndex();
	void SwapZOrder();
	void SwapNextFromQueue();
	void LoadTextureToBuffer(int index, Texture2D* texture);
	bool CheckNextEqualCurrent();
	void ResetNextStartPosition();

	void Run(float _deltaTime);
	void PreStop(float _deltaTime);
	void Stop(float _deltaTime);
};

#endif // !__SCROLLING_BACKGROUND_H__

