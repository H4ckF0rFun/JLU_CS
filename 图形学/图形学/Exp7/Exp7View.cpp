
// Exp7View.cpp : CExp7View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Exp7.h"
#endif

#include "Exp7Doc.h"
#include "Exp7View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExp7View

IMPLEMENT_DYNCREATE(CExp7View, CView)

BEGIN_MESSAGE_MAP(CExp7View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExp7View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_43B, &CExp7View::On43b)
	ON_WM_CREATE()
	ON_COMMAND(ID_DUICHEN, &CExp7View::OnDuichen)
	ON_COMMAND(ID_3D, &CExp7View::On3d)
	ON_COMMAND(ID_CLEAR, &CExp7View::OnClear)
END_MESSAGE_MAP()

// CExp7View ����/����

CExp7View::CExp7View()
{
	// TODO:  �ڴ˴���ӹ������
	m_state = 0;
}

CExp7View::~CExp7View()
{
}

BOOL CExp7View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CExp7View ����

void CExp7View::OnDraw(CDC* pDC)
{
	CExp7Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	if (m_state == 0)
	{
		for (int i = 0; i < m_Points.GetSize() - 1; i++)
		{
			pDC->MoveTo(m_Points[i]);
			pDC->LineTo(m_Points[i + 1]);
		}

		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);

		if (m_Points.GetSize() > 0)
		{
			pDC->MoveTo(m_Points[m_Points.GetSize() - 1]);
			pDC->LineTo(pt); 
		}
	}
	else if (m_state >= 2)
	{
		if (m_state != 4)
		{
			m_TmpPoints.RemoveAll();

			for (int i = 0; i < m_Points.GetSize(); i++)
			{
				if (i == 0 || i == m_Points.GetSize() - 1)
				{
					m_TmpPoints.Add(m_Points[i]);
					m_TmpPoints.Add(m_Points[i]);
				}
				m_TmpPoints.Add(m_Points[i]);
			}

			CArray<float> knot;

			for (int i = 0; i < m_TmpPoints.GetSize() + 4; i++)
			{
				knot.Add(i);
			}
			bspline_to_points(pDC, 4, knot.GetData());
		}
		
		if (m_state == 3)
		{
			m_TmpPoints.RemoveAll();
			int x1 = m_Points[0].x;

			for (int i = 0; i < m_Points.GetSize(); i++)
			{
				CPoint tmp = m_Points[i];
				tmp.x = x1 * 2 - m_Points[i].x;

				if (i == 0 || i == m_Points.GetSize() - 1)
				{
					m_TmpPoints.Add(tmp);
					m_TmpPoints.Add(tmp);
				}
				m_TmpPoints.Add(tmp);
			}

			CArray<float> knot;

			for (int i = 0; i < m_TmpPoints.GetSize() + 4; i++)
			{
				knot.Add(i);
			}
			bspline_to_points(pDC, 4, knot.GetData());
		}

		if (m_state == 4)
		{
			m_TmpPoints.RemoveAll();

			for (int i = 0; i < m_Points.GetSize(); i++)
			{
				if (i == 0 || i == m_Points.GetSize() - 1)
				{
					m_TmpPoints.Add(m_Points[i]);
					m_TmpPoints.Add(m_Points[i]);
				}
				m_TmpPoints.Add(m_Points[i]);
			}

			CArray<float> knot;

			for (int i = 0; i < m_TmpPoints.GetSize() + 4; i++)
			{
				knot.Add(i);
			}
			bspline_to_points3(pDC, 4, knot.GetData());
		}
	}

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CExp7View ��ӡ


void CExp7View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CExp7View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CExp7View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CExp7View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CExp7View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExp7View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExp7View ���

#ifdef _DEBUG
void CExp7View::AssertValid() const
{
	CView::AssertValid();
}

void CExp7View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExp7Doc* CExp7View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp7Doc)));
	return (CExp7Doc*)m_pDocument;
}
#endif //_DEBUG


// CExp7View ��Ϣ�������


void CExp7View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_state == 0)
	{
		m_Points.Add(point);
		InvalidateRect(NULL);
	}
	CView::OnLButtonDown(nFlags, point);
}


void CExp7View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_state == 0)
	{
		InvalidateRect(NULL);
	}
	CView::OnMouseMove(nFlags, point);
}


void CExp7View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_state == 0)
	{
		m_state = 1;
	}
	CView::OnLButtonDblClk(nFlags, point);
}



void CExp7View::deboor(CDC * pDC, int i, int k, float knot[], float u)
{
	float denom, alpha;
	CArray<CPoint> p;
	float epsilon = 0.005;

	for (int j = 0; j < k; j++){
		p.Add(m_TmpPoints[i - k + 1 + j]);
	}

	for (int r = 1; r < k; r++)
	{
		for (int m = k - 1; m >= r; m--)
		{
			int j;
			j = m + i - k + 1;
			denom = knot[j + k - r] - knot[j];
			if (fabs(denom) < epsilon)
				alpha = 0;
			else
				alpha = (u - knot[j]) / denom;

			p[m].x = (1 - alpha) * p[m - 1].x + alpha* p[m].x;
			p[m].y = (1 - alpha) * p[m - 1].y + alpha* p[m].y;
		}
	}
	pDC->SetPixel(p[k - 1], m_CurrentColor);
}


void CExp7View::bspline_to_points(CDC * pDC, int k, float knot[])
{
	float u, delta;
	int i, j;
	int n = m_TmpPoints.GetSize() - 1;
	delta = (knot[n + 1] - knot[k - 1]) / 10000;

	i = k - 1;
	u = knot[k - 1];

	int last_i = -1;

	for (j = 0; j <= 10000; j++){
		while ((i < n) && (u > knot[i + 1])) i++;
		deboor(pDC, i, k, knot, u);
		if (i != last_i)
		{
			last_i = i;
			m_CurrentColor = m_colors[i % 3];
			TRACE(TEXT("%d\n"), i);
		}
		u += delta;
	}

	for (int i = 0; i < m_TmpPoints.GetSize() - 1; i++){
		pDC->MoveTo(m_TmpPoints[i]);
		pDC->LineTo(m_TmpPoints[i + 1]);
	}
}



void CExp7View::On43b()
{
	m_state = 2;
	InvalidateRect(NULL);
}


int CExp7View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_colors[0] = RGB(255, 0, 0);
	m_colors[1] = RGB(0, 255, 0);
	m_colors[2] = RGB(0, 0, 255);
	return 0;
}


void CExp7View::OnDuichen()
{
	m_state = 3;
	InvalidateRect(NULL);
}



void CExp7View::deboor3(CDC * pDC, int i, int k, float knot[], float u)
{
	float denom, alpha;
	CArray<CPoint> p;
	float epsilon = 0.005;

	for (int j = 0; j < k; j++){
		p.Add(m_TmpPoints[i - k + 1 + j]);
	}

	for (int r = 1; r < k; r++)
	{
		for (int m = k - 1; m >= r; m--)
		{
			int j;
			j = m + i - k + 1;
			denom = knot[j + k - r] - knot[j];
			if (fabs(denom) < epsilon)
				alpha = 0;
			else
				alpha = (u - knot[j]) / denom;

			p[m].x = (1 - alpha) * p[m - 1].x + alpha* p[m].x;
			p[m].y = (1 - alpha) * p[m - 1].y + alpha* p[m].y;
		}
	}
	/*
		��ת����������,��ת18��.
	
	*/

	Point spacePoint;
	double delta = m_Points[0].x;

#define PI 3.1415926535

	//�ƶ���y���غ�.
	spacePoint.x = p[k - 1].x - delta;
	spacePoint.y = p[k - 1].y;
	spacePoint.z = 0;

#define ST  0.17453292519943295
#define SIN_BETA 0.8944271909999159
#define COS_BETA 0.4472135954999579

	//��ת18��.
	for (int i = 0; i < 36; i++)
	{
		double x_1 = spacePoint.x * cos(ST) + spacePoint.z * sin(ST);
		double z_1 = spacePoint.z * cos(ST) - spacePoint.x * sin(ST);
		spacePoint.x = x_1;
		spacePoint.z = z_1;

		//б����ͶӰ
		double display_x;
		double display_y;

		display_x = spacePoint.x + spacePoint.z * 0.5 * COS_BETA;
		display_y = spacePoint.y + spacePoint.z * 0.5 * SIN_BETA;

		pDC->SetPixel(display_x + delta, display_y, m_CurrentColor);
	}
}


void CExp7View::bspline_to_points3(CDC * pDC, int k, float knot[])
{
	float u, delta;
	int i, j;
	int n = m_TmpPoints.GetSize() - 1;
	delta = (knot[n + 1] - knot[k - 1]) / 10000;

	i = k - 1;
	u = knot[k - 1];

	int last_i = -1;

	for (j = 0; j <= 10000; j++){
		while ((i < n) && (u > knot[i + 1])) i++;
		deboor3(pDC, i, k, knot, u);
		if (i != last_i)
		{
			last_i = i;
			m_CurrentColor = m_colors[i % 3];
			TRACE(TEXT("%d\n"), i);
		}
		u += delta;
	}
}


void CExp7View::On3d()
{
	m_state = 4;
	InvalidateRect(NULL);
}


void CExp7View::OnClear()
{
	m_state = 0;
	m_Points.RemoveAll();
	InvalidateRect(NULL);
}
