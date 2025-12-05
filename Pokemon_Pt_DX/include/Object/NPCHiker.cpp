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

	
	mRoot->SetTexture("Hiker", TEXT("Texture/Pokemon/NPC/Hiker/Hiker_0.png"), 0);
	// 중심점
	mRoot->SetPivot(0.5f, 0.5f);
	// 투명도
	// mRoot->SetOpacity(1.f);

	mMovement->SetUpdateComponent(mRoot);
	// mMovement->SetMoveAxis(EAxis::X);
	// mMovement->SetMoveSpeed(200.f);
	
	
	

	SetRootComponent(mRoot);

	mRoot->AddChild(mBody);
	mBody->SetBoxSize(100.f, 100.f);
	mRoot->SetWorldScale(100.f, 100.f, 1.f);

	mBody->SetCollisionProfile("NPC");

	
	mRoot->SetFlip(false);


	return true;
}
void CNPCHiker::Update(float DeltaTime)
{
	CNPCManager::Update(DeltaTime);

	if (!bSetStartPos)
	{
		StartPos = mRoot->GetWorldPosition();
		bSetStartPos = true;
	}
	FVector3D CurrentPos = mRoot->GetWorldPosition();


	if (CurrentPos.x <= StartPos.x)
	{
		Dir = 1.f; 
	}
	else if (CurrentPos.x >= StartPos.x + MoveRange)
	{
		Dir = -1.f; 
	}


	TargetPos = CurrentPos + mRootComponent->GetAxis(EAxis::X) * mSpeed * DeltaTime * Dir;

	mRoot->SetWorldPos(TargetPos);

	

}

