#include "z80cdisasm.h"
#include "string.h"

void SetString(DASM_STRSET *strset, const char *nemonic, const char *op1, const char *op2)
{
	strcpy(strset->nemonic, nemonic);
	strcpy(strset->op1, op1);
	strcpy(strset->op2, op2);
}

unsigned char OpCodeToN0x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x00:
		SetString(strset, "NOP", "", "");
		return ENDDISASM;
	case 0x01:
		SetString(strset, "LD", "BC", "");
		return SECONDOP | TWOBYTESOP;
	case 0x02:
		SetString(strset, "LD", "(BC)", "A");
		return ENDDISASM;
	case 0x03:
		SetString(strset, "INC", "BC", "");
		return ENDDISASM;
	case 0x04:
		SetString(strset, "INC", "B", "");
		return ENDDISASM;
	case 0x05:
		SetString(strset, "DEC", "B", "");
		return ENDDISASM;
	case 0x06:
		SetString(strset, "LD", "B", "");
		return SECONDOP;
	case 0x07:
		SetString(strset, "RLCA", "", "");
		return ENDDISASM;
	case 0x08:
		SetString(strset, "LD", "()", "SP");
		return FIRSTOP | TWOBYTEFOP;
	case 0x09:
		SetString(strset, "ADD", "HL", "BC");
		return ENDDISASM;
	case 0x0a:
		SetString(strset, "LD", "A", "(BC)");
		return ENDDISASM;
	case 0x0b:
		SetString(strset, "DEC", "BC", "");
		return ENDDISASM;
	case 0x0c:
		SetString(strset, "INC", "C", "");
		return ENDDISASM;
	case 0x0d:
		SetString(strset, "DEC", "C", "");
		return ENDDISASM;
	case 0x0e:
		SetString(strset, "LD", "C", "");
		return SECONDOP;
	case 0x0f:
		SetString(strset, "RRCA", "", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToN1x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x10:
		SetString(strset, "STOP", "", "");
		return ENDDISASM;
	case 0x11:
		SetString(strset, "LD", "DE", "");
		return SECONDOP | TWOBYTESOP;
	case 0x12:
		SetString(strset, "LD", "(DE)", "A");
		return ENDDISASM;
	case 0x13:
		SetString(strset, "INC", "DE", "");
		return ENDDISASM;
	case 0x14:
		SetString(strset, "INC", "D", "");
		return ENDDISASM;
	case 0x15:
		SetString(strset, "DEC", "D", "");
		return ENDDISASM;
	case 0x16:
		SetString(strset, "LD", "D", "");
		return SECONDOP;
	case 0x17:
		SetString(strset, "RLA", "", "");
		return ENDDISASM;
	case 0x18:
		SetString(strset, "JR", "signed", "");
		return FIRSTOP;
	case 0x19:
		SetString(strset, "ADD", "HL", "DE");
		return ENDDISASM;
	case 0x1a:
		SetString(strset, "LD", "A", "(DE)");
		return ENDDISASM;
	case 0x1b:
		SetString(strset, "DEC", "DE", "");
		return ENDDISASM;
	case 0x1c:
		SetString(strset, "INC", "E", "");
		return ENDDISASM;
	case 0x1d:
		SetString(strset, "DEC", "E", "");
		return ENDDISASM;
	case 0x1e:
		SetString(strset, "LD", "E", "");
		return SECONDOP;
	case 0x1f:
		SetString(strset, "RRA", "", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToN2x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x20:
		SetString(strset, "JR", "NZ", "signed");
		return SECONDOP;
	case 0x21:
		SetString(strset, "LD", "HL", "");
		return SECONDOP | TWOBYTESOP;
	/* 22は表現方法が数パターンあり */
	/* LD (HL+),LD (HLI),LDI (HD) どれも同じ */
	case 0x22:
		SetString(strset, "LDI", "(HL)", "A");
		return ENDDISASM;
	case 0x23:
		SetString(strset, "INC", "HL", "");
		return ENDDISASM;
	case 0x24:
		SetString(strset, "INC", "H", "");
		return ENDDISASM;
	case 0x25:
		SetString(strset, "DEC", "H", "");
		return ENDDISASM;
	case 0x26:
		SetString(strset, "LD", "H", "");
		return SECONDOP;
	case 0x27:
		SetString(strset, "DAA", "", "");
		return ENDDISASM;
	case 0x28:
		SetString(strset, "JR", "Z", "signed");
		return SECONDOP;
	case 0x29:
		SetString(strset, "ADD", "HL", "HL");
		return ENDDISASM;
	/* 2aは表現方法が数パターンあり */
	/* LD A (HL+),LD A (HLI),LDI A (HL) どれも同じ */
	case 0x2a:
		SetString(strset, "LDI", "A", "(HL)");
		return ENDDISASM;
	case 0x2b:
		SetString(strset, "DEC", "HL", "");
		return ENDDISASM;
	case 0x2c:
		SetString(strset, "INC", "L", "");
		return ENDDISASM;
	case 0x2d:
		SetString(strset, "DEC", "L", "");
		return ENDDISASM;
	case 0x2e:
		SetString(strset, "LD", "L", "");
		return SECONDOP;
	case 0x2f:
		SetString(strset, "CPL", "", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToN3x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x30:
		SetString(strset, "JR", "NC", "signed");
		return SECONDOP;
	case 0x31:
		SetString(strset, "LD", "SP", "");
		return SECONDOP | TWOBYTESOP;
	/* 32も表現方法が数パターンあり */
	/* LD (HL-),LD (HLD),LDD (HD) どれも同じ */
	case 0x32:
		SetString(strset, "LDD", "(HL)", "A");
		return ENDDISASM;
	case 0x33:
		SetString(strset, "INC", "SP", "");
		return ENDDISASM;
	case 0x34:
		SetString(strset, "INC", "(HL)", "");
		return ENDDISASM;
	case 0x35:
		SetString(strset, "DEC", "(HL)", "");
		return ENDDISASM;
	case 0x36:
		SetString(strset, "LD", "(HL)", "");
		return SECONDOP;
	case 0x37:
		SetString(strset, "SCF", "", "");
		return ENDDISASM;
	case 0x38:
		SetString(strset, "JR", "C", "signed");
		return SECONDOP;
	case 0x39:
		SetString(strset, "ADD", "HL", "SP");
		return ENDDISASM;
	/* 3aも表現方法が数パターンあり */
	/* LD A (HL-),LD A (HLD),LDD A (HL) どれも同じ */
	case 0x3a:
		SetString(strset, "LDD", "A", "(HL)");
		return ENDDISASM;
	case 0x3b:
		SetString(strset, "DEC", "SP", "");
		return ENDDISASM;
	case 0x3c:
		SetString(strset, "INC", "A", "");
		return ENDDISASM;
	case 0x3d:
		SetString(strset, "DEC", "A", "");
		return ENDDISASM;
	case 0x3e:
		SetString(strset, "LD", "A", "");
		return SECONDOP;
	case 0x3f:
		SetString(strset, "CCF", "", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToN4x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x40:
		SetString(strset, "LD", "B", "B");
		return ENDDISASM;
	case 0x41:
		SetString(strset, "LD", "B", "C");
		return ENDDISASM;
	case 0x42:
		SetString(strset, "LD", "B", "D");
		return ENDDISASM;
	case 0x43:
		SetString(strset, "LD", "B", "E");
		return ENDDISASM;
	case 0x44:
		SetString(strset, "LD", "B", "H");
		return ENDDISASM;
	case 0x45:
		SetString(strset, "LD", "B", "L");
		return ENDDISASM;
	case 0x46:
		SetString(strset, "LD", "B", "(HL)");
		return ENDDISASM;
	case 0x47:
		SetString(strset, "LD", "B", "A");
		return ENDDISASM;
	case 0x48:
		SetString(strset, "LD", "C", "B");
		return ENDDISASM;
	case 0x49:
		SetString(strset, "LD", "C", "C");
		return ENDDISASM;
	case 0x4a:
		SetString(strset, "LD", "C", "D");
		return ENDDISASM;
	case 0x4b:
		SetString(strset, "LD", "C", "E");
		return ENDDISASM;
	case 0x4c:
		SetString(strset, "LD", "C", "H");
		return ENDDISASM;
	case 0x4d:
		SetString(strset, "LD", "C", "L");
		return ENDDISASM;
	case 0x4e:
		SetString(strset, "LD", "C", "(HL)");
		return ENDDISASM;
	case 0x4f:
		SetString(strset, "LD", "C", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToN5x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x50:
		SetString(strset, "LD", "D", "B");
		return ENDDISASM;
	case 0x51:
		SetString(strset, "LD", "D", "C");
		return ENDDISASM;
	case 0x52:
		SetString(strset, "LD", "D", "D");
		return ENDDISASM;
	case 0x53:
		SetString(strset, "LD", "D", "E");
		return ENDDISASM;
	case 0x54:
		SetString(strset, "LD", "D", "H");
		return ENDDISASM;
	case 0x55:
		SetString(strset, "LD", "D", "L");
		return ENDDISASM;
	case 0x56:
		SetString(strset, "LD", "D", "(HL)");
		return ENDDISASM;
	case 0x57:
		SetString(strset, "LD", "D", "A");
		return ENDDISASM;
	case 0x58:
		SetString(strset, "LD", "E", "B");
		return ENDDISASM;
	case 0x59:
		SetString(strset, "LD", "E", "C");
		return ENDDISASM;
	case 0x5a:
		SetString(strset, "LD", "E", "D");
		return ENDDISASM;
	case 0x5b:
		SetString(strset, "LD", "E", "E");
		return ENDDISASM;
	case 0x5c:
		SetString(strset, "LD", "E", "H");
		return ENDDISASM;
	case 0x5d:
		SetString(strset, "LD", "E", "L");
		return ENDDISASM;
	case 0x5e:
		SetString(strset, "LD", "E", "(HL)");
		return ENDDISASM;
	case 0x5f:
		SetString(strset, "LD", "E", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToN6x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x60:
		SetString(strset, "LD", "H", "B");
		return ENDDISASM;
	case 0x61:
		SetString(strset, "LD", "H", "C");
		return ENDDISASM;
	case 0x62:
		SetString(strset, "LD", "H", "D");
		return ENDDISASM;
	case 0x63:
		SetString(strset, "LD", "H", "E");
		return ENDDISASM;
	case 0x64:
		SetString(strset, "LD", "H", "H");
		return ENDDISASM;
	case 0x65:
		SetString(strset, "LD", "H", "L");
		return ENDDISASM;
	case 0x66:
		SetString(strset, "LD", "H", "(HL)");
		return ENDDISASM;
	case 0x67:
		SetString(strset, "LD", "H", "A");
		return ENDDISASM;
	case 0x68:
		SetString(strset, "LD", "L", "B");
		return ENDDISASM;
	case 0x69:
		SetString(strset, "LD", "L", "C");
		return ENDDISASM;
	case 0x6a:
		SetString(strset, "LD", "L", "D");
		return ENDDISASM;
	case 0x6b:
		SetString(strset, "LD", "L", "E");
		return ENDDISASM;
	case 0x6c:
		SetString(strset, "LD", "L", "H");
		return ENDDISASM;
	case 0x6d:
		SetString(strset, "LD", "L", "L");
		return ENDDISASM;
	case 0x6e:
		SetString(strset, "LD", "L", "(HL)");
		return ENDDISASM;
	case 0x6f:
		SetString(strset, "LD", "L", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToN7x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x70:
		SetString(strset, "LD", "(HL)", "B");
		return ENDDISASM;
	case 0x71:
		SetString(strset, "LD", "(HL)", "C");
		return ENDDISASM;
	case 0x72:
		SetString(strset, "LD", "(HL)", "D");
		return ENDDISASM;
	case 0x73:
		SetString(strset, "LD", "(HL)", "E");
		return ENDDISASM;
	case 0x74:
		SetString(strset, "LD", "(HL)", "H");
		return ENDDISASM;
	case 0x75:
		SetString(strset, "LD", "(HL)", "L");
		return ENDDISASM;
	case 0x76:
		SetString(strset, "HALT", "", "");
		return ENDDISASM;
	case 0x77:
		SetString(strset, "LD", "(HL)", "A");
		return ENDDISASM;
	case 0x78:
		SetString(strset, "LD", "A", "B");
		return ENDDISASM;
	case 0x79:
		SetString(strset, "LD", "A", "C");
		return ENDDISASM;
	case 0x7a:
		SetString(strset, "LD", "A", "D");
		return ENDDISASM;
	case 0x7b:
		SetString(strset, "LD", "A", "E");
		return ENDDISASM;
	case 0x7c:
		SetString(strset, "LD", "A", "H");
		return ENDDISASM;
	case 0x7d:
		SetString(strset, "LD", "A", "L");
		return ENDDISASM;
	case 0x7e:
		SetString(strset, "LD", "A", "(HL)");
		return ENDDISASM;
	case 0x7f:
		SetString(strset, "LD", "A", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToN8x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x80:
		SetString(strset, "ADD", "B", "");
		return ENDDISASM;
	case 0x81:
		SetString(strset, "ADD", "C", "");
		return ENDDISASM;
	case 0x82:
		SetString(strset, "ADD", "D", "");
		return ENDDISASM;
	case 0x83:
		SetString(strset, "ADD", "E", "");
		return ENDDISASM;
	case 0x84:
		SetString(strset, "ADD", "H", "");
		return ENDDISASM;
	case 0x85:
		SetString(strset, "ADD", "L", "");
		return ENDDISASM;
	case 0x86:
		SetString(strset, "ADD", "(HL)", "");
		return ENDDISASM;
	case 0x87:
		SetString(strset, "ADD", "A", "");
		return ENDDISASM;
	case 0x88:
		SetString(strset, "ADC", "B", "");
		return ENDDISASM;
	case 0x89:
		SetString(strset, "ADC", "C", "");
		return ENDDISASM;
	case 0x8a:
		SetString(strset, "ADC", "D", "");
		return ENDDISASM;
	case 0x8b:
		SetString(strset, "ADC", "E", "");
		return ENDDISASM;
	case 0x8c:
		SetString(strset, "ADC", "H", "");
		return ENDDISASM;
	case 0x8d:
		SetString(strset, "ADC", "L", "");
		return ENDDISASM;
	case 0x8e:
		SetString(strset, "ADC", "(HL)", "");
		return ENDDISASM;
	case 0x8f:
		SetString(strset, "ADC", "A", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToN9x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x90:
		SetString(strset, "SUB", "B", "");
		return ENDDISASM;
	case 0x91:
		SetString(strset, "SUB", "C", "");
		return ENDDISASM;
	case 0x92:
		SetString(strset, "SUB", "D", "");
		return ENDDISASM;
	case 0x93:
		SetString(strset, "SUB", "E", "");
		return ENDDISASM;
	case 0x94:
		SetString(strset, "SUB", "H", "");
		return ENDDISASM;
	case 0x95:
		SetString(strset, "SUB", "L", "");
		return ENDDISASM;
	case 0x96:
		SetString(strset, "SUB", "(HL)", "");
		return ENDDISASM;
	case 0x97:
		SetString(strset, "SUB", "A", "");
		return ENDDISASM;
	case 0x98:
		SetString(strset, "SBC", "B", "");
		return ENDDISASM;
	case 0x99:
		SetString(strset, "SBC", "C", "");
		return ENDDISASM;
	case 0x9a:
		SetString(strset, "SBC", "D", "");
		return ENDDISASM;
	case 0x9b:
		SetString(strset, "SBC", "E", "");
		return ENDDISASM;
	case 0x9c:
		SetString(strset, "SBC", "H", "");
		return ENDDISASM;
	case 0x9d:
		SetString(strset, "SBC", "L", "");
		return ENDDISASM;
	case 0x9e:
		SetString(strset, "SBC", "(HL)", "");
		return ENDDISASM;
	case 0x9f:
		SetString(strset, "SBC", "A", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToNax(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0xa0:
		SetString(strset, "AND", "B", "");
		return ENDDISASM;
	case 0xa1:
		SetString(strset, "AND", "C", "");
		return ENDDISASM;
	case 0xa2:
		SetString(strset, "AND", "D", "");
		return ENDDISASM;
	case 0xa3:
		SetString(strset, "AND", "E", "");
		return ENDDISASM;
	case 0xa4:
		SetString(strset, "AND", "H", "");
		return ENDDISASM;
	case 0xa5:
		SetString(strset, "AND", "L", "");
		return ENDDISASM;
	case 0xa6:
		SetString(strset, "AND", "(HL)", "");
		return ENDDISASM;
	case 0xa7:
		SetString(strset, "AND", "A", "");
		return ENDDISASM;
	case 0xa8:
		SetString(strset, "XOR", "B", "");
		return ENDDISASM;
	case 0xa9:
		SetString(strset, "XOR", "C", "");
		return ENDDISASM;
	case 0xaa:
		SetString(strset, "XOR", "D", "");
		return ENDDISASM;
	case 0xab:
		SetString(strset, "XOR", "E", "");
		return ENDDISASM;
	case 0xac:
		SetString(strset, "XOR", "H", "");
		return ENDDISASM;
	case 0xad:
		SetString(strset, "XOR", "L", "");
		return ENDDISASM;
	case 0xae:
		SetString(strset, "XOR", "(HL)", "");
		return ENDDISASM;
	case 0xaf:
		SetString(strset, "XOR", "A", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToNbx(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0xb0:
		SetString(strset, "OR", "B", "");
		return ENDDISASM;
	case 0xb1:
		SetString(strset, "OR", "C", "");
		return ENDDISASM;
	case 0xb2:
		SetString(strset, "OR", "D", "");
		return ENDDISASM;
	case 0xb3:
		SetString(strset, "OR", "E", "");
		return ENDDISASM;
	case 0xb4:
		SetString(strset, "OR", "H", "");
		return ENDDISASM;
	case 0xb5:
		SetString(strset, "OR", "L", "");
		return ENDDISASM;
	case 0xb6:
		SetString(strset, "OR", "(HL)", "");
		return ENDDISASM;
	case 0xb7:
		SetString(strset, "OR", "A", "");
		return ENDDISASM;
	case 0xb8:
		SetString(strset, "CP", "B", "");
		return ENDDISASM;
	case 0xb9:
		SetString(strset, "CP", "C", "");
		return ENDDISASM;
	case 0xba:
		SetString(strset, "CP", "D", "");
		return ENDDISASM;
	case 0xbb:
		SetString(strset, "CP", "E", "");
		return ENDDISASM;
	case 0xbc:
		SetString(strset, "CP", "H", "");
		return ENDDISASM;
	case 0xbd:
		SetString(strset, "CP", "L", "");
		return ENDDISASM;
	case 0xbe:
		SetString(strset, "CP", "(HL)", "");
		return ENDDISASM;
	case 0xbf:
		SetString(strset, "CP", "A", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToNcx(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0xc0:
		SetString(strset, "RET", "NZ", "");
		return ENDDISASM;
	case 0xc1:
		SetString(strset, "POP", "BC", "");
		return ENDDISASM;
	case 0xc2:
		SetString(strset, "JP", "NZ", "");
		return SECONDOP | TWOBYTESOP;
	case 0xc3:
		SetString(strset, "JP", "", "");
		return FIRSTOP | TWOBYTEFOP;
	case 0xc4:
		SetString(strset, "CALL", "NZ", "");
		return SECONDOP | TWOBYTESOP;
	case 0xc5:
		SetString(strset, "PUSH", "BC", "");
		return ENDDISASM;
	case 0xc6:
		SetString(strset, "ADD", "", "");
		return FIRSTOP;
	case 0xc7:
		SetString(strset, "RST", "0", "");
		return ENDDISASM;
	case 0xc8:
		SetString(strset, "RET", "Z", "");
		return ENDDISASM;
	case 0xc9:
		SetString(strset, "RET", "", "");
		return ENDDISASM;
	case 0xca:
		SetString(strset, "JP", "Z", "");
		return SECONDOP | TWOBYTESOP;
	case 0xcb:
		return TWOBYTEOPCODE;
	case 0xcc:
		SetString(strset, "CALL", "Z", "");
		return SECONDOP | TWOBYTESOP;
	case 0xcd:
		SetString(strset, "CALL", "", "");
		return FIRSTOP | TWOBYTEFOP;
	case 0xce:
		SetString(strset, "ADC", "", "");
		return FIRSTOP;
	case 0xcf:
		SetString(strset, "RST", "8", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToNdx(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0xd0:
		SetString(strset, "RET", "NC", "");
		return ENDDISASM;
	case 0xd1:
		SetString(strset, "POP", "DE", "");
		return ENDDISASM;
	case 0xd2:
		SetString(strset, "JP", "NC", "");
		return SECONDOP | TWOBYTESOP;
	case 0xd3:
		SetString(strset, "UNUSED", "", "");
		return ENDDISASM;
	case 0xd4:
		SetString(strset, "CALL", "NC", "");
		return SECONDOP | TWOBYTESOP;
	case 0xd5:
		SetString(strset, "PUSH", "DE", "");
		return ENDDISASM;
	case 0xd6:
		SetString(strset, "SUB", "", "");
		return FIRSTOP;
	case 0xd7:
		SetString(strset, "RST", "16", "");
		return ENDDISASM;
	case 0xd8:
		SetString(strset, "RET", "C", "");
		return ENDDISASM;
	case 0xd9:
		SetString(strset, "RETI", "", "");
		return ENDDISASM;
	case 0xda:
		SetString(strset, "JP", "C", "");
		return SECONDOP | TWOBYTESOP;
	case 0xdb:
		SetString(strset, "UNUSED", "", "");
		return ENDDISASM;
	case 0xdc:
		SetString(strset, "CALL", "C", "");
		return SECONDOP | TWOBYTESOP;
	case 0xdd:
		SetString(strset, "UNUSED", "", "");
		return ENDDISASM;
	case 0xde:
		SetString(strset, "SBC", "", "");
		return FIRSTOP;
	case 0xdf:
		SetString(strset, "RST", "24", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToNex(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	/* E0は "LD ($FF00+x) A" と "LDH (x) A"の2種類の表現がある */
	case 0xe0:
		SetString(strset, "LDH", "()", "A");
		return FIRSTOP;
	case 0xe1:
		SetString(strset, "POP", "HL", "");
		return ENDDISASM;
	/* E0と同様にE2にも同じような2種類の表現がある */
	case 0xe2:
		SetString(strset, "LDH", "(C)", "A");
		return FIRSTOP;
	case 0xe3:
		SetString(strset, "UNUSED", "", "");
		return ENDDISASM;
	case 0xe4:
		SetString(strset, "UNUSED", "", "");
		return ENDDISASM;
	case 0xe5:
		SetString(strset, "PUSH", "HL", "");
		return ENDDISASM;
	case 0xe6:
		SetString(strset, "AND", "", "");
		return FIRSTOP;
	case 0xe7:
		SetString(strset, "RST", "32", "");
		return ENDDISASM;
	case 0xe8:
		SetString(strset, "ADD", "SP", "signed");
		return SECONDOP;
	case 0xe9:
		SetString(strset, "LD", "PC", "HL");
		return ENDDISASM;
	case 0xea:
		SetString(strset, "LD", "()", "A");
		return FIRSTOP | TWOBYTEFOP;
	case 0xeb:
		SetString(strset, "UNUSED", "", "");
		return ENDDISASM;
	case 0xec:
		SetString(strset, "UNUSED", "", "");
		return ENDDISASM;
	case 0xed:
		SetString(strset, "NOP", "", "");
		return ENDDISASM;
	case 0xee:
		SetString(strset, "XOR", "", "");
		return FIRSTOP;
	case 0xef:
		SetString(strset, "RST", "40", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToNfx(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	/* F0は"LDH A (x)"と"LD A (&FF00+x)"の2種類の表現がある */
	case 0xf0:
		SetString(strset, "LDH", "A", "()");
		return SECONDOP;
	case 0xf1:
		SetString(strset, "POP", "AF", "");
		return ENDDISASM;
	/* F0と同じようにF2にも2種類の表現がある */
	case 0xf2:
		SetString(strset, "LDH", "A", "(C)");
		return ENDDISASM;
	case 0xf3:
		SetString(strset, "DI", "", "");
		return ENDDISASM;
	case 0xf4:
		SetString(strset, "UNUSED", "", "");
		return ENDDISASM;
	case 0xf5:
		SetString(strset, "PUSH", "AF", "");
		return ENDDISASM;
	case 0xf6:
		SetString(strset, "OR", "", "");
		return FIRSTOP;
	case 0xf7:
		SetString(strset, "RST", "48", "");
		return ENDDISASM;
	case 0xf8:
		SetString(strset, "LD", "HL", "SP+signed");
		return SECONDOP;
	case 0xf9:
		SetString(strset, "LD", "SP", "HL");
		return ENDDISASM;
	case 0xfa:
		SetString(strset, "LD", "A", "()");
		return SECONDOP | TWOBYTESOP;
	case 0xfb:
		SetString(strset, "EI", "", "");
		return ENDDISASM;
	case 0xfc:
		SetString(strset, "UNUSED", "", "");
		return ENDDISASM;
	case 0xfd:
		SetString(strset, "UNUSED", "", "");
		return ENDDISASM;
	case 0xfe:
		SetString(strset, "CP", "", "");
		return FIRSTOP;
	case 0xff:
		SetString(strset, "RST", "56", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char OpCodeToNemonic(DASM_STRSET *strset, unsigned char opcode)
{
	unsigned char status;

	if((opcode < 0x10) && (opcode >= 0x00))
		status = OpCodeToN0x(strset, opcode);
	else if((opcode < 0x20) && (opcode >= 0x10))
		status = OpCodeToN1x(strset, opcode);
	else if((opcode < 0x30) && (opcode >= 0x20))
		status = OpCodeToN2x(strset, opcode);
	else if((opcode < 0x40) && (opcode >= 0x30))
		status = OpCodeToN3x(strset, opcode);
	else if((opcode < 0x50) && (opcode >= 0x40))
		status = OpCodeToN4x(strset, opcode);
	else if((opcode < 0x60) && (opcode >= 0x50))
		status = OpCodeToN5x(strset, opcode);
	else if((opcode < 0x70) && (opcode >= 0x60))
		status = OpCodeToN6x(strset, opcode);
	else if((opcode < 0x80) && (opcode >= 0x70))
		status = OpCodeToN7x(strset, opcode);
	else if((opcode < 0x90) && (opcode >= 0x80))
		status = OpCodeToN8x(strset, opcode);
	else if((opcode < 0xa0) && (opcode >= 0x90))
		status = OpCodeToN9x(strset, opcode);
	else if((opcode < 0xb0) && (opcode >= 0xa0))
		status = OpCodeToNax(strset, opcode);
	else if((opcode < 0xc0) && (opcode >= 0xb0))
		status = OpCodeToNbx(strset, opcode);
	else if((opcode < 0xd0) && (opcode >= 0xc0))
		status = OpCodeToNcx(strset, opcode);
	else if((opcode < 0xe0) && (opcode >= 0xd0))
		status = OpCodeToNdx(strset, opcode);
	else if((opcode < 0xf0) && (opcode >= 0xe0))
		status = OpCodeToNex(strset, opcode);
	else if((opcode <= 0xff) && (opcode >= 0xf0))
		status = OpCodeToNfx(strset, opcode);
	else status = 0;

	return status;
}
