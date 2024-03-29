#pragma once


// CMainWnd
class CToolWnd;
class CMethoedWnd;
class CPaintWnd;
class CMainWnd : public CWnd
{
	DECLARE_DYNAMIC(CMainWnd)

public:
	CMainWnd();
	virtual ~CMainWnd();

protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();

public:
	CToolWnd *m_pToolWnd{};
	CMethoedWnd *m_pMethoedWnd{};
	CPaintWnd *m_pPaintWnd{};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


