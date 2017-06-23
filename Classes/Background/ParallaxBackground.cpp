#include "ParallaxBackground.h"
#include "cocos2d.h"

using namespace cocos2d;

ParallaxBackground::ParallaxBackground()
{
}


ParallaxBackground::~ParallaxBackground()
{
}

void ParallaxBackground::Init(float _seconds)
{
	node = Node::create();
	node->setName("ParallaxBackground");

	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		backgrounds[i] = nullptr;
	}

	seconds = _seconds;
}

void ParallaxBackground::Update(float deltaTime)
{
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		if (backgrounds[i])
			backgrounds[i]->Update(deltaTime);
	}
}

bool ParallaxBackground::AddBackground(int layer, ScrollingBackground* background)
{
	if (layer < 0 || layer >= MAX_LAYERS)
		return false;

	if (backgrounds[layer])
	{
		RemoveBackground(layer);
	}

	node->addChild(background->node[0], layer);
	node->addChild(background->node[1], layer);

	background->node[0]->setName("ScrollingBackground1_" + std::to_string(layer));
	background->node[0]->setName("ScrollingBackground2_" + std::to_string(layer));

	backgrounds[layer] = background;
	SetScrollSpeedByTime(seconds);
	return true;
}

void ParallaxBackground::RemoveBackground(int layer)
{
	node->removeChild(backgrounds[layer]->node[0]);
	node->removeChild(backgrounds[layer]->node[1]);
	delete backgrounds[layer];
	backgrounds[layer] = nullptr;
}

ScrollingBackground& ParallaxBackground::GetBackground(int layer)
{
	return *backgrounds[layer];
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
