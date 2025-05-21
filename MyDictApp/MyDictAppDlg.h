
// MyDictAppDlg.h: файл заголовка
//

#pragma once
#include "Dictionary.h"
#include "Logger.h"

// Диалоговое окно CMyDictAppDlg
class CMyDictAppDlg : public CDialogEx
{
// Создание
public:
	CMyDictAppDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYDICTAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


protected:
    HICON m_hIcon;

    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();

    // Обработчики
    afx_msg void OnBnClickedBtnLoad();
    afx_msg void OnBnClickedBtnSave();
    afx_msg void OnBnClickedRadioAlpha();
    afx_msg void OnBnClickedRadioFreq();

    DECLARE_MESSAGE_MAP()

private:
    // Контролы
    CListCtrl    m_listWords;
    CButton      m_radioAlpha;
    CButton      m_radioFreq;

    // Логика
    Dictionary   dict_;
    Logger       logger_{ L"app.log" };

    // Обновить список слов по выбранному режиму
    void UpdateList();
};