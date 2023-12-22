
// Exp3View.cpp : CExp3View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Exp3.h"
#endif

#include "Exp3Doc.h"
#include "Exp3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define edge_length 120

// CExp3View

IMPLEMENT_DYNCREATE(CExp3View, CView)

BEGIN_MESSAGE_MAP(CExp3View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_ROTATE_X, &CExp3View::OnRotateX)
	ON_COMMAND(ID_ROTATE_Y, &CExp3View::OnRotateY)
	ON_COMMAND(ID_ROTATE_Z, &CExp3View::OnRotateZ)
	ON_COMMAND(ID_SHADOW_0, &CExp3View::OnShadow0)
	ON_COMMAND(ID_SHADOW_1, &CExp3View::OnShadow1)
END_MESSAGE_MAP()

// CExp3View ����/����


//ͶӰƽ��.

CExp3View::CExp3View()
{
	// TODO:  �ڴ˴���ӹ������
	DrawMode = SHADOW_MODE_0;

	m_ViewPoint.x = 20;
	m_ViewPoint.y = 0;
	m_ViewPoint.z = 300;

	cube_center.x = 0;
	cube_center.y = 0;
	cube_center.z = 0;

	RotateMode = 0;		//x

	//

	//�� ,˳ʱ��.
	cube[0].e[0].p[0] = point_t{ edge_length, edge_length, edge_length };
	cube[0].e[0].p[1] = point_t{ edge_length, -edge_length, edge_length };
	cube[0].e[1].p[0] = point_t{ edge_length, -edge_length, edge_length };
	cube[0].e[1].p[1] = point_t{ edge_length, -edge_length, -edge_length };
	cube[0].e[2].p[0] = point_t{ edge_length, -edge_length, -edge_length };
	cube[0].e[2].p[1] = point_t{ edge_length, edge_length, -edge_length };
	cube[0].e[3].p[0] = point_t{ edge_length, edge_length, -edge_length };
	cube[0].e[3].p[1] = point_t{ edge_length, edge_length, edge_length };

	//��,��ʱ��.
	cube[1].e[0].p[0] = point_t{ edge_length, edge_length, edge_length };
	cube[1].e[0].p[1] = point_t{ edge_length, edge_length, -edge_length };
	cube[1].e[1].p[0] = point_t{ edge_length, edge_length, -edge_length };
	cube[1].e[1].p[1] = point_t{ -edge_length, edge_length, -edge_length };
	cube[1].e[2].p[0] = point_t{ -edge_length, edge_length, -edge_length };
	cube[1].e[2].p[1] = point_t{ -edge_length, edge_length, edge_length };
	cube[1].e[3].p[0] = point_t{ -edge_length, edge_length, edge_length };
	cube[1].e[3].p[1] = point_t{ edge_length, edge_length, edge_length };

	//ǰ,��ʱ��
	cube[2].e[0].p[0] = point_t{ edge_length, edge_length, edge_length };
	cube[2].e[0].p[1] = point_t{ -edge_length, edge_length, edge_length };
	cube[2].e[1].p[0] = point_t{ -edge_length, edge_length, edge_length };
	cube[2].e[1].p[1] = point_t{ -edge_length, -edge_length, edge_length };
	cube[2].e[2].p[0] = point_t{ -edge_length, -edge_length, edge_length };
	cube[2].e[2].p[1] = point_t{ edge_length, -edge_length, edge_length };
	cube[2].e[3].p[0] = point_t{ edge_length, -edge_length, edge_length };
	cube[2].e[3].p[1] = point_t{ edge_length, edge_length, edge_length };

	//��
	cube[3].e[0].p[0] = point_t{ -edge_length, edge_length, edge_length };
	cube[3].e[0].p[1] = point_t{ -edge_length, edge_length, -edge_length };
	
	cube[3].e[1].p[0] = point_t{ -edge_length, edge_length, -edge_length };
	cube[3].e[1].p[1] = point_t{ -edge_length, -edge_length, -edge_length };

	cube[3].e[2].p[0] = point_t{ -edge_length, -edge_length, -edge_length };
	cube[3].e[2].p[1] = point_t{ -edge_length, -edge_length, edge_length };
	
	cube[3].e[3].p[0] = point_t{ -edge_length, -edge_length, edge_length };
	cube[3].e[3].p[1] = point_t{ -edge_length, edge_length, edge_length };
	
	//��
	cube[4].e[0].p[0] = point_t{ edge_length, edge_length, -edge_length };
	cube[4].e[0].p[1] = point_t{ edge_length, -edge_length, -edge_length };
	
	cube[4].e[1].p[0] = point_t{ edge_length, -edge_length, -edge_length };
	cube[4].e[1].p[1] = point_t{ -edge_length, -edge_length, -edge_length };

	cube[4].e[2].p[0] = point_t{ -edge_length, -edge_length, -edge_length };
	cube[4].e[2].p[1] = point_t{ -edge_length, edge_length, -edge_length };
	cube[4].e[3].p[0] = point_t{ -edge_length, edge_length, -edge_length };
	cube[4].e[3].p[1] = point_t{ edge_length, edge_length, -edge_length };


	//��.
	cube[5].e[0].p[0] = point_t{ edge_length, -edge_length, edge_length };
	cube[5].e[0].p[1] = point_t{ -edge_length, -edge_length, edge_length };

	cube[5].e[1].p[0] = point_t{ -edge_length, -edge_length, edge_length };
	cube[5].e[1].p[1] = point_t{ -edge_length, -edge_length, -edge_length };

	cube[5].e[2].p[0] = point_t{ -edge_length, -edge_length, -edge_length };
	cube[5].e[2].p[1] = point_t{ edge_length, -edge_length, -edge_length };
	cube[5].e[3].p[0] = point_t{ edge_length, -edge_length, -edge_length };
	cube[5].e[3].p[1] = point_t{ edge_length, -edge_length, edge_length };


	m_Brushs[0] = CreateSolidBrush(RGB(255, 0, 0));
	m_Brushs[1] = CreateSolidBrush(RGB(0, 255, 0));
	m_Brushs[2] = CreateSolidBrush(RGB(0, 0, 255));
	m_Brushs[3] = CreateSolidBrush(RGB(255, 255, 0));
	m_Brushs[4] = CreateSolidBrush(RGB(128, 0, 128));
	m_Brushs[5] = CreateSolidBrush(RGB(255, 165, 0));

}

CExp3View::~CExp3View()
{
	for (int i = 0; i < 6; i++)
	{
		DeleteObject(m_Brushs[i]);
	}
}

BOOL CExp3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CExp3View ����




void CExp3View::OnDraw(CDC* pDC)
{
	CExp3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Draw(pDC);
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CExp3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExp3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExp3View ���

#ifdef _DEBUG
void CExp3View::AssertValid() const
{
	CView::AssertValid();
}

void CExp3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExp3Doc* CExp3View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp3Doc)));
	return (CExp3Doc*)m_pDocument;
}
#endif //_DEBUG


// CExp3View ��Ϣ�������

#define SIN_BETA 0.8944271909999159
#define COS_BETA 0.4472135954999579


void CExp3View::Line(CDC *pDC, CPoint* displayPoint)
{
	pDC->MoveTo(displayPoint[0]);
	pDC->LineTo(displayPoint[1]);

	pDC->MoveTo(displayPoint[0]);
	pDC->LineTo(displayPoint[2]);

	pDC->MoveTo(displayPoint[0]);
	pDC->LineTo(displayPoint[4]);

	////////////////////////////////
	pDC->MoveTo(displayPoint[6]);
	pDC->LineTo(displayPoint[2]);

	pDC->MoveTo(displayPoint[6]);
	pDC->LineTo(displayPoint[4]);

	pDC->MoveTo(displayPoint[6]);
	pDC->LineTo(displayPoint[7]);


	////////////////////////////////
	pDC->MoveTo(displayPoint[3]);
	pDC->LineTo(displayPoint[1]);

	pDC->MoveTo(displayPoint[3]);
	pDC->LineTo(displayPoint[2]);

	pDC->MoveTo(displayPoint[3]);
	pDC->LineTo(displayPoint[7]);

	////////////////////////////////
	pDC->MoveTo(displayPoint[5]);
	pDC->LineTo(displayPoint[1]);

	pDC->MoveTo(displayPoint[5]);
	pDC->LineTo(displayPoint[4]);

	pDC->MoveTo(displayPoint[5]);
	pDC->LineTo(displayPoint[7]);


}

void CExp3View::Draw(CDC *pDC)
{
	pDC->SetWindowOrg(-600,-600);

	CRect rect;
	GetClientRect(rect);

	if (DrawMode == SHADOW_MODE_0)
	{
		face_t temp[6];
		memcpy(temp, cube, sizeof(cube));

		for (int i = 0; i < 6; i++)
		{
			point_t face_center = { 0 };
			int cnt = 0;
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					face_center.x += cube[i].e[j].p[k].x;
					face_center.y += cube[i].e[j].p[k].y;
					face_center.z += cube[i].e[j].p[k].z;

					cnt++;
				}
			}
			face_center.x /= cnt;
			face_center.y /= cnt;
			face_center.z /= cnt;
			//

			//���㵱ǰƽ���Ƿ�yc
			point_t vec_0;
			vec_0.x = face_center.x - cube_center.x;
			vec_0.y = face_center.y - cube_center.y;
			vec_0.z = face_center.z - cube_center.z;

			point_t vec_1;
			vec_1.x = -0.5 * COS_BETA;
			vec_1.y = -0.5 * SIN_BETA;
			vec_1.z = 1;
			//

			double product;
			product = vec_0.x * vec_1.x + vec_0.y * vec_1.y + vec_0.z * vec_1.z;

			if (product > 0)
			{
				for (int j = 0; j < 4; j++)
				{
					int display[2][2] = { 0 };
					for (int k = 0; k < 2; k++)
					{
						double x = cube[i].e[j].p[k].x;
						double y = cube[i].e[j].p[k].y;
						double z = cube[i].e[j].p[k].z;

						temp[i].e[j].p[k].x = x + z * 0.5 * COS_BETA;
						temp[i].e[j].p[k].y = y + z * 0.5 * SIN_BETA;
					}
				}

				CPoint m_Points[5];
				for (int j = 0; j < 4; j++)
				{
					m_Points[j].x = temp[i].e[j % 4].p[0].x;
					m_Points[j].y = temp[i].e[j % 4].p[0].y;
				}
				pDC->SelectObject(m_Brushs[i]);
				pDC->Polygon(m_Points, 4);
			}
		}
	}
	else if (DrawMode == SHADOW_MODE_1)
	{
		face_t temp[6];
		memcpy(temp, cube, sizeof(cube));

		for (int i = 0; i < 6; i++)
		{
			//������.
			for (int j = 0; j < 4; j++)
			{
				//͸��ͶӰתΪ��ֱͶӰ.
				for (int k = 0; k < 2; k++)
				{
					double x = cube[i].e[j].p[k].x;
					double y = cube[i].e[j].p[k].y;
					double d = -cube[i].e[j].p[k].z;
					temp[i].e[j].p[k].x = x + d * (m_ViewPoint.x - x) * 1.0 / (m_ViewPoint.z + d);
					temp[i].e[j].p[k].y = y + d * (m_ViewPoint.y - y) * 1.0 / (m_ViewPoint.z + d);	
				}
			}
			//
			//����ƽ����ⷨ����.
			////͸��ͶӰתΪ��ͶӰ֮��,����������ĳ�����Ƿ�ɼ�.
			////�ȼ���һ����ķ�����.
			point_t v0, v1;
			v0.x = temp[i].e[0].p[1].x - temp[i].e[0].p[0].x;
			v0.y = temp[i].e[0].p[1].y - temp[i].e[0].p[0].y;
			v0.z = temp[i].e[0].p[1].z - temp[i].e[0].p[0].z;


			v1.x = temp[i].e[3].p[0].x - temp[i].e[3].p[1].x;
			v1.y = temp[i].e[3].p[0].y - temp[i].e[3].p[1].y;
			v1.z = temp[i].e[3].p[0].z - temp[i].e[3].p[1].z;

			point_t vec_0;
			vec_0.x = v0.y * v1.z - v1.y * v0.z;
			vec_0.y = -(v0.x * v1.z - v1.x * v0.z);
			vec_0.z = (v0.x * v1.y - v1.x * v0.y);


			//��תΪ͸��ͶӰ֮��۲�����z ����
			point_t vec_1;
			vec_1.x = 0;
			vec_1.y = 0;
			vec_1.z = m_ViewPoint.z;

			double product;
			product = vec_0.x * vec_1.x + vec_0.y * vec_1.y + vec_0.z * vec_1.z;

			if (product > 0)
			{
				CPoint m_Points[5];
				for (int j = 0; j < 4; j++)
				{
					m_Points[j].x = temp[i].e[j % 4].p[0].x;
					m_Points[j].y = temp[i].e[j % 4].p[0].y;
				}
				pDC->SelectObject(m_Brushs[i]);
				pDC->Polygon(m_Points, 4);
			}
		}
	}
}



void CExp3View::Move(int direction, int delta)
{

}

//mode ��˳ʱ�뻹����ʱ��.
//0 ˳ʱ��

#define PI 3.1415926535

void CExp3View::Rotate(int mode, int angle)
{
	if (mode == 1)
	{
		angle = -angle;
	}

	double f_angle = PI * angle / 180;

	////��תΪ˳ʱ��.
	////���ƶ���ԭ��.

	point_t dt = cube_center;
	face_t temp[6];

	memcpy(temp, cube, sizeof(cube));

	dt.x *= -1;
	dt.y *= -1;
	dt.z *= -1;

	//���ƶ���ԭ��.
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				temp[i].e[j].p[k].x += dt.x;
				temp[i].e[j].p[k].y += dt.y;
				temp[i].e[j].p[k].z += dt.z;
			}
		}
	}

	if (RotateMode == 0)
	{
		//��x����ת,ֻ����y��z.
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					double y = temp[i].e[j].p[k].y;
					double z = temp[i].e[j].p[k].z;
					temp[i].e[j].p[k].y = cos(f_angle) * y - sin(f_angle) * z;
					temp[i].e[j].p[k].z = sin(f_angle) * y + cos(f_angle) * z;
				}
			}
		}
	}
	else if (RotateMode == 1)
	{
		//��y����ת,ֻ����x��z.
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					double x = temp[i].e[j].p[k].x;
					double z = temp[i].e[j].p[k].z;

					temp[i].e[j].p[k].x = (cos(f_angle) * x - sin(f_angle) * z);
					temp[i].e[j].p[k].z = (sin(f_angle) * x + cos(f_angle) * z);
				}
			}
		}
	}
	else if (RotateMode == 2)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					double x = temp[i].e[j].p[k].x;
					double y = temp[i].e[j].p[k].y;

					temp[i].e[j].p[k].x = (cos(f_angle) * x - sin(f_angle) * y);
					temp[i].e[j].p[k].y = (sin(f_angle) * x + cos(f_angle) * y);
				}
			}
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				temp[i].e[j].p[k].x -= dt.x;
				temp[i].e[j].p[k].y -= dt.y;
				temp[i].e[j].p[k].z -= dt.z;
			}
		}
	}
	
	memcpy(cube, temp,sizeof(cube));
}

void CExp3View::Scale(int delta)
{
	//����,��Ҫ�Ƚ�������������ƶ���ԭ��,Ȼ���������.
	//��μ������ĵ�.

	point_t dt = cube_center;
	face_t temp[6];

	memcpy(temp, cube, sizeof(cube));

	dt.x *= -1;
	dt.y *= -1;
	dt.z *= -1;

	delta /= 4;
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				temp[i].e[j].p[k].x += dt.x;
				temp[i].e[j].p[k].y += dt.y;
				temp[i].e[j].p[k].z += dt.z;

				//����.
				double scale_k = (edge_length + delta) * 1.0 / edge_length;

				temp[i].e[j].p[k].x *= scale_k;
				temp[i].e[j].p[k].y *= scale_k;
				temp[i].e[j].p[k].z *= scale_k;

				//���ƶ���ȥ
				temp[i].e[j].p[k].x -= dt.x;
				temp[i].e[j].p[k].y -= dt.y;
				temp[i].e[j].p[k].z -= dt.z;
			}
		}
	}

	//
	memcpy(cube, temp, sizeof(cube));
}

BOOL CExp3View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CRect rect;

	Scale(zDelta);

	GetClientRect(rect);
	InvalidateRect(rect);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


#define MOVE_STEP 20

void CExp3View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int delta_x = 0;
	int delta_y = 0;
	int delta_z = 0;

	switch (nChar)
	{
	case 'i':
		delta_z = -MOVE_STEP;
		break;
	case 'j':
		delta_z = MOVE_STEP;
		break;
	case 'a':
		delta_x = -MOVE_STEP;
		break;
	case 'd':
		delta_x = MOVE_STEP;
		break;
	case 'w':
		delta_y = -MOVE_STEP;
		break;
	case 's':
		delta_y = MOVE_STEP;
		break;
	default:
		break;
	}


	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				//���ƶ���ȥ
				cube[i].e[j].p[k].x += delta_x;
				cube[i].e[j].p[k].y += delta_y;
				cube[i].e[j].p[k].z += delta_z;
			}
		}
	}

	//
	cube_center.x += delta_x;
	cube_center.y += delta_y;
	cube_center.z += delta_z;

	CRect rect;
	GetClientRect(rect);

	InvalidateRect(rect);
}


#define ROTATE_STEP 10

void CExp3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	if (nChar != VK_LEFT && nChar != VK_RIGHT)
	{
		return CView::OnKeyDown(nChar, nRepCnt, nFlags);
	}

	if (nChar == VK_LEFT)
	{
		Rotate(0, ROTATE_STEP);
	}
	else if (nChar == VK_RIGHT)
	{
		Rotate(1, ROTATE_STEP);
	}
	
	CRect rect;
	GetClientRect(rect);

	InvalidateRect(rect);
	return;
}


void CExp3View::OnRotateX()
{
	RotateMode = 0;
}


void CExp3View::OnRotateY()
{
	RotateMode = 1;
}


void CExp3View::OnRotateZ()
{
	RotateMode = 2;
}


void CExp3View::OnShadow0()
{
	CRect rect;
	DrawMode = 0;
	GetClientRect(rect);
	InvalidateRect(rect);
}


#include "ViewPointDlg.h"

void CExp3View::OnShadow1()
{
	CViewPointDlg dlg;

	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	m_ViewPoint.x = atoi(CW2A(dlg.m_X));
	m_ViewPoint.y = atoi(CW2A(dlg.m_Y));
	m_ViewPoint.z = atoi(CW2A(dlg.m_Z));

	CRect rect;
	DrawMode = 1;
	GetClientRect(rect);
	InvalidateRect(rect);
}
