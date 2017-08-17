#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "ui/UIImageView.h"
#include "ui\UISlider.h"

using namespace cocos2d;

class Projectile;

class SettingScene : public cocos2d::Layer
{
public:
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	static cocos2d::Scene* createScene();
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(SettingScene);

	std::vector<ui::ImageView*> ImageList;
private:
	//for getting window screen
	Size playingSize;
	ui::Slider *backgroundSlider;
	ui::Slider *effectSlider;
	
	void InitButtons();
};


#endif // !__GAME_SCENE_H__
