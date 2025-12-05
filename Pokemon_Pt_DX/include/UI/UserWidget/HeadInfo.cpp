#include "HeadInfo.h"

#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"

CHeadInfo::CHeadInfo()
{
}

CHeadInfo::~CHeadInfo()
{
}

bool CHeadInfo::Init()
{
	mNameText = mScene->GetUIManager()->CreateWidget<CTextBlock>("NameText");

	mNameText->SetText(L"Monster");
	mNameText->SetFontSize(20.f);
	mNameText->SetPos(0.f, 0.f);
	mNameText->SetPivot(FVector2D(0.5f, 0.f));
	mNameText->SetAlignH(ETextAlignH::Center);
	mNameText->SetSize(100.f, 100.f);
	mNameText->SetTextColor(255, 255, 255, 255);

	AddWidget(mNameText);

	return true;


	return CUserWidget::Init();
}

void CHeadInfo::Render()
{
	CUserWidget::Render();
}

void CHeadInfo::Render(const FVector3D& Pos)
{
	CUserWidget::Render(Pos);

}
