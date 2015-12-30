#pragma once


// CItemEdit

class CItemEdit : public CEdit
{
	DECLARE_DYNAMIC(CItemEdit)

public:
	CItemEdit();
	virtual ~CItemEdit();

protected:
	DECLARE_MESSAGE_MAP()
//private:
public:
	BOOL m_bExchange;   //是否进行数据交换
	DWORD m_dwData;     //待编辑区域行列号信息

public:
	DWORD GetCtrlData();
	void SetCtrlData(DWORD dwData);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


