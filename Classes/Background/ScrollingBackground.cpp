#include "ScrollingBackground.h"

#define BUFFER_LENGTH 2
#define BIAS 5

ScrollingBackground::ScrollingBackground()
{
	Init(0.f, 0.f, 0.f);
}

ScrollingBackground::ScrollingBackground(int _screenWidth, int _screenHeight, float _scrollSpeed)
{
	Init(_screenWidth, _screenHeight, _scrollSpeed);
}

ScrollingBackground::~ScrollingBackground()
{

}

void ScrollingBackground::Init(int _screenWidth, int _screenHeight, float _scrollSpeed)
{
	currIndex = 0;
	nextIndex = 1;
	scrollSpeed = _scrollSpeed;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	buffers[0] = Sprite::create();
	buffers[1] = Sprite::create();
	buffers[1]->setPosition(_screenWidth, 0);
}

void ScrollingBackground::Update(float _deltaTime)
{
	ScrollBackgrounds(_deltaTime);
	if (CheckCurrentLimit())
	{
		SwapIndex();
		if (!imageQueue.empty())
		{
			SwapNextFromQueue();
		}
		else if (!CheckNextEqualCurrent())
		{
			LoadTextureToBuffer(nextIndex, buffers[currIndex]->getTexture());
		}
		ResetNextStartPosition();
	}
}

void ScrollingBackground::SetScreenSize(int _screenWidth, int _screenHeight)
{
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
}

void ScrollingBackground::SetStartingBackground(std::string name)
{
	Texture2D* texture = imageMap.find(name)->second;
	LoadTextureToBuffer(currIndex, texture);
	LoadTextureToBuffer(nextIndex, texture);
	
	Size size = buffers[currIndex]->getContentSize();
	buffers[currIndex]->setPosition(size.width * .5f, size.height * .5f);
	ResetNextStartPosition();
}

void ScrollingBackground::AddImage(std::string name, std::string fileLocation)
{
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fileLocation);
	imageMap.insert(std::pair<std::string, Texture2D*>(name, texture));
}

void ScrollingBackground::AddImageContainer(std::vector<Texture2D*> container)
{
	imageContainer = container;
}

void ScrollingBackground::QueueNextBackground(int index)
{
	imageQueue.push(imageContainer[index]);
}

void ScrollingBackground::QueueNextBackground(std::string name)
{
	imageQueue.push(imageMap.find(name)->second);
}

void ScrollingBackground::ScrollBackgrounds(float _deltaTime)
{
	for (int i = 0; i < BUFFER_LENGTH; ++i)
	{
		Sprite *sprite = buffers[i];
		auto dir = Vec2(-1, 0);
		auto moveEvent = MoveBy::create(_deltaTime, dir * scrollSpeed);
		sprite->runAction(moveEvent);
	}
}

bool ScrollingBackground::CheckCurrentLimit()
{
	auto pos = buffers[currIndex]->getPosition();
	Size size = buffers[currIndex]->getContentSize();
	float halvedSize = -size.width * .5f;
	if (pos.x < halvedSize + BIAS)
	{
		return true;
	}
	return false;
}

void ScrollingBackground::SwapIndex()
{
	int temp = currIndex;
	currIndex = nextIndex;
	nextIndex = temp;
}

void ScrollingBackground::SwapNextFromQueue()
{
	Texture2D *texture = imageQueue.front();
	imageQueue.pop();
	LoadTextureToBuffer(nextIndex, texture);
}

void ScrollingBackground::LoadTextureToBuffer(int index, Texture2D* texture)
{
	Rect rect = Rect::ZERO;
	Size textureSize = texture->getContentSize();
	Size newSize = Size::ZERO;
	newSize.height = screenHeight;
	newSize.width = (newSize.height / textureSize.height) * textureSize.width;
	rect.size = newSize;

	buffers[index]->initWithTexture(texture);
	buffers[index]->setContentSize(newSize);
	buffers[index]->setPosition(0, newSize.height * .5f);
}

bool ScrollingBackground::CheckNextEqualCurrent()
{
	return buffers[currIndex]->getTexture() == buffers[nextIndex]->getTexture();
}

void ScrollingBackground::ResetNextStartPosition()
{
	auto pos = buffers[nextIndex]->getPosition();
	Size nextSize = buffers[nextIndex]->getContentSize();
	Size currSize = buffers[currIndex]->getContentSize();
	float excess = currSize.width - screenWidth;
	pos.x = screenWidth + nextSize.width * .5f + excess;
	buffers[nextIndex]->setPosition(pos);
}
