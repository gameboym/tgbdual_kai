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

extern gb *g_gb[2];

// ____codesearch_________________________
// チートコードサーチ用のクラス
// 前回のリストを保持して指定条件との比較を行う

#define CODESEARCH_STYPE_EQU 0
#define CODESEARCH_STYPE_NEQ 1
#define CODESEARCH_STYPE_GR  2
#define CODESEARCH_STYPE_LE  3
#define CODESEARCH_STYPE_EQG 4
#define CODESEARCH_STYPE_EQL 5

#define CODESEARCH_NTYPE_UNSIGNED 0
#define CODESEARCH_NTYPE_SIGNED 1

#define CODESEARCH_NSIZE_BYTE  0
#define CODESEARCH_NSIZE_WORD  1
#define CODESEARCH_NSIZE_FWORD 2
#define CODESEARCH_NSIZE_DWORD 3

#define CODESEARCH_TARGET_OLD 0
#define CODESEARCH_TARGET_NUM 1

typedef struct memlist
{
	word adr;
	dword num;
	int bank;	// rambankは1～:srambankは10～
} MEMLIST;

class CodeSearch
{
public :
	CodeSearch ()
	{
		stype = CODESEARCH_STYPE_EQU;
		ntype = CODESEARCH_NTYPE_UNSIGNED;
		nsize = CODESEARCH_NSIZE_BYTE;
		target = CODESEARCH_TARGET_OLD;
		rambankf = 0;
		srambankf = 0;
		searchnum = 0;
	}
	virtual ~CodeSearch ()
	{
	}
	int searchstart()
	{
		// 初期化
		mlist.clear();

		for (int i = 0; i < 0xFFFF; i++)
		{
			// 下の条件の時に実行しそれ以外はcontinue
			//	(i >= 0xA000 && i < 0xC000) || (i >= 0xC000 && i < 0xD000) || (i >= 0xD000 && i < 0xE000) || (i >= 0xFF80)
			if ( (i < 0xA000) || (i >= 0xE000 && i < 0xFF80) )
					continue;

			std::list<int> datalist;
			std::list<int>::iterator ite;
			MEMLIST buf;
			dword num;

			if ((datalist.size() == 0) && (i < 0xFFFF-3))
			{
				datalist.push_front( g_gb[0]->get_cpu()->read(i) );
				datalist.push_front( g_gb[0]->get_cpu()->read(i+1) );
				datalist.push_front( g_gb[0]->get_cpu()->read(i+2) );
				datalist.push_front( g_gb[0]->get_cpu()->read(i+3) );
			}
			else
			{
				datalist.pop_back();
				if (i < 0xFFFF-3)
					datalist.push_front(g_gb[0]->get_cpu()->read(i+3));
			}
			
			num = 0;
			for (ite = datalist.begin(); ite != datalist.end(); ite++)
				num = (num << 8) + (*ite & 0xff);
				
			buf.adr = i;
			buf.num = num;
			buf.bank = 0;
			mlist.push_back(buf);
		}

		// RAMバンクの登録
		if (rambankf)
		{
			for (int i = 1; i <= 7; i++)
				searchstartrambank(i);
		}
		if (srambankf)
		{
			int sramsize = g_gb[0]->get_rom()->get_sram_size() / 0x2000;
			if (sramsize > 1)
			{
				for (int i = 0; i < sramsize; i++)
					searchstartsrambank(i);
			}
		}

		return count();
	}
	int search()
	{
		if (count() <= 0)
			return 0;

		dword newnum;
		std::list<MEMLIST>::iterator ite;

		if (target == CODESEARCH_TARGET_OLD) // 前回値と比較
		{
			for (ite = mlist.begin(); ite != mlist.end();)
			{
				if (ite->bank == 0)
					newnum = getdword(ite->adr);
				else if (ite->bank < 10)
					newnum = getramdword(ite->adr, ite->bank);
				else
					newnum = getsramdword(ite->adr, ite->bank);

				if ( compare(changesize(ite->num), changesize(newnum)) )
				{
					ite->num = newnum;
				}
				else
				{
					ite = mlist.erase(ite);
					continue;
				}
				ite++;
			}
		}
		else if (target == CODESEARCH_TARGET_NUM) // 指定値と比較
		{
			for (ite = mlist.begin(); ite != mlist.end();)
			{
				if (ite->bank == 0)
					newnum = getdword(ite->adr);
				else if (ite->bank < 10)
					newnum = getramdword(ite->adr, ite->bank);
				else
					newnum = getsramdword(ite->adr, ite->bank);

				if ( compare(searchnum, changesize(newnum)) )
				{
					ite->num = newnum;
				}
				else
				{
					ite = mlist.erase(ite);
					continue;
				}
				ite++;
			}
		}
		else
			return 0;

		return count();
	}
	int count()
	{
		return mlist.size();
	}
	int getstype() { return stype; }
	int getntype() { return ntype; }
	int getnsize() { return nsize; }
	int gettarget() { return target; }
	int getrambankf() { return rambankf; }
	int getsrambankf() { return srambankf; }
	MEMLIST getmlist(int index)
	{
		std::list<MEMLIST>::iterator ite = mlist.begin();
		for (; index > 0; index--)
			ite++;
		return *ite;
	}
	word getmlistadr(int index)
	{
		std::list<MEMLIST>::iterator ite = mlist.begin();
		for (; index > 0; index--)
			ite++;
		return ite->adr;
	}
	dword getmlistnum(int index)
	{
		std::list<MEMLIST>::iterator ite = mlist.begin();
		for (; index > 0; index--)
			ite++;
		return ite->num;
	}
	int getmlistbank(int index)
	{
		std::list<MEMLIST>::iterator ite = mlist.begin();
		for (; index > 0; index--)
			ite++;
		return ite->bank;
	}
	void setstype(int type)
	{
		if ( (type >= CODESEARCH_STYPE_EQU) && (type <= CODESEARCH_STYPE_EQL) )
			stype = type;
	}
	void setntype(int type)
	{
		if ( (type >= CODESEARCH_NTYPE_UNSIGNED) && (type <= CODESEARCH_NTYPE_SIGNED) )
			ntype = type;
	}
	void setnsize(int type)
	{
		if ( (type >= CODESEARCH_NSIZE_BYTE) && (type <= CODESEARCH_NSIZE_DWORD) )
			nsize = type;
		searchnum = 0;
	}
	void settarget(int type)
	{
		if ( (type >= CODESEARCH_TARGET_OLD) && (type <= CODESEARCH_TARGET_NUM) )
			target = type;
	}
	int setsearchnum(dword num) // nsizeを設定してから代入すること
	{
		if (nsize == CODESEARCH_NSIZE_BYTE)
			num = num & 0xff;
		else if (nsize == CODESEARCH_NSIZE_WORD)
			num = num & 0xffff;
		else if (nsize == CODESEARCH_NSIZE_FWORD)
			num = num & 0xffffff;
		else if (nsize == CODESEARCH_NSIZE_DWORD)
			num = num & 0xffffffff;

		searchnum = num;
		return 0;
	}
	void setrambankf(int flag)
	{
		rambankf = flag ? 1:0;
	}
	void setsrambankf(int flag)
	{
		srambankf = flag ? 1:0;
	}
	dword getdword(word adr)
	{
		dword num = 0;
		for(int i = 0; (i < 4) && (adr + i < 0xffff); i++)
			num = num + ((g_gb[0]->get_cpu()->read(adr+i) & 0xff) << i*8);
		return num;
	}
	dword getramdword(word adr, int bank)
	{
		dword num = 0;
		adr = adr - 0xd000;
		bank = bank * 0x1000;

		for(int i = 0; (i < 4) && (adr + i <= 0xfff); i++)
			num = num + ((g_gb[0]->get_cpu()->get_ram()[adr+i+bank] & 0xff) << i*8);
		return num;
	}
	dword getsramdword(word adr, int bank)
	{
		dword num = 0;
		adr = adr - 0xa000;
		bank = (bank-10) * 0x2000;

		if (bank < 0)
			return -1;

		for(int i = 0; (i < 4) && (adr + i <= 0x1fff); i++)
			num = num + ((g_gb[0]->get_rom()->get_sram()[adr+i+bank] & 0xff) << i*8);
		return num;
	}
private :
	int stype;			// サーチ方法
	int ntype;			// 符号付き、符号無し
	int nsize;			// 数値のサイズ
	int	target;			// 比較対象(直接or前回の値)
	int rambankf;       // ramバンクを対象とするフラグ
	int srambankf;      // sramバンクを対象とするフラグ
	dword searchnum;	// 直接指定用の比較数値
	std::list<MEMLIST> mlist;

	int checksearchnum()
	{
	}
	long changesigned(dword num)
	{
		switch(nsize)
		{
		case CODESEARCH_NSIZE_BYTE:
			return ((signed)num << 24) >> 24;
		case CODESEARCH_NSIZE_WORD:
			return ((signed)num << 16) >> 16;
		case CODESEARCH_NSIZE_FWORD:
			return ((signed)num << 8) >> 8;
		case CODESEARCH_NSIZE_DWORD:
			return (signed)num;
		default:
			break;
		}
		return 0;
	}
	dword changesize(dword num)
	{
		switch(nsize)
		{
		case CODESEARCH_NSIZE_BYTE:
			return num & 0xff;
		case CODESEARCH_NSIZE_WORD:
			return num & 0xffff;
		case CODESEARCH_NSIZE_FWORD:
			return num & 0xffffff;
		case CODESEARCH_NSIZE_DWORD:
			return num & 0xffffffff;
		default:
			break;
		}
		return num;
	}
	int compare(dword num1, dword num2)
	{
		switch(stype)
		{
		case CODESEARCH_STYPE_EQU:
			if (ntype == CODESEARCH_NTYPE_SIGNED)
			{
				if (changesigned(num1) == changesigned(num2))
					return 1;
			}
			else 
			{
				if (num1 == num2)
					return 1;
			}
			break;
		case CODESEARCH_STYPE_NEQ:
			if (ntype == CODESEARCH_NTYPE_SIGNED)
			{
				if (changesigned(num1) != changesigned(num2))
					return 1;
			}
			else
			{
				if (num1 != num2)
					return 1;
			}
			break;
		case CODESEARCH_STYPE_GR:
			if (ntype == CODESEARCH_NTYPE_SIGNED)
			{
				if (changesigned(num1) < changesigned(num2))
					return 1;
			}
			else
			{
				if (num1 < num2)
					return 1;
			}
			break;
		case CODESEARCH_STYPE_LE:
			if (ntype == CODESEARCH_NTYPE_SIGNED)
			{
				if (changesigned(num1) > changesigned(num2))
					return 1;
			}
			else
			{
				if (num1 > num2)
					return 1;
			}
			break;
		case CODESEARCH_STYPE_EQG:
			if (ntype == CODESEARCH_NTYPE_SIGNED)
			{
				if (changesigned(num1) <= changesigned(num2))
					return 1;
			}
			else
			{
				if (num1 <= num2)
					return 1;
			}
			break;
		case CODESEARCH_STYPE_EQL:
			if (ntype == CODESEARCH_NTYPE_SIGNED)
			{
				if (changesigned(num1) >= changesigned(num2))
					return 1;
			}
			else
			{
				if (num1 >= num2)
					return 1;
			}
			break;
		default:
			break;
		}
		return 0;
	}
	void searchstartrambank(int bank)
	{
		int bi = (bank & 0x0f) << 12;
		for (int i = 0; i <= 0x0FFF; i++)
		{
			std::list<int> datalist;
			std::list<int>::iterator ite;
			MEMLIST buf;
			dword num;

			if ((datalist.size() == 0) && (i <= 0x0FFF-3))
			{
				datalist.push_front( g_gb[0]->get_cpu()->get_ram()[bi+i] );
				datalist.push_front( g_gb[0]->get_cpu()->get_ram()[bi+i+1] );
				datalist.push_front( g_gb[0]->get_cpu()->get_ram()[bi+i+2] );
				datalist.push_front( g_gb[0]->get_cpu()->get_ram()[bi+i+3] );
			}
			else
			{
				datalist.pop_back();
				if (i <= 0x0FFF-3)
					datalist.push_front( g_gb[0]->get_cpu()->get_ram()[bi+i+3] );
			}
			
			num = 0;
			for (ite = datalist.begin(); ite != datalist.end(); ite++)
				num = (num << 8) + (*ite & 0xff);
				
			buf.adr = 0xd000+i;
			buf.num = num;
			buf.bank = bank;
			mlist.push_back(buf);
		}
	}
	void searchstartsrambank(int bank)
	{
		int bi = bank * 0x2000;
		for (int i = 0; i <= 0x1FFF; i++)
		{
			std::list<int> datalist;
			std::list<int>::iterator ite;
			MEMLIST buf;
			dword num;

			if ((datalist.size() == 0) && (i <= 0x1FFF-3))
			{
				datalist.push_front( g_gb[0]->get_rom()->get_sram()[bi+i] );
				datalist.push_front( g_gb[0]->get_rom()->get_sram()[bi+i+1] );
				datalist.push_front( g_gb[0]->get_rom()->get_sram()[bi+i+2] );
				datalist.push_front( g_gb[0]->get_rom()->get_sram()[bi+i+3] );
			}
			else
			{
				datalist.pop_back();
				if (i <= 0x1FFF-3)
					datalist.push_front( g_gb[0]->get_rom()->get_sram()[bi+i+3] );
			}
			
			num = 0;
			for (ite = datalist.begin(); ite != datalist.end(); ite++)
				num = (num << 8) + (*ite & 0xff);
				
			buf.adr = 0xa000+i;
			buf.num = num;
			buf.bank = bank + 10;
			mlist.push_back(buf);
		}
	}
};
