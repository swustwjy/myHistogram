#pragma once
//#define WM_USER_EDIT_END WM_USER+1001

// CEditLC
#include "ItemEdit.h"
class CEditLC : public CListCtrl
{
	DECLARE_DYNAMIC(CEditLC)

public:
	CEditLC();
	virtual ~CEditLC();
	CItemEdit m_Edit;
	int m_Row;
	int m_Col;
protected:
	afx_msg LRESULT OnEditEnd(WPARAM wParam, LPARAM lParam = FALSE);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void ShowEdit(BOOL bShow, int nItem, int nIndex, CRect rc=CRect(0,0,0,0));
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	
};


