// ItemEdit.cpp : ʵ���ļ�
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



// CItemEdit ��Ϣ�������




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

	// TODO:  �ڴ˴������Ϣ����������
	m_bExchange = TRUE;
}


void CItemEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	// TODO:  �ڴ˴������Ϣ����������
	CWnd* pParent = this->GetParent();
	::PostMessage(pParent->GetSafeHwnd(), WM_USER_EDIT_END, m_bExchange, 0);
}


BOOL CItemEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
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
