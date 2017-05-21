#include "StdAfx.h"
#include "TypeDef.h"
#include "ConstDef.h"
#include "Resource.h"
#include "MyCodeCounterDlg.h"
#include ".\mytools.h"

CMyTools* CMyTools::pMyToolsHandle = NULL;

CMyTools* CMyTools::getInstance()
{
    TRACE("into CMyTools::getInstance()\n");
    if(NULL == pMyToolsHandle)
    {
         MY_NEW(CMyTools, pMyToolsHandle);
    }

    return pMyToolsHandle;
}

void CMyTools::destory()
{
    TRACE("into CMyTools::destory()\n");
    MY_DELETE(pMyToolsHandle);
}

CMyTools::CMyTools(void):
    m_IntLangType(C_AND_CPP),
    m_StrCodeBegin(_T("")),
    m_StrCodeEnd(_T("")),
    m_StrCodePath(_T("")),
    m_StrResult(_T("")),
    m_CodeFileList(0)
{
    m_IntCommentCount = 0;
    m_IntNBNCCount = 0;
    m_IntTotalCount = 0;
    m_bInAreaComment = FALSE;
    m_bInContinueLine = FALSE;

    m_pView = NULL;
}

CMyTools::~CMyTools(void)
{
    m_CodeFileList.clear();
    m_pView = NULL;//这个指针不用delete
}

void CMyTools::setCodeBegin(const CString& strCodeBegin)
{
    m_StrCodeBegin = strCodeBegin;
}

const CString& CMyTools::getCodeBegin(void) const
{
    return m_StrCodeBegin;
}

void CMyTools::setCodeEnd(const CString& strCodeEnd)
{
    m_StrCodeEnd = strCodeEnd;
}

const CString& CMyTools::getCodeEnd(void) const
{
    return m_StrCodeEnd;
}

void CMyTools::setCodePath(const CString& strCodePath)
{
    m_StrCodePath = strCodePath;
}

const CString& CMyTools::getCodePath(void) const
{
    return m_StrCodePath;
}

void CMyTools::setLangType(int intLangType)
{
    m_IntLangType = intLangType;
}

int CMyTools::getLangType(void) const
{
    return m_IntLangType;
}

void CMyTools::setResult(const CString& strResult)
{
    m_StrResult = strResult;
}

const CString& CMyTools::getResult() const
{
    return m_StrResult;
}

void CMyTools::setView(CDialog* pView)
{
    m_pView = pView;
}

CDialog* CMyTools::getView(void) const
{
    return m_pView;
}

void CMyTools::selectPath(void)
{
    TRACE("into CMyTools::selectPath()\n");

    char pszBuffer[MAX_PATH];
    BROWSEINFO bi;  
    LPITEMIDLIST pidl;
    bi.hwndOwner = NULL;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = pszBuffer;
    bi.lpszTitle = SELECT_DIR;
    bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
    bi.lpfn = NULL;
    bi.lParam = 0;
    if((pidl = SHBrowseForFolder(&bi)) != NULL)
    {
        if(SHGetPathFromIDList(pidl, pszBuffer))
        {
            CString strTmpCodePath = pszBuffer;
            if(strTmpCodePath.GetLength() <= 1)
            {
            }
            else 
            {
                if(strTmpCodePath.Right(1) != _T("\\"))
                {
                    strTmpCodePath += _T("\\");
                }
                m_StrCodePath = strTmpCodePath;
            }
        }
        //The calling application is responsible for freeing the returned PIDL
        LPMALLOC pMalloc;
        if(SUCCEEDED(SHGetMalloc(&pMalloc)))
        {
            pMalloc->Free(pidl);
            pMalloc->Release();
        }
    }
}

CString CMyTools::getFileExtension(const CString& strFileName) const
{
    int index = strFileName.ReverseFind('.');
    if(-1 != index)
    {
        return strFileName.Right(strFileName.GetLength() - (index + 1));
    }
    else
    {
        return _T("");
    }
}

BOOL CMyTools::isCorCPPFile(const CString& strFileExtension) const
{
    CString strLower = strFileExtension;
    strLower = strLower.MakeLower();
    BOOL isCFile = strLower == _T("c") || strLower == _T("h");
    BOOL isCPPFile = strLower == _T("cpp") || strLower == _T("cxx")
        || strLower == _T("hpp") || strLower == _T("hxx");

    return isCFile || isCPPFile;

}

BOOL CMyTools::isJavaFile(const CString& strFileExtension) const
{
    //待实现
    return strFileExtension == strFileExtension;
}

BOOL CMyTools::isCodeFile(const CString& strFileName) const
{
    CString strFileExtension = getFileExtension(strFileName);

    switch (m_IntLangType)
    {
        case C_AND_CPP :
            return isCorCPPFile(strFileExtension);
        case JAVA : 
            return isJavaFile(strFileExtension);
        default:
            return FALSE;
    }
}

void CMyTools::getFileList(const CString& strFilePath)
{
    CFileFind finder;
    CString strCurrFileFullName;
    CString strCurrFileName;
    BOOL bFound = finder.FindFile(strFilePath + _T("\\*.*"));
    while ( bFound )
    {
        bFound = finder.FindNextFile();

        if ( finder.IsDots() )
        {
            continue;
        } 
        else if ( finder.IsDirectory() )
        {
            //递归遍历所有子目录
            getFileList( finder.GetFilePath() );
        }
        else
        {
            strCurrFileFullName = finder.GetFilePath();
            strCurrFileName = finder.GetFileName();
            if(TRUE == isCodeFile(strCurrFileName))
            {
                m_CodeFileList.push_back(strCurrFileFullName);
            }
        }
    }
}

void CMyTools::processComment(char* cpDest, const char* cpSrc)
{

}

void CMyTools::processString(char* cpDest, const char* cpSrc)
{
    if('"' != buf[i] && !isInStr)
    {
        cLine[j] = buf[i];
        ++i,++j;
    }
    else if('"' != buf[i] && isInStr)
    {
        if('\\' == buf[i])
        {
            ++i;
        }
        ++i;
    }
    else if('"' == buf[i] && !isInStr)
    {
        isInStr = TRUE;
        ++i;
    }
    else if('"' == buf[i] && isInStr)
    {
        isInStr = FALSE;
        ++i;
    }
    else
    {
        //这种情况不会出现
    }
}
void CMyTools::removeConstStringFromLine(CString& strLine, BOOL isInComment, BOOL isInString) const
{
    LPTSTR buf = strLine.GetBuffer();
    char cLine[512] = {0};

    int i = 0;
    int j = 0;
    while( '\0' != buf[i])
    {
        if(isInComment)
        {
            processComment(cLine, j, buf, i);
            isInComment = FALSE;
        }
        else if(isInString)
        {
            processString(cLine, j, buf, i);
            isInString = FALSE;
        }
        else
        {
            if('"' == buf[i])
            {
                processString(cLine, j, buf, i);
            }
            else if( '/' == buf[i])
            {
                if('/' == buf[i+1])
                {
                    strncpy(cLine+j, buf+i, 512-j);
                    return;
                }
                else if('*' == buf[i+1])
                {
                    processComment(cLine, j, buf, i);
                }
                else
                {
                    cLine[j++] = buf[i++];
                }
            }
            else
            {
                cLine[j++] = buf[i++];
            }
        }
    }
    strLine = cLine;
}

BOOL CMyTools::isBeginLine(const CString& strLine) const
{
    CString strTemp = strLine;
    CString strSub = m_StrCodeBegin;
    return (-1 != strTemp.Find(strSub.GetBuffer()));
}

BOOL CMyTools::isEndLine(const CString& strLine) const
{
    CString strTemp = strLine;
    CString strSub = m_StrCodeEnd;
    return (-1 != strTemp.Find(strSub.GetBuffer()));
}

BOOL CMyTools::isLineCommentLine(const CString& strLine) const
{
    CString strTemp = strLine;
    strTemp.Trim();
    if( (strTemp.Left(2) == _T("//"))
        || ((strTemp.Left(2) == _T("/*")) && (strTemp.Right(2) == _T("*/")) 
            && (strTemp.GetLength() > 3)) ) //长度大于3，防止出现 /*/的情况
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//判断是否以/**/注释完整形式结尾的行
BOOL CMyTools::isEndByAreaCommentFullLine(const CString& strLine) const
{
    CString strTemp = strLine;
    strTemp.Trim();
    removeConstStringFromLine(strTemp);
    if(strTemp.Right(2) == _T("*/"))
    {
    }
}

//判断是否以/**/注释/*结尾的行
BOOL CMyTools::isEndbyAreaCommentHalfLine(const CString& strLine) const
{
}

//判断是否以/**/注释/*开始的行
BOOL CMyTools::isAreaCommentBeginLine(const CString& strLine) const
{
    CString strTemp = strLine;
    strTemp.Trim();
    if(strTemp.Left(2) == _T("/*"))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//判断是否以/**/注释*/结束的行
BOOL CMyTools::isAreaCommentEndLine(const CString& strLine) const
{
    CString strTemp = strLine;
    strTemp.Trim();
    if(strTemp.Right(2) == _T("*/"))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CMyTools::isBlankLine(const CString& strLine) const
{
    CString strTemp = strLine;
    strTemp.Trim();
    if(0 == strTemp.GetLength())
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CMyTools::isContinueLine(const CString& strLine) const
{
    CString strTemp = strLine;
    strTemp.Trim();
    if(strTemp.Right(1) == _T("\\")
        && strTemp.Left(2) != _T("/*")
        && strTemp.Left(2) != _T("//"))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void CMyTools::countLine(const CString& strLine)
{
    ++m_IntTotalCount;

    removeConstStringFromLine(CString& strLine);

    if(!isContinueLine(strLine) && TRUE == m_bInContinueLine)
    {
        ++m_IntNBNCCount;
        m_bInContinueLine = FALSE;
    }
    else if(isContinueLine(strLine))
    {
        ++m_IntNBNCCount;
        m_bInContinueLine = TRUE;
    }
    else if(isLineCommentLine(strLine))
    {
        ++m_IntCommentCount;
    }
    else if(isAreaCommentBeginLine(strLine))
    {
        ++m_IntCommentCount;
        m_bInAreaComment = TRUE;
    }
    else if(isAreaCommentEndLine(strLine))
    {
        ++m_IntCommentCount;
        m_bInAreaComment = FALSE;
    }
    else if(!isBlankLine(strLine) && TRUE == m_bInAreaComment)
    {
        ++m_IntCommentCount;
    }
    else if(!isBlankLine(strLine) && FALSE == m_bInAreaComment)
    {
        ++m_IntNBNCCount;
    }
    return;
}

void CMyTools::countOneFileCode(const CString& strFileFullName)
{
    CString strTemp = strFileFullName;
    char* pFileName = strTemp.GetBuffer(10);
    BOOL countFlag = FALSE;
    FILE* pFile = NULL;
    if( NULL == (pFile = fopen(pFileName, "r")) )
    {
        return;
    }

    char line[1024] = {0};
    int intIncludeCount = 0; //注释嵌套处理
    while(NULL != fgets(line, 1024, pFile))
    {
        if(isBeginLine(line))
        {
            countFlag = TRUE;
            ++intIncludeCount;
        }
        else if(isEndLine(line))
        {
            if(intIncludeCount > 1)
            {
                --intIncludeCount;
            }
            else if (1 == intIncludeCount)
            {
                --intIncludeCount;
                countFlag = FALSE;
            }
        }
        else
        {
            if(TRUE == countFlag)
            {
                countLine(line);
            }
        }
        memset(line, 0, 1024);
    }
    fclose(pFile);
    pFile = NULL;
}

void CMyTools::countCode()
{
    TRACE("into CMyTools::countCode()\n");

    m_CodeFileList.clear();
    m_IntCommentCount = 0;
    m_IntNBNCCount = 0;
    m_IntTotalCount = 0;

    getFileList(m_StrCodePath);

    //设置进度条控件
    CProgressCtrl* pProg = (CProgressCtrl*)m_pView->GetDlgItem(IDC_PROGRESS);
    pProg->SetRange(0, static_cast<short int>(m_CodeFileList.size()));
    pProg->SetPos(0);

    std::list<CString>::const_iterator pos; 
    int iProgressPos = 0;
    for (pos = m_CodeFileList.begin(); pos != m_CodeFileList.end(); ++pos) 
    {
        countOneFileCode(*pos); 
        pProg->SetPos(++iProgressPos);
        //m_pView->
    }

    m_StrResult.Format(_T("统计结果:  NBNC行: %d  注释行: %d  总行数: %d"), 
        m_IntNBNCCount, m_IntCommentCount, m_IntTotalCount);
}
