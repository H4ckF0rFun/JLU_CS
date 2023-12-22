
// Exp6View.h : CExp6View 类的接口
//

#pragma once


class CExp6View : public CView
{
protected: // 仅从序列化创建
	CExp6View();
	DECLARE_DYNCREATE(CExp6View)

// 特性
public:
	CExp6Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CExp6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	HDC hMemDC;


	int dx;
	int dy;

	int m_ok;
	int m_Start;
	CArray<CPoint> m_Points;

public:

	void CExp6View::bez_to_points(HDC hDC, const CArray<CPoint>& Points);
	void CExp6View::decas(HDC hDC, float t, const CArray<CPoint>& Points);

	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // Exp6View.cpp 中的调试版本
inline CExp6Doc* CExp6View::GetDocument() const
   { return reinterpret_cast<CExp6Doc*>(m_pDocument); }
#endif

