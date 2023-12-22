
// Exp4View.cpp : CExp4View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Exp4.h"
#endif

#include "Exp4Doc.h"
#include "Exp4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExp4View

IMPLEMENT_DYNCREATE(CExp4View, CView)

BEGIN_MESSAGE_MAP(CExp4View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CExp4View ����/����

CExp4View::CExp4View()
{
	// TODO:  �ڴ˴���ӹ������
	m_state = 0;
}

CExp4View::~CExp4View()
{
}

BOOL CExp4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

bool intersect(CPoint p0, CPoint p1, CPoint p2, CPoint p3)
{
	CPoint a, b, c, d;
	a.x = p2.x - p0.x;
	a.y = p2.y - p0.y;

	b.x = p3.x - p0.x;
	b.y = p3.y - p0.y;
	//
	c.x = p3.x - p1.x;
	c.y = p3.y - p1.y;

	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;

	int r0 = (a.x * b.y - a.y * b.x) * (d.x * c.y - d.y * c.x);
	int r1 = (a.x * d.x - a.y * d.y) * (b.x * c.y - b.y * c.x);

	return r0 < 0 && r1 < 0;

}

int x_intersect(int x1, int y1, int x2, int y2,
	int x3, int y3, int x4, int y4)
{
	int num = (x1*y2 - y1*x2) * (x3 - x4) -
		(x1 - x2) * (x3*y4 - y3*x4);
	
	int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	return num / den;
}


int y_intersect(int x1, int y1, int x2, int y2,
	int x3, int y3, int x4, int y4)
{
	int num = (x1*y2 - y1*x2) * (y3 - y4) -
		(y1 - y2) * (x3*y4 - y3*x4);
	int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return num / den;
}


void Clip(CRect &rect,CPoint edges[2], CArray<CPoint> & Poly)
{
	int x1 = edges[0].x;
	int x2 = edges[1].x;

	int y1 = edges[0].y;
	int y2 = edges[1].y;

	CArray<CPoint> ClipPoly;

	// (ix,iy),(kx,ky) are the co-ordinate values of
	// the points
	for (int i = 0; i < Poly.GetSize(); i++)
	{
		// i and k form a line in polygon
		int k = (i + 1) % Poly.GetSize();
		int ix = Poly[i].x, iy = Poly[i].y;
		int kx = Poly[k].x, ky = Poly[k].y;

		// Calculating position of first point
		// w.r.t. clipper line
		int i_pos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);

		// Calculating position of second point
		// w.r.t. clipper line
		int k_pos = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);

		// Case 1 : When both points are inside
		if (i_pos > 0 && k_pos > 0)
		{
			ClipPoly.Add(CPoint(kx, ky));
		}

		// Case 2: When only first point is outside
		else if (i_pos <= 0 && k_pos > 0)
		{
			// Point of intersection with edge
			// and the second point is added
			ClipPoly.Add(CPoint(x_intersect(x1,
				y1, x2, y2, ix, iy, kx, ky),
				y_intersect(x1,
				y1, x2, y2, ix, iy, kx, ky)));

			ClipPoly.Add(CPoint(kx, ky));
		}

		// Case 3: When only second point is outside
		else if (i_pos > 0 && k_pos <= 0)
		{
			//Only point of intersection with edge is added
			ClipPoly.Add(CPoint(x_intersect(x1,
				y1, x2, y2, ix, iy, kx, ky),
				y_intersect(x1,
				y1, x2, y2, ix, iy, kx, ky)));

		}

		// Case 4: When both points are outside
		else
		{
			//No points are added
		}
	}

	// and changing the no. of vertices
	Poly.RemoveAll();
	for (int i = 0; i < ClipPoly.GetSize(); i++)
	{
		Poly.Add(ClipPoly[i]);
	}
}

void CExp4View::OnDraw(CDC* pDC)
{
	CExp4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	pDC->SelectObject(m_Pen0);
	if (m_state > 0)
	{
		pDC->SetPixel(m_rect_p0, RGB(0, 0, 0));
	}

	CPoint point;
	if (m_state == 1)
	{
		GetCursorPos(&point);
		ScreenToClient(&point);
	}
	else if (m_state > 1)
	{
		point = m_rect_p1;
	}
	pDC->SetPixel(point, RGB(0, 0, 0));

	if (m_state >= 1)
	{
		pDC->Rectangle(m_rect_p0.x, m_rect_p0.y,
			point.x, point.y);
	}
	

	pDC->SelectObject(m_Pen1);

	if (m_state > 1)	//����������,������N����,
	{
		for (int i = 0; i < m_Shape.GetSize() - 1; i++)
		{
			CPoint p0 = m_Shape[i];
			CPoint p1 = m_Shape[i + 1];

			pDC->MoveTo(p0);
			pDC->LineTo(p1);
		}

		CPoint point;
		if (m_state != 3)
		{
			GetCursorPos(&point);
			ScreenToClient(&point);
		}
		else
		{
			point = m_Shape[0];
		}

		if (m_Shape.GetSize() > 0)
		{
			pDC->MoveTo(m_Shape[m_Shape.GetSize() - 1]);
			pDC->LineTo(point);
		}
	}

	pDC->SelectObject(m_Pen2);

	if (m_state == 3)		//������,�ü�.
	{
		CArray <CPoint> temp;
		for (int i = 0; i < m_Shape.GetSize(); i++)
		{
			temp.Add(m_Shape[i]);
		}

		CPoint edge[4][2];
		edge[0][0] = m_rect_p0;
		edge[0][1] = m_rect_p0;
		edge[0][1].x = m_rect_p1.x;

		edge[1][0] = m_rect_p0;
		edge[1][1] = m_rect_p1;
		edge[1][0].x = m_rect_p1.x;

		edge[2][0] = m_rect_p1;
		edge[2][1] = m_rect_p1;
		edge[2][1].x = m_rect_p0.x;

		edge[3][0] = edge[2][1];
		edge[3][1] = edge[3][0];
		edge[3][1].y = m_rect_p0.y;

		//�ü�����.
		for (int i = 0; i < 4; i++)
		{
			CRect rect;
			rect.left = m_rect_p0.x;
			rect.top = m_rect_p0.y;

			rect.right = m_rect_p1.x;
			rect.bottom = m_rect_p1.y;

			Clip(rect, edge[i], temp);

		}

		for (int i = 0; i < temp.GetSize(); i++)
		{
			pDC->MoveTo(temp[i].x, temp[i].y);
			pDC->LineTo(
				temp[(i + 1) % temp.GetSize()].x,
				temp[(i + 1) % temp.GetSize()].y);
		}
		printf("");
	}
}


// CExp4View ��ӡ

BOOL CExp4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CExp4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CExp4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CExp4View ���

#ifdef _DEBUG
void CExp4View::AssertValid() const
{
	CView::AssertValid();
}

void CExp4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExp4Doc* CExp4View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp4Doc)));
	return (CExp4Doc*)m_pDocument;
}
#endif //_DEBUG


// CExp4View ��Ϣ�������
void CExp4View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_state == 0)
	{
		m_rect_p0 = point;
		m_state++;
	}
	else if (m_state == 1)
	{
		m_rect_p1 = point;
		m_state++;
	}
	else
	{
		//��������.
		m_Shape.Add(point);
	}

	CView::OnLButtonDown(nFlags, point);
}


void CExp4View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_state > 0 && m_state != 3)
	{
		CRect rect;
		GetClientRect(rect);
		InvalidateRect(rect);
	}

	CView::OnMouseMove(nFlags, point);
}


void CExp4View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_state == 2 && m_Shape.GetSize() >=3 )
	{
		CRect rect;
		m_state = 3;
		GetClientRect(rect);
		InvalidateRect(rect);
	}
	CView::OnLButtonDblClk(nFlags, point);
}


int CExp4View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CDC* pDC = GetDC();

	m_Pen0 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_Pen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pen2 = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	return 0;
}


void CExp4View::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	DeleteObject(m_Pen0);
	DeleteObject(m_Pen1);
	DeleteObject(m_Pen2);

	CView::OnClose();
}
