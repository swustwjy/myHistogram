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
	BOOL m_bExchange;   //�Ƿ�������ݽ���
	DWORD m_dwData;     //���༭�������к���Ϣ

public:
	DWORD GetCtrlData();
	void SetCtrlData(DWORD dwData);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


