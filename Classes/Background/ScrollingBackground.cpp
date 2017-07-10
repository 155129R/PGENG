#include "ScrollingBackground.h"

#define BUFFER_LENGTH 2
#define BIAS 0.5

ScrollingBackground::ScrollingBackground()
{
	stateFunc[RUN] = &ScrollingBackground::Run;
	stateFunc[PRE_STOP] = &ScrollingBackground::PreStop;
	stateFunc[STOP] = &ScrollingBackground::Stop;
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
	state = RUN;

	node[0] = Node::create();
	node[1] = Node::create();
	node[0]->setName("scrollingBackground_1");
	node[1]->setName("scrollingBackground_2");
	node[0]->setPosition(0, 0);
	node[1]->setPosition(0, 0);
	node[0]->addChild(buffers[0], 0);
	node[1]->addChild(buffers[1], 0);
}

void ScrollingBackground::Update(float _deltaTime)
{
	(this->*stateFunc[state])(_deltaTime);
}

void ScrollingBackground::SetScreenSize(int _screenWidth, int _screenHeight)
{
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
}

void ScrollingBackground::SetStartingBackground(std::string name)
{
	std::map<std::string, Texture2D*>::iterator it = imageMap.find(name);
	if (it != imageMap.end())
	{
		Texture2D* texture = it->second;
		currentActiveName = name;
		LoadTextureToBuffer(currIndex, texture);
		LoadTextureToBuffer(nextIndex, texture);

		Size size = buffers[currIndex]->getContentSize();
		imageSize = size;
		buffers[currIndex]->setPosition(size.width * .5f, size.height * .5f);
		ResetNextStartPosition();

		state = RUN;
	}
}

void ScrollingBackground::SetScrollSpeed(float _scrollSpeed)
{
	scrollSpeed = _scrollSpeed;
}

void ScrollingBackground::SetScrollSpeedByTime(float seconds)
{
	scrollSpeed = imageSize.width / seconds;
	int a = 0;
}

bool ScrollingBackground::AddImage(std::string name, std::string fileLocation)
{
	bool exist = CCFileUtils::getInstance()->isFileExist(fileLocation);

	if (!exist)
		return exist;

	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fileLocation);
	imageMap.insert(std::pair<std::string, Texture2D*>(name, texture));
	return exist;
}

bool ScrollingBackground::QueueNextBackground(std::string name)
{
	state = RUN;
	std::map<std::string, Texture2D*>::iterator it = imageMap.find(name);
	std::map<std::string, Texture2D*>::iterator end = imageMap.end();

	if (it == end)
	{
		log("FAILED");
		return false;
	}

	imageQueue.push(it);
	return true;
}

void ScrollingBackground::StopBackground()
{
	while (!imageQueue.empty())
	{
		imageQueue.pop();
	}

	state = PRE_STOP;
	currentActiveName = "";
}

void ScrollingBackground::ScrollBackgrounds(float _deltaTime)
{
	for (int i = 0; i < BUFFER_LENGTH; ++i)
	{
		Sprite *sprite = buffers[i];
		auto dir = Vec2(-1, 0);
		auto moveEvent = MoveBy::create(0.f, dir * scrollSpeed * _deltaTime);
		sprite->runAction(moveEvent);
	}
}

bool ScrollingBackground::CheckScrollLimit()
{
	auto pos = buffers[currIndex]->getPosition();
	
	Size size = buffers[currIndex]->getContentSize();
	float halvedSize = -size.width * .5f;

	if (pos.x <= halvedSize)
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

void ScrollingBackground::SwapNextFromQueue()
{
	Texture2D *texture = imageQueue.front()->second;
	currentActiveName = imageQueue.front()->first;
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
	imageSize = newSize;
	rect.size = newSize;
	buffers[index]->initWithTexture(texture);
	buffers[index]->setContentSize(newSize);
	Vec2 position = buffers[index]->getPosition();
	buffers[index]->setPosition(position.x, newSize.height * .5f);
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
	float cutoff = currSize.width * 0.5f - buffers[currIndex]->getPosition().x;

	pos.x = screenWidth + nextSize.width * .5f + excess - cutoff - BIAS;
	buffers[nextIndex]->setPosition(pos);
}

void ScrollingBackground::Run(float _deltaTime)
{
	ScrollBackgrounds(_deltaTime);
	if (CheckScrollLimit())
	{
		SwapIndex();
		if (!imageQueue.empty())
			SwapNextFromQueue();
		else
			LoadTextureToBuffer(nextIndex, buffers[currIndex]->getTexture());

		ResetNextStartPosition();
	}
}

void ScrollingBackground::PreStop(float _deltaTime)
{
	ScrollBackgrounds(_deltaTime);
	if (CheckScrollLimit())
	{
		SwapIndex();
		if (CheckScrollLimit())
			state = STOP;
	}
}

void ScrollingBackground::Stop(float _deltaTime)
{
}
