#pragma once
#include <list>

class CMyTools
{
public:
    ~CMyTools(void);

    void setCodeBegin(const CString& strCodeBegin);
    const CString& getCodeBegin(void) const;

    void setCodeEnd(const CString& strCodeEnd);
    const CString& getCodeEnd(void) const;

    void setCodePath(const CString& strCodePath);
    const CString& getCodePath(void) const;

    void setLangType(int intLangType);
    int getLangType(void) const;

    void setResult(const CString& strResult);
    const CString& getResult() const;

    void setView(CDialog* pView);
    CDialog* getView(void) const;

    void selectPath(void);
    CString getFileExtension(const CString& strFileName) const;
    BOOL isCorCPPFile(const CString& strFileExtension) const;
    BOOL isJavaFile(const CString& strFileExtension) const;
    BOOL isCodeFile(const CString& strFileName) const;
    void getFileList(const CString& strFilePath);
    void countOneFileCode(const CString& strFileFullName);
    void countCode();

    static CMyTools* getInstance();
    static void destory();

protected:
    CMyTools(void);

    void processComment(char* cpDest, const char* cpSrc) const;
    void processString(char* cpDest, const char* cpSrc) const;
    void removeConstStringFromLine(CString& strLine) const;
    BOOL isBeginLine(const CString& strLine) const;
    BOOL isEndLine(const CString& strLine) const;
    BOOL isLineCommentLine(const CString& strLine) const;
    BOOL isEndByAreaCommentFullLine(const CString& strLine) const;
    BOOL isEndbyAreaCommentHalfLine(const CString& strLine) const;
    BOOL isAreaCommentBeginLine(const CString& strLine) const;
    BOOL isAreaCommentEndLine(const CString& strLine) const;
    BOOL isBlankLine(const CString& strLine) const;
    BOOL isContinueLine(const CString& strLine) const;
    void countLine(const CString& strLine);

private:
    int m_IntLangType;
    CString m_StrCodeBegin;
    CString m_StrCodeEnd;
    CString m_StrCodePath;
    CString m_StrResult;
    std::list<CString> m_CodeFileList;

    int m_IntCommentCount;
    int m_IntNBNCCount;
    int m_IntTotalCount;

    BOOL m_bInAreaComment;
    BOOL m_bInContinueLine;

    CDialog* m_pView;

    static CMyTools* pMyToolsHandle;
};
