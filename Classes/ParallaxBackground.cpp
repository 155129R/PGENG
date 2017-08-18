#include "ParallaxBackground.h"
#include "cocos2d.h"
#include "math/CCMath.h"

using namespace cocos2d;

#define BACKGROUND_PATH "Background/"

ParallaxBackground::ParallaxBackground()
{
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		backgrounds[i] = new ScrollingBackground();
	}

	transitionSprite = Sprite::create();
	targetBackground = nullptr;

	fadeFunc[FADE_STATES::FADE_OUT] = &ParallaxBackground::FadeOut;
	fadeFunc[FADE_STATES::FADE_IN] = &ParallaxBackground::FadeIn;
}

ParallaxBackground::~ParallaxBackground()
{
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		delete backgrounds[i];
		backgrounds[i] = nullptr;
	}
}

void ParallaxBackground::Init(float screenWidth, float screenHeight)
{
	node = Node::create();
	node->setName("ParallaxBackground");
	
	transitionSprite->initWithFile(BACKGROUND_PATH "black.png");
	transitionSprite->setPosition(0.0f, 0.0f);
	transitionSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
	transitionSprite->setScale(screenWidth / transitionSprite->getContentSize().width, screenHeight / transitionSprite->getContentSize().height);
	transitionSprite->setOpacity(0);
	node->addChild(transitionSprite, MAX_LAYERS - 1);

	backgrounds[0]->Init(screenWidth, screenHeight);
	node->addChild(backgrounds[0]->node, MAX_LAYERS);

	fadeState = FADE_STATES::FADE_OUT;
	transition = false;

	for (int i = MAX_LAYERS; i > 1; --i)
	{
		backgrounds[i - 1]->Init(screenWidth, screenHeight);
		node->addChild(backgrounds[i - 1]->node, MAX_LAYERS - i);
	}
}

void ParallaxBackground::Update(float deltaTime)
{
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		backgrounds[i]->Update(deltaTime);
	}

	if (transition)
	{
		(this->*fadeFunc[fadeState])(deltaTime);
	}
}

void ParallaxBackground::AddBackground(std::string name, int layers)
{
	if (layers < 0 || layers > MAX_LAYERS)
	{
		//CCLOG("Layers: %i, is less than minimum %i or more than maximum %i\n", layers, 0, MAX_LAYERS);
		return;
	}

	std::string format = ".png";
	BackgroundInfo info;
	info.layers = layers;

	for (int i = 0; i < layers; ++i)
	{
		std::stringstream ss;
		ss << i;
		std::string fullFileName = (name + '_' + ss.str() + format);
		Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(BACKGROUND_PATH + fullFileName);
		info.storage.push_back(texture);
	}

	backgroundStorage.insert(std::pair<std::string, BackgroundInfo>(name, info));
}

void ParallaxBackground::ChangeBackground(std::string name)
{
	if (activeBackgroundName == name)
		return;

	activeBackgroundName = name;

	std::map<std::string, BackgroundInfo>::iterator it = backgroundStorage.find(name);
	if (it == backgroundStorage.end())
	{
		//CCLOG("Background: %s does not exist", name);
		return;
	}

	BackgroundInfo* info = &it->second;
	for (int i = 0; i < info->layers; ++i)
	{
		backgrounds[i]->ChangeBackground(info->storage[i]);
	}
}

void ParallaxBackground::TransitionBackground(std::string name)
{
	if (activeBackgroundName == name)
		return;

	activeBackgroundName = name;

	std::map<std::string, BackgroundInfo>::iterator it = backgroundStorage.find(name);
	if (it == backgroundStorage.end())
	{
		//CCLOG("Background: %s does not exist", name);
		return;
	}

	transition = true;
	BackgroundInfo* info = &it->second;
	targetBackground = info;
	backgrounds[0]->QueueBackground(info->storage[0]);
}

void ParallaxBackground::FadeOut(float _deltaTime)
{
	int opacity = transitionSprite->getOpacity();
	if (opacity < 255)
	{
		opacity = opacity + (_deltaTime / fadeTime) * 255;
		if (opacity > 255)
			opacity = 255;
		transitionSprite->setOpacity(opacity);
	}
	else
	{
		transitionSprite->setOpacity(255);
		fadeState = FADE_STATES::FADE_IN;
		for (int i = 1; i < MAX_LAYERS; ++i)
		{
			if (i < targetBackground->layers)
				backgrounds[i]->ChangeBackground(targetBackground->storage[i]);
			else
				backgrounds[i]->ChangeBackground(nullptr);
		}
	}
}

void ParallaxBackground::FadeIn(float _deltaTime)
{
	int opacity = transitionSprite->getOpacity();
	if (opacity > 0)
	{
		opacity = opacity - (_deltaTime / fadeTime) * 255;
		if (opacity < 0)
			opacity = 0;
		transitionSprite->setOpacity(opacity);
	}
	else
	{
		transitionSprite->setOpacity(0);
		fadeState = FADE_STATES::FADE_OUT;
		transition = false;
	}
}

void ParallaxBackground::SetScrollSpeed(float _speed)
{
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		backgrounds[i]->SetScrollSpeed(_speed / (i + 1));
	}
}