#include "StartWidget.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneMain.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/SceneUIManager.h"
#include "../Common/Button.h"
#include "../../Share/Log.h"

CStartWidget::CStartWidget()
{
}

CStartWidget::~CStartWidget()
{
}

bool CStartWidget::Init()
{
	CUserWidget::Init();

	//버튼을 추가하기 
	mButton = mScene->GetUIManager()->CreateWidget<CButton>("TestButton");

	mButton->SetPos(200.f, 600.f);
	mButton->SetSize(100.f, 100.f);
	mButton->SetPivot(FVector2D(0.5f, 0.5f));
	//mButton->SetZOrder(1);

	mButton->SetTexture(EButtonState::Normal, "StartButton", TEXT("Texture/Start.png"));
	mButton->SetTexture(EButtonState::Hovered, "StartButton");
	mButton->SetTexture(EButtonState::Click, "StartButton", TEXT("Texture/Start.png"));
	mButton->SetTexture(EButtonState::Disable, "StartButton", TEXT("Texture/Start.png"));

	mButton->SetTint(EButtonState::Normal, 0.8f, 0.8f, 0.8f);
	mButton->SetTint(EButtonState::Hovered, 1.f, 1.f, 1.f);
	mButton->SetTint(EButtonState::Click, 0.5f, 0.5f, 0.5f);
	mButton->SetTint(EButtonState::Disable, 0.1f, 0.1f, 0.1f);

	mButton->SetEventCallBack(EButtonEventState::Click, this, &CStartWidget::StartButtonClick);

	AddWidget(mButton);

	return true;
}


void CStartWidget::StartButtonClick()
{
	CLog::PrintLog("Start Button Click");

	CSceneManager::GetInst()->CreateLoadScene<CSceneMain>();
}
