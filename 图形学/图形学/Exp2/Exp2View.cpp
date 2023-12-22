
// Exp2View.cpp : CExp2View 类的实现
//

#include "stdafx.h"
#include "Resource.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Exp2.h"
#endif

#include "Exp2Doc.h"
#include "Exp2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExp2View

IMPLEMENT_DYNCREATE(CExp2View, CView)

BEGIN_MESSAGE_MAP(CExp2View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CExp2View 构造/析构

CExp2View::CExp2View()
{
	// TODO:  在此处添加构造代码
	m_Brush = NULL;
	m_finish = FALSE;

}

CExp2View::~CExp2View()
{
	if (m_Brush)
	{
		DeleteObject(m_Brush);
	}
}

BOOL CExp2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CExp2View 绘制

bool mask[0x1000][0x1000] = { 0 }; 

void CExp2View::EdgeMarkFill(HDC hDC, COLORREF color)
{
	CRect rect;
	GetClientRect(rect);

	for (int y = 0; y < rect.bottom; y++)
	{
		for (int x = 0; x < rect.right; x++)
		{
			mask[y][x] = false;
		}
	}

	//
	for (int i = 0; i < m_Points.GetSize(); i++)
	{
		POINT pt0 = m_Points[(i + 0) % m_Points.GetSize()];
		POINT pt1 = m_Points[(i + 1) % m_Points.GetSize()];

		//标记一条边.
		double xs = pt0.x;
		double dxs = (double)(pt1.x - pt0.x) / (double)(pt1.y - pt0.y);
		int dy = pt0.y < pt1.y ? 1 : -1;

		dxs *= dy;

		int x_min = min(pt0.x, pt1.x);
		int x_max = max(pt0.x, pt1.x);

		mask[pt0.y][pt0.x] = true;
		mask[pt1.y][pt1.x] = true;

		if (pt1.y == pt0.y)
		{
			for (int f_x = pt0.x; f_x != pt1.x; f_x++)
			{
				SetPixel(hDC, f_x, pt0.y, color);
			}
		}
		else
		{
			for (int ys = pt0.y; ys != pt1.y + dy; ys += dy)
			{
				xs = xs + dxs;
				xs = max(xs, x_min);
				xs = min(xs, x_max);

				int Ixs = xs + 0.5;
				mask[ys][Ixs] = true;

				SetPixel(hDC, Ixs, ys, color);
			}
		}
	}
	for (int y = 0; y < rect.bottom; y++)
	{
		bool inside = false;
		int cnt = 0;
		for (int i = 0; i < rect.right; )
		{
			
			if (mask[y][i])
			{
				cnt += 1;
				i += 1;
				while (i < rect.right && mask[y][i])
				{
					mask[y][i] = false;
					i++;
				}
			}
			else
			{
				i += 1;
			}
		}

		if (cnt & 1)
			continue;

		for (int x = 0; x < rect.right; x++)
		{
			//一行只有这一个像素....
			if (mask[y][x])
			{
				inside = !inside;
			}
			
			if (inside)
			{
				SetPixel(hDC, x, y, color);
			}
		}
	}
}

void CExp2View::OnDraw(CDC* pDC)
{
	CExp2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(rect);

	//

	for (int i = 0; i < m_Points.GetSize(); i++)
	{
		pDC->SetPixel(m_Points[i], RGB(255, 0, 0));

		if (i >= 1)
		{
			pDC->MoveTo(m_Points[i - 1]);
			pDC->LineTo(m_Points[i]);
		}
	}

	if (!m_finish && m_Points.GetSize() > 0)
	{
		CPoint pt;
		GetCursorPos(&pt);


		ScreenToClient(&pt);
		pDC->MoveTo(m_Points[m_Points.GetSize() - 1]);
		pDC->LineTo(pt);
	}

	if (m_finish)
	{
		pDC->MoveTo(m_Points[m_Points.GetSize() - 1]);
		pDC->LineTo(m_Points[0]);

		//填充多边形.
		
		HBITMAP hBitmap = CreateCompatibleBitmap(pDC->m_hDC, rect.Width(), rect.Height());
		HBITMAP hBitmap2 = CreateCompatibleBitmap(pDC->m_hDC, rect.Width(), rect.Height());
		HBITMAP hBitmap3 = CreateCompatibleBitmap(pDC->m_hDC, rect.Width(), rect.Height());

		HDC hMemDC  = CreateCompatibleDC(pDC->m_hDC);
		HDC hMemDC2 = CreateCompatibleDC(pDC->m_hDC);
		HDC hMemDC3 = CreateCompatibleDC(pDC->m_hDC);

		SelectObject(hMemDC, hBitmap);
		SelectObject(hMemDC, m_Brush);
		SelectObject(hMemDC2, hBitmap2);
		SelectObject(hMemDC3, hBitmap3);


		FillRect(hMemDC, &rect, m_Brush);
		FillRect(hMemDC2, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		FillRect(hMemDC3, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

		EdgeMarkFill(hMemDC2, RGB(255,255,255));

		EdgeMarkFill(hMemDC3, 0);
		

		BitBlt(hMemDC, 0, 0, rect.Width(), rect.Height(), hMemDC2, 0, 0, SRCAND);
		BitBlt(pDC->m_hDC, 0, 0, rect.Width(), rect.Height(), hMemDC3, 0, 0, SRCCOPY);
		BitBlt(pDC->m_hDC, 0, 0, rect.Width(), rect.Height(), hMemDC, 0, 0, SRCPAINT);

		DeleteObject(hMemDC);
		DeleteObject(hMemDC2);
		DeleteObject(hMemDC3);
		
		
	/*	for (int i = 0; i < m_Points.GetSize(); i++)
		{
			pDC->SetPixel(m_Points[i], RGB(255, 0, 0));

			if (i >= 1)
			{
				pDC->MoveTo(m_Points[i - 1]);
				pDC->LineTo(m_Points[i]);
			}
		}*/
	}
}

void CExp2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExp2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExp2View 诊断

#ifdef _DEBUG
void CExp2View::AssertValid() const
{
	CView::AssertValid();
}

void CExp2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExp2Doc* CExp2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp2Doc)));
	return (CExp2Doc*)m_pDocument;
}
#endif //_DEBUG


// CExp2View 消息处理程序


int CExp2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_Brush = CreatePatternBrush(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1)));
	return 0;
}


void CExp2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDC * pDC = GetDC();
	CRect rect;

	if (!m_finish)
	{
		m_Points.Add(point);

		GetClientRect(rect);
		InvalidateRect(rect);
	}
	
	CView::OnLButtonDown(nFlags, point);
}


void CExp2View::OnMouseMove(UINT nFlags, CPoint point)
{
	
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!m_finish)
	{
		CRect rect;

		GetClientRect(rect);

		InvalidateRect(rect);

	}
	CView::OnMouseMove(nFlags, point);
}


void CExp2View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//多边形最少得三条边.
	
	CRect rect;

	if (m_Points.GetSize() < 3){
		return;
	}

	//
	m_finish = TRUE;
	GetClientRect(rect);
	InvalidateRect(rect);
	CView::OnMButtonDblClk(nFlags, point);
}


void CExp2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CView::OnRButtonDown(nFlags, point);
}
