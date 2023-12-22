
// Exp3View.h : CExp3View ��Ľӿ�
//

#pragma once


typedef struct _point
{
	double x, y, z;
}point_t;

typedef struct _edge
{
	point_t p[2];
}edge_t;

typedef struct _face
{
	edge_t e[4];
}face_t;




class CExp3View : public CView
{
protected: // �������л�����
	CExp3View();
	DECLARE_DYNCREATE(CExp3View)

// ����
public:
	CExp3Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CExp3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

#define SHADOW_MODE_0    0
#define SHADOW_MODE_1	 1


	typedef struct _Point
	{
		double x, y, z;
	}Point;

	int DrawMode;
	int RotateMode;

	point_t m_ViewPoint;
	point_t cube_center;
	face_t cube[6];
	HBRUSH m_Brushs[6];

	void Draw(CDC *pDC);
	void Line(CDC* pDC, CPoint* displayPoint);

	void Rotate(int mode,int angle);			//��ĳһ������ת
	void Scale(int delta);
	void Move(int direction, int delta);

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRotateX();
	afx_msg void OnRotateY();
	afx_msg void OnRotateZ();
	afx_msg void OnShadow0();
	afx_msg void OnShadow1();
};

#ifndef _DEBUG  // Exp3View.cpp �еĵ��԰汾
inline CExp3Doc* CExp3View::GetDocument() const
   { return reinterpret_cast<CExp3Doc*>(m_pDocument); }
#endif

