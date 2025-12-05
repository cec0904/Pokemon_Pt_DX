#include "SceneMain.h"

#include "SceneAssetManager.h"
#include "SceneUIManager.h"
#include "../Asset/Material/Material.h"
#include "../Object/PlayerObject.h"
#include "../Object/MonsterObject.h"
#include "../Object/GunnerMonster.h"
#include "../Object/NearingMonster.h"
#include "../Object/ObjectSpawnPoint.h"
#include "../UI/UserWidget/MainWidget.h"
#include "../Object/NPCManager.h"
#include "../Object/NPCHiker.h"

CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
}

bool CSceneMain::Init()
{
	if (!CScene::Init())
	{
		return false;
	}

	///////////// 사용할 머티리얼 미리 만든다!!
	mAssetManager->CreateMaterial("Monster1");

	CMaterial* material = mAssetManager->FindMaterial("Monster1");

	material->SetPixelShader("DefaultMaterialShader");
	material->SetSamplerType(ETextureSamplerType::Linear);
	material->AddTexture("MonsterTex", TEXT("Texture/Porori.png"), 0);

	///////////// 사용할 사운드도 미리 추가한다.
	mAssetManager->LoadSound("Hit", "Effect", false, "Sound/Fire1.wav");


	///////////////////////////////////////////////

	CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

	if (Player == nullptr)
		return false;

	//CGunnerMonster* Monster1 = CreateObj<CGunnerMonster>("GunnerMonster2");
	//Monster1->SetWorldPos(400.f, 300.f);
	//Monster1->SetTarget(Player);

	CNPCHiker* pHiker = CreateObj<CNPCHiker>("Hiker");
	pHiker->SetWorldPos(0.f, 300.f);

	
	

	CObjectSpawnPoint* MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint1");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
	MonsterPoint->SetSpawnTime(6.f);
	MonsterPoint->SetImmediateSpawn(true);
	//MonsterPoint->SetDestroySpawnCount(3);
	MonsterPoint->SetWorldPos(400.f, 300.f);


	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint2");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::CountDestroy);
	MonsterPoint->SetImmediateSpawn(false);
	MonsterPoint->SetSpawnTime(5.f);
	MonsterPoint->SetDestroySpawnCount(3);
	MonsterPoint->SetWorldPos(-400.f, 300.f);

	

	//UI 생성
	CMainWidget* Widget = mUIManager->CreateWidget<CMainWidget>("Main");

	mUIManager->AddToViewport(Widget);

	return true;
}