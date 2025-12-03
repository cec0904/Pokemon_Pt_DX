#include "PlayerObject.h"

#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"

#include "../Animation/Animation2D.h"
#include "../Asset/Animation/Animation2DData.h"
#include "../Asset/Texture/Texture.h"

#include "../Scene/Scene.h"
#include "../Scene/Input.h"

#include "BulletObject.h"
#include "TornadoBullet.h"
#include "TalonR.h"
#include "GravityBullet.h"

#include "../Component/SpriteComponent.h"
#include "../Share/Log.h"


CPlayerObject::CPlayerObject()
	: CSceneObject()
{
}

CPlayerObject::CPlayerObject(const CPlayerObject& Obj)
	: CSceneObject(Obj)
{
	
}

CPlayerObject::CPlayerObject(CPlayerObject&& Obj)
	: CSceneObject(Obj)
{
}

CPlayerObject::~CPlayerObject()
{
}

bool CPlayerObject::Init()
{
	// 게임 매니져 -> 씬매니져를 통해 -> 현재 씬을 실행시키고
	// 씬에서는 씬에 포함된 오브젝트들을 전부 순회하면서 시점 함수들을 호출해준다. 
	// 오브젝트들은 본인의 루트 컴포넌트를 호출해주면 
	// 루트 컴포넌트는 자식 컴포넌트들을 호출해준다. 

	// 컴포넌트 하나 등록해줄거다 .
	//mRoot = CreateComponent<CStaticMeshComponent>();
	mRoot = CreateComponent<CSpriteComponent>();
	//mBody = CreateComponent<CColliderAABB2D>();
	//mBody = CreateComponent<CColliderSphere2D>();
	mBody = CreateComponent<CColliderOBB2D>();
	//mLine = CreateComponent<CColliderLine2D>();

	mMovement = CreateComponent<CMovementComponent>();
	mRotation = CreateComponent<CRotationComponent>();
	mCamera = CreateComponent<CCameraComponent>();

	//mRoot->SetMesh("CenterTexRect");
	mRoot->SetTexture("BonoBono", TEXT("Texture/BonoBono.png"),0);
	mRoot->SetTint(0.1f, 0.1f, 0.8f);
	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetOpacity(1.f);
	//mRoot->SetShader("ColorMeshShader");

	mRoot->SetWorldPos(0.f, 0.f, 0.f);
	mRoot->SetWorldScale(100.f, 100.f, 1.f);
	SetRootComponent(mRoot);

	mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
	mAnimation->AddSequence("PlayerIdle", 1.f, 1.f, true, false);
	mAnimation->AddSequence("PlayerWalk", 1.f, 1.f, true, false);
	mAnimation->AddSequence("PlayerAttack", 1.f, 0.6f, true, false);

	mAnimation->SetEndFunction("PlayerAttack", this, &CPlayerObject::AttackEnd);
	mAnimation->AddNotify("PlayerAttack", 1, this, &CPlayerObject::AttackNotify);

	mRoot->SetFlip(false);

	mRoot->AddChild(mBody);
	mBody->SetBoxSize(100.f, 100.f);
	mBody->SetCollisionProfile("Player");
	//mBody->SetRadius(50.f);

	//mBody->AddChild(mLine);
	//mLine->SetCollisionProfile("Player");
	//mLine->SetLineDistance(300.f);
	//mLine->SetRelativePos(0.f, 50.f);

	
	
	

	mMovement->SetUpdateComponent(mRoot);
	mMovement->SetMoveSpeed(500.f);

	mRotation->SetUpdateComponent(mRoot);

	//카메라 셋팅 
	mCamera->SetProjectionType(ECameraProjectionType::Ortho);
	mRoot->AddChild(mCamera);

	//위성 만들기
	mRotationPivot = CreateComponent<CSceneComponent>();
	//mSub = CreateComponent<CStaticMeshComponent>();
	//mSub2 = CreateComponent<CStaticMeshComponent>();
	mSub = CreateComponent<CSpriteComponent>();
	mSub2 = CreateComponent<CSpriteComponent>();

	mRoot->AddChild(mRotationPivot);
	mRotationPivot->AddChild(mSub);
	mRotationPivot->AddChild(mSub2);

	//위성1
	mSub->SetTexture("Wallnut", TEXT("Texture/Wallnut.png"));
	mSub->SetTint(0.f, 0.f, 1.f);
	mSub->SetPivot(0.5f, 0.5f);
	mSub->SetOpacity(1.f);


	mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
	mSub->SetRelativeScale(0.5f, 0.5f, 1.f);

	//위성2
	mSub2->SetTexture("Wallnut");
	mSub2->SetTint(1.f, 0.f, 0.f);
	mSub2->SetPivot(0.5f, 0.5f);
	mSub2->SetOpacity(1.f);
	mSub2->SetRelativePos(mSkill4Range, 0.f, 0.f);
	mSub2->SetRelativeScale(0.5f, 0.5f, 1.f);


	//입력
	mScene->GetInput()->AddBindKey("MoveUp", 'W');
	mScene->GetInput()->AddBindFunction("MoveUp", EInputType::Hold, this, &CPlayerObject::MoveUp);

	mScene->GetInput()->AddBindKey("MoveDown", 'S');
	mScene->GetInput()->AddBindFunction("MoveDown", EInputType::Hold, this, &CPlayerObject::MoveDown);

	//회전
	mScene->GetInput()->AddBindKey("RotationZ", 'D');
	mScene->GetInput()->AddBindFunction("RotationZ", EInputType::Hold, this, &CPlayerObject::rotationZ);
	
	mScene->GetInput()->AddBindKey("RotationZInv", 'A');
	mScene->GetInput()->AddBindFunction("RotationZInv", EInputType::Hold, this, &CPlayerObject::rotationZInv);

	// 총알 발사
	mScene->GetInput()->AddBindKey("Fire", VK_SPACE);
	mScene->GetInput()->AddBindFunction("Fire", EInputType::Down, this, &CPlayerObject::Fire);

	// 스킬 1 
	mScene->GetInput()->AddBindKey("Skill1", '1');
	mScene->GetInput()->ChangeKeyCtrl("Skill1", true);

	mScene->GetInput()->AddBindFunction("Skill1", EInputType::Hold, this, &CPlayerObject::Skill1);
	mScene->GetInput()->AddBindFunction("Skill1", EInputType::Up, this, &CPlayerObject::Skill1Fire);

	//스킬2
	//토네이도샷 
	mScene->GetInput()->AddBindKey("Skill2", '2');
	mScene->GetInput()->AddBindFunction("Skill2", EInputType::Down, this, &CPlayerObject::Skill2);

	//스킬3
	//위성발사 
	mScene->GetInput()->AddBindKey("Skill3", '3');
	mScene->GetInput()->AddBindFunction("Skill3", EInputType::Down, this, &CPlayerObject::Skill3);

	//스킬 4 
	// 롤 아우솔 w 스킬 
	// 돌아가는 위성의 범위를 늘렸다가 몇초후 다시 되돌아오기 
	// 가능하면 위성의 속도도 늘렸다가 줄이기 
	mScene->GetInput()->AddBindKey("Skill4", '4');
	mScene->GetInput()->AddBindFunction("Skill4", EInputType::Down, this, &CPlayerObject::Skill4);

	//스킬 5 
	// 롤 탈론 궁극기 만들기
	// 플레이어 기준으로 8방향으로 총알을 발사하고
	// 해당총알이 몇초 돌다가 
	// 플레이어에게 다시 되돌아오는 부메랑 기능
	mScene->GetInput()->AddBindKey("Skill5", '5');
	mScene->GetInput()->AddBindFunction("Skill5", EInputType::Down, this, &CPlayerObject::Skill5);

	//스킬 6번
	mScene->GetInput()->AddBindKey("Skill6", '6');
	mScene->GetInput()->AddBindFunction("Skill6", EInputType::Down, this, &CPlayerObject::Skill6);

	//스킬 7번
	mScene->GetInput()->AddBindKey("Skill7", '7');
	mScene->GetInput()->AddBindFunction("Skill7", EInputType::Down, this, &CPlayerObject::Skill7);

	return true;
}

void CPlayerObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	//위성을 돌려주면 될거같다!!
	FVector3D Rot = mRotationPivot->GetRelativeRotation();
	Rot.z += DeltaTime * mPivotRotationSpeed;
	mRotationPivot->SetRelativeRotationZ(Rot.z);

	//스킬3 
	if (mSkill3Enable)
	{
		Skill3Update(DeltaTime);
	}

	//스킬4
	if (mSkill4Enable)
	{
		Skill4Update(DeltaTime);
	}

	if (mMovement->GetVelocityLength() == 0.f && mAutoBasePose)
	{
		mAnimation->ChangeAnimation("PlayerIdle");
	}

}

void CPlayerObject::Damage(float Damage)
{
	mHP -= Damage;
}

void CPlayerObject::MoveUp(float DeltaTime)
{
	//FVector3D Pos = mRootComponent->GetWorldPosition();
	////FVector3D Dir = { 0.f, 1.f, 0.f };
	//FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

	//mRootComponent->SetWorldPos(Pos + Dir*DeltaTime * 3.f);

	mAnimation->ChangeAnimation("PlayerWalk");
	mRoot->SetFlip(false);

	mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y));
}

void CPlayerObject::MoveDown(float DeltaTime)
{
	/*FVector3D Pos = mRootComponent->GetWorldPosition();
	FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);
	mRootComponent->SetWorldPos(Pos + Dir * DeltaTime * -3.f);*/
	mAnimation->ChangeAnimation("PlayerWalk");
	mRoot->SetFlip(true);

	mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * -1);
}

void CPlayerObject::rotationZ(float DeltaTime)
{
	//FVector3D Rot = mRootComponent->GetWorldRotation();
	//mRootComponent->SetWorldRotationZ(Rot.z + 90.f * DeltaTime);

	mRotation->AddMoveZ(-90.f);
}

void CPlayerObject::rotationZInv(float DeltaTime)
{
	/*FVector3D Rot = mRootComponent->GetWorldRotation();
	mRootComponent->SetWorldRotationZ(Rot.z + -90.f * DeltaTime);*/

	mRotation->AddMoveZ(90.f);
}

void CPlayerObject::Fire(float DeltaTime)
{
	mAnimation->ChangeAnimation("PlayerAttack");
	mAutoBasePose = false;

	//총알을 만들것이고 
	CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
	Bullet->SetBulletCollisionProfile("PlayerAttack");

	CSceneComponent* Root = Bullet->GetRootComponent();
	//총알의 시작 위치 == 내 월드 위치
	Root->SetWorldPos(mRootComponent->GetWorldPosition());
	Root->SetWorldRotation(mRootComponent->GetWorldRotation());
	Root->SetWorldScale(50.f, 50.f, 1.f);
	Bullet->SetLifeTime(2.f);
}

void CPlayerObject::Skill1(float DeltaTime)
{
	//스킬을 누르는 동안 
	if (!mSkill1Object)
	{
		//발사할 총알을 만든다. 
		mSkill1Object = mScene->CreateObj<CBulletObject>("Skill1Bullet");
		mSkill1Object->SetBulletSpeed(0.f);
	}

	CSceneComponent* Root = mSkill1Object->GetRootComponent();
	Root->SetWorldPos(mRootComponent->GetWorldPosition() + mRootComponent->GetAxis(EAxis::Y));
	Root->SetWorldRotation(mRootComponent->GetWorldRotation());

	FVector3D Scale = Root->GetWorldScale();

	Scale.x += 200.f * DeltaTime;
	Scale.y += 200.f * DeltaTime;

	if (Scale.x >= 400.f)
	{
		Scale.x = 400.f;
	}

	if (Scale.y >= 400.f)
	{
		Scale.y = 400.f;
	}


	mSkill1Object->GetRootComponent()->SetWorldScale(Scale);
}

void CPlayerObject::Skill1Fire(float DeltaTime)
{
	mSkill1Object->SetBulletSpeed(500.f);
	mSkill1Object = nullptr;
}

void CPlayerObject::Skill2(float DeltaTime)
{
	////총알을 만들것이고 
	//CTornadoBullet* Bullet = mScene->CreateObj<CTornadoBullet>("TornadoBullet");

	//CSceneComponent* Root = Bullet->GetRootComponent();
	////총알의 시작 위치 == 내 월드 위치
	//Root->SetWorldPos(mRootComponent->GetWorldPosition());
	//Root->SetWorldRotation(mRootComponent->GetWorldRotation());
	//Bullet->SetBulletSpeed(500.f);
	//Bullet->SetWorldScale(100.f,100.f);
	//Bullet->SetLifeTime(1.f);

	SetWorldPos(FVector3D::Zero);
}

void CPlayerObject::Skill3(float DeltaTime)
{
	//스킬이 발동중이니 ?
	if (!mSkill3Enable)
	{
		mSkill3Enable = true;
		mSkill3Time = 3.f;
		mSkill3TimeAcc = 0.f;
		mSkill3Interval = 0.2f;
	}
}

void CPlayerObject::Skill3Update(float DeltaTime)
{
	mSkill3TimeAcc += DeltaTime;

	if (mSkill3TimeAcc >= mSkill3Interval)
	{
		mSkill3TimeAcc -= mSkill3Interval;

		//총알을 발사한다. 
		CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

		CSceneComponent* Root = Bullet->GetRootComponent();
		//총알의 시작 위치 == 내 월드 위치
		Root->SetWorldPos(mSub->GetWorldPosition());
		Root->SetWorldRotation(mRootComponent->GetWorldRotation());
		Bullet->SetLifeTime(2.f);
		Bullet->SetBulletSpeed(150.f);
		Bullet->SetWorldScale(50.f, 50.f);

		Bullet = mScene->CreateObj<CBulletObject>("Bullet");
		Root = Bullet->GetRootComponent();
		//총알의 시작 위치 == 내 월드 위치
		Root->SetWorldPos(mSub2->GetWorldPosition());
		Root->SetWorldRotation(mRootComponent->GetWorldRotation());
		Bullet->SetLifeTime(2.f);
		Bullet->SetBulletSpeed(150.f);
		Bullet->SetWorldScale(50.f, 50.f);
	}
	mSkill3Time -= DeltaTime;

	if (mSkill3Time <= 0.f)
	{
		mSkill3Enable = false;
	}
}

void CPlayerObject::Skill4(float DeltatTime)
{
	if (!mSkill4Enable)
	{
		mSkill4Enable = true;
		mSkill4Time = 5.f;
		mSkill4TimeAcc = 0.f;
		mSkill4ReadyTime = 2.l;

		mPivotRotationSpeed = 360.f;
		mSkill4State = ESkill4State::Expansion;
	}
}

void CPlayerObject::Skill4Update(float DeltaTime)
{
	//스킬4 구현 
	mSkill4TimeAcc += DeltaTime;

	switch (mSkill4State)
	{
	case ESkill4State::Expansion:

		// DeltaTime / mSkill4ReadyTime 을 하게되면 확장하는 시간 2초라는 시간에 대해서 
		// 현재 DeltaTime이 몇 퍼센트의 시간이 흘렀는지를 구해낼수 있다. 
		mSkill4Range += DeltaTime / mSkill4ReadyTime * mSkill4RangeLength;

		if (mSkill4TimeAcc >= mSkill4ReadyTime)	//예를들어서 시작하고나서 2초가 지나면 
		{
			mSkill4TimeAcc -= mSkill4ReadyTime;
			mSkill4Range = mSkill4MaxRange;
			mSkill4State = ESkill4State::Maintain;
		}

		mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
		mSub2->SetRelativePos(mSkill4Range, 0.f, 0.f);

		break;
	case ESkill4State::Maintain:
		
		if (mSkill4TimeAcc >= mSkill4Time)
		{
			mSkill4TimeAcc = 0.f;
			mSkill4State = ESkill4State::Reduction;
		}
		break;
	case ESkill4State::Reduction:
		mSkill4Range -= DeltaTime / mSkill4ReadyTime * mSkill4RangeLength;

		if (mSkill4TimeAcc >= mSkill4ReadyTime)
		{
			mSkill4Enable = false;
			mSkill4TimeAcc = 0;
			mSkill4Range = 200.f;
			mSkill4State = ESkill4State::Expansion;
			mPivotRotationSpeed = 180.f;
		}
		mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
		mSub2->SetRelativePos(mSkill4Range, 0.f, 0.f);
		break;
	}
}

void CPlayerObject::Skill5(float DeltaTime)
{
	//8방향으로 총알 발사
	FVector3D Dir = mRoot->GetAxis(EAxis::Y);
	FVector3D Rot = mRoot->GetWorldRotation();

	FMatrix matRot;
	matRot.RotationZ(45.f);

	for (int i = 0 ; i < 8; ++i)
	{
		CTalonR* Bullet = mScene->CreateObj<CTalonR>("TalonBullet");

		CSceneComponent* Root = Bullet->GetRootComponent();
		FVector3D Pos = mRoot->GetWorldPosition();
		Root->SetWorldPos(Pos + Dir);
		Root->SetWorldRotation(Rot);
		Root->SetWorldScale(50.f, 50.f, 1.f);
		Rot.z += 45;

		Dir = Dir.TransformNormal(matRot);
		Dir.Normalize();
		Bullet->SetTarget(this);
	}


}

void CPlayerObject::Skill6(float DeltaTime)
{
	CGravityBullet* Bullet = mScene->CreateObj<CGravityBullet>("PullBullet");

	FVector3D Pos = GetWorldPosition();
	FVector3D Dir = GetAxis(EAxis::Y);
	Bullet->SetWorldPos(Pos + Dir * 75.f);
	Bullet->SetWorldRotation(GetWorldRotation());
}

void CPlayerObject::Skill7(float DeltaTime)
{
	CGravityBullet* Bullet = mScene->CreateObj<CGravityBullet>("PushBullet");

	FVector3D Pos = GetWorldPosition();
	FVector3D Dir = GetAxis(EAxis::Y);
	Bullet->SetWorldPos(Pos + Dir * 75.f);
	Bullet->SetWorldRotation(GetWorldRotation());
	Bullet->SetGravityType(EGravityType::Push);
}

void CPlayerObject::AttackEnd()
{
	mAutoBasePose = true;
}

void CPlayerObject::AttackNotify()
{
}
