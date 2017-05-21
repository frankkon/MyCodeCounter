// MyCodeCounterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyCodeCounter.h"
#include "MyCodeCounterDlg.h"
#include "ConstDef.h"
#include "TypeDef.h"
#include "MyTools.h"
#include ".\mycodecounterdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyCodeCounterDlg 对话框



CMyCodeCounterDlg::CMyCodeCounterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyCodeCounterDlg::IDD, pParent)
    , m_StrCodePath(_T(""))
    , m_IntLangType(0)
    , m_StrResult(_T(""))
    , m_StrCodeBegin(_T(""))
    , m_StrCodeEnd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyCodeCounterDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_PATH, m_StrCodePath);
    DDV_MaxChars(pDX, m_StrCodePath, 256);
    DDX_CBIndex(pDX, IDC_LANG, m_IntLangType);
    DDX_Text(pDX, IDC_RESULT, m_StrResult);
    DDX_Text(pDX, IDC_CODEBEGIN, m_StrCodeBegin);
    DDV_MaxChars(pDX, m_StrCodeBegin, 256);
    DDX_Text(pDX, IDC_CODEEND, m_StrCodeEnd);
	DDV_MaxChars(pDX, m_StrCodeEnd, 256);
}

BEGIN_MESSAGE_MAP(CMyCodeCounterDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_COUNT, OnBnClickedCount)
    ON_BN_CLICKED(IDC_EXIT, OnBnClickedExit)
    ON_BN_CLICKED(IDC_SHOWPATH, OnBnClickedShowpath)
END_MESSAGE_MAP()


// CMyCodeCounterDlg 消息处理程序

BOOL CMyCodeCounterDlg::OnInitDialog()
{
	// 给控件设置默认值
    m_StrCodePath = DEFAULT_CODE_PATH;
    m_IntLangType = C_AND_CPP;
    m_StrResult = CONUT_RESULT_COMMENT;

    CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyCodeCounterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMyCodeCounterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyCodeCounterDlg::OnBnClickedCount()
{
    TRACE("into CMyCodeCounterDlg::OnBnClickedCount()\n");

    //从控件中获得代码路径和被统计语言的类型信息
    UpdateData(TRUE);
    m_StrCodePath.Trim();
    m_StrCodeBegin.Trim();
    m_StrCodeEnd.Trim();

    if(0 == m_StrCodePath.GetLength()
        || 0 == m_StrCodeBegin.GetLength()
        || 0 == m_StrCodeEnd.GetLength())
    {
        m_StrResult = CONUT_RESULT_INFO_NOT_FINISH;
        UpdateData(FALSE);
        return;
    }


    //执行代码统计
    CMyTools* pMyTool = CMyTools::getInstance();
    if(NULL == pMyTool)
    {
        m_StrResult = CONUT_RESULT_SYS_ERR;
    }
    else
    {
        pMyTool->setLangType(m_IntLangType);
        pMyTool->setCodePath(m_StrCodePath);
        pMyTool->setCodeBegin(m_StrCodeBegin);
        pMyTool->setCodeEnd(m_StrCodeEnd);

        pMyTool->setView(this);

        pMyTool->countCode();
        m_StrResult = pMyTool->getResult();
    }

    //将统计结果显示在文本控件中
    UpdateData(FALSE);
}

void CMyCodeCounterDlg::OnOK()
{
    TRACE("into CMyCodeCounterDlg::OnOK()\n");
}

void CMyCodeCounterDlg::OnCancel()
{
    // TODO: 在此添加专用代码和/或调用基类
    TRACE("into CMyCodeCounterDlg::OnCancel()\n");
}

void CMyCodeCounterDlg::OnBnClickedExit()
{
    // TODO: 在此添加控件通知处理程序代码
    TRACE("into CMyCodeCounterDlg::OnBnClickedExit()\n");
    CMyTools::destory();
    CDialog::OnCancel();
}

void CMyCodeCounterDlg::OnBnClickedShowpath()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    CMyTools* pMyTool = CMyTools::getInstance();
    if(NULL == pMyTool)
    {
        m_StrResult = CONUT_RESULT_SYS_ERR;
    }
    else
    {
        pMyTool->selectPath();
        m_StrCodePath = pMyTool->getCodePath();
    }

    UpdateData(FALSE);

}
