
// EditListCtrlDlg.h : ͷ�ļ�
//

#pragma once
#include "EditLC.h"
#include "afxcmn.h"

// CEditListCtrlDlg �Ի���
class CEditListCtrlDlg : public CDialogEx
{
// ����
public:
	CEditListCtrlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EDITLISTCTRL_DIALOG };
	CEditLC m_LC;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

};
