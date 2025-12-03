#include "MainWidget.h"

#include "../Common/Button.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../Common/TextBlock.h"

CMainWidget::CMainWidget()
{
}

CMainWidget::~CMainWidget()
{
}

bool CMainWidget::Init()
{
	CWindowWidget::Init();

	//버튼을 추가하기 
	mButton = mScene->GetUIManager()->CreateWidget<CButton>("TestButton");

	mButton->SetPos(500.f, 500.f);
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

	AddWidget(mButton);

	CSharedPtr<CTextBlock> Text = mScene->GetUIManager()->CreateWidget<CTextBlock>("ButtonText");

	Text->SetText(TEXT("전의찬"));
	Text->SetTextColor(0, 255, 255, 255);
	Text->SetPos(500.f, 500.f);
	Text->SetSize(100.f, 100.f);
	Text->SetFontSize(20.f);
	Text->SetAlignH(ETextAlignH::Center);
	Text->SetAlignV(ETextAlignV::Middle);
	mButton->SetChild(Text);

	return true;
}
