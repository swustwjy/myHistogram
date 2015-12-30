
// EditListCtrlDlg.h : 头文件
//

#pragma once
#include "EditLC.h"
#include "afxcmn.h"

// CEditListCtrlDlg 对话框
class CEditListCtrlDlg : public CDialogEx
{
// 构造
public:
	CEditListCtrlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EDITLISTCTRL_DIALOG };
	CEditLC m_LC;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

};
