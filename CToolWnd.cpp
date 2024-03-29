// CToolWnd.cpp: 实现文件
//

#include "stdafx.h"
#include "demo.h"
#include "CToolWnd.h"
#include "Resource.h"


// CToolWnd

IMPLEMENT_DYNAMIC(CToolWnd, CWnd)

CToolWnd::CToolWnd()
{

}

CToolWnd::~CToolWnd()
{
	if (m_pImg)
	{
		delete m_pImg;
		m_pImg = NULL;
	}
}


BEGIN_MESSAGE_MAP(CToolWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CToolWnd 消息处理程序




BOOL CToolWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	//注册窗口类
	HINSTANCE hInstance = AfxGetInstanceHandle();
	assert(hInstance);

	WNDCLASSEXW wc{};
	wc.cbSize = sizeof WNDCLASSEXW;

	BOOL bRet = GetClassInfoExW(hInstance, cs.lpszClass, &wc);
	if (bRet)
	{
		return true;
	}

	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = AfxWndProc;
	wc.lpszClassName = cs.lpszClass;
	wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;


	//注册
	bRet = (BOOL)RegisterClassExW(&wc);
	assert(bRet);


	return true;
}


void CToolWnd::PostNcDestroy()
{
	delete this;
	CWnd::PostNcDestroy();
}


int CToolWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_pImg)
	{
		m_pImg = new CImage;
		m_pImg->LoadFromResource(AfxGetInstanceHandle(), IDBM_TOOL);//此函数需要资源必须为bitmap类型
		assert(!m_pImg->IsNull());
	}

	return 0;
}


void CToolWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()
	//x:116 y:348
	CRect rtSrc{0,0,m_pImg->GetWidth()/2,m_pImg->GetHeight()};
	CRect rtDest = rtSrc;
	
	m_pImg->Draw(dc, rtDest, rtSrc);


	//绘制选择的功能
	int x = HIWORD(m_dwToolFlag);//得到高位
	int y = LOWORD(m_dwToolFlag);//得到低位
	m_iFactor = rtDest.right / 2; //第一个小功能的宽度

	rtDest.left = x * m_iFactor;
	rtDest.top = y * m_iFactor;
	rtDest.right = (x+1) * m_iFactor;
	rtDest.bottom = (y+1) * m_iFactor;

	rtSrc = rtDest;
	rtSrc.left += 2 * m_iFactor;
	rtSrc.right += 2 * m_iFactor;

	m_pImg->Draw(dc, rtDest, rtSrc);


}


void CToolWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//m_dwToolFlag = point.x / m_iFactor;
	//m_dwToolFlag += point.y / m_iFactor;
	m_dwToolFlag = ((point.x / m_iFactor) << 16) + point.y / m_iFactor;
	Invalidate();//触发一个重绘

	CWnd::OnLButtonDown(nFlags, point);
}
