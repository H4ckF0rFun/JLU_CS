
// Exp1View.cpp : CExp1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Exp1.h"
#endif

#include "Exp1Doc.h"
#include "Exp1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExp1View

IMPLEMENT_DYNCREATE(CExp1View, CView)

BEGIN_MESSAGE_MAP(CExp1View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAW_CIRCLE, &CExp1View::OnDrawCircle)
	ON_COMMAND(ID_DRAW_ELLIPSE, &CExp1View::OnDrawEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
//	ON_WM_MOVE()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CExp1View ����/����

#define SHAPE_CIRCLE   1
#define SHAPE_ELLPISE  2

CExp1View::CExp1View()
{
	// TODO:  �ڴ˴���ӹ������
	m_DrawShape = 0;
	m_IsDrawing = false;
}

CExp1View::~CExp1View()
{
}

BOOL CExp1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CExp1View ����

void CExp1View::OnDraw(CDC* pDc)
{
	CExp1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	
	if (m_IsDrawing)
	{
		pDc->SetPixel(m_StartPoint, RGB(255,0,0));

		if (m_IsDrawing == SHAPE_CIRCLE)
		{
			CPoint point;
			GetCursorPos(&point);
			ScreenToClient(&point);
			
			double radius = sqrt(
				(double)((point.x - m_StartPoint.x) * (point.x - m_StartPoint.x) +
				(point.y - m_StartPoint.y) * (point.y - m_StartPoint.y)));

			DrawCircle(pDc, m_StartPoint.x, m_StartPoint.y, radius);

			//DrawEllipse(pDc, 100, 200);

			return;
		}
		else if (m_IsDrawing == SHAPE_ELLPISE)
		{
			CPoint point;
			GetCursorPos(&point);
			ScreenToClient(&point);

			//DrawCircle(pDc, m_StartPoint.x, m_StartPoint.y, radius);

			pDc->Rectangle(m_StartPoint.x, m_StartPoint.y, point.x, point.y);

			DrawEllipse(
				pDc, 
				(m_StartPoint.x + point.x) / 2,
				(m_StartPoint.y + point.y) / 2,
				(point.x - m_StartPoint.x) / 2 ,
				(point.y - m_StartPoint.y) / 2);

			return;
		}
	}
}

void CExp1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExp1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExp1View ���

#ifdef _DEBUG
void CExp1View::AssertValid() const
{
	CView::AssertValid();
}

void CExp1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExp1Doc* CExp1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp1Doc)));
	return (CExp1Doc*)m_pDocument;
}
#endif //_DEBUG


// CExp1View ��Ϣ�������


//����Բ
void CExp1View::OnDrawCircle()
{
	m_DrawShape = SHAPE_CIRCLE;
}


//������Բ.
void CExp1View::OnDrawEllipse()
{
	m_DrawShape = SHAPE_ELLPISE;

}


//����������
void CExp1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_DrawShape != SHAPE_CIRCLE && m_DrawShape != SHAPE_ELLPISE)
		return;


	m_IsDrawing = m_DrawShape;
	m_StartPoint = point;

	CView::OnLButtonDown(nFlags, point);

	CRect rect;
	InvalidateRect(rect);
}

//�������ɿ�.
void CExp1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//ȡ������

	m_IsDrawing = 0;

	CView::OnLButtonUp(nFlags, point);
}


//void CExp1View::OnMove(int x, int y)
//{
//	CView::OnMove(x, y);
//
//	
//	// TODO:  �ڴ˴������Ϣ����������
//}


void CExp1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_IsDrawing)
		return;

	
	RECT rect;
	GetClientRect(&rect);
	InvalidateRect(&rect, TRUE);
	

	CView::OnMouseMove(nFlags, point);
}


void CExp1View::DrawCircle(CDC* pDC, int start_x, int start_y, int radius)
{
	int p;

	int x = 0;
	int y = radius;

	p = 3 - 2 * radius;

	for (; x <= y; x++)
	{
		//ʵ������һ����8������.
		pDC->SetPixel(start_x + x, start_y + y, 0);
		pDC->SetPixel(start_x + y, start_y + x, 0);				// y = -x �Գ�.

		pDC->SetPixel(start_x - x, start_y + y, 0);
		pDC->SetPixel(start_x + y, start_y - x, 0);
		
		pDC->SetPixel(start_x - x, start_y - y, 0);
		pDC->SetPixel(start_x - y, start_y - x, 0);

		pDC->SetPixel(start_x + x, start_y - y, 0);
		pDC->SetPixel(start_x - y, start_y + x, 0);

		if (p >= 0)
		{
			p += 4 * (x - y) + 10;
			y--;
		}
		else
		{
			p += 4 * x + 6;
		}
	}
}

void CExp1View::DrawEllipse(CDC* pDC,int start_x ,int start_y, int a,int b)
{
	int x, y;
	double d1, d2;
	x = 0;
	y = b;

	d1 = b * b + a * a * (-b + 0.25);

	pDC->SetPixel(start_x + x, start_y + y, 0);
	pDC->SetPixel(start_x + x, start_y - y, 0);

	while (b * b * (x + 1) < a * a * (y - 0.5))
	{
		if (d1 < 0)
		{
			d1 += b * b * (2 * x + 3);
			x++;
		}
		else
		{
			d1 += (b*b*(2 * x + 3) + a * a * (-2 * y + 2));
			x++;
			y--;
		}
		pDC->SetPixel(start_x + x, start_y + y, 0);
		pDC->SetPixel(start_x + x, start_y - y, 0);
		pDC->SetPixel(start_x - x, start_y + y, 0);
		pDC->SetPixel(start_x - x, start_y - y, 0);
	}

	d2 = b * b * ((x + 0.5) * (x + 0.5) - a * a ) + a * a * (y - 1) * (y - 1);

	while (y > 0)
	{
		if (d2 < 0)
		{
			d2 += b*b*(2 * x + 2) + a * a * (-2 * y + 3);
			x++;
			y--;
		}
		else
		{
			d2 += a * a * (-2 * y + 3);
			y--;
		}
		pDC->SetPixel(start_x + x, start_y + y, 0);
		pDC->SetPixel(start_x + x, start_y - y, 0);
		pDC->SetPixel(start_x - x, start_y + y, 0);
		pDC->SetPixel(start_x - x, start_y - y, 0);
	}
}