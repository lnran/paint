#pragma once


// CToolWnd

class CToolWnd : public CWnd
{
	DECLARE_DYNAMIC(CToolWnd)
	CImage *m_pImg {};

	DWORD m_dwToolFlag{}; //DWORD是32位，用前16位表示x方向，后16位表示y方向          用以表示选择的功能
	int m_iFactor{}; //功能单元格，一个功能的尺寸大小

public:
	CToolWnd();
	virtual ~CToolWnd();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


