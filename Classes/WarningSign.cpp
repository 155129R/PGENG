#include "WarningSign.h"

void WarningSign::Init(const char* _srcImg, const char* _name, float _x, float _y)
{
	m_mainSprite = Sprite::create(_srcImg);
	m_mainSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_mainSprite->setPosition(_x, _y);
	m_mainSprite->setName(_name);
	m_dir = 0;
	m_speed = 0.0f;

	mLoc.set(.5f, .5f);
	mLocInc.set(.005f, .01f);
	entityType = EntityType::WARNINGSIGN;

	//For Animation Purpose
	warningScale = 1.0f;
	scaleLimit = 2.0f;
	scaleUp = true;
	scaleDown = false;

	isAlive = false;

	charEffect = new GLProgram();
	charEffect->initWithFilenames("Basic.vsh", "CharEffect.fsh");
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	charEffect->link();
	charEffect->updateUniforms();
}

void WarningSign::SetType(WarningType mytype)
{
	warningType = mytype;
}

WarningSign::WarningType WarningSign::GetType()
{
	return warningType;
}


void WarningSign::Update(float _delta)
{
	if (isAlive)
	{
		if (warningScale > scaleLimit)
		{
			scaleUp = false;
			scaleDown = true;
		}
		else if (warningScale <= 1.0f)
		{
			scaleDown = false;
			scaleUp = true;
		}

		if (scaleUp)
			warningScale += 0.1f;
		else
			warningScale -= 0.1f;
		
		m_mainSprite->setScale(warningScale,warningScale);
		m_mainSprite->setVisible(true);

	}
	else
	{
		m_mainSprite->setScale(1, 1);
		m_mainSprite->setVisible(false);
	}
}

