/******************************************************************
**                                                               **
**                                                               **
**              Z80-custom (nintendo game boy)                   **
**                      disassembler                             **
**                                                               **
**                                                               **
**     LAST UP DATE:  2006/09/06                                 **
**                    2006/05/15                                 **
**                                                               **
******************************************************************/

/* 使用後は必ずBOOL値でTRUEが返ってくることを確認すること。	*/


/* static unsigned char status__________
** 現在の状態を表すステータスフラグ
** 8bitあるbitにそれぞれ役割を与えてある
**
** 1bit:初期状態を表すフラグ 
**     opcodeを解析しdisasmする
** 2bit:2byte opcode解析フラグ
** 3bit:op1解析フラグ
** 4bit:op1,2byte解析フラグ
** 5bit:op2解析フラグ
** 6bit:op2,2byte解析フラグ
** 7bit:NOT
** 8bit:完了フラグ_____________________*/


#define Z80CDISASM

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "z80cdisasm.h"

/*______________________________________________________**
** z80cdisasm: "z80 custom"dis asemmbler				**
** 引数:DASM_STRSET *s: 解析結果の格納先			    **
**     :unsigned char opcode: オペコード（バイナリ値）  **
**     :bool reset: resetフラグ。必要に応じてtrueを渡す **
** 戻り値:false : opcodeの追加読み込みが必要            **
**       :true  : 解析完了                              **
**__________________________________________________________________________________**
** 静的変数のため初期化処理が必要だが、こちら側での調整は行わない。					**
**__________________________________________________________________________________*/
bool z80cdisasm(DASM_STRSET *s, unsigned char opcode, bool reset)
{
	static unsigned char status = STARTDISASM;
	static DASM_STRSET strset;

	if (reset)
	{
		ResetDisAsm(&strset, &status);
		return true;
	}
	StatusCheckAndGo(&strset, &status, opcode);

	if (status & ENDDISASM)
	{
		EndProcessing(s, &strset, &status);
		return true;
	}
	return false;
}

void StrSetToStr(char *string, const DASM_STRSET *strset)
{
	sprintf(string, "$%s\t%s\t%s\t%s", strset->UsedOpCode,
		strset->nemonic, strset->op1, strset->op2);
}

static void ResetDisAsm(DASM_STRSET *strset, unsigned char *status)
{
		*status = STARTDISASM;
		InitializeStrSet(strset);
}

static void StatusCheckAndGo(DASM_STRSET *strset, unsigned char *status, unsigned char opcode)
{
	if (*status & STARTDISASM)
		FirstProcessing(strset, status, opcode);
	else if (*status & TWOBYTEOPCODE)
		TwoByteOpCodeAnalysis(strset, status, opcode);
	else if (*status & FIRSTOP)
		FirstOperandAnalysis(strset, status, opcode);
	else if (*status & TWOBYTEFOP)
		TwoByteFOpAnalysis(strset, status, opcode);
	else if (*status & SECONDOP)
		SecondOperandAnalys(strset, status, opcode);
	else if (*status & TWOBYTESOP)
		TwoByteSOpAnalysis(strset, status, opcode);
	else
		exit(-1);

	PushOpCode(strset, opcode);
}

static void FirstProcessing(DASM_STRSET *strset, unsigned char *status, unsigned char opcode)
{
	InitializeStrSet(strset);
	*status = OpCodeToNemonic(strset, opcode);
}

static void TwoByteOpCodeAnalysis(DASM_STRSET *strset, unsigned char *status, unsigned char opcode)
{
	*status = TwoByteOpCoToN(strset, opcode);
}

static void FirstOperandAnalysis(DASM_STRSET *strset, unsigned char *status, unsigned char opcode)
{
	SetOperand(strset->op1, opcode);
	EndCheck(status, FIRSTOP);
}

static void TwoByteFOpAnalysis(DASM_STRSET *strset, unsigned char *status, unsigned char opcode)
{
	SetTwoByteOperand(strset->op1, opcode);
	EndCheck(status, TWOBYTEFOP);
}

static void SecondOperandAnalys(DASM_STRSET *strset, unsigned char *status, unsigned char opcode)
{
	SetOperand(strset->op2, opcode);
	EndCheck(status, SECONDOP);
}

static void TwoByteSOpAnalysis(DASM_STRSET *strset, unsigned char *status, unsigned char opcode)
{
	SetTwoByteOperand(strset->op2, opcode);
	EndCheck(status, TWOBYTESOP);
}

static void EndProcessing(DASM_STRSET *s, DASM_STRSET *strset, unsigned char *status)
{
	memcpy(s, strset, sizeof(DASM_STRSET));
	ResetDisAsm(strset, status);
}

static void InitializeStrSet(DASM_STRSET *strset)
{
	int i;
	for (i = 0; i < STRSIZE; i++)
	{
		strset->nemonic[i] = '\0';
		strset->UsedOpCode[i] = '\0';
		strset->op1[i] = '\0';
		strset->op2[i] = '\0';
	}
}

static void PushOpCode(DASM_STRSET *strset, unsigned char opcode)
{
	char buf[STRSIZE];

	sprintf(buf, "%02X", opcode);
	strcat(strset->UsedOpCode, buf);
}

static void SetOperand(char *operand, unsigned char opcode)
{
	if (0 == strcmp(operand, "SP+signed"))
		sprintf(operand, "SP%+02d", ((signed char)opcode));
	else if (0 == strcmp(operand, "signed"))
		sprintf(operand, "$%+02d", ((signed char)opcode));
	else if (0 == strcmp(operand, "()"))
		sprintf(operand, "(%02X)", opcode);
	else
		sprintf(operand, "$%02X", opcode);
}

static void SetTwoByteOperand(char *operand, unsigned char opcode)
{
	char buf[STRSIZE];

	if (operand[0] == '(')
		sprintf(buf, "(%02X%s", opcode, operand+1); // (を飛ばすためoperand+1となる。)はそのまま利用
	else
		sprintf(buf, "$%02X%s", opcode, operand+1); // $マークを飛ばすためoperand+1となる。
	strcpy(operand, buf);
}

static void EndCheck(unsigned char *status, unsigned char checkstatus)
{
	*status -= checkstatus;
	if (!(*status))
		*status = ENDDISASM;
}

