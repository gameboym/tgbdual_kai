
// romサイズ-表示行数
#define DBGMAXSCROLLSIZE ROMSIZE-24
#define DBGDISASMSTARTPOS 30
#define DBGDISASMENDPOS 20
#define DBGDISASMLINESIZE 10
#define DBGDISASMPAGESIZE 80
#define DBGDISASMMAXSIZE (DBGDISASMSTARTPOS+DBGDISASMENDPOS+DBGDISASMLINESIZE+DBGDISASMPAGESIZE)

#define MEMDUMPSTARTLINE 56
#define MEMDUMPSTARTPOS 63
#define MEMDUMPNEXTLINE 75
#define MEMDUMPMAXSTR (MEMDUMPSTARTLINE + MEMDUMPNEXTLINE * 16)

#define ROMSIZE 0x7fff

#define REGD_A regs->AF.b.h
#define REGD_F regs->AF.b.l
#define REGD_B regs->BC.b.h
#define REGD_C regs->BC.b.l
#define REGD_D regs->DE.b.h
#define REGD_E regs->DE.b.l
#define REGD_H regs->HL.b.h
#define REGD_L regs->HL.b.l
#define REGD_AF regs->AF.w
#define REGD_BC regs->BC.w
#define REGD_DE regs->DE.w
#define REGD_HL regs->HL.w
#define REGD_SP regs->SP
#define REGD_PC regs->PC

static int id8b[] = {
	IDC_EDIT_A, IDC_EDIT_F,
	IDC_EDIT_B, IDC_EDIT_C,
	IDC_EDIT_D, IDC_EDIT_E,
	IDC_EDIT_H, IDC_EDIT_L,
};

static WNDPROC old_medit_proc;
static WNDPROC old_redit_procA;
static WNDPROC old_redit_procF;
static WNDPROC old_redit_procB;
static WNDPROC old_redit_procC;
static WNDPROC old_redit_procD;
static WNDPROC old_redit_procE;
static WNDPROC old_redit_procH;
static WNDPROC old_redit_procL;
static WNDPROC old_redit_procSP;
static WNDPROC old_redit_procPC;

typedef struct DISASMSET {
		int adr;
		int size;
		char str[40];
} DASMSET;


#include "../debugtool/z80cdisasm.h"


// メモリアドレス値チェック(a000-dfff)
static bool MemAdrstow(const char *s, word &addres)
{
	unsigned long ulbuf;
	int slen = strlen(s);
	for (int i = 0; (i < 4) && (i < slen); i++)
	{
		if (! isxdigit(s[i]) )
			return false;
	}

	sscanf(s, "%04x", &ulbuf);
	addres = (word)(ulbuf & 0xffff);
	if ((addres < 0xa000) || (addres >= 0xe000))
		return false;

	return true;
}

// 読込みアドレス値チェック(0000-ffff)
static bool ReadAdrstow(const char *s, word &addres)
{
	unsigned long ulbuf;
	int slen = strlen(s);
	for (int i = 0; (i < 4) && (i < slen); i++)
	{
		if (! isxdigit(s[i]) )
			return false;
	}

	sscanf(s, "%04x", &ulbuf);
	addres = (word)(ulbuf & 0xffff);
	if (addres > 0xffff)
		return false;

	return true;
}

// アドレス値チェック(0000-7fff)
static bool Adrstow(const char *s, word &addres)
{
	unsigned long ulbuf;
	int slen = strlen(s);
	for (int i = 0; (i < 4) && (i < slen); i++)
	{
		if (! isxdigit(s[i]) )
			return false;
	}

	sscanf(s, "%04x", &ulbuf);
	addres = (word)(ulbuf & 0xffff);
	if (addres >= 0x8000)
		return false;

	return true;
}

// ログサイズ指定用の値チェック(1000-30000)
// 戻り値：0 = 範囲外　それ以外 正常
static int LogSizeCheck(const char *slogsize)
{
	int ilogsize;
	ilogsize = atoi(slogsize);
	if (ilogsize < 1000 || ilogsize > 30000)
		return 0;
	return ilogsize;
}

static void BrAdrSetCmbBox(HWND hwnd, unsigned int *wbradr)
{
	char sbradr[3][10];
	gBreakerb.get(wbradr);
	
	// コンボボックスの初期化
	while(SendMessage(GetDlgItem(hwnd, IDC_COMBO2), CB_GETCOUNT, 0, 0) != 0)
		SendMessage(GetDlgItem(hwnd, IDC_COMBO2), CB_DELETESTRING, 0, 0);

	for (int i = 0; i < 3; i++)
	{
		if (wbradr[i] > 0xffff)
			strcpy(sbradr[i], "");
		else
			sprintf(sbradr[i], "0x%04x", wbradr[i]);
		SendMessage(GetDlgItem(hwnd, IDC_COMBO2), CB_INSERTSTRING, (WPARAM)i, (LPARAM)sbradr[i]);
	}
	SendMessage(GetDlgItem(hwnd, IDC_COMBO2), CB_SETCURSEL, (WPARAM)0, 0L);
}

static void BrReadAdrSetCmbBox(HWND hwnd, unsigned int *wbradr)
{
	char sbradr[3][10];
	gBreakerreadb.get(wbradr);
	
	// コンボボックスの初期化
	while(SendMessage(GetDlgItem(hwnd, IDC_COMBO3), CB_GETCOUNT, 0, 0) != 0)
		SendMessage(GetDlgItem(hwnd, IDC_COMBO3), CB_DELETESTRING, 0, 0);

	for (int i = 0; i < 3; i++)
	{
		if (wbradr[i] > 0xffff)
			strcpy(sbradr[i], "");
		else
			sprintf(sbradr[i], "0x%04x", wbradr[i]);
		SendMessage(GetDlgItem(hwnd, IDC_COMBO3), CB_INSERTSTRING, (WPARAM)i, (LPARAM)sbradr[i]);
	}
	SendMessage(GetDlgItem(hwnd, IDC_COMBO3), CB_SETCURSEL, (WPARAM)0, 0L);
}

static void BrMemAdrSetCmbBox(HWND hwnd, unsigned int *wbrmemadr)
{
	char sbrmemadr[3][10];
	gBreakermemb.get(wbrmemadr);

	// コンボボックスの初期化
	while(SendMessage(GetDlgItem(hwnd, IDC_COMBO1), CB_GETCOUNT, 0, 0) != 0)
		SendMessage(GetDlgItem(hwnd, IDC_COMBO1), CB_DELETESTRING, 0, 0);

	for (int i = 0; i < 3; i++)
	{
		if (wbrmemadr[i] > 0xffff)
			strcpy(sbrmemadr[i], "");
		else
			sprintf(sbrmemadr[i], "0x%04x", wbrmemadr[i]);
		SendMessage(GetDlgItem(hwnd, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)i, (LPARAM)sbrmemadr[i]);
	}
	SendMessage(GetDlgItem(hwnd, IDC_COMBO1), CB_SETCURSEL, (WPARAM)0, 0L);
}

static int DbgInfoDisasm(DASMSET *dasmset, int startadr, int endadr)
{
	DASM_STRSET strset;
	int adrhead;
	int i, j;

	z80cdisasm(NULL, 0, true);	// reset

	for (i = startadr, j = 0; i < endadr && i <= ROMSIZE ; i++, j++)
	{
		adrhead = i;
		while (! z80cdisasm(&strset, g_gb[0]->get_cpu()->read_nocheck(i)))
		{
			i++;
			if (i > ROMSIZE) 
			{
				while (! z80cdisasm(&strset, 0x00)){}
				break;
			}
		}
		sprintf(dasmset[j].str, "#%04X\t$%s\t %s\t%s\t%s\r\n", adrhead, strset.UsedOpCode,
			strset.nemonic, strset.op1, strset.op2);
		dasmset[j].adr = adrhead;
		dasmset[j].size = i -adrhead +1;
	}
	return j;
}

// 戻り値：表示している解析結果最後尾のアドレス。
// linepos：sidbgi->nPosの位置から表示したい行までの差
static int ShowInfoEdit(HWND hwnd, SCROLLINFO *sidbgi, int sadr, int eadr, int linepos)
{
	DASMSET dasmset[DBGDISASMMAXSIZE];
	char infostr[0x25 * 40];
	int i ,home ,dasmssize;

	infostr[0] = '\0';
	home = -1;
	if (sadr < 0) sadr = 0;
	if (eadr > ROMSIZE) eadr = ROMSIZE;
	dasmssize = DbgInfoDisasm(dasmset , sadr, eadr);

	for (i = 0; i < dasmssize; i++)
	{
		if ( (dasmset[i].adr <= sidbgi->nPos) && 
			(dasmset[i].adr + dasmset[i].size-1 >= sidbgi->nPos) )
		{
			home = i + linepos;
			break;
		}
	}
	if (home < 0 || home > dasmssize)
	{
		SetDlgItemText(hwnd, IDC_INFO_MAIN, infostr);
		MessageBox(hwnd, "スクロールポジションのエラー", "エラーの発生", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	for (i = 0; home+i < dasmssize && i < 24; i++)
		strcat(infostr, dasmset[home+i].str);

	SetDlgItemText(hwnd, IDC_INFO_MAIN, infostr);
	sidbgi->nPos = dasmset[home].adr;
	SetScrollInfo(GetDlgItem(hwnd, IDC_DBG_INFO_SCROLL), SB_CTL, sidbgi, TRUE);
	return dasmset[home+i-1].adr;
}

void VKNumPadToNum(WPARAM *wParam) {
	switch (*wParam) {
	case VK_NUMPAD0:
		*wParam = (WPARAM)'0';
		break;
	case VK_NUMPAD1:
		*wParam = (WPARAM)'1';
		break;
	case VK_NUMPAD2:
		*wParam = (WPARAM)'2';
		break;
	case VK_NUMPAD3:
		*wParam = (WPARAM)'3';
		break;
	case VK_NUMPAD4:
		*wParam = (WPARAM)'4';
		break;
	case VK_NUMPAD5:
		*wParam = (WPARAM)'5';
		break;
	case VK_NUMPAD6:
		*wParam = (WPARAM)'6';
		break;
	case VK_NUMPAD7:
		*wParam = (WPARAM)'7';
		break;
	case VK_NUMPAD8:
		*wParam = (WPARAM)'8';
		break;
	case VK_NUMPAD9:
		*wParam = (WPARAM)'9';
		break;
	default:
		break;
	}
	return;
}

static void ShowRegister(HWND hwnd)
{
	cpu_regs *regs;
	char sregs[10][5];
		
	regs = g_gb[0]->get_cpu()->get_regs();

	sprintf(sregs[0], "%02X", REGD_A);
	sprintf(sregs[1], "%02X", REGD_F);
	sprintf(sregs[2], "%02X", REGD_B);
	sprintf(sregs[3], "%02X", REGD_C);
	sprintf(sregs[4], "%02X", REGD_D);
	sprintf(sregs[5], "%02X", REGD_E);
	sprintf(sregs[6], "%02X", REGD_H);
	sprintf(sregs[7], "%02X", REGD_L);
	for (int i = 0; i < 8; i++)
		SetDlgItemText(hwnd, id8b[i], sregs[i]);

	sprintf(sregs[8], "%04X", REGD_SP);
	sprintf(sregs[9], "%04X", REGD_PC);
	SetDlgItemText(hwnd, IDC_EDIT_SP, sregs[8]);
	SetDlgItemText(hwnd, IDC_EDIT_PC, sregs[9]);

	// TGBDualではフラグレジスタがGBのフラグではなくZ80のものになっている。
	// 通常GBではZNHC 0000のビットでフラグを管理する。TGBはソースの通り。
	SendMessage(GetDlgItem(hwnd, IDC_CHECK_Z), BM_SETCHECK, (WPARAM)(REGD_F & 0x40), 0L);
	SendMessage(GetDlgItem(hwnd, IDC_CHECK_N), BM_SETCHECK, (WPARAM)(REGD_F & 0x02), 0L);
	SendMessage(GetDlgItem(hwnd, IDC_CHECK_H), BM_SETCHECK, (WPARAM)(REGD_F & 0x10), 0L);
	SendMessage(GetDlgItem(hwnd, IDC_CHECK_C), BM_SETCHECK, (WPARAM)(REGD_F & 0x01), 0L);
}

// 戻り値：表示している解析結果最後尾のアドレス。
static int InfoWindowSelectJump(HWND hwnd, SCROLLINFO *sidbgi, word jumpaddress)
{
	FINDTEXT findtext;
	char sserchtext[10];
	int startpos, endpos, dasmunderpos;
	int ret = 0;

	if (jumpaddress > DBGMAXSCROLLSIZE)
		sidbgi->nPos = DBGMAXSCROLLSIZE;
	else
		sidbgi->nPos = (int)jumpaddress;
	startpos = sidbgi->nPos - DBGDISASMSTARTPOS;
	endpos = sidbgi->nPos + DBGDISASMPAGESIZE + DBGDISASMENDPOS;
	dasmunderpos = ShowInfoEdit(hwnd, sidbgi, startpos, endpos, 0);

	findtext.chrg.cpMin = 0;
	findtext.chrg.cpMax = -1;
	for (int i = 0; i < 5; jumpaddress--, i++)
	{
		sprintf(sserchtext, "#%04X", jumpaddress);
		findtext.lpstrText = sserchtext;
		ret = SendMessage(GetDlgItem(hwnd, IDC_INFO_MAIN), EM_FINDTEXT, FR_DOWN, (LPARAM)&findtext);
		if (ret != -1)
			break;
	}
	if (ret < 0)
	{
		MessageBox(hwnd, "原因不明のエラー001", "エラーの発生", MB_OK | MB_ICONEXCLAMATION);
		ret = 0;
		return dasmunderpos;
	}
	SendMessage(GetDlgItem(hwnd, IDC_INFO_MAIN), EM_SETSEL, ret, ret+5);
	SendMessage(GetDlgItem(hwnd, IDC_INFO_MAIN), EM_SCROLLCARET, 0, 0);
	return dasmunderpos;
}

// 戻り値: 構造体の使用数
static BOOL CALLBACK DbgBrSetProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	char sbrmemadr[5];
	char sbrreadadr[5];
	char sbradr[5];
	word wbrmemadr;
	word wbrreadadr;
	word wbradr;

	switch(uMsg)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hwnd, IDC_ED_BR_SET1), EM_SETLIMITTEXT, (WPARAM)4, 0);
		SendMessage(GetDlgItem(hwnd, IDC_ED_BR_SET2), EM_SETLIMITTEXT, (WPARAM)4, 0);
		SendMessage(GetDlgItem(hwnd, IDC_ED_BR_SET3), EM_SETLIMITTEXT, (WPARAM)4, 0);
		// 自身をメインウインドウの横に移動させる
		RECT rect;
		GetWindowRect(hwnd,&rect);
		SetWindowPos(hwnd,NULL,rect.right,rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);

		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_MEMADR_SET)
		{
			GetDlgItemText(hwnd, IDC_ED_BR_SET1, sbrmemadr, 5);
			if (MemAdrstow(sbrmemadr, wbrmemadr))
			{
				if (gBreakermemb.set(wbrmemadr) == -1)
				{
					MessageBox(hwnd, "設定数を超えています。\n他を削除した後もう一度登録してください。",
						"設定数オーバー", MB_OK | MB_ICONEXCLAMATION);
				}
			}
			else
			{
				MessageBox(hwnd, "0xA000～0xDFFFの範囲で16進で入力してください。",
					"入力エラー", MB_OK | MB_ICONEXCLAMATION);
			}
			SetDlgItemText(hwnd, IDC_ED_BR_SET1, "");
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_READADR_SET)
		{
			GetDlgItemText(hwnd, IDC_ED_BR_SET3, sbrreadadr, 5);
			if (ReadAdrstow(sbrreadadr, wbrreadadr))
			{
				if (gBreakerreadb.set(wbrreadadr) == -1)
				{
					MessageBox(hwnd, "設定数を超えています。\n他を削除した後もう一度登録してください。",
						"設定数オーバー", MB_OK | MB_ICONEXCLAMATION);
				}
			}
			else
			{
				MessageBox(hwnd, "0x0000～0xFFFFの範囲で16進で入力してください。",
					"入力エラー", MB_OK | MB_ICONEXCLAMATION);
			}
			SetDlgItemText(hwnd, IDC_ED_BR_SET3, "");
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_ADR_SET)
		{
			GetDlgItemText(hwnd, IDC_ED_BR_SET2, sbradr, 5);
			if (Adrstow(sbradr, wbradr))
			{
				if (gBreakerb.set(wbradr) == -1)
				{
					MessageBox(hwnd, "設定数を超えています。\n他を削除した後もう一度登録してください。",
						"設定数オーバー", MB_OK | MB_ICONEXCLAMATION);
				}
			}
			else
			{
				MessageBox(hwnd, "0x0000～0x7FFFの範囲で16進数値を入力してください。",
				"入力エラー", MB_OK | MB_ICONEXCLAMATION);
			}
			SetDlgItemText(hwnd, IDC_ED_BR_SET2, "");
			return TRUE;
		}
		if (LOWORD(wParam) == IDOK)
		{
			DestroyWindow(hwnd);
			return TRUE;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return TRUE;
	}
    return FALSE;
}

static BOOL CALLBACK DbgLogViewProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int logsize;
	char strbuf[40];
	char *logstr;
	word pcbuf;
	HWND hedit;

	LOGLIST *loglist;
	DASM_STRSET strset;


	switch(uMsg)
	{
	case WM_USER+1: // 初期化処理を実行
		/* Fall Through */
	case WM_INITDIALOG:
		hedit = GetDlgItem(hwnd, IDC_RICHEDIT23);
		logsize = gLoging.logsizeget();
		loglist = new LOGLIST[logsize];
		gLoging.logget(loglist);

		logstr = new char[logsize*30];
		logstr[0] = '\0';

		SendMessage(hedit, EM_LIMITTEXT, logsize*30, 0);
		
		z80cdisasm(NULL, 0, true);	// reset

		for (int i = 0; i < logsize; i++)
		{
			pcbuf = loglist[i].pc;
			while (! z80cdisasm(&strset, loglist[i].nemonic))
			{
				i++;
			}
			sprintf(strbuf, "PC:%04X\t$%s\t %s\t%s\t%s\r\n", pcbuf, strset.UsedOpCode,
				strset.nemonic, strset.op1, strset.op2);
			strcat(logstr, strbuf);	
		}
		SetDlgItemText(hwnd, IDC_RICHEDIT23, logstr);

		// スクロールポジションを一番最後に変更する(ログの最後が最新であるため)
		SetFocus(hedit);
		SendMessage(hedit, EM_SETSEL, 0, 0);
		SendMessage(hedit, EM_SCROLLCARET, 0, 0);
		SendMessage(hedit, EM_SETSEL, -1, -1);
		SendMessage(hedit, EM_SCROLLCARET, 0, 0);

		delete[] loglist;
		delete[] logstr;

		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hwnd, 0);
			return TRUE;
		}
		if (LOWORD(wParam) == IDUPDATE)
		{
			PostMessage(hwnd, WM_USER+1, 0, 0);
			return TRUE;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;
	}
    return FALSE;
}


static BOOL CALLBACK DbgMenuProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	char slogsize[6];
	int ilogsize;

	switch(uMsg)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hwnd, IDC_ED_LOG), EM_SETLIMITTEXT, (WPARAM)5, 0);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			GetDlgItemText(hwnd, IDC_ED_LOG, slogsize, 6);
			ilogsize = LogSizeCheck(slogsize);
			if (ilogsize == 0)
			{
				MessageBox(hwnd, "1000～30000の範囲で入力してください。",
					"入力エラー", MB_OK | MB_ICONEXCLAMATION);
				SetDlgItemText(hwnd, IDC_ED_LOG, "");
				return TRUE;
			}
			gLoging.resize(ilogsize);
			EndDialog(hwnd, 0);
			return TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hwnd, 0);
			return TRUE;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;
	}
    return FALSE;
}

static BOOL CALLBACK DbgBrDelProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int index;
	// 登録可能数が現在固定されているため配列として扱う
	static unsigned int wbreakaddres[3];
	static unsigned int wbreakreadaddres[3];
	static unsigned int wbreakmemaddres[3];

	switch(uMsg)
	{
	case WM_INITDIALOG:
		BrAdrSetCmbBox(hwnd, wbreakaddres);
		BrReadAdrSetCmbBox(hwnd, wbreakreadaddres);
		BrMemAdrSetCmbBox(hwnd, wbreakmemaddres);
		// 自身をメインウインドウの横に移動させる
		RECT rect;
		GetWindowRect(hwnd,&rect);
		SetWindowPos(hwnd,NULL,rect.right,rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			DestroyWindow(hwnd);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_UPDATE)
		{
			BrAdrSetCmbBox(hwnd, wbreakaddres);
			BrReadAdrSetCmbBox(hwnd, wbreakreadaddres);
			BrMemAdrSetCmbBox(hwnd, wbreakmemaddres);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_ADR_DEL)
		{
			index = SendMessage(GetDlgItem(hwnd, IDC_COMBO2), CB_GETCURSEL, 0L, 0L);
			if (index == CB_ERR)
				MessageBox(hwnd, "対象を正しく選択してください。",
					"対象指定エラー", MB_OK | MB_ICONEXCLAMATION);
			else if (wbreakaddres[index] > 0xffff)
				MessageBox(hwnd, "対象を正しく選択してください。",
					"対象指定エラー", MB_OK | MB_ICONEXCLAMATION);
			else if (gBreakerb.del(wbreakaddres[index]) == -1)
				MessageBox(hwnd, "その値は現在登録されていません。\r\n最新の状態を確認してください。",
					"不正な値が選択されました。", MB_OK | MB_ICONEXCLAMATION);

			BrAdrSetCmbBox(hwnd, wbreakaddres);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_READADR_DEL)
		{
			index = SendMessage(GetDlgItem(hwnd, IDC_COMBO3), CB_GETCURSEL, 0L, 0L);
			if (index == CB_ERR)
				MessageBox(hwnd, "対象を正しく選択してください。",
					"対象指定エラー", MB_OK | MB_ICONEXCLAMATION);
			else if (wbreakreadaddres[index] > 0xffff)
				MessageBox(hwnd, "対象を正しく選択してください。",
					"対象指定エラー", MB_OK | MB_ICONEXCLAMATION);
			else if (gBreakerreadb.del(wbreakreadaddres[index]) == -1)
				MessageBox(hwnd, "その値は現在登録されていません。\r\n最新の状態を確認してください。",
					"不正な値が選択されました。", MB_OK | MB_ICONEXCLAMATION);

			BrReadAdrSetCmbBox(hwnd, wbreakreadaddres);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_MEMADR_DEL)
		{
			index = SendMessage(GetDlgItem(hwnd, IDC_COMBO1), CB_GETCURSEL, 0L, 0L);
			if (index == CB_ERR)
				MessageBox(hwnd, "対象を正しく選択してください。",
					"対象指定エラー", MB_OK | MB_ICONEXCLAMATION);
			else if (wbreakmemaddres[index] > 0xffff)
				MessageBox(hwnd, "対象を正しく選択してください。",
					"対象指定エラー", MB_OK | MB_ICONEXCLAMATION);
			else if (gBreakermemb.del(wbreakmemaddres[index]) == -1)
				MessageBox(hwnd, "その値は現在登録されていません。\r\n最新の状態を確認してください。",
					"不正な値が選択されました。", MB_OK | MB_ICONEXCLAMATION);

			BrMemAdrSetCmbBox(hwnd, wbreakmemaddres);
			return TRUE;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return TRUE;
	}
    return FALSE;
}

#include "debugregisteredit.h"

static BOOL CALLBACK DbgRegisterProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	char buf[10];
	word wadr;
	int startpos, endpos;
	static int dasmunderpos = 0;
	static SCROLLINFO sidbgi;

	switch(uMsg)
	{
	case WM_INITDIALOG:
		if (b_running)
			PAUSEprocess();

		// エディット領域の処理関数を変更
		old_redit_procA = (WNDPROC)GetWindowLong( GetDlgItem( hwnd, IDC_EDIT_A ), GWL_WNDPROC );
		SetWindowLong( GetDlgItem( hwnd, IDC_EDIT_A ), GWL_WNDPROC, (LONG)MyRegEditProcA );

		old_redit_procF = (WNDPROC)GetWindowLong( GetDlgItem( hwnd, IDC_EDIT_F ), GWL_WNDPROC );
		SetWindowLong( GetDlgItem( hwnd, IDC_EDIT_F ), GWL_WNDPROC, (LONG)MyRegEditProcF );

		old_redit_procB = (WNDPROC)GetWindowLong( GetDlgItem( hwnd, IDC_EDIT_B ), GWL_WNDPROC );
		SetWindowLong( GetDlgItem( hwnd, IDC_EDIT_B ), GWL_WNDPROC, (LONG)MyRegEditProcB );

		old_redit_procC = (WNDPROC)GetWindowLong( GetDlgItem( hwnd, IDC_EDIT_C ), GWL_WNDPROC );
		SetWindowLong( GetDlgItem( hwnd, IDC_EDIT_C ), GWL_WNDPROC, (LONG)MyRegEditProcC );

		old_redit_procD = (WNDPROC)GetWindowLong( GetDlgItem( hwnd, IDC_EDIT_D ), GWL_WNDPROC );
		SetWindowLong( GetDlgItem( hwnd, IDC_EDIT_D ), GWL_WNDPROC, (LONG)MyRegEditProcD );

		old_redit_procE = (WNDPROC)GetWindowLong( GetDlgItem( hwnd, IDC_EDIT_E ), GWL_WNDPROC );
		SetWindowLong( GetDlgItem( hwnd, IDC_EDIT_E ), GWL_WNDPROC, (LONG)MyRegEditProcE );

		old_redit_procH = (WNDPROC)GetWindowLong( GetDlgItem( hwnd, IDC_EDIT_H ), GWL_WNDPROC );
		SetWindowLong( GetDlgItem( hwnd, IDC_EDIT_H ), GWL_WNDPROC, (LONG)MyRegEditProcH );

		old_redit_procL = (WNDPROC)GetWindowLong( GetDlgItem( hwnd, IDC_EDIT_L ), GWL_WNDPROC );
		SetWindowLong( GetDlgItem( hwnd, IDC_EDIT_L ), GWL_WNDPROC, (LONG)MyRegEditProcL );

		old_redit_procSP = (WNDPROC)GetWindowLong( GetDlgItem( hwnd, IDC_EDIT_SP ), GWL_WNDPROC );
		SetWindowLong( GetDlgItem( hwnd, IDC_EDIT_SP ), GWL_WNDPROC, (LONG)MyRegEditProcSP );

		old_redit_procPC = (WNDPROC)GetWindowLong( GetDlgItem( hwnd, IDC_EDIT_PC ), GWL_WNDPROC );
		SetWindowLong( GetDlgItem( hwnd, IDC_EDIT_PC ), GWL_WNDPROC, (LONG)MyRegEditProcPC );


		for (int i = 0; i < 8; i++)
			SendMessage(GetDlgItem(hwnd, id8b[i]), EM_SETLIMITTEXT, (WPARAM)2, 0);

		SendMessage(GetDlgItem(hwnd, IDC_EDIT_SP), EM_SETLIMITTEXT, (WPARAM)4, 0);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_PC), EM_SETLIMITTEXT, (WPARAM)4, 0);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_JUMP), EM_SETLIMITTEXT, (WPARAM)4, 0);
		SendMessage(GetDlgItem(hwnd, IDC_INFO_MAIN), EM_LIMITTEXT, 0x7fff*30, 0);

		// ScrollBarの初期化
		sidbgi.cbSize = sizeof(SCROLLINFO);
		sidbgi.fMask = SIF_POS | SIF_RANGE | SIF_DISABLENOSCROLL;
		sidbgi.nMin = 0;
		sidbgi.nMax = DBGMAXSCROLLSIZE;
		sidbgi.nPos = 0;
		SetScrollInfo(GetDlgItem(hwnd, IDC_DBG_INFO_SCROLL), SB_CTL, &sidbgi, TRUE);

		ShowRegister(hwnd);
		dasmunderpos = InfoWindowSelectJump(hwnd, &sidbgi, g_gb[0]->get_cpu()->get_regs()->PC);

		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			DestroyWindow(hwnd);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_UPDATE)
		{
			if (b_running)
				PAUSEprocess();
			SendMessage(hwnd, WM_USER+2, 0, 0);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_STEP)
		{
			gstepflag = true;
			PostMessage(hwnd, WM_USER+2, 0, 0);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_JUMP)
		{
			GetDlgItemText(hwnd, IDC_EDIT_JUMP, buf, 10);
			if (! Adrstow(buf, wadr))
			{
				MessageBox(hwnd, "0x0000～0x7FFFの範囲で16進数値を入力してください。",
					"入力エラー", MB_OK | MB_ICONEXCLAMATION);
				SetDlgItemText(hwnd, IDC_EDIT_JUMP, "");
				return TRUE;
			}
			dasmunderpos = InfoWindowSelectJump(hwnd, &sidbgi, wadr);
			SetDlgItemText(hwnd, IDC_EDIT_JUMP, "");
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_PCJUMP)
		{
			dasmunderpos = InfoWindowSelectJump(hwnd, &sidbgi, g_gb[0]->get_cpu()->get_regs()->PC);
			return TRUE;
		}
		break;
	case WM_VSCROLL:
		switch (LOWORD(wParam)) {
			case SB_LINEUP:
				if (sidbgi.nPos <= sidbgi.nMin) break;
				startpos = sidbgi.nPos - DBGDISASMSTARTPOS - DBGDISASMLINESIZE;
				endpos = sidbgi.nPos + DBGDISASMPAGESIZE + DBGDISASMENDPOS;
				dasmunderpos = ShowInfoEdit(hwnd, &sidbgi, startpos, endpos, -1);
				break;
			case SB_LINEDOWN:
				if (sidbgi.nPos >= sidbgi.nMax) break;
				startpos = sidbgi.nPos - DBGDISASMSTARTPOS;
				endpos = sidbgi.nPos + DBGDISASMPAGESIZE + DBGDISASMLINESIZE + DBGDISASMENDPOS;
				dasmunderpos = ShowInfoEdit(hwnd, &sidbgi, startpos, endpos, 1);
				break;
			case SB_PAGEUP:
				if (sidbgi.nPos <= sidbgi.nMin) break;
				startpos = sidbgi.nPos - DBGDISASMSTARTPOS - DBGDISASMPAGESIZE;
				endpos = sidbgi.nPos + DBGDISASMLINESIZE + DBGDISASMENDPOS;
				dasmunderpos = ShowInfoEdit(hwnd, &sidbgi, startpos, endpos, -24);
				break;
			case SB_PAGEDOWN:
				if (sidbgi.nPos >= sidbgi.nMax) break;
				sidbgi.nPos = dasmunderpos;
				startpos = sidbgi.nPos - DBGDISASMSTARTPOS;
				endpos = sidbgi.nPos + DBGDISASMPAGESIZE + DBGDISASMLINESIZE + DBGDISASMENDPOS;
				dasmunderpos = ShowInfoEdit(hwnd, &sidbgi, startpos, endpos, 1);
				break;
			case SB_THUMBPOSITION:
				sidbgi.nPos = HIWORD(wParam);
				startpos = sidbgi.nPos - DBGDISASMSTARTPOS;
				endpos = sidbgi.nPos + DBGDISASMPAGESIZE + DBGDISASMENDPOS;
				dasmunderpos = ShowInfoEdit(hwnd, &sidbgi, startpos, endpos, 0);
				break;
			default:
				break;
		}
		return TRUE;
	case WM_USER+2:
		ShowRegister(hwnd);
		dasmunderpos = InfoWindowSelectJump(hwnd, &sidbgi, g_gb[0]->get_cpu()->get_regs()->PC);
		return TRUE;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return TRUE;
	}
    return FALSE;
}

// セルが選択可能な位置かどうかチェックする。
int MemDumpSelCheck(int selpos) {
	int selcheck;

	if (selpos > MEMDUMPMAXSTR) // 最大文字数オーバー
		return 0;

	selcheck = selpos - MEMDUMPSTARTPOS; // 最初のアドレス開始位置

	if (0 <= selcheck) {
		selcheck = (selcheck % MEMDUMPNEXTLINE) + 1; //　1行75文字のため75で割る。0始まりなので+1

		// 2文字+空白1文字 = 3 * 16個で48文字
		// 3文字目は空白のため3の倍数は選択不能
		if (48 >= selcheck && selcheck % 3) {
			return 1;
		}
	}
	return 0;
}

// セル位置からアドレスを取得する
word MemDumpGetAddress(word baddress, int selpos, int *high)
{
	int temp, line, column;
	
	// 行位置の決定
	temp = selpos - MEMDUMPSTARTPOS;
	line = temp / MEMDUMPNEXTLINE;

	// 列位置の決定
	temp = temp % MEMDUMPNEXTLINE + 1;
	column = temp - temp / 3; // 3で割ることで3文字目の空白を飛ばす

	if (column % 2) //奇数であれば上位ビット
		*high = 1;
	else
		*high = 0;

	// 上位ビットと下位ビットを統合して1バイトとする。
	// ここで+1することによって開始アドレスが2となる
	// この状態で2で割ってそこから-1引けば0除算を回避できる。
	column = (column+1) / 2 -1; 

	return baddress + line * 16 + column;
}

word MemDumpGetBaseAddress(HWND hwnd)
{
	char selbuf[MEMDUMPSTARTPOS];
	char address[5];
	char strbuf[256];
	char *tocheck;
	int i;
	word baddress;

	GetWindowText(hwnd, selbuf, MEMDUMPSTARTPOS);
	strncpy(address, &selbuf[MEMDUMPSTARTLINE], 4);
	for (i = 0; i < 4; i++) {
		if (!isxdigit((int)address[i])) {
			sprintf(strbuf, "正常にアドレスが取得できませんでした。buf[%d] = %c", i, address[i]);
			MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
			return 0;
		}
	}
	address[4] = '\0';
	baddress = (word)strtol(address, &tocheck, 16);
	if (tocheck == &address[0]) {
		sprintf(strbuf, "正常にアドレスが取得できませんでした。文字列 = %s", address);
		MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
		return 0;
	}

	return baddress;
}

int MemDumpSelUp(HWND hwnd)
{
	int start, end;
	SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
	if (MemDumpSelCheck(start - MEMDUMPNEXTLINE))
		SendMessage(hwnd, EM_SETSEL, (WPARAM)start - MEMDUMPNEXTLINE, (LPARAM) end - MEMDUMPNEXTLINE);
	else
	{
		SendMessage(GetParent(hwnd), WM_VSCROLL, (WPARAM)SB_LINEUP, (LPARAM)GetDlgItem(GetParent(hwnd), IDC_SCROLL));	// 1つ上にスクロールする
		SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM)end);
	}
	return 0;
}

int MemDumpSelDown(HWND hwnd)
{
	int start, end;
	SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
	if (MemDumpSelCheck(start + MEMDUMPNEXTLINE))
		SendMessage(hwnd, EM_SETSEL, (WPARAM)start + MEMDUMPNEXTLINE, (LPARAM) end + MEMDUMPNEXTLINE);
	else
	{
		SendMessage(GetParent(hwnd), WM_VSCROLL, (WPARAM)SB_LINEDOWN, (LPARAM)GetDlgItem(GetParent(hwnd), IDC_SCROLL));	// 1つ下へスクロールする
		SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM)end);
	}
	return 0;
}

int MemDumpSelLineStart(HWND hwnd)
{
	int start, end;
	int linestart, selpos;

	SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

	selpos = start - MEMDUMPSTARTPOS;
	selpos = selpos % MEMDUMPNEXTLINE;
	linestart = start - selpos;

	if (MemDumpSelCheck(linestart))
		SendMessage(hwnd, EM_SETSEL, (WPARAM)linestart, (LPARAM)linestart+1);
	else
		return 1;

	return 0;
}

int MemDumpSelLineEnd(HWND hwnd)
{
	int start, end;
	int lineend, selpos;

	SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

	selpos = start - MEMDUMPSTARTPOS;
	selpos = selpos % MEMDUMPNEXTLINE;
	lineend = start - selpos + 48; //(3*6=48文文字)
	lineend -= 2; // 0文字から47文字で最後が空白のため-2

	if (MemDumpSelCheck(lineend))
		SendMessage(hwnd, EM_SETSEL, (WPARAM)lineend, (LPARAM)lineend+1);
	else
		return 1;

	return 0;
}

int MemDumpSelLeft(HWND hwnd)
{
	int start, end;
	SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
	if (MemDumpSelCheck(start - 1))
		SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 1, (LPARAM) end - 1);
	else if (MemDumpSelCheck(start - 2)) // 間に空白があった場合その隣へ移動するため
		SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 2, (LPARAM) end - 2);
	else
	{
		if (MemDumpSelUp(hwnd))
			return 1;
		if (MemDumpSelLineEnd(hwnd))
			return 1;
	}
	return 0;
}


int MemDumpSelRight(HWND hwnd)
{
	int start, end;
	SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
	if (MemDumpSelCheck(start + 1))
		SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
	else if (MemDumpSelCheck(start + 2)) // 間に空白があった場合その隣へ移動するため
		SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 2, (LPARAM) end + 2);
	else
	{
		if (MemDumpSelDown(hwnd))
			return 1;
		if (MemDumpSelLineStart(hwnd))
			return 1;
	}
	return 0;
}

LRESULT CALLBACK MyMemEditProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static bool pause = false;
	int start, end, high;
	
	char strbuf[256];
	char num[2];
	char *tocheck;

	byte chgdata, olddata;
	word baddress, seladdress;

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		VKNumPadToNum(&wParam);
		if (isxdigit((int)wParam)) {
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			// 選択可能領域か判定する
			if (!MemDumpSelCheck(start))
				return TRUE;

			baddress = MemDumpGetBaseAddress(hwnd);
			if (!baddress)
				return TRUE;

			seladdress = MemDumpGetAddress(baddress, start, &high);
			if (!seladdress)
				return TRUE;

			num[0] = (char)wParam;
			num[1] = '\0';
			chgdata = (byte)strtol(num, &tocheck, 16); 
			if (tocheck == &num[0]) {
				sprintf(strbuf, "入力文字が不正です。文字 = %c", num[0]);
				MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
				return TRUE;
			}

			olddata = g_gb[0]->get_cpu()->read_nocheck(seladdress);
			if (high)
				chgdata = (chgdata << 4) + (olddata & 0x0f);
			else
				chgdata = chgdata + (olddata & 0xf0);
			g_gb[0]->get_cpu()->write_nocheck(seladdress, chgdata);

			// 数値を新しいものに置き換える
			SendMessage(hwnd, EM_REPLACESEL, 0, (LPARAM)num);

			// 次のセルに移動する
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM)end); // 選択が解除されているため初期位置にセット
			MemDumpSelRight(hwnd);

			return TRUE;
		}
		switch (wParam)
		{
		case VK_UP:
			MemDumpSelUp(hwnd);
			return TRUE;
		case VK_DOWN:
			MemDumpSelDown(hwnd);
			return TRUE;
		case VK_LEFT:
			MemDumpSelLeft(hwnd);
			return TRUE;
		case VK_RIGHT:
			MemDumpSelRight(hwnd);
			return TRUE;
		default:
			return TRUE;
		}
		break;

	case WM_CHAR:
	case WM_SYSKEYDOWN:
		return FALSE;

	case WM_LBUTTONDOWN:
		if (b_running)
		{
			pause = true;
			PAUSEprocess();
			KillTimer(GetParent(hwnd), 789);
		}
		else if (!pause) // PAUSEprocessが他によって既に行われていた場合タイマーだけ止める
		{
			KillTimer(GetParent(hwnd), 789);
		}

		::CallWindowProc( old_medit_proc, hwnd, uMsg, wParam, lParam );
		::CallWindowProc( old_medit_proc, hwnd, WM_LBUTTONUP, wParam, lParam );
		SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

		// 選択可能領域か判定する
		if (MemDumpSelCheck(start)) {
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM) end+1);
			SetFocus(hwnd);			// ADD 2012/8/4 セットフォーカスしないとフォーカスが復帰しないため修正
			return TRUE; // 選択してから戻る
		}

		SetFocus(GetParent(hwnd)); // フォーカスを渡して戻る
		return TRUE;

	case WM_KILLFOCUS:
		if (pause)
		{
			pause = false;
			PAUSEprocess();
		}
		SetTimer(GetParent(hwnd), 789, 100, NULL);
		return TRUE;

	case WM_CLOSE:
		pause = false;
		break;

	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYUP:
		return FALSE;

	}
	return ::CallWindowProc( old_medit_proc, hwnd, uMsg, wParam, lParam );
}

static BOOL CALLBACK MemDumpKaiProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static WORD cur_adr;
	HWND hScrl;
	HWND hMEdit;
	SCROLLINFO scr;
	char buf[256*17];
	int tmp, i, j;

	switch(uMsg)
	{
	case WM_INITDIALOG:
		cur_adr = 0xC000;

		scr.cbSize = sizeof(scr);
		scr.fMask = SIF_RANGE|SIF_POS;
		scr.nMin = 0;
		scr.nMax = 0xFFF-0x9;
		scr.nPos = cur_adr >> 4;
		hScrl = GetDlgItem(hwnd, IDC_SCROLL);
		SetScrollInfo(hScrl, SB_CTL, &scr, TRUE);
		tmp = scr.nPos;
		SendMessage(hwnd, WM_USER+1, (WPARAM)tmp, 0);

		SetTimer(hwnd, 789, 100, NULL);

		// エディット領域の処理関数を変更
		hMEdit = GetDlgItem( hwnd, IDC_DUMP );
		old_medit_proc = (WNDPROC)GetWindowLong( hMEdit, GWL_WNDPROC );
		SetWindowLong( hMEdit, GWL_WNDPROC, (LONG)MyMemEditProc );

		return TRUE;

	case WM_VSCROLL:

		int max, min;

		max = 0xFFF-0x0f;
		min = 0;
		hScrl = (HWND)lParam;
		scr.cbSize = sizeof(scr);
		scr.fMask = SIF_POS;
		GetScrollInfo(hScrl, SB_CTL, &scr);
		
		switch(LOWORD(wParam))
		{
		case SB_BOTTOM:
			scr.nPos = max;
			break;
		case SB_LINEDOWN:
			scr.nPos++;
			break;
		case SB_PAGEDOWN:
			scr.nPos += 10;
			break;
		case SB_LINEUP:
			scr.nPos--;
			break;
		case SB_PAGEUP:
			scr.nPos -= 10;
			break;
		case SB_TOP:
			scr.nPos = min;
			break;
		case SB_ENDSCROLL:
			break;
		default:
			scr.nPos = (short)HIWORD(wParam);
			break;
		}
		if (scr.nPos > max) scr.nPos = max;
		if (scr.nPos < min) scr.nPos = min;

		tmp = scr.nPos;

		SetScrollInfo(hScrl, SB_CTL, &scr, TRUE);

		SendMessage(hwnd, WM_USER+1, (WPARAM)tmp, 0);

		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			DestroyWindow(hwnd);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_MOVE)
		{
			GetDlgItemText(hwnd, IDC_ADDRESS, buf, 256);
			tmp = (strtol(buf, NULL, 16) >> 4) & 0xFFF;
			
			if (tmp > 0xFF6) tmp = 0xFF6;
			
			hScrl = GetDlgItem(hwnd, IDC_SCROLL);
			SetScrollPos(hScrl, SB_CTL, tmp, TRUE);
			SendMessage(hwnd, WM_USER+1, (WPARAM)tmp, 0);

			return TRUE;
		}
		break;
	case WM_USER+1: // 画面表示
		tmp = (int)wParam;
		char strbuf[256];
		unsigned char asciibuf[16];

		strcpy(buf, "       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
		for (i = 0; i < 16; i++)
		{
			sprintf(strbuf, "\r\n%04X | %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X | ", tmp << 4,
				g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+0),g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+1),
				g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+2),g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+3),
				g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+4),g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+5),
				g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+6),g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+7),	
				g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+8),g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+9),
				g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+10),g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+11),
				g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+12),g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+13),
				g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+14),g_gb[0]->get_cpu()->read_nocheck(((tmp)<<4)+15));
			strcat(buf, strbuf);

			for (j = 0; j < 16; j++)
			{
				asciibuf[j] = g_gb[0]->get_cpu()->read_nocheck( ((tmp) << 4) + j );
				if (asciibuf[j] < 0x21 || (asciibuf[j] > 0x7e && asciibuf[j] < 0xa1) || asciibuf[j] > 0xdf) 
					asciibuf[j] = '.';
			}
			sprintf(strbuf, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
				asciibuf[0], asciibuf[1], asciibuf[2], asciibuf[3],
				asciibuf[4], asciibuf[5], asciibuf[6], asciibuf[7],
				asciibuf[8], asciibuf[9], asciibuf[10], asciibuf[11],
				asciibuf[12], asciibuf[13], asciibuf[14], asciibuf[15]);
			strcat(buf, strbuf);

			tmp++;
		}
		SetDlgItemText(hwnd, IDC_DUMP, buf);
		return TRUE;
	case WM_TIMER:
		hScrl = GetDlgItem(hwnd, IDC_SCROLL);
		scr.cbSize = sizeof(scr);
		scr.fMask = SIF_POS;
		GetScrollInfo(hScrl, SB_CTL, &scr);
		SendMessage(hwnd, WM_USER+1, (WPARAM)scr.nPos, 0);
		return TRUE;
	case WM_CLOSE:
		KillTimer(hwnd, 789);
		DestroyWindow(hwnd);
		return TRUE;
	}

    return FALSE;
}

void ParKaiGetgCodeButton(HWND hwnd)
{
	int stype, ntype, nsize, target, ram, sram;

	stype = gCodesearch.getstype();
	ntype = gCodesearch.getntype();
	nsize = gCodesearch.getnsize();
	target = gCodesearch.gettarget();
	ram = gCodesearch.getrambankf();
	sram = gCodesearch.getsrambankf();

	switch (stype)
	{
	case CODESEARCH_STYPE_EQU:
		CheckDlgButton(hwnd, IDC_SEARCH_EQUAL, BST_CHECKED);
		break;
	case CODESEARCH_STYPE_NEQ:
		CheckDlgButton(hwnd, IDC_SEARCH_NEQ, BST_CHECKED);
		break;
	case CODESEARCH_STYPE_GR:
		CheckDlgButton(hwnd, IDC_SEARCH_GREATER, BST_CHECKED);
		break;
	case CODESEARCH_STYPE_LE:
		CheckDlgButton(hwnd, IDC_SEARCH_LESS, BST_CHECKED);
		break;
	case CODESEARCH_STYPE_EQG:
		CheckDlgButton(hwnd, IDC_SEARCH_EQG, BST_CHECKED);
		break;
	case CODESEARCH_STYPE_EQL:
		CheckDlgButton(hwnd, IDC_SEARCH_EQL, BST_CHECKED);
		break;
	default:
		gCodesearch.setstype(CODESEARCH_STYPE_EQU);
		CheckDlgButton(hwnd, IDC_SEARCH_EQUAL, BST_CHECKED);
		break;
	}

	switch (ntype)
	{
	case CODESEARCH_NTYPE_UNSIGNED:
		CheckDlgButton(hwnd, IDC_HEX, BST_CHECKED);
		break;
	case CODESEARCH_NTYPE_SIGNED:
		CheckDlgButton(hwnd, IDC_DEC_SIGNED, BST_CHECKED);
		break;
	default:
		gCodesearch.setntype(CODESEARCH_NTYPE_UNSIGNED);
		CheckDlgButton(hwnd, IDC_HEX, BST_CHECKED);
		break;
	}

	switch (nsize)
	{
	case CODESEARCH_NSIZE_BYTE:
		CheckDlgButton(hwnd, IDC_BYTE, BST_CHECKED);
		break;
	case CODESEARCH_NSIZE_WORD:
		CheckDlgButton(hwnd, IDC_WORD, BST_CHECKED);
		break;
	case CODESEARCH_NSIZE_FWORD:
		CheckDlgButton(hwnd, IDC_FWORD, BST_CHECKED);
		break;
	case CODESEARCH_NSIZE_DWORD:
		CheckDlgButton(hwnd, IDC_DWORD, BST_CHECKED);
		break;
	default:
		gCodesearch.setnsize(CODESEARCH_NSIZE_BYTE);
		CheckDlgButton(hwnd, IDC_BYTE, BST_CHECKED);
		break;
	}

	switch (target)
	{
	case CODESEARCH_TARGET_OLD:
		CheckDlgButton(hwnd, IDC_MUCH, BST_CHECKED);
		break;
	case CODESEARCH_TARGET_NUM:
		CheckDlgButton(hwnd, IDC_NORMAL, BST_CHECKED);
		break;
	default:
		gCodesearch.settarget(CODESEARCH_TARGET_OLD);
		CheckDlgButton(hwnd, IDC_MUCH, BST_CHECKED);
		break;
	}

	if (ram)
		CheckDlgButton(hwnd, IDC_RAMBANK, BST_CHECKED);
	
	if (sram)
		CheckDlgButton(hwnd, IDC_SRAMBANK, BST_CHECKED);
}

void ParKaiSetgCodeButton(HWND hwnd)
{
	// サーチタイプ設定
	if      (IsDlgButtonChecked(hwnd, IDC_SEARCH_EQUAL) == BST_CHECKED)
		gCodesearch.setstype(CODESEARCH_STYPE_EQU);
	else if (IsDlgButtonChecked(hwnd, IDC_SEARCH_NEQ) == BST_CHECKED)
		gCodesearch.setstype(CODESEARCH_STYPE_NEQ);
	else if (IsDlgButtonChecked(hwnd, IDC_SEARCH_GREATER) == BST_CHECKED)
		gCodesearch.setstype(CODESEARCH_STYPE_GR);
	else if (IsDlgButtonChecked(hwnd, IDC_SEARCH_LESS) == BST_CHECKED)
		gCodesearch.setstype(CODESEARCH_STYPE_LE);
	else if (IsDlgButtonChecked(hwnd, IDC_SEARCH_EQG) == BST_CHECKED)
		gCodesearch.setstype(CODESEARCH_STYPE_EQG);
	else if (IsDlgButtonChecked(hwnd, IDC_SEARCH_EQL) == BST_CHECKED)
		gCodesearch.setstype(CODESEARCH_STYPE_EQL);
	else
	{
		CheckDlgButton(hwnd, IDC_SEARCH_EQUAL, BST_CHECKED);
		gCodesearch.setstype(CODESEARCH_STYPE_EQU);
	}

	// 符号設定
	if (IsDlgButtonChecked(hwnd, IDC_HEX) == BST_CHECKED)
		gCodesearch.setntype(CODESEARCH_NTYPE_UNSIGNED);
	else if (IsDlgButtonChecked(hwnd, IDC_DEC_SIGNED) == BST_CHECKED)
		gCodesearch.setntype(CODESEARCH_NTYPE_SIGNED);
	else if (IsDlgButtonChecked(hwnd, IDC_DEC_UNSIGNED) == BST_CHECKED)
		gCodesearch.setntype(CODESEARCH_NTYPE_UNSIGNED);
	else
	{
		CheckDlgButton(hwnd, IDC_HEX, BST_CHECKED);
		gCodesearch.setntype(CODESEARCH_NTYPE_UNSIGNED);
	}

	// 数値サイズ設定
	if      (IsDlgButtonChecked(hwnd, IDC_BYTE) == BST_CHECKED)
		gCodesearch.setnsize(CODESEARCH_NSIZE_BYTE);
	else if (IsDlgButtonChecked(hwnd, IDC_WORD) == BST_CHECKED)
		gCodesearch.setnsize(CODESEARCH_NSIZE_WORD);
	else if (IsDlgButtonChecked(hwnd, IDC_FWORD) == BST_CHECKED)
		gCodesearch.setnsize(CODESEARCH_NSIZE_FWORD);
	else if (IsDlgButtonChecked(hwnd, IDC_DWORD) == BST_CHECKED)
		gCodesearch.setnsize(CODESEARCH_NSIZE_DWORD);
	else
	{
		CheckDlgButton(hwnd, IDC_BYTE, BST_CHECKED);
		gCodesearch.setnsize(CODESEARCH_NSIZE_BYTE);
	}

	// 対象設定
	if      (IsDlgButtonChecked(hwnd, IDC_MUCH) == BST_CHECKED)   // 前回値指定
		gCodesearch.settarget(CODESEARCH_TARGET_OLD);
	else if (IsDlgButtonChecked(hwnd, IDC_NORMAL) == BST_CHECKED) // 直接指定
	{
		char buf[256];
		dword dat;

		// 指定値を取得
		GetDlgItemText(hwnd, IDC_SEARCH_NUM, buf, 256);
		if (IsDlgButtonChecked(hwnd, IDC_DEC_SIGNED) == BST_CHECKED)
			dat = strtol(buf, NULL, 10);
		else
			dat = strtoul(buf, NULL, (IsDlgButtonChecked(hwnd, IDC_HEX) == BST_CHECKED) ? 16:10);

		gCodesearch.settarget(CODESEARCH_TARGET_NUM);
		gCodesearch.setsearchnum(dat);
	}
	else
	{
		CheckDlgButton(hwnd, IDC_MUCH, BST_CHECKED);
		gCodesearch.settarget(CODESEARCH_TARGET_OLD);
	}

	// RAMBANK設定
	if (IsDlgButtonChecked(hwnd, IDC_RAMBANK) == BST_CHECKED)
		gCodesearch.setrambankf(1);
	else
		gCodesearch.setrambankf(0);

	// SRAMBANK設定
	if (IsDlgButtonChecked(hwnd, IDC_SRAMBANK) == BST_CHECKED)
		gCodesearch.setsrambankf(1);
	else
		gCodesearch.setsrambankf(0);
}

void ParKaiNumToStr(HWND hwnd, char* str, dword num)
{
	char buf[16];
	char format[16];
	int shift;

	// サイズを設定し、numを適正な値に変換する(BYTEorWORDorFWORDorDWORD)
	if      (IsDlgButtonChecked(hwnd, IDC_BYTE) == BST_CHECKED)
	{
		strcpy(buf, "%02");
		num = num & 0xff;
		shift = 24;
	}
	else if (IsDlgButtonChecked(hwnd, IDC_WORD) == BST_CHECKED)
	{
		strcpy(buf, "%04");
		num = num & 0xffff;
		shift = 16;
	}
	else if (IsDlgButtonChecked(hwnd, IDC_FWORD) == BST_CHECKED)
	{
		strcpy(buf, "%06");
		num = num & 0xffffff;
		shift = 8;
	}
	else if (IsDlgButtonChecked(hwnd, IDC_DWORD) == BST_CHECKED)
	{
		strcpy(buf, "%08");
		num = num & 0xffffffff;
		shift = 0;
	}
	else
	{
		CheckDlgButton(hwnd, IDC_BYTE, BST_CHECKED);
		gCodesearch.setnsize(CODESEARCH_NSIZE_BYTE);
		strcpy(buf, "%02");
		num = num & 0xff;
		shift = 0;
	}

	// 数値タイプを設定する(16進数or10進数)
	if      (IsDlgButtonChecked(hwnd, IDC_HEX) == BST_CHECKED)
	{
		sprintf(format, "%sX", buf);
	}
	else if (IsDlgButtonChecked(hwnd, IDC_DEC_SIGNED) == BST_CHECKED)
	{
		num = ((signed)num << shift) >> shift;

		strcpy(format, "%d");
	}
	else if (IsDlgButtonChecked(hwnd, IDC_DEC_UNSIGNED) == BST_CHECKED)
	{
		strcpy(format, "%u");
	}
	else
	{
		CheckDlgButton(hwnd, IDC_HEX, BST_CHECKED);
		sprintf(format, "%sX", buf);
	}

	// 文字列に変換する
	wsprintf(str, format, num);
}

static BOOL CALLBACK ParKaiProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static char filename[256]="";

	HWND hList = GetDlgItem(hwnd, IDC_CODELIST);
	LV_COLUMN lvcol;
	cheat_dat tmp_dat, *cur;
	std::list<cheat_dat>::iterator ite;

	switch(uMsg)
	{
	case WM_INITDIALOG:
		
		lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvcol.fmt = LVCFMT_CENTER;
		
		lvcol.cx = 100;
		lvcol.pszText = "アドレス";
		lvcol.iSubItem = 0;
		ListView_InsertColumn(hList, 0, &lvcol);
		ListView_SetColumn(hList, 0, &lvcol);	// 最初のカラムを中央揃えにするため必要。

		lvcol.cx = 100;
		lvcol.pszText = "前回の値";
		lvcol.iSubItem = 1;
		ListView_InsertColumn(hList, 1, &lvcol);

		lvcol.cx = 100;
		lvcol.pszText = "現在値";
		lvcol.iSubItem = 2;
		ListView_InsertColumn(hList, 2, &lvcol);

		lvcol.cx = 160;
		lvcol.pszText = "バンク(sram:10-25)";
		lvcol.iSubItem = 3;
		ListView_InsertColumn(hList, 3, &lvcol);

		ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT);

		// ボタンの初期状態
		ParKaiGetgCodeButton(hwnd);
		CheckDlgButton(hwnd, IDC_FOREVER, BST_CHECKED);

		if (gCodesearch.count() <= 0)
		{
			EnableWindow(GetDlgItem(hwnd, IDC_SEARCH), FALSE);
			EnableWindow(GetDlgItem(hwnd, IDC_SEARCH_RESET), FALSE);
			EnableWindow(GetDlgItem(hwnd, IDC_SEARCH_UPDATE), FALSE);
		}
		else
			EnableWindow(GetDlgItem(hwnd, IDC_SEARCH_START), FALSE);

		ListView_SetItemCountEx(hList, gCodesearch.count(), 0);

		filename[0]='\0';

		return TRUE;

	case WM_NOTIFY:
		if ( ((LPNMHDR)lParam)->code == LVN_GETDISPINFO )
		{
			TCHAR        szBuf[256];
			NMLVDISPINFO *lpDispInfo = (NMLVDISPINFO *)lParam;

			switch ( lpDispInfo->item.iSubItem )
			{
			case 0:		// アドレス
				if (lpDispInfo->item.mask & LVIF_TEXT)
				{
					wsprintf(szBuf, TEXT("%04X"), gCodesearch.getmlistadr(lpDispInfo->item.iItem));
					lstrcpy(lpDispInfo->item.pszText, szBuf);
				}
				break;
			case 1:		// 前回の値
				if (lpDispInfo->item.mask & LVIF_TEXT)
				{
					ParKaiNumToStr(hwnd, szBuf, gCodesearch.getmlistnum(lpDispInfo->item.iItem));
					lstrcpy(lpDispInfo->item.pszText, szBuf);
				}
				break;
			case 2:		// 現在値
				if (lpDispInfo->item.mask & LVIF_TEXT)
				{
					MEMLIST mlist = gCodesearch.getmlist(lpDispInfo->item.iItem);
					if (mlist.bank == 0)
						ParKaiNumToStr(hwnd, szBuf, gCodesearch.getdword(mlist.adr));
					else if ((mlist.bank >= 1) && (mlist.bank <= 7))
						ParKaiNumToStr(hwnd, szBuf, gCodesearch.getramdword(mlist.adr, mlist.bank));
					else if ((mlist.bank >= 10) && (mlist.bank <= 25))
						ParKaiNumToStr(hwnd, szBuf, gCodesearch.getsramdword(mlist.adr, mlist.bank));
					else
						break;
					lstrcpy(lpDispInfo->item.pszText, szBuf);
				}
				break;
			case 3:		// バンク
				if (lpDispInfo->item.mask & LVIF_TEXT)
				{
					wsprintf(szBuf, TEXT("%d"), gCodesearch.getmlistbank(lpDispInfo->item.iItem));
					lstrcpy(lpDispInfo->item.pszText, szBuf);
				}
				break;
			default:
				break;
			}
		}
		else if ( ((LPNMHDR)lParam)->code == NM_DBLCLK)
		{
			int index = -1;
			char buf[256];

			index = ListView_GetNextItem(hList, index, LVNI_ALL | LVNI_SELECTED);
			if (index == -1)
				break;
			ListView_GetItemText(hList, index, 0, buf, 256);

			SetDlgItemText(hwnd, IDC_ADDR, buf);
		}
		return TRUE;

	case WM_COMMAND:
		if (	(LOWORD(wParam) == IDC_HEX) ||
				(LOWORD(wParam) == IDC_DEC_SIGNED) ||
				(LOWORD(wParam) == IDC_DEC_UNSIGNED) ||
				(LOWORD(wParam) == IDC_BYTE) ||
				(LOWORD(wParam) == IDC_WORD) ||
				(LOWORD(wParam) == IDC_FWORD) ||
				(LOWORD(wParam) == IDC_DWORD) ||
				(LOWORD(wParam) == IDC_SEARCH_UPDATE) )
		{
			int start, end;
			start = ListView_GetTopIndex(hList);
			end = start + ListView_GetCountPerPage(hList);

			ListView_RedrawItems(hList, start, end);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDOK)
		{
			DestroyWindow(hwnd);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_SEARCH_START)
		{
			ParKaiSetgCodeButton(hwnd);
			gCodesearch.searchstart();
			ListView_SetItemCountEx(hList, gCodesearch.count(), 0);

			EnableWindow(GetDlgItem(hwnd, IDC_SEARCH), TRUE);
			EnableWindow(GetDlgItem(hwnd, IDC_SEARCH_RESET), TRUE);
			EnableWindow(GetDlgItem(hwnd, IDC_SEARCH_UPDATE), TRUE);
			EnableWindow(GetDlgItem(hwnd, IDC_SEARCH_START), FALSE);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_SEARCH_RESET)
		{
			ParKaiSetgCodeButton(hwnd);
			gCodesearch.searchstart();
			ListView_SetItemCountEx(hList, gCodesearch.count(), 0);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_SEARCH)
		{
			ParKaiSetgCodeButton(hwnd);
			if (gCodesearch.search() <= 0)
			{
				EnableWindow(GetDlgItem(hwnd, IDC_SEARCH), FALSE);
				EnableWindow(GetDlgItem(hwnd, IDC_SEARCH_UPDATE), FALSE);
				EnableWindow(GetDlgItem(hwnd, IDC_SEARCH_RESET), FALSE);
				EnableWindow(GetDlgItem(hwnd, IDC_SEARCH_START), TRUE);
			}
			ListView_SetItemCountEx(hList, gCodesearch.count(), 0);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_ADD_SEARCH)
		{
			char buf[256];
			char name[16];
			BYTE bank;
			WORD adr, adr2;
			DWORD dat, dat2;
			bool have_2 = true;
			BYTE code;

			GetDlgItemText(hwnd, IDC_ADDR, buf, 256);
			if (buf[1] == ':')
			{
				bank = buf[0] - '0';
				buf[0] = buf[2];
				buf[1] = buf[3];
				buf[2] = buf[4];
				buf[3] = buf[5];
				buf[4] = '\0';
			}
			else
				bank = 0;
			adr = (WORD)strtoul(buf, NULL, 16);
			GetDlgItemText(hwnd, IDC_DAT, buf, 256);
			dat = strtoul(buf, NULL, (IsDlgButtonChecked(hwnd, IDC_HEX) == BST_CHECKED) ? 16:10);
			GetDlgItemText(hwnd, IDC_ADDR2, buf, 256);
			adr2 = (WORD)strtoul(buf, NULL, 16);
			
			if (buf[0] == '\0')
				have_2 = false;

			GetDlgItemText(hwnd, IDC_DAT2, buf, 256);
			dat2 = strtoul(buf, NULL, (IsDlgButtonChecked(hwnd, IDC_HEX) == BST_CHECKED) ? 16:10);
			if (buf[0] == '\0')
				have_2 = false;

			int dat_len, i;

			dat_len = (IsDlgButtonChecked(hwnd, IDC_BYTE) == BST_CHECKED) ? 1:0 +
				(IsDlgButtonChecked(hwnd, IDC_WORD) == BST_CHECKED) ? 2:0 +
				(IsDlgButtonChecked(hwnd, IDC_FWORD) == BST_CHECKED) ? 3:0 +
				(IsDlgButtonChecked(hwnd, IDC_DWORD) == BST_CHECKED) ? 4:0;

			if (IsDlgButtonChecked(hwnd, IDC_ONCE) == BST_CHECKED)
			{
				if (adr < 0x8000)
					return TRUE;
				for (i = 0; i < dat_len; i++)
					if (bank)
						g_gb[0]->get_cpu()->get_ram()[(bank*0x1000 + adr-0xd000+i) & 0x7fff] = (BYTE)((dat >> (8*i)) & 0xFF);
					else
						g_gb[0]->get_cpu()->write(adr+i, (BYTE)((dat >> (8*i)) & 0xFF));
				return TRUE;
			}
			else
			{
				if (IsDlgButtonChecked(hwnd, IDC_FOREVER) == BST_CHECKED)
				{
					if (bank) code = 0x90 + bank;
					else code = 1;
				}
				else if (IsDlgButtonChecked(hwnd, IDC_LOOP) == BST_CHECKED)
				{
					code = 0x10;
					dat_len = 1;
				}
				else if (IsDlgButtonChecked(hwnd, IDC_CMP_EQUAL) == BST_CHECKED)
				{
					code = 0x20;
					dat_len = 1;
				}
				else if (IsDlgButtonChecked(hwnd, IDC_CMP_LESS) == BST_CHECKED)
				{
					code = 0x21;
					dat_len = 1;
				}
				else if (IsDlgButtonChecked(hwnd, IDC_CMP_LARGE) == BST_CHECKED)
				{
					code = 0x22;
					dat_len = 1;
				}
				tmp_dat.code = code;

				for (i = 0; i < dat_len; i++)
				{
					GetDlgItemText(hwnd, IDC_CHEAT_NAME, name, 16);
					if (name[0] == '\0')
						g_gb[0]->get_cheat()->create_unique_name(name);
					else if (dat_len > 1)
						sprintf(name, "%s%d", name, i);
					strcpy(tmp_dat.name, name);

					if (have_2)
					{
						if (tmp_dat.code == 10)
						{
							tmp_dat.adr = adr;
							tmp_dat.dat = (byte)(dat & 0xff);
							tmp_dat.next = new cheat_dat;
							tmp_dat.next->code = 1;
							tmp_dat.next->adr = adr2+i;
							tmp_dat.next->dat = (byte)((dat2 >> (8*i)) & 0xff);
							tmp_dat.next->next = NULL;
						}
						else
						{
							tmp_dat.adr = adr+i;
							tmp_dat.dat = (byte)((dat >> (8*i)) & 0xff);
							tmp_dat.next = new cheat_dat;
							tmp_dat.next->code = 1;
							tmp_dat.next->adr = adr2;
							tmp_dat.next->dat = (byte)(dat2 & 0xff);
							tmp_dat.next->next = NULL;
						}
					}
					else
					{
						tmp_dat.adr = adr+i;
						tmp_dat.dat = (byte)((dat >> (8*i)) & 0xff);
						tmp_dat.next = NULL;
					}
					tmp_dat.enable = true;
					g_gb[0]->get_cheat()->add_cheat(&tmp_dat);
				}


				if (SendMessage(hList, LB_GETTEXTLEN, 0, 0) != LB_ERR)
					while(SendMessage(hList, LB_DELETESTRING, 0, 0));

				for (ite = g_gb[0]->get_cheat()->get_first(); ite != g_gb[0]->get_cheat()->get_end(); ite++)
				{
					char buf[256], buf2[256];
					buf[0] = 0;
					cur = &(*ite);

					do
					{
						sprintf(buf, "%s%02X%02X%02X%02X", buf, cur->code, cur->dat, cur->adr & 0xFF, (cur->adr >> 8));
						cur = cur->next;
					}while(cur);

					sprintf(buf2, "%s:%s", buf, ite->name);
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buf2);
				}
			}
			return TRUE;
		}
		else if ( (LOWORD(wParam) == IDC_OVER_RIDE) && (filename[0] != '\0') )
		{
			FILE *tmp_file=fopen(filename,"w");
			g_gb[0]->get_cheat()->save(tmp_file);
			fclose(tmp_file);
			return TRUE;
		}
		else if ( (LOWORD(wParam) == IDC_OVER_RIDE) || (LOWORD(wParam) == IDC_CHEAT_SAVE) )
		{
			char dir[256], save_dir[256];
			GetCurrentDirectory(256, dir);
			config->get_media_dir(save_dir);
			SetCurrentDirectory(save_dir);
			OPENFILENAME ofn;

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.hInstance       = hInstance;
			ofn.hwndOwner       = hWnd;
			ofn.lStructSize     = sizeof(ofn);
			ofn.lpstrDefExt     = "tch";
			ofn.lpstrFilter     = "TGB cheat code file\0*.tch\0All Files (*.*)\0*.*\0\0";
			ofn.nMaxFile        = 256;
			ofn.nMaxFileTitle   = 256;
			ofn.lpstrFileTitle  = filename;
			ofn.lpstrTitle      = "TGB Cheat Save";
			ofn.lpstrInitialDir = save_dir;

			if (GetSaveFileName(&ofn) == IDOK)
			{
				if (strstr(filename, ".tch") == 0) strcat(filename, ".tch");

				FILE *tmp_file = fopen(filename, "w");
				g_gb[0]->get_cheat()->save(tmp_file);
				fclose(tmp_file);
			}
			SetCurrentDirectory(dir);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_CHEAT_READ)
		{
			char dir[256], save_dir[256];
			GetCurrentDirectory(256, dir);
			config->get_media_dir(save_dir);
			SetCurrentDirectory(save_dir);
			OPENFILENAME ofn;

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.hInstance       = hInstance;
			ofn.hwndOwner       = hWnd;
			ofn.lStructSize     = sizeof(ofn);
			ofn.lpstrDefExt     = "tch";
			ofn.lpstrFilter     = "TGB cheat code file\0*.tch\0All Files (*.*)\0*.*\0\0";
			ofn.nMaxFile        = 256;
			ofn.nMaxFileTitle   = 256;
			ofn.lpstrFileTitle  = filename;
			ofn.lpstrTitle      = "TGB Cheat Load";
			ofn.lpstrInitialDir = save_dir;

			if (GetOpenFileName(&ofn) == IDOK)
			{
				FILE *tmp_file = fopen(filename, "r");
				g_gb[0]->get_cheat()->load(tmp_file);
				fclose(tmp_file);
			}

			if (SendMessage(hList, LB_GETTEXTLEN, 0, 0) != LB_ERR)
				while( SendMessage(hList, LB_DELETESTRING, 0, 0) );

			for (ite = g_gb[0]->get_cheat()->get_first(); ite != g_gb[0]->get_cheat()->get_end(); ite++)
			{
				char buf[256], buf2[256];
				buf[0] = 0;
				cur = &(*ite);

				do
				{
					sprintf(buf, "%s%02X%02X%02X%02X", buf, cur->code, cur->dat, cur->adr&0xFF, (cur->adr>>8));
					cur = cur->next;
				} while(cur);
				
				sprintf(buf2, "%s:%s", buf, ite->name);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buf2);
			}
			SetCurrentDirectory(dir);
			return TRUE;
		}

		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return TRUE;
	}

    return FALSE;
}
