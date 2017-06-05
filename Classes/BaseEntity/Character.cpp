#include "Character.h"
#include "scene\\HelloWorldScene.h"


void Character::Init(const char* _srcImg, const char* _name, float _x, float _y)
{
	m_mainSprite = Sprite::create(_srcImg);
	m_mainSprite->setAnchorPoint(Vec2(0, 0));
	m_mainSprite->setPosition(_x, _y);
	m_mainSprite->setName(_name);
	m_dir = 0;
	m_speed = 1.f;

	mLoc.set(.5f, .5f);
	mLocInc.set(.005f, .01f);

	entityType = EntityType::CHARACTER;

	animator.animType = Animator::NIL;

	isAlive = true;

	charEffect = new GLProgram();
	charEffect->initWithFilenames("Basic.vsh", "CharEffect.fsh");
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	charEffect->link();
	charEffect->updateUniforms();

	Stop();
}

void Character::MoveChar(int _dir)
{
	m_dir = _dir;

	if (m_dir == -1)
	{
		animator.animType = Animator::PLAYERJUMP;
		animator.PlayAnimation(animator.animType, (BaseEntity*)this);
	}
	else
	{
		animator.animType = Animator::PLAYERRUN;
		animator.PlayAnimation(animator.animType, (BaseEntity*)this);
	}
}

void Character::MoveCharByCoord(float _x, float _y)
{
	/*m_dir = 0;
	m_mainSprite->stopAllActions();
	float diffX = _x - m_mainSprite->getPosition().x;
	float diffY = _y - m_mainSprite->getPosition().y;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveTo::create(vec.length() / m_speed, Vec2(_x, _y));
	m_mainSprite->runAction(moveEvent);*/
	m_mainSprite->stopAllActions();
	float diffX = _x - m_mainSprite->getPosition().x;
	float diffY = _y - m_mainSprite->getPosition().y;
	auto vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * m_speed, vec);

	auto callbackStop = CallFunc::create([]()
	{
		auto scene = Director::getInstance()->getRunningScene();
		auto layer = scene->getChildByTag(999);
		HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
		if (helloLayer != NULL)
			helloLayer->getChar()->Stop();
	});
	auto seq = Sequence::create(moveEvent, callbackStop, nullptr);
	m_mainSprite->runAction(seq);

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	Animate* animate = Animate::create(animation);
	m_mainSprite->runAction(animate);
}

void Character::Update(float _dt)
{
	if (m_dir != 0)
	{
		auto moveEvent = MoveBy::create(0.f, Vec2(m_dir, 0.f) * m_speed);
		m_mainSprite->runAction(moveEvent);
	}
	printf("hello");
	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(charEffect);
	m_mainSprite->setGLProgram(charEffect);
	m_mainSprite->setGLProgramState(state);
	state->setUniformVec2("loc", mLoc);
}

void Character::Stop(void)
{
	m_dir = 0;
	m_mainSprite->stopAllActions();

	animator.animType = Animator::PLAYERRUN;
	animator.PlayAnimation(animator.animType, (BaseEntity*)this);
}

void Character::MoveRight()
{
	MoveChar(1);
}

void Character::MoveLeft()
{
	MoveChar(-1);
}