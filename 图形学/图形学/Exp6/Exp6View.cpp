
// Exp6View.cpp : CExp6View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Exp6.h"
#endif

#include "Exp6Doc.h"
#include "Exp6View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExp6View

IMPLEMENT_DYNCREATE(CExp6View, CView)

BEGIN_MESSAGE_MAP(CExp6View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExp6View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_START, &CExp6View::OnStart)
	ON_COMMAND(ID_STOP, &CExp6View::OnStop)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CExp6View 构造/析构

CExp6View::CExp6View()
{
	// TODO:  在此处添加构造代码
	m_ok = 0;
	m_Start = 0;

	dx = 3;
	dy = 3;
	hMemDC = NULL;
}

CExp6View::~CExp6View()
{
}

BOOL CExp6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CExp6View 绘制

void CExp6View::OnDraw(CDC* pDC)
{
	CExp6Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!m_ok){
		for (int i = 0; i < m_Points.GetSize() - 1; i++){
			pDC->MoveTo(m_Points[i]);
			pDC->LineTo(m_Points[i + 1]);
		}

		if (m_Points.GetSize() > 0){
			CPoint point;
			GetCursorPos(&point);
			ScreenToClient(&point);

			pDC->MoveTo(m_Points[m_Points.GetSize() - 1]);
			pDC->LineTo(point);
		}
	}
	else if(!m_Start){
		for (int i = 0; i < m_Points.GetSize(); i++){
			pDC->MoveTo(m_Points[i]);
			pDC->LineTo(m_Points[(i + 1) % m_Points.GetSize()]);
		}
	}
	else{

		if (hMemDC == NULL)
		{
			hMemDC = CreateCompatibleDC(GetDC()->GetSafeHdc());

			CRect rect;
			GetClientRect(rect);

			HBITMAP hBitMap = CreateCompatibleBitmap(GetDC()->GetSafeHdc(), rect.Width(), rect.Height());
			SelectObject(hMemDC, hBitMap);
		}

		CRect rect;
		GetClientRect(rect);

		FillRect(hMemDC, rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

		//动态效果.
		for (int i = 0; i < m_Points.GetSize(); i++){
			CArray<CPoint> tempPoints;

			CPoint p0 = m_Points[i];
			CPoint p1 = m_Points[(i + 1) % m_Points.GetSize()];
			CPoint p2 = m_Points[(i + 2) % m_Points.GetSize()];

			CPoint tmp = p0 + p1;
			tmp.x /= 2;
			tmp.y /= 2;

			tempPoints.Add(tmp);
			tempPoints.Add(p1);
			
			tmp = p2 + p1;
			tmp.x /= 2;
			tmp.y /= 2;

			tempPoints.Add(tmp);
			bez_to_points(hMemDC, tempPoints);		

			//多边形边框
			//MoveToEx(hMemDC, m_Points[i].x, m_Points[i].y, NULL);
			//LineTo(hMemDC, m_Points[(i + 1) % m_Points.GetSize()].x, m_Points[(i + 1) % m_Points.GetSize()].y);
		}
		BitBlt(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), hMemDC, 0, 0, SRCCOPY);
	}
	// TODO:  在此处为本机数据添加绘制代码
}


// CExp6View 打印


void CExp6View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CExp6View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CExp6View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CExp6View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CExp6View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExp6View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExp6View 诊断

#ifdef _DEBUG
void CExp6View::AssertValid() const
{
	CView::AssertValid();
}

void CExp6View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExp6Doc* CExp6View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp6Doc)));
	return (CExp6Doc*)m_pDocument;
}
#endif //_DEBUG


// CExp6View 消息处理程序


void CExp6View::OnStart()
{
	// TODO:  在此添加命令处理程序代码
	m_Start = 1;
	CRect rect;
	GetClientRect(rect);

	InvalidateRect(rect,FALSE);

	SetTimer(10086, 50,NULL);
}


void CExp6View::OnStop()
{
	// TODO:  在此添加命令处理程序代码
	KillTimer(10086);
}


void CExp6View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	if (!m_ok){
		CRect rect;
		GetClientRect(rect);
		m_Points.Add(point);
		InvalidateRect(rect);
	}
	CView::OnLButtonDown(nFlags, point);
}


void CExp6View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!m_ok){
		CRect rect;
		GetClientRect(rect);
		InvalidateRect(rect);
	}
	CView::OnMouseMove(nFlags, point);
}


void CExp6View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_ok = 1;
	CRect rect;
	GetClientRect(rect);
	InvalidateRect(rect);
	CView::OnLButtonDblClk(nFlags, point);
}


void CExp6View::bez_to_points(HDC hDC,const CArray<CPoint>& Points)
{
	float t, delta;

	delta = 1.0 / 1000;
	t = 0;

	for (int i = 0; i <= 1000; i++){
		decas(hDC, t, Points);
		t += delta;
	}
}


void CExp6View::decas(HDC hDC, float t, const CArray<CPoint>& Points)
{
	int n = Points.GetSize() - 1;
	int m, i;

	CArray<CPoint> R, Q;
	for (int i = 0; i < Points.GetSize(); i++){
		R.Add(Points[i]);
		Q.Add(CPoint(0, 0));
	}

	for (m = n; m > 0; m--){

		for (i = 0; i <= m - 1; i++){
			Q[i].x = R[i].x + t * (R[i + 1].x - R[i].x);
			Q[i].y = R[i].y + t * (R[i + 1].y - R[i].y);
		}

		for (i = 0; i <= m - 1; i++)
			R[i] = Q[i];
	}
	//
	SetPixel(hDC, R[0].x, R[0].y, RGB(255, 0, 0));
}


void CExp6View::OnTimer(UINT_PTR nIDEvent)
{

	CRect rect;
	GetClientRect(rect);


	for (int i = 0; i < m_Points.GetSize(); i++)
	{
		int id = i + 1;
		if (id & 1)		//odd
		{
			if ((dx > 0 && m_Points[i].x + (id * dx) > rect.right) ||
				(dx < 0 && m_Points[i].x + (id * dx) < rect.left)){
				dx *= -1;
			}
			m_Points[i].x += id * dx;
		}
		else
		{
			if ((dy > 0 && m_Points[i].y + (id * dy) > rect.bottom) ||
				(dy < 0 && m_Points[i].y + (id * dy) < rect.top)){
				dy *= -1;
			}
			m_Points[i].y += id * dy;
		}
	}

	InvalidateRect(rect,FALSE);
	CView::OnTimer(nIDEvent);
	
	CView::OnTimer(nIDEvent);
}


int CExp6View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}
