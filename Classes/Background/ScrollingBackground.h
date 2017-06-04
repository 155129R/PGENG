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
	float scrollSpeed;
	Sprite* buffers[2];

	ScrollingBackground();
	ScrollingBackground(int _screenWidth, int _screenHeight, float _scrollSpeed);
	~ScrollingBackground();

	void Init(int _screenWidth, int _screenHeight, float _scrollSpeed);
	void Update(float _deltaTime);
	void SetScreenSize(int _screenWidth, int _screenHeight);
	void SetStartingBackground(std::string name);
	void AddImage(std::string name, std::string fileLocation);
	void AddImageContainer(std::vector<Texture2D*> container);
	void QueueNextBackground(int index);
	void QueueNextBackground(std::string name);

private:
	std::map<std::string, Texture2D*> imageMap;
	std::vector<Texture2D*> imageContainer;
	std::queue<Texture2D*> imageQueue;

	float screenWidth;
	float screenHeight;
	int currIndex;
	int nextIndex;

	void ScrollBackgrounds(float _deltaTime);
	bool CheckCurrentLimit();
	void SwapIndex();
	void SwapNextFromQueue();
	void LoadTextureToBuffer(int index, Texture2D* texture);
	bool CheckNextEqualCurrent();
	void ResetNextStartPosition();
};

#endif // !__SCROLLING_BACKGROUND_H__

