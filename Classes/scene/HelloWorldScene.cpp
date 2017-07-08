#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Screen size
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	// Halved of screen height
	float halvedHeight = playingSize.height * .5f;

	// Node for items
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");
	nodeItems->setPosition(0, halvedHeight);
	this->addChild(nodeItems, 1);

	// Reference sprite to get height and width from
	auto referenceSprite = Sprite::create("ZigzagGrass_Mud_Round.png");
	float count = std::ceil(playingSize.width / referenceSprite->getContentSize().width);

	// Variable used to render tiles
	int sX = 0;
	int sY = 0;

	// Render amount of tiles according to screen width
	for (int i = 0; i < count; ++i)
	{
		auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");

		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(sX, sY);
		sX += sprite->getContentSize().width;
		nodeItems->addChild(sprite, 0);
	}
	
	auto playerNode = Node::create();
	playerNode->setName("playerNode");
	playerNode->setPosition(0, 0);
	this->addChild(playerNode, 1);

	mainChar.Init("Blue_Front1.png", "Player", 100, halvedHeight + referenceSprite->getContentSize().height);
	playerNode->addChild(mainChar.getSprite(), 1);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	proPostProcess = GLProgram::createWithFilenames("shader\\Basic.vsh", "shader\\GreyScale.fsh");
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);

	proPostProcess->link();
	proPostProcess->updateUniforms();

	rendtex = RenderTexture::create(visibleSize.width, visibleSize.height);
	rendtex->retain();

	rendtexSprite = Sprite::createWithTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setTextureRect(Rect(0, 0, rendtexSprite->getTexture()->getContentSize().width,
		rendtexSprite->getTexture()->getContentSize().height));
	rendtexSprite->setAnchorPoint(Point::ZERO);
	rendtexSprite->setPosition(Point::ZERO);
	rendtexSprite->setFlippedY(true);
	rendtexSprite->setGLProgram(proPostProcess);
	this->addChild(rendtexSprite, 2);

	this->scheduleUpdate();

    return true;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		//CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 255, 255)));
		SceneManager::getInstance()->runSceneWithType(CONSTANTS::SceneType::GAMEPLAY);
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
}

void HelloWorld::onMouseDown(Event* event)
{
	EventMouse* mouse = (EventMouse*)event;
	float x = mouse->getCursorX();
	float y = mouse->getCursorY();
}

void HelloWorld::update(float _delta)
{
	auto cam = Camera::getDefaultCamera();
	cam->setPosition(mainChar.getPosition());

	rendtex->beginWithClear(.0f, .0f, .0f, .0f);
	this->visit();
	rendtex->end();
	rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setGLProgram(proPostProcess);

	mainChar.Update(_delta);

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
