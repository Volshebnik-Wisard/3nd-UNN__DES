
// DESDlg.h: файл заголовка
//
#pragma once
#include "afxwin.h"
#include <string>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;
// Диалоговое окно CDESDlg

class CDESDlg : public CDialogEx
{
	// Создание
public:
	CDESDlg(CWnd* pParent = nullptr);	// стандартный конструктор

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DES_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


	// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	CStringW OTXT;
	CStringW KEY;
	CStringW CTXT;
	void Decrypt();
	void Crypt();
	afx_msg void OnBnClickedLoadOtxt();
	afx_msg void OnBnClickedSaveOtxt();
	afx_msg void OnBnClickedLoadCtxt();
	afx_msg void OnBnClickedSaveCtxt();
	afx_msg void OnBnClickedGenkey();
	afx_msg void OnBnClickedSavekey();
	afx_msg void OnBnClickedLoadkey();
	CButton RADIO_DEC;
	CButton RADIO_CR;

	afx_msg void OnBnClickedDec();
	afx_msg void OnBnClickedCr();
};


class DES
{
public:

	wstring data;
	wstring key;

	DES(wstring& data_, wstring& key_, bool DoEncrypt)
	{
		wstring data = data_;
		wstring key = key_;
		vector<int> roundKey[16];
		vector<int> binaryKey;
		KeyGenerator(binaryKey, roundKey, key, key.length());


		while (data.length() % 8 != 0)
		{
			data += L'\0';
		}

		vector<int> binaryData;
		DataToBinary(binaryData, data);

		if (DoEncrypt)
		{
			for (int i = 0; i < data.length() / 8; i++)	Encrypt(binaryData, binaryData.begin() + i * 64, roundKey);
			BinaryToString(binaryData);
		}

		else if (!DoEncrypt)
		{
			for (int i = 0; i < data.length() / 8; i++)	Decrypt(binaryData, binaryData.begin() + i * 64, roundKey);
			BinaryToString(binaryData);
		}

	}

	void BinaryToString(vector<int>&);
	void DataToBinary(vector<int>&, wstring&);
	void InitialPermutation(vector<int>::iterator);
	void RInitialPermutation(vector<int>::iterator);
	void KeyGenerator(vector<int>&, vector<int>*, wstring&, int);
	void SPermutation(vector<int>&, vector<int>::iterator, int);
	void FeistelTransform(vector<int>& rkey, vector<int>& dataR);
	void Encrypt(vector<int>&, vector<int>::iterator, vector<int>*);
	void Decrypt(vector<int>&, vector<int>::iterator, vector<int>*);
};