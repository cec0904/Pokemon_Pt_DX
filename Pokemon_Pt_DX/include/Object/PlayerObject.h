#pragma once
#include "SceneObject.h"

enum class ESkill4State
{
	Expansion,	//확장
	Maintain,	//유지
	Reduction	//축소
};

class CPlayerObject :
    public CSceneObject
{
	friend class CScene;

protected:
	CPlayerObject();
	CPlayerObject(const CPlayerObject& Obj);
	CPlayerObject(CPlayerObject&& Obj);
	virtual ~CPlayerObject();

protected:
	//CSharedPtr<class CStaticMeshComponent> mRoot;
	CSharedPtr<class CSpriteComponent> mRoot;
	//CSharedPtr<class CColliderAABB2D> mBody;
	//CSharedPtr<class CColliderSphere2D> mBody;
	CSharedPtr<class CColliderOBB2D> mBody;
	//CSharedPtr<class CColliderLine2D> mLine;

	CSharedPtr<class CSceneComponent> mRotationPivot;
	CSharedPtr<class CSpriteComponent> mSub;
	//MovementComponent
	//RotationComponent
	CSharedPtr<class CMovementComponent> mMovement;
	CSharedPtr<class CRotationComponent> mRotation;

	//CameraComponent
	CSharedPtr<class CCameraComponent> mCamera;

	//애니메이션
	class CAnimation2D* mAnimation = nullptr;

	//Idel 상태값으로 돌아갈건지 여부 
	bool mAutoBasePose = true;


		//실습1 
	//위성 반대편 방향에 하나더 출력해보기 
	CSharedPtr<class CSpriteComponent> mSub2;

	// 총알용 오브젝트 
	//스킬 1
	CSharedPtr<class CBulletObject> mSkill1Object;

	//스킬 3 : 위성에서 발사하기 
	bool mSkill3Enable = false;
	float mSkill3Time = 3.f;	// 3초동안
	float mSkill3TimeAcc = 0.f;	// 시간 측정용  
	float mSkill3Interval = 0.2f; //0.2초마다 총알을 발사할것이다.

	//스킬 4 : 아우솔
	bool mSkill4Enable = false;
	// 스킬 커지는 시간
	float mSkill4Time = 2.f;
	float mSkill4TimeAcc = 0.f;
	float mSkill4ReadyTime = 2.f;	// 확장, 축소하는데 걸리는 시간. 
	float mSkill4MaxRange = 400.f;
	float mSkill4Range = 200.f;
	float mSkill4RangeLength = 200.f;
	//스킬 다시 작아지는 시간 
	ESkill4State mSkill4State = ESkill4State::Expansion;

	float mPivotRotationSpeed = 180.f;

	float mHP = 10;
	int mEnergy = 3;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	void Damage(float Damage);

private:
	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveRight(float DeltaTime);
	void MoveLeft(float DeltaTime);

	void rotationZ(float DeltaTime);
	void rotationZInv(float DeltaTime);

	void Fire(float DeltaTime);

	//스킬
	void Skill1(float DeltaTime);
	void Skill1Fire(float DeltaTime);

	// 스킬 2 토네이도 샷 
	void Skill2(float DeltaTime);

	//스킬 3 : 위성 2개에서 각각 총알에 생성된다. 날라가는 방향은 플레이어 바라보는 방향으로 
	void Skill3(float DeltaTime);
	void Skill3Update(float DeltaTime);

	//스킬 4 : 위성을 더 멀리 빠르게 돌렸다가 되돌린다. 
	// 예시는 롤 : 아우솔 옛날 W 
	void Skill4(float DeltatTime);
	void Skill4Update(float DeltaTime);

	//스킬5 탈론 궁
	// 8각형 기준으로 스폰해주고 
	// 총알은 각각 돌다가 돌아온다.
	void Skill5(float DeltaTime);


	//중력탄!
	// 끌어당기기
	void Skill6(float DeltaTime);
	// 밀쳐내기 
	void Skill7(float DeltaTime);


	//애니메이션 바인드 함수 
	void AttackEnd();
	void AttackNotify();
};

