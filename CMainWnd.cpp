// CMainWnd.cpp: 实现文件
//

#include "stdafx.h"
#include "demo.h"
#include "CMainWnd.h"
#include "CToolWnd.h"
#include "CPaintWnd.h"
#include "CMethoedWnd.h"


// CMainWnd

IMPLEMENT_DYNAMIC(CMainWnd, CWnd)

CMainWnd::CMainWnd()
{

}

CMainWnd::~CMainWnd()
{
	if (m_pToolWnd)
	{
		m_pToolWnd = NULL;
		delete m_pToolWnd;
		m_pToolWnd = NULL;
	}
	if (m_pMethoedWnd)
	{
		m_pMethoedWnd = NULL;
		delete m_pMethoedWnd;
		m_pMethoedWnd = NULL;
	}
	if (m_pPaintWnd)
	{
		m_pPaintWnd = nullptr;
		delete m_pPaintWnd;
		m_pPaintWnd = nullptr;
	}
}


BEGIN_MESSAGE_MAP(CMainWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CMainWnd 消息处理程序




BOOL CMainWnd::PreCreateWindow(CREATESTRUCT& cs)//创建窗口之前 的消息
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


void CMainWnd::PostNcDestroy()//投递非客户区销毁
{
	//释放new出来的框架窗口
	delete this;

	CWnd::PostNcDestroy();
}


int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)//发送此消息时 主窗口已经创建好
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rtClnt{}, rtToolWnd{}, rtMethodWnd{}, rtPaintWnd{};
	GetClientRect(rtClnt);


	//rtToolWnd
	CImage oImg;
	oImg.LoadFromResource(AfxGetInstanceHandle(), IDBM_TOOL);
	assert(!oImg.IsNull());
	rtToolWnd.right = oImg.GetWidth() / 2;
	rtToolWnd.bottom = rtClnt.bottom;


	//rtMethodWnd
	rtMethodWnd = rtClnt;//得到左下角   然后下面得到左上角
	rtMethodWnd.left = rtToolWnd.right;
	rtMethodWnd.top = rtClnt.bottom - 150;


	//rtPaintWnd
	rtPaintWnd.left = rtToolWnd.right;
	rtPaintWnd.right = rtClnt.right;
	rtPaintWnd.bottom = rtMethodWnd.top;


	

	// TODO:  在此添加您专用的创建代码
	if (!m_pToolWnd)
	{
		m_pToolWnd = new CToolWnd;

		//CRect rt{ 0,0,100,705 };
		assert(m_pToolWnd->CreateEx(WS_EX_CLIENTEDGE, L"CN_TOOL", L"WN", WS_CHILD | WS_BORDER  , rtToolWnd, this, IDWND_TOOL));//注意给父窗口this
		m_pToolWnd->ShowWindow(SW_SHOW);
		m_pToolWnd->UpdateWindow();
	}

	if (!m_pMethoedWnd)
	{
		m_pMethoedWnd = new CMethoedWnd;

		//CRect rt{ 100,605,1366,705 };
		assert(m_pMethoedWnd->CreateEx(WS_EX_CLIENTEDGE, L"CN_METHOD", L"WN", WS_CHILD, rtMethodWnd, this, IDWND_METHOD));
		m_pMethoedWnd->ShowWindow(SW_SHOW);
		m_pMethoedWnd->UpdateWindow();
	}

	if (!m_pPaintWnd)
	{
		m_pPaintWnd = new CPaintWnd;

		//CRect rt{ 100,0,1366,605 };
		assert(m_pPaintWnd->CreateEx(WS_EX_CLIENTEDGE, L"CN_PAINT", L"WN", WS_CHILD, rtPaintWnd, this, IDWND_PAINT));
		m_pPaintWnd->ShowWindow(SW_SHOW);
		m_pPaintWnd->UpdateWindow();
	}
	return 0;
}

