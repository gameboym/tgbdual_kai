/*--------------------------------------------------
   TGB Dual - Gameboy Emulator -
   Copyright (C) 2001-2012  Hii & gbm

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include <stdio.h>

extern void PAUSEprocess(void);

// ____processbreaker_________________________
// 強制割り込みで停止させるため処理の流れを乱す。
// ブレークの数を固定にするか非固定かは速度を見て決める。
// ただ、重要事項のため多少の速度は我慢する必要があり。
// 固定の場合は空きの管理を自分で行うようにするため処理を変更する。
class ProcessBreaker
{
public :
	ProcessBreaker(int num = 3) : breaknum(num)
	{
		checknum = new unsigned int[breaknum];
		for(int i = 0; i < breaknum; i++)
			checknum[i] = 0xffffffff;
	}
	virtual ~ProcessBreaker()
	{
		delete[] checknum;
	}
	virtual inline void check(unsigned int data) // リアルタイム処理
	{
		for (int i = 0; i < breaknum; i++)
			if (checknum[i] == data)
				breakprocess(); // 強制停止
	}

	virtual inline int set(int num, unsigned int data)
	{
		if (num >= breaknum)
			return -1;
		checknum[num] = data;
		return 0;
	}
	virtual inline int del(int num)
	{
		if (num >= breaknum)
			return -1;
		checknum[num] = 0xffffffff;
		return 0;
	}
	virtual inline void alldel()
	{
		for (int i = 0; i < breaknum; i++)
			checknum[i] = 0xffffffff;
	}
	virtual inline void get(unsigned int *check)
	{
		for (int i = 0; i < breaknum; i++)
			check[i] = checknum[i];
	}
	inline int getnum(void)
	{
		return breaknum;
	}
protected :
	int breaknum;
	unsigned int *checknum;

	inline void breakprocess(void) // 依存処理
	{
		PAUSEprocess();
	}
};


// ブレークの数が3に固定されたバージョン
class ProcessBreakerb : public ProcessBreaker
{
public :
	ProcessBreakerb() : ProcessBreaker(3)
	{
		for (int i = 0; i < breaknum; i++)
			freenumflug[i] = true;
	}
	virtual ~ProcessBreakerb(){}
	inline void check(unsigned int data) // リアルタイム処理
	{
			if (checknum[0] == data)
				breakprocess(); // 強制停止
			else if (checknum[1] == data)
				breakprocess(); // 強制停止
			else if (checknum[2] == data)
				breakprocess(); // 強制停止
	}
	inline int set(unsigned int data)
	{
		for (int i = 0; i < breaknum; i++)
		{
			if (! freenumflug[i])
			{
				if (checknum[i] == data)
					return 0;
			}
		}
		for (int i = 0; i < breaknum; i++)
		{
			if (freenumflug[i])
			{
				checknum[i] = data;
				freenumflug[i] = false;
				return 0;
			}
		}
		return -1;
	}
	inline void get(unsigned int *check)
	{
		for (int i = 0; i < breaknum; i++)
		{
			if (freenumflug[i])
				check[i] = 0xffffffff;
			else
				check[i] = checknum[i];
		}
	}
	inline int del(unsigned int data)
	{
		for (int i = 0; i < breaknum; i++)
		{
			if (!freenumflug[i])
			{
				if (checknum[i] == data)
				{
					checknum[i] = 0xffffffff;
					freenumflug[i] = true;
					return 0;
				}
			}
		}
		return -1;
	}
	inline void alldel()
	{
		for (int i = 0; i < breaknum; i++)
		{
			checknum[i] = 0xffffffff;
			freenumflug[i] = true;
		}
	}

private :
	bool freenumflug[3];
};

// __gb_code_loging______________________________________
// 速度面を考慮しリスト構造ではなく単純なループ配列を利用
// 重い処理は非リアルタイムに移った際に行う。
typedef struct logset
{
	byte nemonic;
	word pc;
} LOGLIST;

class GbCodeLoging
{
public :
	GbCodeLoging (int size) : size(size), change_point(size-1), top(0)
	{
		loglist = new LOGLIST[size];
		for (int i = 0; i < size; i++)
		{
			loglist[i].nemonic = 0;
			loglist[i].pc = 0;
		}
	}
	virtual ~GbCodeLoging ()
	{
		delete[] loglist;
	}
	inline void resize(int newsize)
	{
		if (newsize == size) return;

		LOGLIST *buf = new LOGLIST[size]; int i;

		logsortcpy(buf);
		delete loglist;
		loglist = new LOGLIST[newsize];

		for (i = 0; i < newsize; i++)
		{	// clear
			loglist[i].nemonic = 0;
			loglist[i].pc = 0;
		}
		for (i = newsize-1; i >= 0 && change_point >= 0; i--, change_point--)
		{
			loglist[i].nemonic = buf[change_point].nemonic;
			loglist[i].pc = buf[change_point].pc;
		}
		size = newsize; change_point = size-1; top = 0;
		delete buf;
	}	
	inline void insert(byte nemonic, word pc) // リアルタイム処理
	{
		if (top < change_point)
		{
			loglist[top].nemonic = nemonic;
			loglist[top].pc = pc;
			++top;
		}
		else
		{
			loglist[top].nemonic = nemonic;
			loglist[top].pc = pc;
			top = 0;
		}
	}
	inline void logget(LOGLIST* log)
	{
		logsortcpy(log);
	}
	inline int logsizeget()
	{
		return size;
	}
private :
	int size;
	int change_point;
	int top;
	LOGLIST *loglist;

	// ログを整列させた物をコピーする。
	inline void logsortcpy(LOGLIST *log)
	{
		int head = top;
		for (int i = 0; i < size; i++)
		{
			log[i].nemonic = loglist[head].nemonic;
			log[i].pc = loglist[head].pc;
			if (head < change_point)
				head++;
			else
				head = 0;
		}
	}
};
