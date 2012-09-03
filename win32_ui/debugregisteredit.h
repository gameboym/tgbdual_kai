// 2010/09/13製作
// クラス化や抽象化できそうにないので
// 各レジストリ用の処理関数を個別に作成。
// もし処理内容に変更があったら全て変更する必要あり。

int RegEditSelCheck(HWND hwnd, int selpos) {
	int strlen;

	strlen = SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0);

	if (selpos >= strlen)
		return 0;

	if (selpos < 0)
		return 0;

	return 1;
}


LRESULT CALLBACK MyRegEditProcA(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int start, end;
	
	char strbuf[256];
	char num[2];
	char *tocheck;

	byte chgdata, olddata;
	cpu_regs *regs;
		
	regs = g_gb[0]->get_cpu()->get_regs();

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		VKNumPadToNum(&wParam);
		if (isxdigit((int)wParam)) {
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			// 選択可能領域か判定する
			if (!RegEditSelCheck(hwnd, start))
				return 0;

			num[0] = (char)wParam;
			num[1] = '\0';
			chgdata = (byte)strtol(num, &tocheck, 16); 
			if (tocheck == &num[0]) {
				sprintf(strbuf, "入力文字が不正です。文字 = %c", num[0]);
				MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
				return 0;
			}

			olddata = REGD_A;
			if (! start)
				REGD_A = (chgdata << 4) + (olddata & 0x0f);
			else
				REGD_A = chgdata + (olddata & 0xf0);

			// 数値を新しいものに置き換える
			ShowRegister(GetParent(hwnd));

			if (! start && RegEditSelCheck(hwnd, start + 1)) // 上位ビットの場合下位に移動させる
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			else // 下位ビットであればフォーカスを渡す。
				SetFocus(GetParent(hwnd));

			return 0;
		}
		switch (wParam)
		{
		case VK_LEFT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start - 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 1, (LPARAM) end - 1);
			return 0;
		case VK_RIGHT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start + 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			return 0;
		default:
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:
		::CallWindowProc( old_redit_procA, hwnd, uMsg, wParam, lParam );
		::CallWindowProc( old_redit_procA, hwnd, WM_LBUTTONUP, wParam, lParam );
		SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

		// 選択可能領域か判定する
		if (RegEditSelCheck(hwnd, start)) {
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM) end+1);
			return 0; // 選択してから戻る
		}

		SetFocus(GetParent(hwnd)); // フォーカスを渡して戻る
		return 0;

	case WM_CHAR:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYUP:
		return 0;

	}
	return ::CallWindowProc( old_redit_procA, hwnd, uMsg, wParam, lParam );
}

LRESULT CALLBACK MyRegEditProcF(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int start, end;
	
	char strbuf[256];
	char num[2];
	char *tocheck;

	byte chgdata, olddata;
	cpu_regs *regs;
		
	regs = g_gb[0]->get_cpu()->get_regs();

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		VKNumPadToNum(&wParam);
		if (isxdigit((int)wParam)) {
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			// 選択可能領域か判定する
			if (!RegEditSelCheck(hwnd, start))
				return 0;

			num[0] = (char)wParam;
			num[1] = '\0';
			chgdata = (byte)strtol(num, &tocheck, 16); 
			if (tocheck == &num[0]) {
				sprintf(strbuf, "入力文字が不正です。文字 = %c", num[0]);
				MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
				return 0;
			}

			olddata = REGD_F;
			if (! start)
				REGD_F = (chgdata << 4) + (olddata & 0x0f);
			else
				REGD_F = chgdata + (olddata & 0xf0);

			// 数値を新しいものに置き換える
			ShowRegister(GetParent(hwnd));

			if (!start && RegEditSelCheck(hwnd, start + 1)) // 上位ビットの場合下位に移動させる
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			else // 下位ビットであればフォーカスを渡す。
				SetFocus(GetParent(hwnd));

			return 0;
		}
		switch (wParam)
		{
		case VK_LEFT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start - 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 1, (LPARAM) end - 1);
			return 0;
		case VK_RIGHT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start + 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			return 0;
		default:
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:
		::CallWindowProc( old_redit_procF, hwnd, uMsg, wParam, lParam );
		::CallWindowProc( old_redit_procF, hwnd, WM_LBUTTONUP, wParam, lParam );
		SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

		// 選択可能領域か判定する
		if (RegEditSelCheck(hwnd, start)) {
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM) end+1);
			return 0; // 選択してから戻る
		}

		SetFocus(GetParent(hwnd)); // フォーカスを渡して戻る
		return 0;

	case WM_CHAR:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYUP:
		return 0;

	}
	return ::CallWindowProc( old_redit_procF, hwnd, uMsg, wParam, lParam );
}

LRESULT CALLBACK MyRegEditProcB(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int start, end;
	
	char strbuf[256];
	char num[2];
	char *tocheck;

	byte chgdata, olddata;
	cpu_regs *regs;
		
	regs = g_gb[0]->get_cpu()->get_regs();

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		VKNumPadToNum(&wParam);
		if (isxdigit((int)wParam)) {
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			// 選択可能領域か判定する
			if (!RegEditSelCheck(hwnd, start))
				return 0;

			num[0] = (char)wParam;
			num[1] = '\0';
			chgdata = (byte)strtol(num, &tocheck, 16); 
			if (tocheck == &num[0]) {
				sprintf(strbuf, "入力文字が不正です。文字 = %c", num[0]);
				MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
				return 0;
			}

			olddata = REGD_B;
			if (! start)
				REGD_B = (chgdata << 4) + (olddata & 0x0f);
			else
				REGD_B = chgdata + (olddata & 0xf0);

			// 数値を新しいものに置き換える
			ShowRegister(GetParent(hwnd));

			if (! start && RegEditSelCheck(hwnd, start + 1)) // 上位ビットの場合下位に移動させる
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			else // 下位ビットであればフォーカスを渡す。
				SetFocus(GetParent(hwnd));

			return 0;
		}
		switch (wParam)
		{
		case VK_LEFT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start - 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 1, (LPARAM) end - 1);
			return 0;
		case VK_RIGHT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start + 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			return 0;
		default:
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:
		::CallWindowProc( old_redit_procB, hwnd, uMsg, wParam, lParam );
		::CallWindowProc( old_redit_procB, hwnd, WM_LBUTTONUP, wParam, lParam );
		SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

		// 選択可能領域か判定する
		if (RegEditSelCheck(hwnd, start)) {
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM) end+1);
			return 0; // 選択してから戻る
		}

		SetFocus(GetParent(hwnd)); // フォーカスを渡して戻る
		return 0;

	case WM_CHAR:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYUP:
		return 0;

	}
	return ::CallWindowProc( old_redit_procB, hwnd, uMsg, wParam, lParam );
}

LRESULT CALLBACK MyRegEditProcC(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int start, end;
	
	char strbuf[256];
	char num[2];
	char *tocheck;

	byte chgdata, olddata;
	cpu_regs *regs;
		
	regs = g_gb[0]->get_cpu()->get_regs();

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		VKNumPadToNum(&wParam);
		if (isxdigit((int)wParam)) {
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			// 選択可能領域か判定する
			if (!RegEditSelCheck(hwnd, start))
				return 0;

			num[0] = (char)wParam;
			num[1] = '\0';
			chgdata = (byte)strtol(num, &tocheck, 16); 
			if (tocheck == &num[0]) {
				sprintf(strbuf, "入力文字が不正です。文字 = %c", num[0]);
				MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
				return 0;
			}

			olddata = REGD_C;
			if (! start)
				REGD_C = (chgdata << 4) + (olddata & 0x0f);
			else
				REGD_C = chgdata + (olddata & 0xf0);

			// 数値を新しいものに置き換える
			ShowRegister(GetParent(hwnd));

			if (! start && RegEditSelCheck(hwnd, start + 1)) // 上位ビットの場合下位に移動させる
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			else // 下位ビットであればフォーカスを渡す。
				SetFocus(GetParent(hwnd));

			return 0;
		}
		switch (wParam)
		{
		case VK_LEFT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start - 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 1, (LPARAM) end - 1);
			return 0;
		case VK_RIGHT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start + 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			return 0;
		default:
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:
		::CallWindowProc( old_redit_procC, hwnd, uMsg, wParam, lParam );
		::CallWindowProc( old_redit_procC, hwnd, WM_LBUTTONUP, wParam, lParam );
		SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

		// 選択可能領域か判定する
		if (RegEditSelCheck(hwnd, start)) {
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM) end+1);
			return 0; // 選択してから戻る
		}

		SetFocus(GetParent(hwnd)); // フォーカスを渡して戻る
		return 0;

	case WM_CHAR:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYUP:
		return 0;

	}
	return ::CallWindowProc( old_redit_procC, hwnd, uMsg, wParam, lParam );
}

LRESULT CALLBACK MyRegEditProcD(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int start, end;
	
	char strbuf[256];
	char num[2];
	char *tocheck;

	byte chgdata, olddata;
	cpu_regs *regs;
		
	regs = g_gb[0]->get_cpu()->get_regs();

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		VKNumPadToNum(&wParam);
		if (isxdigit((int)wParam)) {
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			// 選択可能領域か判定する
			if (!RegEditSelCheck(hwnd, start))
				return 0;

			num[0] = (char)wParam;
			num[1] = '\0';
			chgdata = (byte)strtol(num, &tocheck, 16); 
			if (tocheck == &num[0]) {
				sprintf(strbuf, "入力文字が不正です。文字 = %c", num[0]);
				MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
				return 0;
			}

			olddata = REGD_D;
			if (! start)
				REGD_D = (chgdata << 4) + (olddata & 0x0f);
			else
				REGD_D = chgdata + (olddata & 0xf0);

			// 数値を新しいものに置き換える
			ShowRegister(GetParent(hwnd));

			if (! start && RegEditSelCheck(hwnd, start + 1)) // 上位ビットの場合下位に移動させる
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			else // 下位ビットであればフォーカスを渡す。
				SetFocus(GetParent(hwnd));

			return 0;
		}
		switch (wParam)
		{
		case VK_LEFT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start - 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 1, (LPARAM) end - 1);
			return 0;
		case VK_RIGHT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start + 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			return 0;
		default:
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:
		::CallWindowProc( old_redit_procD, hwnd, uMsg, wParam, lParam );
		::CallWindowProc( old_redit_procD, hwnd, WM_LBUTTONUP, wParam, lParam );
		SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

		// 選択可能領域か判定する
		if (RegEditSelCheck(hwnd, start)) {
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM) end+1);
			return 0; // 選択してから戻る
		}

		SetFocus(GetParent(hwnd)); // フォーカスを渡して戻る
		return 0;

	case WM_CHAR:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYUP:
		return 0;

	}
	return ::CallWindowProc( old_redit_procD, hwnd, uMsg, wParam, lParam );
}

LRESULT CALLBACK MyRegEditProcE(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int start, end;
	
	char strbuf[256];
	char num[2];
	char *tocheck;

	byte chgdata, olddata;
	cpu_regs *regs;
		
	regs = g_gb[0]->get_cpu()->get_regs();

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		VKNumPadToNum(&wParam);
		if (isxdigit((int)wParam)) {
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			// 選択可能領域か判定する
			if (!RegEditSelCheck(hwnd, start))
				return 0;

			num[0] = (char)wParam;
			num[1] = '\0';
			chgdata = (byte)strtol(num, &tocheck, 16); 
			if (tocheck == &num[0]) {
				sprintf(strbuf, "入力文字が不正です。文字 = %c", num[0]);
				MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
				return 0;
			}

			olddata = REGD_E;
			if (! start)
				REGD_E = (chgdata << 4) + (olddata & 0x0f);
			else
				REGD_E = chgdata + (olddata & 0xf0);

			// 数値を新しいものに置き換える
			ShowRegister(GetParent(hwnd));

			if (! start && RegEditSelCheck(hwnd, start + 1)) // 上位ビットの場合下位に移動させる
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			else // 下位ビットであればフォーカスを渡す。
				SetFocus(GetParent(hwnd));

			return 0;
		}
		switch (wParam)
		{
		case VK_LEFT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start - 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 1, (LPARAM) end - 1);
			return 0;
		case VK_RIGHT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start + 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			return 0;
		default:
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:
		::CallWindowProc( old_redit_procE, hwnd, uMsg, wParam, lParam );
		::CallWindowProc( old_redit_procE, hwnd, WM_LBUTTONUP, wParam, lParam );
		SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

		// 選択可能領域か判定する
		if (RegEditSelCheck(hwnd, start)) {
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM) end+1);
			return 0; // 選択してから戻る
		}

		SetFocus(GetParent(hwnd)); // フォーカスを渡して戻る
		return 0;

	case WM_CHAR:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYUP:
		return 0;

	}
	return ::CallWindowProc( old_redit_procE, hwnd, uMsg, wParam, lParam );
}

LRESULT CALLBACK MyRegEditProcH(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int start, end;
	
	char strbuf[256];
	char num[2];
	char *tocheck;

	byte chgdata, olddata;
	cpu_regs *regs;
		
	regs = g_gb[0]->get_cpu()->get_regs();

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		VKNumPadToNum(&wParam);
		if (isxdigit((int)wParam)) {
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			// 選択可能領域か判定する
			if (!RegEditSelCheck(hwnd, start))
				return 0;

			num[0] = (char)wParam;
			num[1] = '\0';
			chgdata = (byte)strtol(num, &tocheck, 16); 
			if (tocheck == &num[0]) {
				sprintf(strbuf, "入力文字が不正です。文字 = %c", num[0]);
				MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
				return 0;
			}

			olddata = REGD_H;
			if (! start)
				REGD_H = (chgdata << 4) + (olddata & 0x0f);
			else
				REGD_H = chgdata + (olddata & 0xf0);

			// 数値を新しいものに置き換える
			ShowRegister(GetParent(hwnd));

			if (! start && RegEditSelCheck(hwnd, start + 1)) // 上位ビットの場合下位に移動させる
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			else // 下位ビットであればフォーカスを渡す。
				SetFocus(GetParent(hwnd));

			return 0;
		}
		switch (wParam)
		{
		case VK_LEFT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start - 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 1, (LPARAM) end - 1);
			return 0;
		case VK_RIGHT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start + 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			return 0;
		default:
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:
		::CallWindowProc( old_redit_procH, hwnd, uMsg, wParam, lParam );
		::CallWindowProc( old_redit_procH, hwnd, WM_LBUTTONUP, wParam, lParam );
		SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

		// 選択可能領域か判定する
		if (RegEditSelCheck(hwnd, start)) {
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM) end+1);
			return 0; // 選択してから戻る
		}

		SetFocus(GetParent(hwnd)); // フォーカスを渡して戻る
		return 0;

	case WM_CHAR:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYUP:
		return 0;

	}
	return ::CallWindowProc( old_redit_procH, hwnd, uMsg, wParam, lParam );
}

LRESULT CALLBACK MyRegEditProcL(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int start, end;
	
	char strbuf[256];
	char num[2];
	char *tocheck;

	byte chgdata, olddata;
	cpu_regs *regs;
		
	regs = g_gb[0]->get_cpu()->get_regs();

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		VKNumPadToNum(&wParam);
		if (isxdigit((int)wParam)) {
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			// 選択可能領域か判定する
			if (!RegEditSelCheck(hwnd, start))
				return 0;

			num[0] = (char)wParam;
			num[1] = '\0';
			chgdata = (byte)strtol(num, &tocheck, 16); 
			if (tocheck == &num[0]) {
				sprintf(strbuf, "入力文字が不正です。文字 = %c", num[0]);
				MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
				return 0;
			}

			olddata = REGD_L;
			if (! start)
				REGD_L = (chgdata << 4) + (olddata & 0x0f);
			else
				REGD_L = chgdata + (olddata & 0xf0);

			// 数値を新しいものに置き換える
			ShowRegister(GetParent(hwnd));

			if (! start && RegEditSelCheck(hwnd, start + 1)) // 上位ビットの場合下位に移動させる
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			else // 下位ビットであればフォーカスを渡す。
				SetFocus(GetParent(hwnd));

			return 0;
		}
		switch (wParam)
		{
		case VK_LEFT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start - 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 1, (LPARAM) end - 1);
			return 0;
		case VK_RIGHT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start + 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			return 0;
		default:
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:
		::CallWindowProc( old_redit_procL, hwnd, uMsg, wParam, lParam );
		::CallWindowProc( old_redit_procL, hwnd, WM_LBUTTONUP, wParam, lParam );
		SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

		// 選択可能領域か判定する
		if (RegEditSelCheck(hwnd, start)) {
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM) end+1);
			return 0; // 選択してから戻る
		}

		SetFocus(GetParent(hwnd)); // フォーカスを渡して戻る
		return 0;

	case WM_CHAR:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYUP:
		return 0;

	}
	return ::CallWindowProc( old_redit_procL, hwnd, uMsg, wParam, lParam );
}

LRESULT CALLBACK MyRegEditProcSP(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int start, end;
	
	char strbuf[256];
	char num[2];
	char *tocheck;

	byte chgdata;
	word olddata;
	cpu_regs *regs;
		
	regs = g_gb[0]->get_cpu()->get_regs();

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		VKNumPadToNum(&wParam);
		if (isxdigit((int)wParam)) {
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			// 選択可能領域か判定する
			if (!RegEditSelCheck(hwnd, start))
				return 0;

			num[0] = (char)wParam;
			num[1] = '\0';
			chgdata = (byte)strtol(num, &tocheck, 16); 
			if (tocheck == &num[0]) {
				sprintf(strbuf, "入力文字が不正です。文字 = %c", num[0]);
				MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
				return 0;
			}

			olddata = REGD_SP;
			switch (start)
			{
			case 0:
				REGD_SP = (chgdata << 12) + (olddata & 0x0fff);
				break;
			case 1:
				REGD_SP = (chgdata << 8) + (olddata & 0xf0ff);
				break;
			case 2:
				REGD_SP = (chgdata << 4) + (olddata & 0xff0f);
				break;
			default:
				REGD_SP = chgdata+ (olddata & 0xfff0);
				break;
			}

			// 数値を新しいものに置き換える
			ShowRegister(GetParent(hwnd));

			if (start < 3 && RegEditSelCheck(hwnd, start + 1)) // 上位ビットの場合下位に移動させる
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			else // 下位ビットであればフォーカスを渡す。
				SetFocus(GetParent(hwnd));

			return 0;
		}
		switch (wParam)
		{
		case VK_LEFT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start - 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 1, (LPARAM) end - 1);
			return 0;
		case VK_RIGHT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start + 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			return 0;
		default:
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:
		::CallWindowProc( old_redit_procSP, hwnd, uMsg, wParam, lParam );
		::CallWindowProc( old_redit_procSP, hwnd, WM_LBUTTONUP, wParam, lParam );
		SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

		// 選択可能領域か判定する
		if (RegEditSelCheck(hwnd, start)) {
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM) end+1);
			return 0; // 選択してから戻る
		}

		SetFocus(GetParent(hwnd)); // フォーカスを渡して戻る
		return 0;

	case WM_CHAR:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYUP:
		return 0;

	}
	return ::CallWindowProc( old_redit_procSP, hwnd, uMsg, wParam, lParam );
}

LRESULT CALLBACK MyRegEditProcPC(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int start, end;
	
	char strbuf[256];
	char num[2];
	char *tocheck;

	byte chgdata;
	word olddata;
	cpu_regs *regs;
		
	regs = g_gb[0]->get_cpu()->get_regs();

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		VKNumPadToNum(&wParam);
		if (isxdigit((int)wParam)) {
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			// 選択可能領域か判定する
			if (!RegEditSelCheck(hwnd, start))
				return 0;

			num[0] = (char)wParam;
			num[1] = '\0';
			chgdata = (byte)strtol(num, &tocheck, 16); 
			if (tocheck == &num[0]) {
				sprintf(strbuf, "入力文字が不正です。文字 = %c", num[0]);
				MessageBox( hwnd, strbuf, "メッセージ", MB_OK );
				return 0;
			}

			olddata = REGD_PC;
			switch (start)
			{
			case 0:
				REGD_PC = (chgdata << 12) + (olddata & 0x0fff);
				break;
			case 1:
				REGD_PC = (chgdata << 8) + (olddata & 0xf0ff);
				break;
			case 2:
				REGD_PC = (chgdata << 4) + (olddata & 0xff0f);
				break;
			default:
				REGD_PC = chgdata+ (olddata & 0xfff0);
				break;
			}

			// 数値を新しいものに置き換える
			SendMessage(GetParent(hwnd), WM_USER+2, 0, 0);

			if (start < 3 && RegEditSelCheck(hwnd, start + 1)) // 上位ビットの場合下位に移動させる
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			else // 下位ビットであればフォーカスを渡す。
				SetFocus(GetParent(hwnd));

			return 0;
		}
		switch (wParam)
		{
		case VK_LEFT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start - 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start - 1, (LPARAM) end - 1);
			return 0;
		case VK_RIGHT:
			SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
			if (RegEditSelCheck(hwnd, start + 1))
				SendMessage(hwnd, EM_SETSEL, (WPARAM)start + 1, (LPARAM) end + 1);
			return 0;
		default:
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:
		::CallWindowProc( old_redit_procPC, hwnd, uMsg, wParam, lParam );
		::CallWindowProc( old_redit_procPC, hwnd, WM_LBUTTONUP, wParam, lParam );
		SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

		// 選択可能領域か判定する
		if (RegEditSelCheck(hwnd, start)) {
			SendMessage(hwnd, EM_SETSEL, (WPARAM)start, (LPARAM) end+1);
			return 0; // 選択してから戻る
		}

		SetFocus(GetParent(hwnd)); // フォーカスを渡して戻る
		return 0;

	case WM_CHAR:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYUP:
		return 0;

	}
	return ::CallWindowProc( old_redit_procPC, hwnd, uMsg, wParam, lParam );
}

