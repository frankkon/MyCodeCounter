// MyCodeCounterDlg.cpp : ʵ���ļ�
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


// CMyCodeCounterDlg �Ի���



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


// CMyCodeCounterDlg ��Ϣ�������

BOOL CMyCodeCounterDlg::OnInitDialog()
{
	// ���ؼ�����Ĭ��ֵ
    m_StrCodePath = DEFAULT_CODE_PATH;
    m_IntLangType = C_AND_CPP;
    m_StrResult = CONUT_RESULT_COMMENT;

    CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyCodeCounterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CMyCodeCounterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyCodeCounterDlg::OnBnClickedCount()
{
    TRACE("into CMyCodeCounterDlg::OnBnClickedCount()\n");

    //�ӿؼ��л�ô���·���ͱ�ͳ�����Ե�������Ϣ
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


    //ִ�д���ͳ��
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

    //��ͳ�ƽ����ʾ���ı��ؼ���
    UpdateData(FALSE);
}

void CMyCodeCounterDlg::OnOK()
{
    TRACE("into CMyCodeCounterDlg::OnOK()\n");
}

void CMyCodeCounterDlg::OnCancel()
{
    // TODO: �ڴ����ר�ô����/����û���
    TRACE("into CMyCodeCounterDlg::OnCancel()\n");
}

void CMyCodeCounterDlg::OnBnClickedExit()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    TRACE("into CMyCodeCounterDlg::OnBnClickedExit()\n");
    CMyTools::destory();
    CDialog::OnCancel();
}

void CMyCodeCounterDlg::OnBnClickedShowpath()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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
