#include "ParallaxBackground.h"
#include "cocos2d.h"
#include "math/CCMath.h"

using namespace cocos2d;

ParallaxBackground::ParallaxBackground()
{
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		backgrounds[i] = new ScrollingBackground();
	}
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

	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		backgrounds[i]->Init(screenWidth, screenHeight);
		node->addChild(backgrounds[i]->node[0]);
		node->addChild(backgrounds[i]->node[1]);
	}
}

void ParallaxBackground::Update(float deltaTime)
{
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		backgrounds[i]->Update(deltaTime);
	}
}

bool ParallaxBackground::AddBackground(std::string name, std::string path)
{
	bool exist = false;
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		if (backgrounds[i]->AddImage(name, path + name + "_" + std::to_string(i) + ".png"))
			exist = true;
	}

	if (exist)
	{
		backgroundNames.push_back(name);
	}
	
	return exist;
}

void ParallaxBackground::SetStartingBackground(std::string name)
{
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		backgrounds[i]->SetStartingBackground(name);
	}
}

void ParallaxBackground::QueueBackground(std::string name)
{
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		if (!backgrounds[i]->QueueNextBackground(name))
			backgrounds[i]->StopBackground();
	}
}

void ParallaxBackground::SetScrollSpeed(float _speed)
{
	//scrollSpeed = std::pow(_speed, 1.f / (float)MAX_LAYERS);
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		//backgrounds[i]->SetScrollSpeed(std::pow(scrollSpeed, i));
		backgrounds[i]->SetScrollSpeed(_speed / (8 - i));
	}
}

void ParallaxBackground::SetScrollSpeedByTime(float _seconds)
{
	seconds = _seconds;
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		if (backgrounds[i])
			backgrounds[i]->SetScrollSpeedByTime(_seconds);
	}
}
