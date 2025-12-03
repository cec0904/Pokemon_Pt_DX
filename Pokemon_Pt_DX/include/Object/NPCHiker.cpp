#include "NPCHiker.h"
#include "../Scene/Scene.h"
#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/SpriteComponent.h"
#include "SceneObject.h"

#include "../Component/MovementComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"

#include "../Animation/Animation2D.h"
#include "../Asset/Animation/Animation2DData.h"
#include "../Asset/Texture/Texture.h"


#include "../Share/Log.h"

CNPCHiker::CNPCHiker()
{
}

CNPCHiker::CNPCHiker(const CNPCHiker& Obj)
{
}

CNPCHiker::CNPCHiker(CNPCHiker&& Obj)
{
}

CNPCHiker::~CNPCHiker()
{
}

bool CNPCHiker::Init()
{
	if (!CNPCManager::Init())
	{
		return false;
	}

	mRoot = CreateComponent<CSpriteComponent>();
	mBody = CreateComponent<CColliderOBB2D>();

	mMovement = CreateComponent<CMovementComponent>();

	mRoot->SetTexture("Hiker");
	// 중심점
	mRoot->SetPivot(0.5f, 0.5f);
	// 투명도
	// mRoot->SetOpacity(1.f);

	mMovement->SetUpdateComponent(mRoot);
	
	
	

	SetRootComponent(mRoot);

	mRoot->AddChild(mBody);
	mBody->SetBoxSize(100.f, 100.f);

	mBody->SetCollisionProfile("NPC");

	mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
	mAnimation->AddSequence("Hiker", 1.f, 1.f, true, false);
	mRoot->SetFlip(false);
	mAnimation->ChangeAnimation("Hiker");


	

	





	return true;
}
void CNPCHiker::Update(float DeltaTime)
{
	CNPCManager::Update(DeltaTime);

	FVector3D StartPos = mRoot->GetWorldPosition(0.f, 300.f);
	mRoot->SetWorldPos(StartPos + mRootComponent->GetAxis(EAxis::X) * mSpeed * DeltaTime);
}

