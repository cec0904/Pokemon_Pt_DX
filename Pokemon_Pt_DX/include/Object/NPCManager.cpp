#include "NPCManager.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "../Component/SpriteComponent.h"
#include "../Animation/Animation2D.h"
#include "../Asset/Animation/Animation2DData.h"
#include "../Asset/Texture/Texture.h"

#include "../Scene/Scene.h"
#include "../Share/Log.h"


//문자열 
#include <sstream>

CNPCManager::CNPCManager()
{
}

CNPCManager::CNPCManager(const CNPCManager& Obj)
{
}

CNPCManager::CNPCManager(CNPCManager&& Obj)
{
}

CNPCManager::~CNPCManager()
{
}

void CNPCManager::CollisionNPC(const FVector3D& HitPont, CColliderBase* Dest)
{
}

void CNPCManager::CollisionNPCEnd(CColliderBase* Dest)
{
}

bool CNPCManager::Init()
{
	if (!CSceneObject::Init())
	{
		return false;
	}

	
	return true;
}

void CNPCManager::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
}
