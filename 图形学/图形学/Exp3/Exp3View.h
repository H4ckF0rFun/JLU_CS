
// Exp3View.h : CExp3View 类的接口
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
protected: // 仅从序列化创建
	CExp3View();
	DECLARE_DYNCREATE(CExp3View)

// 特性
public:
	CExp3Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
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

	void Rotate(int mode,int angle);			//绕某一个轴旋转
	void Scale(int delta);
	void Move(int direction, int delta);

// 生成的消息映射函数
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

#ifndef _DEBUG  // Exp3View.cpp 中的调试版本
inline CExp3Doc* CExp3View::GetDocument() const
   { return reinterpret_cast<CExp3Doc*>(m_pDocument); }
#endif

