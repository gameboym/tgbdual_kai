

/*        statusèÛë‘Çï\Ç∑íËêî         */
/* '|'ââéZéqÇégÇ¢ï°êîéwíËÇ∑ÇÈÇ±Ç∆Ç‡â¬ */

#define STARTDISASM		1
#define TWOBYTEOPCODE	2
#define FIRSTOP			4
#define TWOBYTEFOP		8
#define SECONDOP		16
#define TWOBYTESOP		32
#define ENDDISASM		128
/*_______________________________________*/

#define STRSIZE			20
#define ANALYSISSIZE	255

typedef struct dasm_strset
{
	char UsedOpCode[STRSIZE];	/* âêÕÇ…égópÇµÇΩopcodeÇäiî[ */
	char nemonic[STRSIZE];		/* disasmÇµÇΩopcodeÇäiî[ */
	char op1[STRSIZE];			/* op1äiî[óp */
	char op2[STRSIZE];			/* op2äiî[óp */
//	char info[STRSIZE];
} DASM_STRSET;

bool z80cdisasm(DASM_STRSET *s, unsigned char opcode, bool reset = false);
void StrSetToStr(char *string, const DASM_STRSET *strset);

#ifdef Z80CDISASM
	void ResetDisAsm(DASM_STRSET *strset, unsigned char *status);
	void StatusCheckAndGo(DASM_STRSET *strset, unsigned char *status, unsigned char opcode);
	void FirstProcessing(DASM_STRSET *strset, unsigned char *status, unsigned char opcode);
	void TwoByteOpCodeAnalysis(DASM_STRSET *strset, unsigned char *status, unsigned char opcode);
	void FirstOperandAnalysis(DASM_STRSET *strset, unsigned char *status, unsigned char opcode);
	void TwoByteFOpAnalysis(DASM_STRSET *strset, unsigned char *status, unsigned char opcode);
	void SecondOperandAnalys(DASM_STRSET *strset, unsigned char *status, unsigned char opcode);
	void TwoByteSOpAnalysis(DASM_STRSET *strset, unsigned char *status, unsigned char opcode);
	void EndProcessing(DASM_STRSET *s, DASM_STRSET *strset, unsigned char *status);
	void InitializeStrSet(DASM_STRSET *strset);
	void PushOpCode(DASM_STRSET *strset, unsigned char opcode);
	void SetOperand(char *operand, unsigned char opcode);
	void SetTwoByteOperand(char *operand, unsigned char opcode);
	void EndCheck(unsigned char *status, unsigned char checkstatus);

	unsigned char OpCodeToNemonic(DASM_STRSET *strset, unsigned char opcode);
	unsigned char TwoByteOpCoToN(DASM_STRSET *strset, unsigned char opcode);
#endif

#undef Z80CDISASM