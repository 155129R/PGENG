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
	Node* node;

	ScrollingBackground();
	~ScrollingBackground();

	void Init(int _screenWidth, int _screenHeight);
	void Update(float _deltaTime);
	
	void SetScreenSize(int _screenWidth, int _screenHeight);
	void ChangeBackground(Texture2D* _texture);
	void QueueBackground(Texture2D* _texture);
	void SetScrollSpeed(float _scrollSpeed);
	
private:
	Sprite* buffers[2];
	Texture2D* imageQueue;

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
	void ResetNextStartPosition();
	void RescaleSpriteBuffer(int index);
	void SetBackground(Texture2D* texture, int index);
};

#endif // !__SCROLLING_BACKGROUND_H__

