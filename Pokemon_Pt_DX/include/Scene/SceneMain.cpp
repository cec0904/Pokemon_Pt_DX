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

	// Hiker material
	/*mAssetManager->CreateMaterial("Hiker");

	CMaterial* mHiker = mAssetManager->FindMaterial("Hiker");

	mHiker->SetPixelShader("DefaultMaterialShader");
	mHiker->SetSamplerType(ETextureSamplerType::Linear);
	mHiker->AddTexture("HikerTex", TEXT("Texture\\Pokemon\\NPC\\Hiker\\Hiker_0"), 0);*/


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

	/*MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint3");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetImmediateSpawn(false);
	MonsterPoint->SetSpawnTime(5.f);
	MonsterPoint->SetWorldPos(400.f, -300.f);

	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint4");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetImmediateSpawn(false);
	MonsterPoint->SetSpawnTime(3.5f);
	MonsterPoint->SetWorldPos(-400.f, -300.f);

	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint5");
	MonsterPoint->SetSpawnType(EObjectSpawnType::NearingMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetImmediateSpawn(true);
	MonsterPoint->SetSpawnTime(10.f);
	MonsterPoint->SetWorldPos(200.f, 0.f);*/

	//UI 생성
	CMainWidget* Widget = mUIManager->CreateWidget<CMainWidget>("Main");

	mUIManager->AddToViewport(Widget);




	//CGunnerMonster* Monster1 = CreateObj<CGunnerMonster>("GunnerMonster2");
	//Monster1->SetWorldPos(400.f, 300.f);
	//Monster1->SetTarget(Player);

	//CNearingMonster* Monster2 = CreateObj<CNearingMonster>("NearingMonster");
	//Monster2->SetWorldPos(0.f, 300.f);
	//Monster2->SetTarget(Player);

	//CGunnerMonster* Monster3 = CreateObj<CGunnerMonster>("GunnerMonster3");
	//Monster3->SetWorldPos(400.f, -300.f);
	//Monster3->SetTarget(Player);

	//CGunnerMonster* Monster4 = CreateObj<CGunnerMonster>("GunnerMonster4");
	//Monster4->SetWorldPos(0.f, -300.f);
	//Monster4->SetTarget(Player);

	//CGunnerMonster* Monster5 = CreateObj<CGunnerMonster>("GunnerMonster3");
	//Monster5->SetWorldPos(200.f, -300.f);
	//Monster5->SetTarget(Player);

	//CGunnerMonster* Monster6 = CreateObj<CGunnerMonster>("GunnerMonster4");
	//Monster6->SetWorldPos(0.f, -150.f);
	//Monster6->SetTarget(Player);

	return true;
}