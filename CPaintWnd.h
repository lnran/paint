#pragma once


// CPaintWnd

class CPaintWnd : public CWnd
{
	DECLARE_DYNAMIC(CPaintWnd)

public:
	CPaintWnd();
	virtual ~CPaintWnd();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
};


