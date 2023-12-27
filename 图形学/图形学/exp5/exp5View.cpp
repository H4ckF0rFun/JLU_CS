
// exp5View.cpp : Cexp5View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "exp5.h"
#endif

#include "exp5Doc.h"
#include "exp5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cexp5View

IMPLEMENT_DYNCREATE(Cexp5View, CView)

BEGIN_MESSAGE_MAP(Cexp5View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_DRAW, &Cexp5View::OnDraw)
	ON_COMMAND(ID_B, &Cexp5View::OnB)
	ON_COMMAND(ID_BEZIER, &Cexp5View::OnBezier)
	ON_COMMAND(ID_HERMITE, &Cexp5View::OnHermite)
	ON_COMMAND(ID_CLEAR, &Cexp5View::OnClear)
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// Cexp5View 构造/析构

Cexp5View::Cexp5View()
{
	// TODO:  在此处添加构造代码
	m_state = 0;
	m_type = 0;
}

Cexp5View::~Cexp5View()
{
}

BOOL Cexp5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}


// Cexp5View 打印

BOOL Cexp5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cexp5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void Cexp5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// Cexp5View 诊断

#ifdef _DEBUG
void Cexp5View::AssertValid() const
{
	CView::AssertValid();
}

void Cexp5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cexp5Doc* Cexp5View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cexp5Doc)));
	return (Cexp5Doc*)m_pDocument;
}
#endif //_DEBUG


// Cexp5View 消息处理程序

void matrix_mul(float * A, int A_row, int A_col,
	float * B, int B_row, int B_col,
	float * C){

	assert(A_col == B_row);

	for (int i = 0; i < A_row; i++){
		for (int j = 0; j < B_col; j++){
			float temp = 0;
			for (int k = 0; k < A_col; k++){
				temp += A[i * A_col + k] * B[k * B_col + j];
			}
			C[i * B_col + j] = temp;
		}
	}
}



// Cexp5View 绘制

void Cexp5View::OnDraw(CDC* pDC)
{
	Cexp5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < m_Points.GetSize(); i++){
		for (int dx = -1; dx <= 1; dx++){
			for (int dy = -1; dy <= 1; dy++){
				pDC->SetPixel(m_Points[i].x + dx, m_Points[i].y + dy, RGB(255, 0, 0));
			}
		}
	}

	if (m_state == 2){
		switch (m_type)
		{
		case 0:
			DrawHermite(pDC);
			break;
		case 1:
			bez_to_points(pDC);
			break;
		case 2:
			do{
				CArray<float> knot;
				for (int i = 0; i < m_Points.GetSize() + 4; i++){
					knot.Add(i);
				}
				bspline_to_points(pDC, 4, knot.GetData());
			} while (0);
			//
			break;
		default:
			break;
		}
	}
	// TODO:  在此处为本机数据添加绘制代码
}

void Cexp5View::DrawHermite(CDC* pDC)
{
	
	float C[4][2] = { 0 };
	float A[4][4] = { 
		2, -2, 1, 1,
		-3, 3, -2, -1,
		0, 0, 1, 0,
		1, 0, 0, 0 };
		
	float B[4][2] = {
		m_Points[0].x, m_Points[0].y,
		m_Points[3].x , m_Points[3].y,
		m_Points[1].x - m_Points[0].x, m_Points[1].y - m_Points[0].y,
		m_Points[3].x - m_Points[2].x, m_Points[3].y - m_Points[2].y
	};

	matrix_mul((float*)A, 4, 4, (float*)B, 4, 2, (float*)C);

	for (float u = 0; u <= 1; u += 0.0001){
		float x =
			C[0][0] * u * u * u +
			C[1][0] * u * u +
			C[2][0] * u  +
			C[3][0];

		float y =
			C[0][1] * u * u * u +
			C[1][1] * u * u +
			C[2][1] * u  +
			C[3][1];

		pDC->SetPixel(x, y, RGB(0, 255, 0));
	}

	pDC->MoveTo(m_Points[0]);
	pDC->LineTo(m_Points[1]);

	pDC->MoveTo(m_Points[2]);
	pDC->LineTo(m_Points[3]);
	
}

void Cexp5View::bez_to_points(CDC * pDC)
{
	
	float t, delta;

	delta = 1.0 / 20000;
	t = 0;

	for (int i = 0; i <= 20000; i++){
		decas(pDC, t);
		t += delta;
	}

	for (int i = 0; i < m_Points.GetSize() - 1; i++){
		pDC->MoveTo(m_Points[i]);
		pDC->LineTo(m_Points[i + 1]);
	}
}


void Cexp5View::decas(CDC * pDC,float t)
{
	int n = m_Points.GetSize() - 1;
	int m, i;

	CArray<CPoint> R, Q;
	for (int i = 0; i < m_Points.GetSize(); i++){
		R.Add(m_Points[i]);
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
	pDC->SetPixel(R[0], RGB(255, 0, 0));
}

void Cexp5View::deboor(CDC * pDC, int i, int k, float knot[], float u)
{
	float denom, alpha;
	CArray<CPoint> p;
	float epsilon = 0.005;

	for (int j = 0; j < k; j++){
		p.Add(m_Points[i - k + 1 + j]);
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
	pDC->SetPixel(p[k - 1],RGB(255,0,0));
}


void Cexp5View::bspline_to_points(CDC * pDC, int k, float knot[])
{
	float u, delta;
	int i, j;
	int n = m_Points.GetSize() - 1;
	delta = (knot[n + 1] - knot[k - 1]) / 10000;

	i = k - 1;
	u = knot[k - 1];

	for (j = 0; j <= 10000; j++){
		while ((i < n) && (u > knot[i + 1])) i++;
		deboor(pDC, i, k, knot, u);
		u += delta;
	}

	for (int i = 0; i < m_Points.GetSize() - 1; i++){
		pDC->MoveTo(m_Points[i]);
		pDC->LineTo(m_Points[i + 1]);
	}
}



void Cexp5View::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
	if (m_state == 2){
		CView::OnLButtonDown(nFlags, point);
		return;
	}

	if (m_state == 0){
		m_Points.Add(point);
	}

	GetClientRect(rect);
	InvalidateRect(rect);
	

	CView::OnLButtonDown(nFlags, point);
}


void Cexp5View::OnDraw()
{
	CRect rect;
	m_state = 2;
	GetClientRect(rect);
	InvalidateRect(rect);
}


void Cexp5View::OnB()
{
	m_type = 2;

}


void Cexp5View::OnBezier()
{
	m_type = 1;
}


void Cexp5View::OnHermite()
{
	m_type = 0;
}


void Cexp5View::OnClear()
{
	CRect rect;
	m_state = 0;
	m_Points.RemoveAll();


	GetClientRect(rect);
	InvalidateRect(rect);
}



int Cexp5View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	return 0;
}
