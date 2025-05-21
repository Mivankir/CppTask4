#include "pch.h"
#include "MyDictApp.h"
#include "MyDictAppDlg.h"
#include "afxdialogex.h"
#include <codecvt>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMyDictAppDlg::CMyDictAppDlg(CWnd* pParent)
    : CDialogEx(IDD_MYDICTAPP_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDictAppDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_WORDS, m_listWords);
    DDX_Control(pDX, IDC_RADIO_ALPHA, m_radioAlpha);
    DDX_Control(pDX, IDC_RADIO_FREQ, m_radioFreq);
}

BEGIN_MESSAGE_MAP(CMyDictAppDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_LOAD, &CMyDictAppDlg::OnBnClickedBtnLoad)
    ON_BN_CLICKED(IDC_BTN_SAVE, &CMyDictAppDlg::OnBnClickedBtnSave)
    ON_BN_CLICKED(IDC_RADIO_ALPHA, &CMyDictAppDlg::OnBnClickedRadioAlpha)
    ON_BN_CLICKED(IDC_RADIO_FREQ, &CMyDictAppDlg::OnBnClickedRadioFreq)
END_MESSAGE_MAP()

BOOL CMyDictAppDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    // Настройка списка: два столбца
    m_listWords.InsertColumn(0, L"Слово", LVCFMT_LEFT, 150);
    m_listWords.InsertColumn(1, L"Частота", LVCFMT_LEFT, 70);

    // По умолчанию — алфавит
    m_radioAlpha.SetCheck(BST_CHECKED);
    UpdateList();

    return TRUE;
}

void CMyDictAppDlg::OnPaint()
{
    if (IsIconic()) {
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        dc.DrawIcon(x, y, m_hIcon);
    }
    else {
        CDialogEx::OnPaint();
    }
}

HCURSOR CMyDictAppDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CMyDictAppDlg::OnBnClickedBtnLoad()
{
    CFileDialog dlg(TRUE, L"txt", nullptr, 0, L"Text Files (*.txt)|*.txt|All Files|*.*||");
    if (dlg.DoModal() != IDOK) return;

    try {
        dict_.loadFromFile(dlg.GetPathName().GetString());
        logger_.log(Level::Info, L"Loaded file: " + dlg.GetPathName().GetString());
        UpdateList();
    }
    catch (const exception& ex) {
        // конвертация UTF-8 сообщения в wstring
        wstring msg = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(ex.what());
        logger_.log(Level::Error, msg);
        AfxMessageBox(L"Ошибка при загрузке файла");
    }
}

void CMyDictAppDlg::OnBnClickedBtnSave()
{
    CFileDialog dlg(FALSE, L"txt", nullptr, 0, L"Text Files (*.txt)|*.txt|All Files|*.*||");
    if (dlg.DoModal() != IDOK) return;

    try {
        dict_.saveToFile(dlg.GetPathName().GetString());
        logger_.log(Level::Info, L"Saved file: " + dlg.GetPathName().GetString());
    }
    catch (const exception& ex) {
        wstring msg = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(ex.what());
        logger_.log(Level::Error, msg);
        AfxMessageBox(L"Ошибка при сохранении файла");
    }
}

void CMyDictAppDlg::OnBnClickedRadioAlpha()
{
    UpdateList();
}

void CMyDictAppDlg::OnBnClickedRadioFreq()
{
    UpdateList();
}

void CMyDictAppDlg::UpdateList()
{
    m_listWords.DeleteAllItems();
    auto vec = (m_radioAlpha.GetCheck() == BST_CHECKED)
        ? dict_.getByAlphabet()
        : dict_.getByFrequency();

    for (int i = 0; i < static_cast<int>(vec.size()); ++i) {
        m_listWords.InsertItem(i, vec[i].first.c_str());
        m_listWords.SetItemText(i, 1, to_wstring(vec[i].second).c_str());
    }
}
