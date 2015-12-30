// ItemEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "EditListCtrl.h"
#include "ItemEdit.h"


// CItemEdit

IMPLEMENT_DYNAMIC(CItemEdit, CEdit)

CItemEdit::CItemEdit()
{

}

CItemEdit::~CItemEdit()
{
}


BEGIN_MESSAGE_MAP(CItemEdit, CEdit)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CItemEdit 消息处理程序




DWORD CItemEdit::GetCtrlData()
{
	return m_dwData;
}


void CItemEdit::SetCtrlData(DWORD dwData)
{
	m_dwData = dwData;
}


void CItemEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);

	// TODO:  在此处添加消息处理程序代码
	m_bExchange = TRUE;
}


void CItemEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	// TODO:  在此处添加消息处理程序代码
	CWnd* pParent = this->GetParent();
	::PostMessage(pParent->GetSafeHwnd(), WM_USER_EDIT_END, m_bExchange, 0);
}


BOOL CItemEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message==WM_KEYDOWN)
	{
	if (pMsg->wParam==VK_RETURN)
	{
	CWnd* pParent = this->GetParent();
	m_bExchange = TRUE;
	::PostMessage(pParent->GetSafeHwnd(), WM_USER_EDIT_END, m_bExchange,0);
	return true;
	}
	else
	if (pMsg->wParam==VK_ESCAPE)
	{
	CWnd* pParent = this->GetParent();
	m_bExchange = FALSE;
	::PostMessage(pParent->GetSafeHwnd(), WM_USER_EDIT_END, m_bExchange, 0);
	return true;
	}
	}
	return CEdit::PreTranslateMessage(pMsg);
}
