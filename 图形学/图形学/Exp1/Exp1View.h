
// Exp1View.h : CExp1View ��Ľӿ�
//

#pragma once


class CExp1View : public CView
{
protected: // �������л�����
	CExp1View();
	DECLARE_DYNCREATE(CExp1View)

// ����
public:
	CExp1Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CExp1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	int m_DrawShape;
	int m_IsDrawing;
	CPoint m_StartPoint;

public:


	void DrawCircle(CDC* pDC,int x,int y,int radius);
	void DrawEllipse(CDC* pDC, int start_x, int start_y, int a, int b);

	afx_msg void OnDrawCircle();
	afx_msg void OnDrawEllipse();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMove(int x, int y);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Exp1View.cpp �еĵ��԰汾
inline CExp1Doc* CExp1View::GetDocument() const
   { return reinterpret_cast<CExp1Doc*>(m_pDocument); }
#endif

