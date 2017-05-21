// MyCodeCounterDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMyCodeCounterDlg 对话框
class CMyCodeCounterDlg : public CDialog
{
// 构造
public:
	CMyCodeCounterDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYCODECOUNTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedCount();
    afx_msg void OnBnClickedExit();

private:
    // 代码文件所在目录
    CString m_StrCodePath;
    // 被统计的语言类型
    int m_IntLangType;
    // 显示统计结果
    CString m_StrResult;
    // 代码开始标志字符串
    CString m_StrCodeBegin;
    // 代码结束标志字符串
    CString m_StrCodeEnd;

protected:
    virtual void OnOK();
    virtual void OnCancel();
public:
    afx_msg void OnBnClickedShowpath();
};
