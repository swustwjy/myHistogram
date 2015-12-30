// EditLC.cpp : 实现文件
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



// CEditLC 消息处理程序




void CEditLC::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
	CRect rectCtrl;          //数据项所在区域
	LVHITTESTINFO lvhi;      //用于列表控件子项鼠标点击测试的数据结构
	lvhi.pt = point;         //输入鼠标位置
	int nItem = CListCtrl::SubItemHitTest(&lvhi);  //调用基类的子项测试函数，返回行号
	if (nItem==-1)            //如果鼠标在控件外双击，不做任何处理
	{
		return;
	}
	int nSubItem = lvhi.iSubItem;  //获得列号
	CListCtrl::GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rectCtrl);  //获得子项所在区域，存入rectCtrl
	ShowEdit(TRUE, nItem, nSubItem, rectCtrl); //调用自定义函数，显示编辑框
	CListCtrl::OnLButtonDblClk(nFlags, point); //调用基类鼠标双击事件的响应函数
}


void CEditLC::ShowEdit(BOOL bShow, int nItem, int nIndex, CRect rc)
{
	//如果编辑框对象尚未创建
	if (m_Edit.m_hWnd==NULL)
	{
		//创建一个编辑框（大小为零）
		m_Edit.Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN | WS_BORDER, CRect(0, 0, 0, 0), this, IDC_EDITME);
		m_Edit.ShowWindow(SW_HIDE);                    //隐藏
		//使用默认字体
		CFont tpFont;
		tpFont.CreateStockObject(DEFAULT_GUI_FONT);
		m_Edit.SetFont(&tpFont);
		tpFont.DeleteObject();
	}
	//如果bShow为TRUE，显示编辑框
	if (bShow == TRUE)
	{
		CString strItem = CListCtrl::GetItemText(nItem, nIndex);//获取列表控件中数据项的内容
		m_Edit.MoveWindow(rc);      //移动到子项所在区域
		m_Edit.ShowWindow(SW_SHOW);     //显示控件
		m_Edit.SetWindowText(strItem);  //显示数据
		::SetFocus(m_Edit.GetSafeHwnd()); //设置焦点

		DWORD dt = nItem << 16 | nIndex;    //
		m_Edit.SetCtrlData(dt);             //设置item和iSubitem

		::SendMessage(m_Edit.GetSafeHwnd(), EM_SETSEL, 0, -1);//使数据处于选中状态
	}
	else
		m_Edit.ShowWindow(SW_HIDE);
}


void CEditLC::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
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