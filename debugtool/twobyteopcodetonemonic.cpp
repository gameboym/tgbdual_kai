#include "z80cdisasm.h"
#include "string.h"

void SetString(DASM_STRSET *strset, const char *nemonic, const char *op1, const char *op2);

unsigned char TBOpCoToN0x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x00:
		SetString(strset, "RLC", "B", "");
		return ENDDISASM;
	case 0x01:
		SetString(strset, "RLC", "C", "");
		return ENDDISASM;
	case 0x02:
		SetString(strset, "RLC", "D", "");
		return ENDDISASM;
	case 0x03:
		SetString(strset, "RLC", "E", "");
		return ENDDISASM;
	case 0x04:
		SetString(strset, "RLC", "H", "");
		return ENDDISASM;
	case 0x05:
		SetString(strset, "RLC", "L", "");
		return ENDDISASM;
	case 0x06:
		SetString(strset, "RLC", "(HL)", "");
		return ENDDISASM;
	case 0x07:
		SetString(strset, "RLC", "A", "");
		return ENDDISASM;
	case 0x08:
		SetString(strset, "RRC", "B", "");
		return ENDDISASM;
	case 0x09:
		SetString(strset, "RRC", "C", "");
		return ENDDISASM;
	case 0x0a:
		SetString(strset, "RRC", "D", "");
		return ENDDISASM;
	case 0x0b:
		SetString(strset, "RRC", "E", "");
		return ENDDISASM;
	case 0x0c:
		SetString(strset, "RRC", "H", "");
		return ENDDISASM;
	case 0x0d:
		SetString(strset, "RRC", "L", "");
		return ENDDISASM;
	case 0x0e:
		SetString(strset, "RRC", "(HL)", "");
		return ENDDISASM;
	case 0x0f:
		SetString(strset, "RRC", "A", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToN1x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x10:
		SetString(strset, "RL", "B", "");
		return ENDDISASM;
	case 0x11:
		SetString(strset, "RL", "C", "");
		return ENDDISASM;
	case 0x12:
		SetString(strset, "RL", "D", "");
		return ENDDISASM;
	case 0x13:
		SetString(strset, "RL", "E", "");
		return ENDDISASM;
	case 0x14:
		SetString(strset, "RL", "H", "");
		return ENDDISASM;
	case 0x15:
		SetString(strset, "RL", "L", "");
		return ENDDISASM;
	case 0x16:
		SetString(strset, "RL", "(HL)", "");
		return ENDDISASM;
	case 0x17:
		SetString(strset, "RL", "A", "");
		return ENDDISASM;
	case 0x18:
		SetString(strset, "RR", "B", "");
		return ENDDISASM;
	case 0x19:
		SetString(strset, "RR", "C", "");
		return ENDDISASM;
	case 0x1a:
		SetString(strset, "RR", "D", "");
		return ENDDISASM;
	case 0x1b:
		SetString(strset, "RR", "E", "");
		return ENDDISASM;
	case 0x1c:
		SetString(strset, "RR", "H", "");
		return ENDDISASM;
	case 0x1d:
		SetString(strset, "RR", "L", "");
		return ENDDISASM;
	case 0x1e:
		SetString(strset, "RR", "(HL)", "");
		return ENDDISASM;
	case 0x1f:
		SetString(strset, "RR", "A", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToN2x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x20:
		SetString(strset, "SLA", "B", "");
		return ENDDISASM;
	case 0x21:
		SetString(strset, "SLA", "C", "");
		return ENDDISASM;
	case 0x22:
		SetString(strset, "SLA", "D", "");
		return ENDDISASM;
	case 0x23:
		SetString(strset, "SLA", "E", "");
		return ENDDISASM;
	case 0x24:
		SetString(strset, "SLA", "H", "");
		return ENDDISASM;
	case 0x25:
		SetString(strset, "SLA", "L", "");
		return ENDDISASM;
	case 0x26:
		SetString(strset, "SLA", "(HL)", "");
		return ENDDISASM;
	case 0x27:
		SetString(strset, "SLA", "A", "");
		return ENDDISASM;
	case 0x28:
		SetString(strset, "SRA", "B", "");
		return ENDDISASM;
	case 0x29:
		SetString(strset, "SRA", "C", "");
		return ENDDISASM;
	case 0x2a:
		SetString(strset, "SRA", "D", "");
		return ENDDISASM;
	case 0x2b:
		SetString(strset, "SRA", "E", "");
		return ENDDISASM;
	case 0x2c:
		SetString(strset, "SRA", "H", "");
		return ENDDISASM;
	case 0x2d:
		SetString(strset, "SRA", "L", "");
		return ENDDISASM;
	case 0x2e:
		SetString(strset, "SRA", "(HL)", "");
		return ENDDISASM;
	case 0x2f:
		SetString(strset, "SRA", "A", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToN3x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x30:
		SetString(strset, "SWAP", "B", "");
		return ENDDISASM;
	case 0x31:
		SetString(strset, "SWAP", "C", "");
		return ENDDISASM;
	case 0x32:
		SetString(strset, "SWAP", "D", "");
		return ENDDISASM;
	case 0x33:
		SetString(strset, "SWAP", "E", "");
		return ENDDISASM;
	case 0x34:
		SetString(strset, "SWAP", "H", "");
		return ENDDISASM;
	case 0x35:
		SetString(strset, "SWAP", "L", "");
		return ENDDISASM;
	case 0x36:
		SetString(strset, "SWAP", "(HL)", "");
		return ENDDISASM;
	case 0x37:
		SetString(strset, "SWAP", "A", "");
		return ENDDISASM;
	case 0x38:
		SetString(strset, "SRL", "B", "");
		return ENDDISASM;
	case 0x39:
		SetString(strset, "SRL", "C", "");
		return ENDDISASM;
	case 0x3a:
		SetString(strset, "SRL", "D", "");
		return ENDDISASM;
	case 0x3b:
		SetString(strset, "SRL", "E", "");
		return ENDDISASM;
	case 0x3c:
		SetString(strset, "SRL", "H", "");
		return ENDDISASM;
	case 0x3d:
		SetString(strset, "SRL", "L", "");
		return ENDDISASM;
	case 0x3e:
		SetString(strset, "SRL", "(HL)", "");
		return ENDDISASM;
	case 0x3f:
		SetString(strset, "SRL", "A", "");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToN4x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x40:
		SetString(strset, "BIT", "0", "B");
		return ENDDISASM;
	case 0x41:
		SetString(strset, "BIT", "0", "C");
		return ENDDISASM;
	case 0x42:
		SetString(strset, "BIT", "0", "D");
		return ENDDISASM;
	case 0x43:
		SetString(strset, "BIT", "0", "E");
		return ENDDISASM;
	case 0x44:
		SetString(strset, "BIT", "0", "H");
		return ENDDISASM;
	case 0x45:
		SetString(strset, "BIT", "0", "L");
		return ENDDISASM;
	case 0x46:
		SetString(strset, "BIT", "0", "(HL)");
		return ENDDISASM;
	case 0x47:
		SetString(strset, "BIT", "0", "A");
		return ENDDISASM;
	case 0x48:
		SetString(strset, "BIT", "1", "B");
		return ENDDISASM;
	case 0x49:
		SetString(strset, "BIT", "1", "C");
		return ENDDISASM;
	case 0x4a:
		SetString(strset, "BIT", "1", "D");
		return ENDDISASM;
	case 0x4b:
		SetString(strset, "BIT", "1", "E");
		return ENDDISASM;
	case 0x4c:
		SetString(strset, "BIT", "1", "H");
		return ENDDISASM;
	case 0x4d:
		SetString(strset, "BIT", "1", "L");
		return ENDDISASM;
	case 0x4e:
		SetString(strset, "BIT", "1", "(HL)");
		return ENDDISASM;
	case 0x4f:
		SetString(strset, "BIT", "1", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToN5x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x50:
		SetString(strset, "BIT", "2", "B");
		return ENDDISASM;
	case 0x51:
		SetString(strset, "BIT", "2", "C");
		return ENDDISASM;
	case 0x52:
		SetString(strset, "BIT", "2", "D");
		return ENDDISASM;
	case 0x53:
		SetString(strset, "BIT", "2", "E");
		return ENDDISASM;
	case 0x54:
		SetString(strset, "BIT", "2", "H");
		return ENDDISASM;
	case 0x55:
		SetString(strset, "BIT", "2", "L");
		return ENDDISASM;
	case 0x56:
		SetString(strset, "BIT", "2", "(HL)");
		return ENDDISASM;
	case 0x57:
		SetString(strset, "BIT", "2", "A");
		return ENDDISASM;
	case 0x58:
		SetString(strset, "BIT", "3", "B");
		return ENDDISASM;
	case 0x59:
		SetString(strset, "BIT", "3", "C");
		return ENDDISASM;
	case 0x5a:
		SetString(strset, "BIT", "3", "D");
		return ENDDISASM;
	case 0x5b3:
		SetString(strset, "BIT", "3", "E");
		return ENDDISASM;
	case 0x5c:
		SetString(strset, "BIT", "3", "H");
		return ENDDISASM;
	case 0x5d:
		SetString(strset, "BIT", "3", "L");
		return ENDDISASM;
	case 0x5e:
		SetString(strset, "BIT", "3", "(HL)");
		return ENDDISASM;
	case 0x5f:
		SetString(strset, "BIT", "3", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToN6x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x60:
		SetString(strset, "BIT", "4", "B");
		return ENDDISASM;
	case 0x61:
		SetString(strset, "BIT", "4", "C");
		return ENDDISASM;
	case 0x62:
		SetString(strset, "BIT", "4", "D");
		return ENDDISASM;
	case 0x63:
		SetString(strset, "BIT", "4", "E");
		return ENDDISASM;
	case 0x64:
		SetString(strset, "BIT", "4", "H");
		return ENDDISASM;
	case 0x65:
		SetString(strset, "BIT", "4", "L");
		return ENDDISASM;
	case 0x66:
		SetString(strset, "BIT", "4", "(HL)");
		return ENDDISASM;
	case 0x67:
		SetString(strset, "BIT", "4", "A");
		return ENDDISASM;
	case 0x68:
		SetString(strset, "BIT", "5", "B");
		return ENDDISASM;
	case 0x69:
		SetString(strset, "BIT", "5", "C");
		return ENDDISASM;
	case 0x6a:
		SetString(strset, "BIT", "5", "D");
		return ENDDISASM;
	case 0x6b:
		SetString(strset, "BIT", "5", "E");
		return ENDDISASM;
	case 0x6c:
		SetString(strset, "BIT", "5", "H");
		return ENDDISASM;
	case 0x6d:
		SetString(strset, "BIT", "5", "L");
		return ENDDISASM;
	case 0x6e:
		SetString(strset, "BIT", "5", "(HL)");
		return ENDDISASM;
	case 0x6f:
		SetString(strset, "BIT", "5", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToN7x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x70:
		SetString(strset, "BIT", "6", "B");
		return ENDDISASM;
	case 0x71:
		SetString(strset, "BIT", "6", "C");
		return ENDDISASM;
	case 0x72:
		SetString(strset, "BIT", "6", "D");
		return ENDDISASM;
	case 0x73:
		SetString(strset, "BIT", "6", "E");
		return ENDDISASM;
	case 0x74:
		SetString(strset, "BIT", "6", "H");
		return ENDDISASM;
	case 0x75:
		SetString(strset, "BIT", "6", "L");
		return ENDDISASM;
	case 0x76:
		SetString(strset, "BIT", "6", "(HL)");
		return ENDDISASM;
	case 0x77:
		SetString(strset, "BIT", "6", "A");
		return ENDDISASM;
	case 0x78:
		SetString(strset, "BIT", "7", "B");
		return ENDDISASM;
	case 0x79:
		SetString(strset, "BIT", "7", "C");
		return ENDDISASM;
	case 0x7a:
		SetString(strset, "BIT", "7", "D");
		return ENDDISASM;
	case 0x7b:
		SetString(strset, "BIT", "7", "E");
		return ENDDISASM;
	case 0x7c:
		SetString(strset, "BIT", "7", "H");
		return ENDDISASM;
	case 0x7d:
		SetString(strset, "BIT", "7", "L");
		return ENDDISASM;
	case 0x7e:
		SetString(strset, "BIT", "7", "(HL)");
		return ENDDISASM;
	case 0x7f:
		SetString(strset, "BIT", "7", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToN8x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x80:
		SetString(strset, "RES", "0", "B");
		return ENDDISASM;
	case 0x81:
		SetString(strset, "RES", "0", "C");
		return ENDDISASM;
	case 0x82:
		SetString(strset, "RES", "0", "D");
		return ENDDISASM;
	case 0x83:
		SetString(strset, "RES", "0", "E");
		return ENDDISASM;
	case 0x84:
		SetString(strset, "RES", "0", "H");
		return ENDDISASM;
	case 0x85:
		SetString(strset, "RES", "0", "L");
		return ENDDISASM;
	case 0x86:
		SetString(strset, "RES", "0", "(HL)");
		return ENDDISASM;
	case 0x87:
		SetString(strset, "RES", "0", "A");
		return ENDDISASM;
	case 0x88:
		SetString(strset, "RES", "1", "B");
		return ENDDISASM;
	case 0x89:
		SetString(strset, "RES", "1", "C");
		return ENDDISASM;
	case 0x8a:
		SetString(strset, "RES", "1", "D");
		return ENDDISASM;
	case 0x8b:
		SetString(strset, "RES", "1", "E");
		return ENDDISASM;
	case 0x8c:
		SetString(strset, "RES", "1", "H");
		return ENDDISASM;
	case 0x8d:
		SetString(strset, "RES", "1", "L");
		return ENDDISASM;
	case 0x8e:
		SetString(strset, "RES", "1", "(HL)");
		return ENDDISASM;
	case 0x8f:
		SetString(strset, "RES", "1", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToN9x(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0x90:
		SetString(strset, "RES", "2", "B");
		return ENDDISASM;
	case 0x91:
		SetString(strset, "RES", "2", "C");
		return ENDDISASM;
	case 0x92:
		SetString(strset, "RES", "2", "D");
		return ENDDISASM;
	case 0x93:
		SetString(strset, "RES", "2", "E");
		return ENDDISASM;
	case 0x94:
		SetString(strset, "RES", "2", "H");
		return ENDDISASM;
	case 0x95:
		SetString(strset, "RES", "2", "L");
		return ENDDISASM;
	case 0x96:
		SetString(strset, "RES", "2", "(HL)");
		return ENDDISASM;
	case 0x97:
		SetString(strset, "RES", "2", "A");
		return ENDDISASM;
	case 0x98:
		SetString(strset, "RES", "3", "B");
		return ENDDISASM;
	case 0x99:
		SetString(strset, "RES", "3", "C");
		return ENDDISASM;
	case 0x9a:
		SetString(strset, "RES", "3", "D");
		return ENDDISASM;
	case 0x9b:
		SetString(strset, "RES", "3", "E");
		return ENDDISASM;
	case 0x9c:
		SetString(strset, "RES", "3", "H");
		return ENDDISASM;
	case 0x9d:
		SetString(strset, "RES", "3", "L");
		return ENDDISASM;
	case 0x9e:
		SetString(strset, "RES", "3", "(HL)");
		return ENDDISASM;
	case 0x9f:
		SetString(strset, "RES", "3", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToNax(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0xa0:
		SetString(strset, "RES", "4", "B");
		return ENDDISASM;
	case 0xa1:
		SetString(strset, "RES", "4", "C");
		return ENDDISASM;
	case 0xa2:
		SetString(strset, "RES", "4", "D");
		return ENDDISASM;
	case 0xa3:
		SetString(strset, "RES", "4", "E");
		return ENDDISASM;
	case 0xa4:
		SetString(strset, "RES", "4", "H");
		return ENDDISASM;
	case 0xa5:
		SetString(strset, "RES", "4", "L");
		return ENDDISASM;
	case 0xa6:
		SetString(strset, "RES", "4", "(HL)");
		return ENDDISASM;
	case 0xa7:
		SetString(strset, "RES", "4", "A");
		return ENDDISASM;
	case 0xa8:
		SetString(strset, "RES", "5", "B");
		return ENDDISASM;
	case 0xa9:
		SetString(strset, "RES", "5", "C");
		return ENDDISASM;
	case 0xaa:
		SetString(strset, "RES", "5", "D");
		return ENDDISASM;
	case 0xab:
		SetString(strset, "RES", "5", "E");
		return ENDDISASM;
	case 0xac:
		SetString(strset, "RES", "5", "H");
		return ENDDISASM;
	case 0xad:
		SetString(strset, "RES", "5", "L");
		return ENDDISASM;
	case 0xae:
		SetString(strset, "RES", "5", "(HL)");
		return ENDDISASM;
	case 0xaf:
		SetString(strset, "RES", "5", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToNbx(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0xb0:
		SetString(strset, "RES", "6", "B");
		return ENDDISASM;
	case 0xb1:
		SetString(strset, "RES", "6", "C");
		return ENDDISASM;
	case 0xb2:
		SetString(strset, "RES", "6", "D");
		return ENDDISASM;
	case 0xb3:
		SetString(strset, "RES", "6", "E");
		return ENDDISASM;
	case 0xb4:
		SetString(strset, "RES", "6", "H");
		return ENDDISASM;
	case 0xb5:
		SetString(strset, "RES", "6", "L");
		return ENDDISASM;
	case 0xb6:
		SetString(strset, "RES", "6", "(HL)");
		return ENDDISASM;
	case 0xb7:
		SetString(strset, "RES", "6", "A");
		return ENDDISASM;
	case 0xb8:
		SetString(strset, "RES", "7", "B");
		return ENDDISASM;
	case 0xb9:
		SetString(strset, "RES", "7", "C");
		return ENDDISASM;
	case 0xba:
		SetString(strset, "RES", "7", "D");
		return ENDDISASM;
	case 0xbb:
		SetString(strset, "RES", "7", "E");
		return ENDDISASM;
	case 0xbc:
		SetString(strset, "RES", "7", "H");
		return ENDDISASM;
	case 0xbd:
		SetString(strset, "RES", "7", "L");
		return ENDDISASM;
	case 0xbe:
		SetString(strset, "RES", "7", "(HL)");
		return ENDDISASM;
	case 0xbf:
		SetString(strset, "RES", "7", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToNcx(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0xc0:
		SetString(strset, "SET", "0", "B");
		return ENDDISASM;
	case 0xc1:
		SetString(strset, "SET", "0", "C");
		return ENDDISASM;
	case 0xc2:
		SetString(strset, "SET", "0", "D");
		return ENDDISASM;
	case 0xc3:
		SetString(strset, "SET", "0", "E");
		return ENDDISASM;
	case 0xc4:
		SetString(strset, "SET", "0", "H");
		return ENDDISASM;
	case 0xc5:
		SetString(strset, "SET", "0", "L");
		return ENDDISASM;
	case 0xc6:
		SetString(strset, "SET", "0", "(HL)");
		return ENDDISASM;
	case 0xc7:
		SetString(strset, "SET", "0", "A");
		return ENDDISASM;
	case 0xc8:
		SetString(strset, "SET", "1", "B");
		return ENDDISASM;
	case 0xc9:
		SetString(strset, "SET", "1", "C");
		return ENDDISASM;
	case 0xca:
		SetString(strset, "SET", "1", "D");
		return ENDDISASM;
	case 0xcb:
		SetString(strset, "SET", "1", "E");
		return ENDDISASM;
	case 0xcc:
		SetString(strset, "SET", "1", "H");
		return ENDDISASM;
	case 0xcd:
		SetString(strset, "SET", "1", "L");
		return ENDDISASM;
	case 0xce:
		SetString(strset, "SET", "1", "(HL)");
		return ENDDISASM;
	case 0xcf:
		SetString(strset, "SET", "1", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToNdx(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0xd0:
		SetString(strset, "SET", "2", "B");
		return ENDDISASM;
	case 0xd1:
		SetString(strset, "SET", "2", "C");
		return ENDDISASM;
	case 0xd2:
		SetString(strset, "SET", "2", "D");
		return ENDDISASM;
	case 0xd3:
		SetString(strset, "SET", "2", "E");
		return ENDDISASM;
	case 0xd4:
		SetString(strset, "SET", "2", "H");
		return ENDDISASM;
	case 0xd5:
		SetString(strset, "SET", "2", "L");
		return ENDDISASM;
	case 0xd6:
		SetString(strset, "SET", "2", "(HL)");
		return ENDDISASM;
	case 0xd7:
		SetString(strset, "SET", "2", "A");
		return ENDDISASM;
	case 0xd8:
		SetString(strset, "SET", "3", "B");
		return ENDDISASM;
	case 0xd9:
		SetString(strset, "SET", "3", "C");
		return ENDDISASM;
	case 0xda:
		SetString(strset, "SET", "3", "D");
		return ENDDISASM;
	case 0xdb:
		SetString(strset, "SET", "3", "E");
		return ENDDISASM;
	case 0xdc:
		SetString(strset, "SET", "3", "H");
		return ENDDISASM;
	case 0xdd:
		SetString(strset, "SET", "3", "L");
		return ENDDISASM;
	case 0xde:
		SetString(strset, "SET", "3", "(HL)");
		return ENDDISASM;
	case 0xdf:
		SetString(strset, "SET", "3", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToNex(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0xe0:
		SetString(strset, "SET", "4", "B");
		return ENDDISASM;
	case 0xe1:
		SetString(strset, "SET", "4", "C");
		return ENDDISASM;
	case 0xe2:
		SetString(strset, "SET", "4", "D");
		return ENDDISASM;
	case 0xe3:
		SetString(strset, "SET", "4", "E");
		return ENDDISASM;
	case 0xe4:
		SetString(strset, "SET", "4", "H");
		return ENDDISASM;
	case 0xe5:
		SetString(strset, "SET", "4", "L");
		return ENDDISASM;
	case 0xe6:
		SetString(strset, "SET", "4", "(HL)");
		return ENDDISASM;
	case 0xe7:
		SetString(strset, "SET", "4", "A");
		return ENDDISASM;
	case 0xe8:
		SetString(strset, "SET", "5", "B");
		return ENDDISASM;
	case 0xe9:
		SetString(strset, "SET", "5", "C");
		return ENDDISASM;
	case 0xea:
		SetString(strset, "SET", "5", "D");
		return ENDDISASM;
	case 0xebE:
		SetString(strset, "SET", "5", "E");
		return ENDDISASM;
	case 0xec:
		SetString(strset, "SET", "5", "H");
		return ENDDISASM;
	case 0xed:
		SetString(strset, "SET", "5", "L");
		return ENDDISASM;
	case 0xee:
		SetString(strset, "SET", "5", "(HL)");
		return ENDDISASM;
	case 0xef:
		SetString(strset, "SET", "5", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TBOpCoToNfx(DASM_STRSET *strset, unsigned char opcode)
{
	switch (opcode)
	{
	case 0xf0:
		SetString(strset, "SET", "6", "B");
		return ENDDISASM;
	case 0xf1:
		SetString(strset, "SET", "6", "C");
		return ENDDISASM;
	case 0xf2:
		SetString(strset, "SET", "6", "D");
		return ENDDISASM;
	case 0xf3:
		SetString(strset, "SET", "6", "E");
		return ENDDISASM;
	case 0xf4:
		SetString(strset, "SET", "6", "H");
		return ENDDISASM;
	case 0xf5:
		SetString(strset, "SET", "6", "L");
		return ENDDISASM;
	case 0xf6:
		SetString(strset, "SET", "6", "(HL)");
		return ENDDISASM;
	case 0xf7:
		SetString(strset, "SET", "6", "A");
		return ENDDISASM;
	case 0xf8:
		SetString(strset, "SET", "7", "B");
		return ENDDISASM;
	case 0xf9:
		SetString(strset, "SET", "7", "C");
		return ENDDISASM;
	case 0xfa:
		SetString(strset, "SET", "7", "D");
		return ENDDISASM;
	case 0xfb:
		SetString(strset, "SET", "7", "E");
		return ENDDISASM;
	case 0xfc:
		SetString(strset, "SET", "7", "H");
		return ENDDISASM;
	case 0xfd:
		SetString(strset, "SET", "7", "L");
		return ENDDISASM;
	case 0xfe:
		SetString(strset, "SET", "7", "(HL)");
		return ENDDISASM;
	case 0xff:
		SetString(strset, "SET", "7", "A");
		return ENDDISASM;
	}
	return 0;
}

unsigned char TwoByteOpCoToN(DASM_STRSET *strset, unsigned char opcode)
{
	unsigned char status;

	if((opcode < 0x10) && (opcode >= 0x00))
		status = TBOpCoToN0x(strset, opcode);
	else if((opcode < 0x20) && (opcode >= 0x10))
		status = TBOpCoToN1x(strset, opcode);
	else if((opcode < 0x30) && (opcode >= 0x20))
		status = TBOpCoToN2x(strset, opcode);
	else if((opcode < 0x40) && (opcode >= 0x30))
		status = TBOpCoToN3x(strset, opcode);
	else if((opcode < 0x50) && (opcode >= 0x40))
		status = TBOpCoToN4x(strset, opcode);
	else if((opcode < 0x60) && (opcode >= 0x50))
		status = TBOpCoToN5x(strset, opcode);
	else if((opcode < 0x70) && (opcode >= 0x60))
		status = TBOpCoToN6x(strset, opcode);
	else if((opcode < 0x80) && (opcode >= 0x70))
		status = TBOpCoToN7x(strset, opcode);
	else if((opcode < 0x90) && (opcode >= 0x80))
		status = TBOpCoToN8x(strset, opcode);
	else if((opcode < 0xa0) && (opcode >= 0x90))
		status = TBOpCoToN9x(strset, opcode);
	else if((opcode < 0xb0) && (opcode >= 0xa0))
		status = TBOpCoToNax(strset, opcode);
	else if((opcode < 0xc0) && (opcode >= 0xb0))
		status = TBOpCoToNbx(strset, opcode);
	else if((opcode < 0xd0) && (opcode >= 0xc0))
		status = TBOpCoToNcx(strset, opcode);
	else if((opcode < 0xe0) && (opcode >= 0xd0))
		status = TBOpCoToNdx(strset, opcode);
	else if((opcode < 0xf0) && (opcode >= 0xe0))
		status = TBOpCoToNex(strset, opcode);
	else if((opcode <= 0xff) && (opcode >= 0xf0))
		status = TBOpCoToNfx(strset, opcode);
	else status = 0;

	return status;
}