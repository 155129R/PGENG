#include "ScrollingBackground.h"

#define BUFFER_LENGTH 2
#define BIAS 0.5

ScrollingBackground::ScrollingBackground()
{
	imageQueue = nullptr;
}

ScrollingBackground::~ScrollingBackground()
{

}

void ScrollingBackground::Init(int _screenWidth, int _screenHeight)
{
	currIndex = 0;
	nextIndex = 1;
	scrollSpeed = 0.f;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	buffers[0] = Sprite::create();
	buffers[1] = Sprite::create();
	buffers[1]->setPosition(_screenWidth, 0);

	currentActiveName = "";

	node = Node::create();
	node->setName("scrollingBackground");
	node->setPosition(0, 0);
	node->addChild(buffers[0], 0);
	node->addChild(buffers[1], 1);

	buffers[currIndex]->init();
	buffers[currIndex]->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
	buffers[currIndex]->setPosition(0, 0);
	buffers[currIndex]->setContentSize(Size(screenWidth, screenHeight));

	buffers[nextIndex]->init();
	buffers[nextIndex]->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
	buffers[nextIndex]->setPosition(screenWidth, 0);
	buffers[nextIndex]->setContentSize(Size(screenWidth, screenHeight));
}

void ScrollingBackground::Update(float _deltaTime)
{
	ScrollBackgrounds(_deltaTime);
	if (CheckScrollLimit())
	{
		SwapIndex();
		if (imageQueue != nullptr)
		{
			SetBackground(imageQueue, nextIndex);
			imageQueue = nullptr;
		}
		else if (buffers[nextIndex]->getTexture() != buffers[currIndex]->getTexture())
		{
			SetBackground(buffers[currIndex]->getTexture(), nextIndex);
		}
		ResetNextStartPosition();
	}
}

void ScrollingBackground::SetScreenSize(int _screenWidth, int _screenHeight)
{
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
}

void ScrollingBackground::ChangeBackground(Texture2D* _texture)
{
	SetBackground(_texture, currIndex);
	SetBackground(_texture, nextIndex);

	ResetNextStartPosition();
}

void ScrollingBackground::QueueBackground(Texture2D* _texture)
{
	imageQueue = _texture;
}

void ScrollingBackground::SetScrollSpeed(float _scrollSpeed)
{
	scrollSpeed = _scrollSpeed;
}

void ScrollingBackground::ScrollBackgrounds(float _deltaTime)
{
	for (int i = 0; i < BUFFER_LENGTH; ++i)
	{
		Sprite *sprite = buffers[i];
		float dir = -1;
		sprite->setPositionX(sprite->getPositionX() + dir * scrollSpeed * _deltaTime);
	}
}

bool ScrollingBackground::CheckScrollLimit()
{
	auto pos = buffers[currIndex]->getPosition();
	
	Size size = buffers[currIndex]->getContentSize();

	if (pos.x < -size.width)
		return true;
	return false;
}

void ScrollingBackground::SwapIndex()
{
	int temp = currIndex;
	currIndex = nextIndex;
	nextIndex = temp;

	SwapZOrder();
}

void ScrollingBackground::SwapZOrder()
{
	buffers[currIndex]->setPositionZ(0.1f);
	buffers[nextIndex]->setPositionZ(0);
}

void ScrollingBackground::ResetNextStartPosition()
{
	auto currPos = buffers[currIndex]->getPosition();
	Size nextSize = buffers[nextIndex]->getContentSize();
	Size currSize = buffers[currIndex]->getContentSize();
	buffers[nextIndex]->setPosition(currPos.x + currSize.width - BIAS, 0.0f);
}

void ScrollingBackground::RescaleSpriteBuffer(int index)
{
	if (index < 0 || index > 1)
	{
		CCLOG("Index: %i, is less than minimum %i or more than maximum %i\n", index, 0, 1);
		return;
	}

	float imageHeight = buffers[index]->getContentSize().height;
	float scaleFactor = screenHeight / imageHeight;
	buffers[index]->setScale(scaleFactor);
}

void ScrollingBackground::SetBackground(Texture2D* texture, int index)
{
	buffers[index]->setTexture(texture);

	if (texture == nullptr)
		return;

	Rect rect = Rect::ZERO;
	rect.size = texture->getContentSize();

	buffers[index]->setTextureRect(rect);
	buffers[index]->setScale(screenHeight / rect.size.height);
}