// CMethoedWnd.cpp: 实现文件
//

#include "stdafx.h"
#include "demo.h"
#include "CMethoedWnd.h"


// CMethoedWnd

IMPLEMENT_DYNAMIC(CMethoedWnd, CWnd)

CMethoedWnd::CMethoedWnd()
{

}

CMethoedWnd::~CMethoedWnd()
{
}


BEGIN_MESSAGE_MAP(CMethoedWnd, CWnd)
END_MESSAGE_MAP()



// CMethoedWnd 消息处理程序




BOOL CMethoedWnd::PreCreateWindow(CREATESTRUCT& cs)
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


void CMethoedWnd::PostNcDestroy()
{
	delete this;

	CWnd::PostNcDestroy();
}
