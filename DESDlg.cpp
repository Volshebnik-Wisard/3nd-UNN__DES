
// DESDlg.cpp: файл реализации
//

#include <math.h>
#include "pch.h"
#include "framework.h"
#include "DES.h"
#include "DESDlg.h"
#include "afxdialogex.h"


#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <sstream>
#include <ctime>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
wstring buffCr;

// Диалоговое окно CDESDlg
CDESDlg::CDESDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DES_DIALOG, pParent)
	, OTXT(L"Ware wa naseru kotoba nogotoku Ware wa tsukuru kotoba nogotoku Ware wa kowasu kotoba nogotoku	Shizumi izuru kurikaesu hi yo")
	, KEY(L"Buttom click plz --------------> ")
	, CTXT(L"")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDESDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OTXT, OTXT);
	DDX_Text(pDX, IDC_KEY, KEY);
	DDX_Text(pDX, IDC_CTXT, CTXT);
	DDX_Control(pDX, IDC_DEC, RADIO_DEC);
	DDX_Control(pDX, IDC_CR, RADIO_CR);

}

BEGIN_MESSAGE_MAP(CDESDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_OTXT, &CDESDlg::OnBnClickedLoadOtxt)
	ON_BN_CLICKED(IDC_SAVE_OTXT, &CDESDlg::OnBnClickedSaveOtxt)
	ON_BN_CLICKED(IDC_LOAD_CTXT, &CDESDlg::OnBnClickedLoadCtxt)
	ON_BN_CLICKED(IDC_SAVE_CTXT, &CDESDlg::OnBnClickedSaveCtxt)
	ON_BN_CLICKED(IDC_GENKEY, &CDESDlg::OnBnClickedGenkey)
	ON_BN_CLICKED(IDC_SAVEKEY, &CDESDlg::OnBnClickedSavekey)
	ON_BN_CLICKED(IDC_LOADKEY, &CDESDlg::OnBnClickedLoadkey)
	ON_BN_CLICKED(IDC_DEC, &CDESDlg::OnBnClickedDec)
	ON_BN_CLICKED(IDC_CR, &CDESDlg::OnBnClickedCr)
END_MESSAGE_MAP()


// Обработчики сообщений CDESDlg

BOOL CDESDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CDESDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDESDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDESDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//функции нажатия кнопок в окне
void CDESDlg::OnBnClickedLoadOtxt()
{
	CFileDialog FileForEnc(TRUE);
	if (FileForEnc.DoModal() != IDOK) return;
	wfstream file;
	file.open(FileForEnc.GetPathName(), wfstream::in | wfstream::binary);
	wstring str = L"";
	if (file.is_open()) {
		wchar_t c;

		while (file >> noskipws >> c) {
			str += c;
		}
	}
	OTXT = str.c_str();
	file.close();
	UpdateData(FALSE);
}


void CDESDlg::OnBnClickedSaveOtxt()
{
	UpdateData(TRUE);
	CFileDialog FileForEnc(FALSE);
	if (FileForEnc.DoModal() != IDOK) return;
	wfstream file;
	file.open(FileForEnc.GetPathName(), wfstream::out | wfstream::binary);
	wstring otxt = OTXT;
	for (wchar_t c : otxt) {
		file << c;
	}
	file.close();
	UpdateData(FALSE);
}


void CDESDlg::OnBnClickedLoadCtxt()
{
	CFileDialog FileForEnc(TRUE);
	if (FileForEnc.DoModal() != IDOK) return;
	wfstream file;
	file.open(FileForEnc.GetPathName(), wfstream::in | wfstream::binary);
	wstring str = L"";
	if (file.is_open()) {
		wchar_t c;

		while (file >> noskipws >> c) {
			str += c;
		}
	}
	CTXT = str.c_str();
	file.close();
	UpdateData(FALSE);
}


void CDESDlg::OnBnClickedSaveCtxt()
{
	UpdateData(TRUE);
	CFileDialog FileForEnc(FALSE);
	if (FileForEnc.DoModal() != IDOK) return;
	wfstream file;
	file.open(FileForEnc.GetPathName(), wfstream::out | wfstream::binary);
	wstring ctxt = CTXT;
	for (wchar_t c : ctxt) {
		file << c;
	}
	file.close();
	UpdateData(FALSE);
}



void CDESDlg::OnBnClickedSavekey()
{
	UpdateData(TRUE);
	CFileDialog FileForEnc(FALSE);
	if (FileForEnc.DoModal() != IDOK) return;
	wfstream file;
	file.open(FileForEnc.GetPathName(), wfstream::out | wfstream::binary);
	wstring key = KEY;
	for (wchar_t c : key) {
		file << c;
	}
	file.close();
	UpdateData(FALSE);
}


void CDESDlg::OnBnClickedLoadkey()
{
	CFileDialog FileForEnc(TRUE);
	if (FileForEnc.DoModal() != IDOK) return;
	wfstream file;
	file.open(FileForEnc.GetPathName(), wfstream::in | wfstream::binary);
	wstring str = L"";
	if (file.is_open()) {
		wchar_t c;
		while (file >> noskipws >> c) {
			str += c;
		}
	}
	KEY = str.c_str();
	file.close();
	UpdateData(FALSE);
}

void CDESDlg::OnBnClickedGenkey()
{
	wstring key = L"";
	srand(time(0));
	wchar_t c;
	for (int i = 0; i < 7; i++)
	{
		c = 33 + (int)(93 * (rand() * 1.0 / RAND_MAX));
		key += c;
	}
	KEY = key.c_str();
	UpdateData(FALSE);
}



void DES::BinaryToString(vector<int>& data)
{
	this->data = L"";
	wchar_t c;
	for (int j = 0; j < data.size() / 64; j++) {
		for (int i = 0; i < 8; i++)
		{
			c = 0;
			for (int k = 0; k < 8; k++)
			{
				c += pow(2, 7 - k) * data[i * 8 + k + j * 64];
			}
			this->data += c;
		}
	}

}


void DES::DataToBinary(vector<int>& biD, wstring& data)
{

	bitset<8>* bin = new bitset<8>[data.length()];
	for (int i = 0; i < data.length(); i++)
	{
		bin[i] = bitset<8>(data[i]);
		for (int k = 7; k >= 0; k--)
		{
			biD.push_back(bin[i][k]);

		}
	}

	delete[] bin;

}

void DES::InitialPermutation(vector<int>::iterator biD)
{

	vector<int> buf(biD, biD + 64);


	int IP[64] =
	{ 58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7, };


	for (int i = 0; i < 64; i++)
	{
		*(biD + i) = buf[IP[i] - 1];
	}


}

void DES::RInitialPermutation(vector<int>::iterator biD)
{

	vector<int> buf(biD, biD + 64);


	int rIP[64] =
	{
		40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25
	};


	for (int i = 0; i < 64; i++)
	{
		*(biD + i) = buf[rIP[i] - 1];
	}



}


void DES::KeyGenerator(vector<int>& biK, vector<int>* rkey, wstring& data, int cLength)
{

	bitset<8>* bin = new bitset<8>[cLength];
	for (int i = 0; i < cLength; i++)
	{
		bin[i] = bitset<8>(data[i]);
		for (int k = 7; k >= 0; k--)
		{
			biK.push_back(bin[i][k]);

		}
	}



	bool parity = 0;
	for (int i = 1; i < 64; i++)
	{
		parity ^= biK[i - 1];
		if ((i + 1) % 8 == 0)
		{
			biK.insert(biK.begin() + i, parity);

		}

	}


	int CD[56] =
	{
		57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4
	};

	int shift[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

	int P[48] =
	{
		14, 17, 11, 24, 1, 5,
		3, 28, 15, 6, 21, 10,
		23, 19, 12, 4, 26, 8,
		16, 7, 27, 20, 13, 2,
		41, 52, 31, 37, 47, 55,
		30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53,
		46, 42, 50, 36, 29, 32
	};

	int shifts = 0;
	for (int i = 0; i < 16; i++)
	{
		shifts += shift[i];
		for (int k = 0; k < 48; k++)
		{

			rkey[i].push_back(biK[CD[28 * ((28 + P[k] - 1) / 56) + (P[k] + shifts - 1) % 28]]);

		}
	}


}

void DES::SPermutation(vector<int>& buf, vector<int>::iterator it, int n)
{
	int S[8][4][16] =
	{
		{
			{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
			{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
			{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
			{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
		},
		{
			{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
			{ 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
			{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
			{ 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
		},
		{
			{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
			{ 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
			{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
			{ 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }
		},
		{
			{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
			{ 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
			{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
			{ 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
		},
		{
			{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
			{ 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
			{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
			{ 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
		},
		{
			{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
			{ 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
			{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
			{ 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
		},
		{
			{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
			{ 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
			{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
			{ 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
		},
		{
			{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
			{ 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
			{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
			{ 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
		}
	};

	int row = 2 * (*it) + *(it + 5);
	int col = 8 * (*(it + 1)) + 4 * (*(it + 2)) + 2 * (*(it + 3)) + 1 * (*(it + 4));

	int num = S[n][row][col];
	for (int i = 0; i < 4; i++)
	{
		buf[3 - i] = num % 2;
		num /= 2;
	}


}



void DES::FeistelTransform(vector<int>& rkey, vector<int>& dataR)
{
	int E[48] =
	{
		32, 1, 2, 3, 4, 5,
		4, 5, 6, 7, 8, 9,
		8, 9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1
	};

	vector<int> buf = dataR;
	dataR.resize(48);
	for (int i = 0; i < 48; i++)
	{
		dataR[i] = buf[E[i] - 1];
		dataR[i] = (dataR[i] + rkey[i]) % 2;
	}
	buf.resize(4);
	for (int i = 0; i < 8; i++)
	{
		SPermutation(buf, dataR.begin() + i * 6, i);

		for (int k = 0; k < 4; k++)
		{
			dataR[i * 4 + k] = buf[k];
		}
	}

	dataR.resize(32);
	buf = dataR;
	int P[32] =
	{
		16, 7, 20, 21,
		29, 12, 28, 17,
		1, 15, 23, 26,
		5, 18, 31, 10,
		2, 8, 24, 14,
		32, 27, 3, 9,
		19, 13, 30, 6,
		22, 11, 4, 25,
	};

	for (int i = 0; i < 32; i++)
	{
		dataR[i] = buf[P[i] - 1];

	}

}


void DES::Encrypt(vector<int>& binaryData, vector<int>::iterator binaryDataIt, vector<int>* roundKey)
{
	InitialPermutation(binaryDataIt);



	vector<int> binaryDataL(binaryDataIt, binaryDataIt + 32);
	vector<int> binaryDataR(binaryDataIt + 32, binaryDataIt + 64);
	vector<int> rbuf(binaryDataR);
	for (int i = 0; i < 16; i++)
	{
		rbuf = binaryDataR;
		FeistelTransform(roundKey[i], binaryDataR);
		for (int k = 0; k < 32; k++)
		{
			binaryDataR[k] = (binaryDataR[k] + binaryDataL[k]) % 2;
		}
		binaryDataL = rbuf;
	}

	binaryDataIt = binaryData.erase(binaryDataIt, binaryDataIt + 64);
	binaryDataIt = binaryData.insert(binaryDataIt, binaryDataL.begin(), binaryDataL.end());
	binaryDataIt = binaryData.insert(binaryDataIt + 32, binaryDataR.begin(), binaryDataR.end());

	RInitialPermutation(binaryDataIt - 32);

}


void DES::Decrypt(vector<int>& binaryData, vector<int>::iterator binaryDataIt, vector<int>* roundKey)
{
	InitialPermutation(binaryDataIt);

	vector<int>binaryDataL(binaryDataIt, binaryDataIt + 32);
	vector<int>binaryDataR(binaryDataIt + 32, binaryDataIt + 64);
	vector<int> lbuf(binaryDataL);

	for (int i = 15; i >= 0; i--)
	{
		lbuf = binaryDataL;
		FeistelTransform(roundKey[i], binaryDataL);
		for (int k = 0; k < 32; k++)
		{
			binaryDataL[k] = (binaryDataR[k] + binaryDataL[k]) % 2;
		}
		binaryDataR = lbuf;

	}


	binaryDataIt = binaryData.erase(binaryDataIt, binaryDataIt + 64);
	binaryDataIt = binaryData.insert(binaryDataIt, binaryDataL.begin(), binaryDataL.end());
	binaryDataIt = binaryData.insert(binaryDataIt + 32, binaryDataR.begin(), binaryDataR.end());

	RInitialPermutation(binaryDataIt - 32);

}

void CDESDlg::Crypt()
{
	GetDlgItemTextW(IDC_OTXT, OTXT);
	wstring data = OTXT;
	wstring key = KEY;
	DES encrypted(data, key, true);
	buffCr = encrypted.data;
	CTXT = buffCr.c_str();
}

void CDESDlg::Decrypt()
{
	GetDlgItemTextW(IDC_CTXT, CTXT);
	wstring data = CTXT;
	wstring key = KEY;
	if (!CTXT.Compare(buffCr.c_str())) {
		data = buffCr;
	}

	DES decrypted(data, key, false);
	OTXT = decrypted.data.c_str();
}

void CDESDlg::OnBnClickedDec()
{
	srand(time(0));
	UpdateData(TRUE);
	if (IsDlgButtonChecked(IDC_DEC)) Decrypt();
	UpdateData(FALSE);
}


void CDESDlg::OnBnClickedCr()
{
	srand(time(0));
	UpdateData(TRUE);
	if (IsDlgButtonChecked(IDC_CR)) Crypt();
	UpdateData(FALSE);
}
