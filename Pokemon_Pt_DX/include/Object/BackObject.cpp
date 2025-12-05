#include "BackObject.h"
#include "../Component/SpriteComponent.h"

CBackObject::CBackObject()
{
}

CBackObject::CBackObject(const CBackObject& Obj)
{
}

CBackObject::CBackObject(CBackObject&& Obj)
{
}

CBackObject::~CBackObject()
{
}

bool CBackObject::Init()
{
	CSceneObject::Init();

	mRoot = CreateComponent<CSpriteComponent>("BackGround");

	mRoot->SetTexture("BackGround", TEXT("Texture/Pokemon/BackGround/Twinleaf_Town.png"), 0);
	mRoot->SetTint(1.f, 1.f, 1.f);
	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetOpacity(1.f);

	SetRootComponent(mRoot);

	return true;
}