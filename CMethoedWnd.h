#pragma once


// CMethoedWnd

class CMethoedWnd : public CWnd
{
	DECLARE_DYNAMIC(CMethoedWnd)

public:
	CMethoedWnd();
	virtual ~CMethoedWnd();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
};


