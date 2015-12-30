// EditLC.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EditListCtrl.h"
#include "EditLC.h"

// CEditLC

IMPLEMENT_DYNAMIC(CEditLC, CListCtrl)

CEditLC::CEditLC()
{
	m_Edit.m_hWnd = NULL;
}

CEditLC::~CEditLC()
{
}


BEGIN_MESSAGE_MAP(CEditLC, CListCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(NM_CLICK, &CEditLC::OnNMClick)
	ON_MESSAGE(WM_USER_EDIT_END,OnEditEnd)
END_MESSAGE_MAP()



// CEditLC ��Ϣ�������




void CEditLC::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*LVHITTESTINFO lvhi;
	lvhi.pt = point;
	if (SubItemHitTest(&lvhi)!=-1)
	{
		m_Row = lvhi.iItem;
		m_Col = lvhi.iSubItem;
		if (m_Edit.m_hWnd==NULL)
		{
			RECT rect;
			rect.left = rect.top = 0;
			rect.bottom = 20;
			rect.right = 20;
			m_Edit.Create(WS_CHILD | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN | ES_MULTILINE, rect, this, IDC_EDITME);
			m_Edit.SetFont(this->GetFont(), FALSE);
		}
		CRect rect;
		GetSubItemRect(lvhi.iItem, lvhi.iSubItem, LVIR_BOUNDS, rect);
		m_Edit.SetWindowText(this->GetItemText(lvhi.iItem, lvhi.iSubItem));
		m_Edit.MoveWindow(&rect, TRUE);
		m_Edit.ShowWindow(1);
	}*/
	CRect rectCtrl;          //��������������
	LVHITTESTINFO lvhi;      //�����б�ؼ�������������Ե����ݽṹ
	lvhi.pt = point;         //�������λ��
	int nItem = CListCtrl::SubItemHitTest(&lvhi);  //���û����������Ժ����������к�
	if (nItem==-1)            //�������ڿؼ���˫���������κδ���
	{
		return;
	}
	int nSubItem = lvhi.iSubItem;  //����к�
	CListCtrl::GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rectCtrl);  //��������������򣬴���rectCtrl
	ShowEdit(TRUE, nItem, nSubItem, rectCtrl); //�����Զ��庯������ʾ�༭��
	CListCtrl::OnLButtonDblClk(nFlags, point); //���û������˫���¼�����Ӧ����
}


void CEditLC::ShowEdit(BOOL bShow, int nItem, int nIndex, CRect rc)
{
	//����༭�������δ����
	if (m_Edit.m_hWnd==NULL)
	{
		//����һ���༭�򣨴�СΪ�㣩
		m_Edit.Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN | WS_BORDER, CRect(0, 0, 0, 0), this, IDC_EDITME);
		m_Edit.ShowWindow(SW_HIDE);                    //����
		//ʹ��Ĭ������
		CFont tpFont;
		tpFont.CreateStockObject(DEFAULT_GUI_FONT);
		m_Edit.SetFont(&tpFont);
		tpFont.DeleteObject();
	}
	//���bShowΪTRUE����ʾ�༭��
	if (bShow == TRUE)
	{
		CString strItem = CListCtrl::GetItemText(nItem, nIndex);//��ȡ�б�ؼ��������������
		m_Edit.MoveWindow(rc);      //�ƶ���������������
		m_Edit.ShowWindow(SW_SHOW);     //��ʾ�ؼ�
		m_Edit.SetWindowText(strItem);  //��ʾ����
		::SetFocus(m_Edit.GetSafeHwnd()); //���ý���

		DWORD dt = nItem << 16 | nIndex;    //
		m_Edit.SetCtrlData(dt);             //����item��iSubitem

		::SendMessage(m_Edit.GetSafeHwnd(), EM_SETSEL, 0, -1);//ʹ���ݴ���ѡ��״̬
	}
	else
		m_Edit.ShowWindow(SW_HIDE);
}


void CEditLC::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_Edit.m_hWnd!=NULL)
	{
		DWORD dwStyle = m_Edit.GetStyle();
		if ((dwStyle&WS_VISIBLE)==WS_VISIBLE)
		{
			m_Edit.ShowWindow(SW_HIDE);
		}
	}
	*pResult = 0;
}

LRESULT CEditLC::OnEditEnd(WPARAM wParam, LPARAM lParam  /*= FALSE*/ )
{
	if (wParam==TRUE)
	{
		CString strText(_T(""));
		m_Edit.GetWindowText(strText);
		
		DWORD dwData = m_Edit.GetCtrlData();
		int nItem = dwData >> 16;
		int nIndex = dwData & 0x0000ffff;
		CListCtrl::SetItemText(nItem, nIndex, strText);
	}
	if (lParam==FALSE)
	{
		m_Edit.ShowWindow(SW_HIDE);
	}
	return 0;
}