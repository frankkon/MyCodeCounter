// MyCodeCounterDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMyCodeCounterDlg �Ի���
class CMyCodeCounterDlg : public CDialog
{
// ����
public:
	CMyCodeCounterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYCODECOUNTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedCount();
    afx_msg void OnBnClickedExit();

private:
    // �����ļ�����Ŀ¼
    CString m_StrCodePath;
    // ��ͳ�Ƶ���������
    int m_IntLangType;
    // ��ʾͳ�ƽ��
    CString m_StrResult;
    // ���뿪ʼ��־�ַ���
    CString m_StrCodeBegin;
    // ���������־�ַ���
    CString m_StrCodeEnd;

protected:
    virtual void OnOK();
    virtual void OnCancel();
public:
    afx_msg void OnBnClickedShowpath();
};
