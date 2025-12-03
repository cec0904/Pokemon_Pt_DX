#pragma once
#include "NPCManager.h"

class CNPCHiker :
	public CNPCManager
{
	friend class CScene;

protected:
	CNPCHiker();
	CNPCHiker(const CNPCHiker& Obj);
	CNPCHiker(CNPCHiker&& Obj);
	virtual ~CNPCHiker();

protected:
	CSharedPtr<class CSpriteComponent> mRoot;
	CSharedPtr<class CColliderOBB2D> mBody;
	CSharedPtr<class CMovementComponent> mMovement;
	CSharedPtr<CSceneObject> mTarget;

	//애니메이션
	class CAnimation2D* mAnimation = nullptr;
	//Idel 상태값으로 돌아갈건지 여부 
	bool mAutoBasePose = true;

	float mSpeed = 300.f;
	
	

public:
	void SetTarget(CSceneObject* Target)
	{
		mTarget = Target;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

};

