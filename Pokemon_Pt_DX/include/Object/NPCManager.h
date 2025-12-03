#pragma once
#include "SceneObject.h"


class CNPCManager :
	public CSceneObject
{
	friend class CScene;

protected:
	CNPCManager();
	CNPCManager(const CNPCManager& Obj);
	CNPCManager(CNPCManager&& Obj);
	virtual ~CNPCManager();

protected:
	CSharedPtr<class CSpriteComponent> mRoot;
	CSharedPtr<class CColliderOBB2D> mBody;
	CSharedPtr<CSceneObject> mTarget;

	

	float mDetectDistance = 0.f;


private:
	void CollisionNPC(const FVector3D& HitPont, class CColliderBase* Dest);
	void CollisionNPCEnd(class CColliderBase* Dest);


public:
	void SetTarget(CSceneObject* Target)
	{
		mTarget = Target;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

