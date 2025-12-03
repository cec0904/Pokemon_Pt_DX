#pragma once
#include "WindowWidget.h"

class CMainWidget :
    public CWindowWidget
{
	friend class CSceneUIManager;

protected:
	CMainWidget();
	virtual ~CMainWidget();

protected:
	CSharedPtr<class CButton> mButton;

public:


public:
	virtual bool Init();




};

