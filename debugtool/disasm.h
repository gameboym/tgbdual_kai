// ！！！signed char scconvert 解析対象データ char binary[] カウンタ int i 解析結果格納領域 char strbuf[40]
// ！！！上記をそれぞれ組み込み先で用意しなければならない。
// ！！！binaryの大きさは実際のデータ領域+2byte余分に無いと範囲外アクセスをしてしまう可能性がある。
// ！！！使用するにはwhile(binary size > i)のループ内で#includeしstrbufの解析結果を利用する。

switch (binary[i])
{
	case 0x00:
		sprintf(strbuf, "#%04X:\t$00\tNOP\t\r\n", i);
		i += 1;
		break;
	case 0x01:
		sprintf(strbuf, "#%04X:\t$01%02X%02X\tLD\tBC\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0x02:
		sprintf(strbuf, "#%04X:\t$02\tLD\t(BC)\tA\t\r\n", i);
		i += 1;
		break;
	case 0x03:
		sprintf(strbuf, "#%04X:\t$03\tINC\tBC\t\r\n", i);
		i += 1;
		break;
	case 0x04:
		sprintf(strbuf, "#%04X:\t$04\tINC\tB\t\r\n", i);
		i += 1;
		break;
	case 0x05:
		sprintf(strbuf, "#%04X:\t$05\tDEC\tB\t\r\n", i);
		i += 1;
		break;
	case 0x06:
		sprintf(strbuf, "#%04X:\t$06%02X\tLD\tB\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0x07:
		sprintf(strbuf, "#%04X:\t$07\tRLCA\t\r\n", i);
		i += 1;
		break;
	case 0x08:
		sprintf(strbuf, "#%04X:\t$08%02X%02X\tLD\t(%02X%02X)\tSP\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0x09:
		sprintf(strbuf, "#%04X:\t$09\tADD\tHL\tBC\t\r\n", i);
		i += 1;
		break;
	case 0x0a:
		sprintf(strbuf, "#%04X:\t$0A\tLD\tA\t(BC)\t\r\n", i);
		i += 1;
		break;
	case 0x0b:
		sprintf(strbuf, "#%04X:\t$0B\tDEC\tBC\t\r\n", i);
		i += 1;
		break;
	case 0x0c:
		sprintf(strbuf, "#%04X:\t$0C\tINC\tC\t\r\n", i);
		i += 1;
		break;
	case 0x0d:
		sprintf(strbuf, "#%04X:\t$0D\tDEC\tC\t\r\n", i);
		i += 1;
		break;
	case 0x0e:
		sprintf(strbuf, "#%04X:\t$0E%02X\tLD\tC\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0x0f:
		sprintf(strbuf, "#%04X:\t$0F\tRRCA\t\r\n", i);
		i += 1;
		break;
	case 0x10:
		sprintf(strbuf, "#%04X:\t$10\tSTOP\t\r\n", i);
		i += 1;
		break;
	case 0x11:
		sprintf(strbuf, "#%04X:\t$11%02X%02X\tLD\tDE\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0x12:
		sprintf(strbuf, "#%04X:\t$12\tLD\t(DE)\tA\t\r\n", i);
		i += 1;
		break;
	case 0x13:
		sprintf(strbuf, "#%04X:\t$13\tINC\tDE\t\r\n", i);
		i += 1;
		break;
	case 0x14:
		sprintf(strbuf, "#%04X:\t$14\tINC\tD\t\r\n", i);
		i += 1;
		break;
	case 0x15:
		sprintf(strbuf, "#%04X:\t$15\tDEC\tD\t\r\n", i);
		i += 1;
		break;
	case 0x16:
		sprintf(strbuf, "#%04X:\t$16%02X\tLD\tD\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0x17:
		sprintf(strbuf, "#%04X:\t$17\tRLA\t\r\n", i);
		i += 1;
		break;
	case 0x18:
		scconverter = (signed)binary[i+1];
		sprintf(strbuf, "#%04X:\t$18%02X\tJR\t$%+02d\t\r\n", i, binary[i+1], scconverter);
		i += 2;
		break;
	case 0x19:
		sprintf(strbuf, "#%04X:\t$19\tADD\tHL\tDE\t\r\n", i);
		i += 1;
		break;
	case 0x1a:
		sprintf(strbuf, "#%04X:\t$1A\tLD\tA\t(DE)\t\r\n", i);
		i += 1;
		break;
	case 0x1b:
		sprintf(strbuf, "#%04X:\t$1B\tDEC\tDE\t\r\n", i);
		i += 1;
		break;
	case 0x1c:
		sprintf(strbuf, "#%04X:\t$1C\tINC\tE\t\r\n", i);
		i += 1;
		break;
	case 0x1d:
		sprintf(strbuf, "#%04X:\t$1D\tDEC\tE\t\r\n", i);
		i += 1;
		break;
	case 0x1e:
		sprintf(strbuf, "#%04X:\t$1E%02X\tLD\tE\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0x1f:
		sprintf(strbuf, "#%04X:\t$1F\tRRA\t\r\n", i);
		i += 1;
		break;
	case 0x20:
		scconverter = (signed)binary[i+1];
		sprintf(strbuf, "#%04X:\t$20%02X\tJR\tNZ\t$%+02d\t\r\n", i, binary[i+1], scconverter);
		i += 2;
		break;
	case 0x21:
		sprintf(strbuf, "#%04X:\t$21%02X%02X\tLD\tHL\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0x22:
		sprintf(strbuf, "#%04X:\t$22\tLDI\t(HL)\tA\t\r\n", i);
		i += 1;
		break;
	case 0x23:
		sprintf(strbuf, "#%04X:\t$23\tINC\tHL\t\r\n", i);
		i += 1;
		break;
	case 0x24:
		sprintf(strbuf, "#%04X:\t$24\tINC\tH\t\r\n", i);
		i += 1;
		break;
	case 0x25:
		sprintf(strbuf, "#%04X:\t$25\tDEC\tH\t\r\n", i);
		i += 1;
		break;
	case 0x26:
		sprintf(strbuf, "#%04X:\t$26%02X\tLD\tH\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0x27:
		sprintf(strbuf, "#%04X:\t$27\tDAA\t\r\n", i);
		i += 1;
		break;
	case 0x28:
		scconverter = (signed)binary[i+1];
		sprintf(strbuf, "#%04X:\t$28%02X\tJR\tZ\t$%+02d\t\r\n", i, binary[i+1], scconverter);
		i += 2;
		break;
	case 0x29:
		sprintf(strbuf, "#%04X:\t$29\tADD\tHL\tHL\t\r\n", i);
		i += 1;
		break;
	case 0x2a:
		sprintf(strbuf, "#%04X:\t$2A\tLDI\tA\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x2b:
		sprintf(strbuf, "#%04X:\t$2B\tDEC\tHL\t\r\n", i);
		i += 1;
		break;
	case 0x2c:
		sprintf(strbuf, "#%04X:\t$2C\tINC\tL\t\r\n", i);
		i += 1;
		break;
	case 0x2d:
		sprintf(strbuf, "#%04X:\t$2D\tDEC\tL\t\r\n", i);
		i += 1;
		break;
	case 0x2e:
		sprintf(strbuf, "#%04X:\t$2E%02X\tLD\tL\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0x2f:
		sprintf(strbuf, "#%04X:\t$2F\tCPL\t\r\n", i);
		i += 1;
		break;
	case 0x30:
		scconverter = (signed)binary[i+1];
		sprintf(strbuf, "#%04X:\t$30%02X\tJR\tNC\t$%+02d\t\r\n", i, binary[i+1], scconverter);
		i += 2;
		break;
	case 0x31:
		sprintf(strbuf, "#%04X:\t$31%02X%02X\tLD\tSP\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0x32:
		sprintf(strbuf, "#%04X:\t$32\tLDD\t(HL)\tA\t\r\n", i);
		i += 1;
		break;
	case 0x33:
		sprintf(strbuf, "#%04X:\t$33\tINC\tSP\t\r\n", i);
		i += 1;
		break;
	case 0x34:
		sprintf(strbuf, "#%04X:\t$34\tINC\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x35:
		sprintf(strbuf, "#%04X:\t$35\tDEC\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x36:
		sprintf(strbuf, "#%04X:\t$36%02X\tLD\t(HL)\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0x37:
		sprintf(strbuf, "#%04X:\t$37\tSCF\t\r\n", i);
		i += 1;
		break;
	case 0x38:
		scconverter = (signed)binary[i+1];
		sprintf(strbuf, "#%04X:\t$38%02X\tJR\tC\t$%+02d\t\r\n", i, binary[i+1], scconverter);
		i += 2;
		break;
	case 0x39:
		sprintf(strbuf, "#%04X:\t$39\tADD\tHL\tSP\t\r\n", i);
		i += 1;
		break;
	case 0x3a:
		sprintf(strbuf, "#%04X:\t$3A\tLDD\tA\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x3b:
		sprintf(strbuf, "#%04X:\t$3B\tDEC\tSP\t\r\n", i);
		i += 1;
		break;
	case 0x3c:
		sprintf(strbuf, "#%04X:\t$3C\tINC\tA\t\r\n", i);
		i += 1;
		break;
	case 0x3d:
		sprintf(strbuf, "#%04X:\t$3D\tDEC\tA\t\r\n", i);
		i += 1;
		break;
	case 0x3e:
		sprintf(strbuf, "#%04X:\t$3E%02X\tLD\tA\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0x3f:
		sprintf(strbuf, "#%04X:\t$3F\tCCF\t\r\n", i);
		i += 1;
		break;
	case 0x40:
		sprintf(strbuf, "#%04X:\t$40\tLD\tB\tB\t\r\n", i);
		i += 1;
		break;
	case 0x41:
		sprintf(strbuf, "#%04X:\t$41\tLD\tB\tC\t\r\n", i);
		i += 1;
		break;
	case 0x42:
		sprintf(strbuf, "#%04X:\t$42\tLD\tB\tD\t\r\n", i);
		i += 1;
		break;
	case 0x43:
		sprintf(strbuf, "#%04X:\t$43\tLD\tB\tE\t\r\n", i);
		i += 1;
		break;
	case 0x44:
		sprintf(strbuf, "#%04X:\t$44\tLD\tB\tH\t\r\n", i);
		i += 1;
		break;
	case 0x45:
		sprintf(strbuf, "#%04X:\t$45\tLD\tB\tL\t\r\n", i);
		i += 1;
		break;
	case 0x46:
		sprintf(strbuf, "#%04X:\t$46\tLD\tB\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x47:
		sprintf(strbuf, "#%04X:\t$47\tLD\tB\tA\t\r\n", i);
		i += 1;
		break;
	case 0x48:
		sprintf(strbuf, "#%04X:\t$48\tLD\tC\tB\t\r\n", i);
		i += 1;
		break;
	case 0x49:
		sprintf(strbuf, "#%04X:\t$49\tLD\tC\tC\t\r\n", i);
		i += 1;
		break;
	case 0x4a:
		sprintf(strbuf, "#%04X:\t$4A\tLD\tC\tD\t\r\n", i);
		i += 1;
		break;
	case 0x4b:
		sprintf(strbuf, "#%04X:\t$4B\tLD\tC\tE\t\r\n", i);
		i += 1;
		break;
	case 0x4c:
		sprintf(strbuf, "#%04X:\t$4C\tLD\tC\tH\t\r\n", i);
		i += 1;
		break;
	case 0x4d:
		sprintf(strbuf, "#%04X:\t$4D\tLD\tC\tL\t\r\n", i);
		i += 1;
		break;
	case 0x4e:
		sprintf(strbuf, "#%04X:\t$4E\tLD\tC\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x4f:
		sprintf(strbuf, "#%04X:\t$4F\tLD\tC\tA\t\r\n", i);
		i += 1;
		break;
	case 0x50:
		sprintf(strbuf, "#%04X:\t$50\tLD\tD\tB\t\r\n", i);
		i += 1;
		break;
	case 0x51:
		sprintf(strbuf, "#%04X:\t$51\tLD\tD\tC\t\r\n", i);
		i += 1;
		break;
	case 0x52:
		sprintf(strbuf, "#%04X:\t$52\tLD\tD\tD\t\r\n", i);
		i += 1;
		break;
	case 0x53:
		sprintf(strbuf, "#%04X:\t$53\tLD\tD\tE\t\r\n", i);
		i += 1;
		break;
	case 0x54:
		sprintf(strbuf, "#%04X:\t$54\tLD\tD\tH\t\r\n", i);
		i += 1;
		break;
	case 0x55:
		sprintf(strbuf, "#%04X:\t$55\tLD\tD\tL\t\r\n", i);
		i += 1;
		break;
	case 0x56:
		sprintf(strbuf, "#%04X:\t$56\tLD\tD\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x57:
		sprintf(strbuf, "#%04X:\t$57\tLD\tD\tA\t\r\n", i);
		i += 1;
		break;
	case 0x58:
		sprintf(strbuf, "#%04X:\t$58\tLD\tE\tB\t\r\n", i);
		i += 1;
		break;
	case 0x59:
		sprintf(strbuf, "#%04X:\t$59\tLD\tE\tC\t\r\n", i);
		i += 1;
		break;
	case 0x5a:
		sprintf(strbuf, "#%04X:\t$5A\tLD\tE\tD\t\r\n", i);
		i += 1;
		break;
	case 0x5b:
		sprintf(strbuf, "#%04X:\t$5B\tLD\tE\tE\t\r\n", i);
		i += 1;
		break;
	case 0x5c:
		sprintf(strbuf, "#%04X:\t$5C\tLD\tE\tH\t\r\n", i);
		i += 1;
		break;
	case 0x5d:
		sprintf(strbuf, "#%04X:\t$5D\tLD\tE\tL\t\r\n", i);
		i += 1;
		break;
	case 0x5e:
		sprintf(strbuf, "#%04X:\t$5E\tLD\tE\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x5f:
		sprintf(strbuf, "#%04X:\t$5F\tLD\tE\tA\t\r\n", i);
		i += 1;
		break;
	case 0x60:
		sprintf(strbuf, "#%04X:\t$60\tLD\tH\tB\t\r\n", i);
		i += 1;
		break;
	case 0x61:
		sprintf(strbuf, "#%04X:\t$61\tLD\tH\tC\t\r\n", i);
		i += 1;
		break;
	case 0x62:
		sprintf(strbuf, "#%04X:\t$62\tLD\tH\tD\t\r\n", i);
		i += 1;
		break;
	case 0x63:
		sprintf(strbuf, "#%04X:\t$63\tLD\tH\tE\t\r\n", i);
		i += 1;
		break;
	case 0x64:
		sprintf(strbuf, "#%04X:\t$64\tLD\tH\tH\t\r\n", i);
		i += 1;
		break;
	case 0x65:
		sprintf(strbuf, "#%04X:\t$65\tLD\tH\tL\t\r\n", i);
		i += 1;
		break;
	case 0x66:
		sprintf(strbuf, "#%04X:\t$66\tLD\tH\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x67:
		sprintf(strbuf, "#%04X:\t$67\tLD\tH\tA\t\r\n", i);
		i += 1;
		break;
	case 0x68:
		sprintf(strbuf, "#%04X:\t$68\tLD\tL\tB\t\r\n", i);
		i += 1;
		break;
	case 0x69:
		sprintf(strbuf, "#%04X:\t$69\tLD\tL\tC\t\r\n", i);
		i += 1;
		break;
	case 0x6a:
		sprintf(strbuf, "#%04X:\t$6A\tLD\tL\tD\t\r\n", i);
		i += 1;
		break;
	case 0x6b:
		sprintf(strbuf, "#%04X:\t$6B\tLD\tL\tE\t\r\n", i);
		i += 1;
		break;
	case 0x6c:
		sprintf(strbuf, "#%04X:\t$6C\tLD\tL\tH\t\r\n", i);
		i += 1;
		break;
	case 0x6d:
		sprintf(strbuf, "#%04X:\t$6D\tLD\tL\tL\t\r\n", i);
		i += 1;
		break;
	case 0x6e:
		sprintf(strbuf, "#%04X:\t$6E\tLD\tL\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x6f:
		sprintf(strbuf, "#%04X:\t$6F\tLD\tL\tA\t\r\n", i);
		i += 1;
		break;
	case 0x70:
		sprintf(strbuf, "#%04X:\t$70\tLD\t(HL)\tB\t\r\n", i);
		i += 1;
		break;
	case 0x71:
		sprintf(strbuf, "#%04X:\t$71\tLD\t(HL)\tC\t\r\n", i);
		i += 1;
		break;
	case 0x72:
		sprintf(strbuf, "#%04X:\t$72\tLD\t(HL)\tD\t\r\n", i);
		i += 1;
		break;
	case 0x73:
		sprintf(strbuf, "#%04X:\t$73\tLD\t(HL)\tE\t\r\n", i);
		i += 1;
		break;
	case 0x74:
		sprintf(strbuf, "#%04X:\t$74\tLD\t(HL)\tH\t\r\n", i);
		i += 1;
		break;
	case 0x75:
		sprintf(strbuf, "#%04X:\t$75\tLD\t(HL)\tL\t\r\n", i);
		i += 1;
		break;
	case 0x76:
		sprintf(strbuf, "#%04X:\t$76\tHALT\t\r\n", i);
		i += 1;
		break;
	case 0x77:
		sprintf(strbuf, "#%04X:\t$77\tLD\t(HL)\tA\t\r\n", i);
		i += 1;
		break;
	case 0x78:
		sprintf(strbuf, "#%04X:\t$78\tLD\tA\tB\t\r\n", i);
		i += 1;
		break;
	case 0x79:
		sprintf(strbuf, "#%04X:\t$79\tLD\tA\tC\t\r\n", i);
		i += 1;
		break;
	case 0x7a:
		sprintf(strbuf, "#%04X:\t$7A\tLD\tA\tD\t\r\n", i);
		i += 1;
		break;
	case 0x7b:
		sprintf(strbuf, "#%04X:\t$7B\tLD\tA\tE\t\r\n", i);
		i += 1;
		break;
	case 0x7c:
		sprintf(strbuf, "#%04X:\t$7C\tLD\tA\tH\t\r\n", i);
		i += 1;
		break;
	case 0x7d:
		sprintf(strbuf, "#%04X:\t$7D\tLD\tA\tL\t\r\n", i);
		i += 1;
		break;
	case 0x7e:
		sprintf(strbuf, "#%04X:\t$7E\tLD\tA\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x7f:
		sprintf(strbuf, "#%04X:\t$7F\tLD\tA\tA\t\r\n", i);
		i += 1;
		break;
	case 0x80:
		sprintf(strbuf, "#%04X:\t$80\tADD\tB\t\r\n", i);
		i += 1;
		break;
	case 0x81:
		sprintf(strbuf, "#%04X:\t$81\tADD\tC\t\r\n", i);
		i += 1;
		break;
	case 0x82:
		sprintf(strbuf, "#%04X:\t$82\tADD\tD\t\r\n", i);
		i += 1;
		break;
	case 0x83:
		sprintf(strbuf, "#%04X:\t$83\tADD\tE\t\r\n", i);
		i += 1;
		break;
	case 0x84:
		sprintf(strbuf, "#%04X:\t$84\tADD\tH\t\r\n", i);
		i += 1;
		break;
	case 0x85:
		sprintf(strbuf, "#%04X:\t$85\tADD\tL\t\r\n", i);
		i += 1;
		break;
	case 0x86:
		sprintf(strbuf, "#%04X:\t$86\tADD\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x87:
		sprintf(strbuf, "#%04X:\t$87\tADD\tA\t\r\n", i);
		i += 1;
		break;
	case 0x88:
		sprintf(strbuf, "#%04X:\t$88\tADC\tB\t\r\n", i);
		i += 1;
		break;
	case 0x89:
		sprintf(strbuf, "#%04X:\t$89\tADC\tC\t\r\n", i);
		i += 1;
		break;
	case 0x8a:
		sprintf(strbuf, "#%04X:\t$8A\tADC\tD\t\r\n", i);
		i += 1;
		break;
	case 0x8b:
		sprintf(strbuf, "#%04X:\t$8B\tADC\tE\t\r\n", i);
		i += 1;
		break;
	case 0x8c:
		sprintf(strbuf, "#%04X:\t$8C\tADC\tH\t\r\n", i);
		i += 1;
		break;
	case 0x8d:
		sprintf(strbuf, "#%04X:\t$8D\tADC\tL\t\r\n", i);
		i += 1;
		break;
	case 0x8e:
		sprintf(strbuf, "#%04X:\t$8E\tADC\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x8f:
		sprintf(strbuf, "#%04X:\t$8F\tADC\tA\t\r\n", i);
		i += 1;
		break;
	case 0x90:
		sprintf(strbuf, "#%04X:\t$90\tSUB\tB\t\r\n", i);
		i += 1;
		break;
	case 0x91:
		sprintf(strbuf, "#%04X:\t$91\tSUB\tC\t\r\n", i);
		i += 1;
		break;
	case 0x92:
		sprintf(strbuf, "#%04X:\t$92\tSUB\tD\t\r\n", i);
		i += 1;
		break;
	case 0x93:
		sprintf(strbuf, "#%04X:\t$93\tSUB\tE\t\r\n", i);
		i += 1;
		break;
	case 0x94:
		sprintf(strbuf, "#%04X:\t$94\tSUB\tH\t\r\n", i);
		i += 1;
		break;
	case 0x95:
		sprintf(strbuf, "#%04X:\t$95\tSUB\tL\t\r\n", i);
		i += 1;
		break;
	case 0x96:
		sprintf(strbuf, "#%04X:\t$96\tSUB\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x97:
		sprintf(strbuf, "#%04X:\t$97\tSUB\tA\t\r\n", i);
		i += 1;
		break;
	case 0x98:
		sprintf(strbuf, "#%04X:\t$98\tSBC\tB\t\r\n", i);
		i += 1;
		break;
	case 0x99:
		sprintf(strbuf, "#%04X:\t$99\tSBC\tC\t\r\n", i);
		i += 1;
		break;
	case 0x9a:
		sprintf(strbuf, "#%04X:\t$9A\tSBC\tD\t\r\n", i);
		i += 1;
		break;
	case 0x9b:
		sprintf(strbuf, "#%04X:\t$9B\tSBC\tE\t\r\n", i);
		i += 1;
		break;
	case 0x9c:
		sprintf(strbuf, "#%04X:\t$9C\tSBC\tH\t\r\n", i);
		i += 1;
		break;
	case 0x9d:
		sprintf(strbuf, "#%04X:\t$9D\tSBC\tL\t\r\n", i);
		i += 1;
		break;
	case 0x9e:
		sprintf(strbuf, "#%04X:\t$9E\tSBC\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0x9f:
		sprintf(strbuf, "#%04X:\t$9F\tSBC\tA\t\r\n", i);
		i += 1;
		break;
	case 0xa0:
		sprintf(strbuf, "#%04X:\t$A0\tAND\tB\t\r\n", i);
		i += 1;
		break;
	case 0xa1:
		sprintf(strbuf, "#%04X:\t$A1\tAND\tC\t\r\n", i);
		i += 1;
		break;
	case 0xa2:
		sprintf(strbuf, "#%04X:\t$A2\tAND\tD\t\r\n", i);
		i += 1;
		break;
	case 0xa3:
		sprintf(strbuf, "#%04X:\t$A3\tAND\tE\t\r\n", i);
		i += 1;
		break;
	case 0xa4:
		sprintf(strbuf, "#%04X:\t$A4\tAND\tH\t\r\n", i);
		i += 1;
		break;
	case 0xa5:
		sprintf(strbuf, "#%04X:\t$A5\tAND\tL\t\r\n", i);
		i += 1;
		break;
	case 0xa6:
		sprintf(strbuf, "#%04X:\t$A6\tAND\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0xa7:
		sprintf(strbuf, "#%04X:\t$A7\tAND\tA\t\r\n", i);
		i += 1;
		break;
	case 0xa8:
		sprintf(strbuf, "#%04X:\t$A8\tXOR\tB\t\r\n", i);
		i += 1;
		break;
	case 0xa9:
		sprintf(strbuf, "#%04X:\t$A9\tXOR\tC\t\r\n", i);
		i += 1;
		break;
	case 0xaa:
		sprintf(strbuf, "#%04X:\t$AA\tXOR\tD\t\r\n", i);
		i += 1;
		break;
	case 0xab:
		sprintf(strbuf, "#%04X:\t$AB\tXOR\tE\t\r\n", i);
		i += 1;
		break;
	case 0xac:
		sprintf(strbuf, "#%04X:\t$AC\tXOR\tH\t\r\n", i);
		i += 1;
		break;
	case 0xad:
		sprintf(strbuf, "#%04X:\t$AD\tXOR\tL\t\r\n", i);
		i += 1;
		break;
	case 0xae:
		sprintf(strbuf, "#%04X:\t$AE\tXOR\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0xaf:
		sprintf(strbuf, "#%04X:\t$AF\tXOR\tA\t\r\n", i);
		i += 1;
		break;
	case 0xb0:
		sprintf(strbuf, "#%04X:\t$B0\tOR\tB\t\r\n", i);
		i += 1;
		break;
	case 0xb1:
		sprintf(strbuf, "#%04X:\t$B1\tOR\tC\t\r\n", i);
		i += 1;
		break;
	case 0xb2:
		sprintf(strbuf, "#%04X:\t$B2\tOR\tD\t\r\n", i);
		i += 1;
		break;
	case 0xb3:
		sprintf(strbuf, "#%04X:\t$B3\tOR\tE\t\r\n", i);
		i += 1;
		break;
	case 0xb4:
		sprintf(strbuf, "#%04X:\t$B4\tOR\tH\t\r\n", i);
		i += 1;
		break;
	case 0xb5:
		sprintf(strbuf, "#%04X:\t$B5\tOR\tL\t\r\n", i);
		i += 1;
		break;
	case 0xb6:
		sprintf(strbuf, "#%04X:\t$B6\tOR\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0xb7:
		sprintf(strbuf, "#%04X:\t$B7\tOR\tA\t\r\n", i);
		i += 1;
		break;
	case 0xb8:
		sprintf(strbuf, "#%04X:\t$B8\tCP\tB\t\r\n", i);
		i += 1;
		break;
	case 0xb9:
		sprintf(strbuf, "#%04X:\t$B9\tCP\tC\t\r\n", i);
		i += 1;
		break;
	case 0xba:
		sprintf(strbuf, "#%04X:\t$BA\tCP\tD\t\r\n", i);
		i += 1;
		break;
	case 0xbb:
		sprintf(strbuf, "#%04X:\t$BB\tCP\tE\t\r\n", i);
		i += 1;
		break;
	case 0xbc:
		sprintf(strbuf, "#%04X:\t$BC\tCP\tH\t\r\n", i);
		i += 1;
		break;
	case 0xbd:
		sprintf(strbuf, "#%04X:\t$BD\tCP\tL\t\r\n", i);
		i += 1;
		break;
	case 0xbe:
		sprintf(strbuf, "#%04X:\t$BE\tCP\t(HL)\t\r\n", i);
		i += 1;
		break;
	case 0xbf:
		sprintf(strbuf, "#%04X:\t$BF\tCP\tA\t\r\n", i);
		i += 1;
		break;
	case 0xc0:
		sprintf(strbuf, "#%04X:\t$C0\tRET\tNZ\t\r\n", i);
		i += 1;
		break;
	case 0xc1:
		sprintf(strbuf, "#%04X:\t$C1\tPOP\tBC\t\r\n", i);
		i += 1;
		break;
	case 0xc2:
		sprintf(strbuf, "#%04X:\t$C2%02X%02X\tJP\tNZ\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xc3:
		sprintf(strbuf, "#%04X:\t$C3%02X%02X\tJP\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xc4:
		sprintf(strbuf, "#%04X:\t$C4%02X%02X\tCALL\tNZ\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xc5:
		sprintf(strbuf, "#%04X:\t$C5\tPUSH\tBC\t\r\n", i);
		i += 1;
		break;
	case 0xc6:
		sprintf(strbuf, "#%04X:\t$C6%02X\tADD\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0xc7:
		sprintf(strbuf, "#%04X:\t$C7\tRST\t0\t\r\n", i);
		i += 1;
		break;
	case 0xc8:
		sprintf(strbuf, "#%04X:\t$C8\tRET\tZ\t\r\n", i);
		i += 1;
		break;
	case 0xc9:
		sprintf(strbuf, "#%04X:\t$C9\tRET\t\r\n", i);
		i += 1;
		break;
	case 0xca:
		sprintf(strbuf, "#%04X:\t$CA%02X%02X\tJP\tZ\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xcb:
		switch(binary[i+1])
		{
			case 0x00:
				sprintf(strbuf, "#%04X:\t$CB00\tRLC\tB\t\r\n", i);
				i += 2;
				break;
			case 0x01:
				sprintf(strbuf, "#%04X:\t$CB01\tRLC\tC\t\r\n", i);
				i += 2;
				break;
			case 0x02:
				sprintf(strbuf, "#%04X:\t$CB02\tRLC\tD\t\r\n", i);
				i += 2;
				break;
			case 0x03:
				sprintf(strbuf, "#%04X:\t$CB03\tRLC\tE\t\r\n", i);
				i += 2;
				break;
			case 0x04:
				sprintf(strbuf, "#%04X:\t$CB04\tRLC\tH\t\r\n", i);
				i += 2;
				break;
			case 0x05:
				sprintf(strbuf, "#%04X:\t$CB05\tRLC\tL\t\r\n", i);
				i += 2;
				break;
			case 0x06:
				sprintf(strbuf, "#%04X:\t$CB06\tRLC\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x07:
				sprintf(strbuf, "#%04X:\t$CB07\tRLC\tA\t\r\n", i);
				i += 2;
				break;
			case 0x08:
				sprintf(strbuf, "#%04X:\t$CB08\tRRC\tB\t\r\n", i);
				i += 2;
				break;
			case 0x09:
				sprintf(strbuf, "#%04X:\t$CB09\tRRC\tC\t\r\n", i);
				i += 2;
				break;
			case 0x0a:
				sprintf(strbuf, "#%04X:\t$CB0A\tRRC\tD\t\r\n", i);
				i += 2;
				break;
			case 0x0b:
				sprintf(strbuf, "#%04X:\t$CB0B\tRRC\tE\t\r\n", i);
				i += 2;
				break;
			case 0x0c:
				sprintf(strbuf, "#%04X:\t$CB0C\tRRC\tH\t\r\n", i);
				i += 2;
				break;
			case 0x0d:
				sprintf(strbuf, "#%04X:\t$CB0D\tRRC\tL\t\r\n", i);
				i += 2;
				break;
			case 0x0e:
				sprintf(strbuf, "#%04X:\t$CB0E\tRRC\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x0f:
				sprintf(strbuf, "#%04X:\t$CB0F\tRRC\tA\t\r\n", i);
				i += 2;
				break;
			case 0x10:
				sprintf(strbuf, "#%04X:\t$CB10\tRL\tB\t\r\n", i);
				i += 2;
				break;
			case 0x11:
				sprintf(strbuf, "#%04X:\t$CB11\tRL\tC\t\r\n", i);
				i += 2;
				break;
			case 0x12:
				sprintf(strbuf, "#%04X:\t$CB12\tRL\tD\t\r\n", i);
				i += 2;
				break;
			case 0x13:
				sprintf(strbuf, "#%04X:\t$CB13\tRL\tE\t\r\n", i);
				i += 2;
				break;
			case 0x14:
				sprintf(strbuf, "#%04X:\t$CB14\tRL\tH\t\r\n", i);
				i += 2;
				break;
			case 0x15:
				sprintf(strbuf, "#%04X:\t$CB15\tRL\tL\t\r\n", i);
				i += 2;
				break;
			case 0x16:
				sprintf(strbuf, "#%04X:\t$CB16\tRL\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x17:
				sprintf(strbuf, "#%04X:\t$CB17\tRL\tA\t\r\n", i);
				i += 2;
				break;
			case 0x18:
				sprintf(strbuf, "#%04X:\t$CB18\tRR\tB\t\r\n", i);
				i += 2;
				break;
			case 0x19:
				sprintf(strbuf, "#%04X:\t$CB19\tRR\tC\t\r\n", i);
				i += 2;
				break;
			case 0x1a:
				sprintf(strbuf, "#%04X:\t$CB1A\tRR\tD\t\r\n", i);
				i += 2;
				break;
			case 0x1b:
				sprintf(strbuf, "#%04X:\t$CB1B\tRR\tE\t\r\n", i);
				i += 2;
				break;
			case 0x1c:
				sprintf(strbuf, "#%04X:\t$CB1C\tRR\tH\t\r\n", i);
				i += 2;
				break;
			case 0x1d:
				sprintf(strbuf, "#%04X:\t$CB1D\tRR\tL\t\r\n", i);
				i += 2;
				break;
			case 0x1e:
				sprintf(strbuf, "#%04X:\t$CB1E\tRR\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x1f:
				sprintf(strbuf, "#%04X:\t$CB1F\tRR\tA\t\r\n", i);
				i += 2;
				break;
			case 0x20:
				sprintf(strbuf, "#%04X:\t$CB20\tSLA\tB\t\r\n", i);
				i += 2;
				break;
			case 0x21:
				sprintf(strbuf, "#%04X:\t$CB21\tSLA\tC\t\r\n", i);
				i += 2;
				break;
			case 0x22:
				sprintf(strbuf, "#%04X:\t$CB22\tSLA\tD\t\r\n", i);
				i += 2;
				break;
			case 0x23:
				sprintf(strbuf, "#%04X:\t$CB23\tSLA\tE\t\r\n", i);
				i += 2;
				break;
			case 0x24:
				sprintf(strbuf, "#%04X:\t$CB24\tSLA\tH\t\r\n", i);
				i += 2;
				break;
			case 0x25:
				sprintf(strbuf, "#%04X:\t$CB25\tSLA\tL\t\r\n", i);
				i += 2;
				break;
			case 0x26:
				sprintf(strbuf, "#%04X:\t$CB26\tSLA\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x27:
				sprintf(strbuf, "#%04X:\t$CB27\tSLA\tA\t\r\n", i);
				i += 2;
				break;
			case 0x28:
				sprintf(strbuf, "#%04X:\t$CB28\tSRA\tB\t\r\n", i);
				i += 2;
				break;
			case 0x29:
				sprintf(strbuf, "#%04X:\t$CB29\tSRA\tC\t\r\n", i);
				i += 2;
				break;
			case 0x2a:
				sprintf(strbuf, "#%04X:\t$CB2A\tSRA\tD\t\r\n", i);
				i += 2;
				break;
			case 0x2b:
				sprintf(strbuf, "#%04X:\t$CB2B\tSRA\tE\t\r\n", i);
				i += 2;
				break;
			case 0x2c:
				sprintf(strbuf, "#%04X:\t$CB2C\tSRA\tH\t\r\n", i);
				i += 2;
				break;
			case 0x2d:
				sprintf(strbuf, "#%04X:\t$CB2D\tSRA\tL\t\r\n", i);
				i += 2;
				break;
			case 0x2e:
				sprintf(strbuf, "#%04X:\t$CB2E\tSRA\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x2f:
				sprintf(strbuf, "#%04X:\t$CB2F\tSRA\tA\t\r\n", i);
				i += 2;
				break;
			case 0x30:
				sprintf(strbuf, "#%04X:\t$CB30\tSWAP\tB\t\r\n", i);
				i += 2;
				break;
			case 0x31:
				sprintf(strbuf, "#%04X:\t$CB31\tSWAP\tC\t\r\n", i);
				i += 2;
				break;
			case 0x32:
				sprintf(strbuf, "#%04X:\t$CB32\tSWAP\tD\t\r\n", i);
				i += 2;
				break;
			case 0x33:
				sprintf(strbuf, "#%04X:\t$CB33\tSWAP\tE\t\r\n", i);
				i += 2;
				break;
			case 0x34:
				sprintf(strbuf, "#%04X:\t$CB34\tSWAP\tH\t\r\n", i);
				i += 2;
				break;
			case 0x35:
				sprintf(strbuf, "#%04X:\t$CB35\tSWAP\tL\t\r\n", i);
				i += 2;
				break;
			case 0x36:
				sprintf(strbuf, "#%04X:\t$CB36\tSWAP\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x37:
				sprintf(strbuf, "#%04X:\t$CB37\tSWAP\tA\t\r\n", i);
				i += 2;
				break;
			case 0x38:
				sprintf(strbuf, "#%04X:\t$CB38\tSRL\tB\t\r\n", i);
				i += 2;
				break;
			case 0x39:
				sprintf(strbuf, "#%04X:\t$CB39\tSRL\tC\t\r\n", i);
				i += 2;
				break;
			case 0x3a:
				sprintf(strbuf, "#%04X:\t$CB3A\tSRL\tD\t\r\n", i);
				i += 2;
				break;
			case 0x3b:
				sprintf(strbuf, "#%04X:\t$CB3B\tSRL\tE\t\r\n", i);
				i += 2;
				break;
			case 0x3c:
				sprintf(strbuf, "#%04X:\t$CB3C\tSRL\tH\t\r\n", i);
				i += 2;
				break;
			case 0x3d:
				sprintf(strbuf, "#%04X:\t$CB3D\tSRL\tL\t\r\n", i);
				i += 2;
				break;
			case 0x3e:
				sprintf(strbuf, "#%04X:\t$CB3E\tSRL\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x3f:
				sprintf(strbuf, "#%04X:\t$CB3F\tSRL\tA\t\r\n", i);
				i += 2;
				break;
			case 0x40:
				sprintf(strbuf, "#%04X:\t$CB40\tBIT\t0\tB\t\r\n", i);
				i += 2;
				break;
			case 0x41:
				sprintf(strbuf, "#%04X:\t$CB41\tBIT\t0\tC\t\r\n", i);
				i += 2;
				break;
			case 0x42:
				sprintf(strbuf, "#%04X:\t$CB42\tBIT\t0\tD\t\r\n", i);
				i += 2;
				break;
			case 0x43:
				sprintf(strbuf, "#%04X:\t$CB43\tBIT\t0\tE\t\r\n", i);
				i += 2;
				break;
			case 0x44:
				sprintf(strbuf, "#%04X:\t$CB44\tBIT\t0\tH\t\r\n", i);
				i += 2;
				break;
			case 0x45:
				sprintf(strbuf, "#%04X:\t$CB45\tBIT\t0\tL\t\r\n", i);
				i += 2;
				break;
			case 0x46:
				sprintf(strbuf, "#%04X:\t$CB46\tBIT\t0\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x47:
				sprintf(strbuf, "#%04X:\t$CB47\tBIT\t0\tA\t\r\n", i);
				i += 2;
				break;
			case 0x48:
				sprintf(strbuf, "#%04X:\t$CB48\tBIT\t1\tB\t\r\n", i);
				i += 2;
				break;
			case 0x49:
				sprintf(strbuf, "#%04X:\t$CB49\tBIT\t1\tC\t\r\n", i);
				i += 2;
				break;
			case 0x4a:
				sprintf(strbuf, "#%04X:\t$CB4A\tBIT\t1\tD\t\r\n", i);
				i += 2;
				break;
			case 0x4b:
				sprintf(strbuf, "#%04X:\t$CB4B\tBIT\t1\tE\t\r\n", i);
				i += 2;
				break;
			case 0x4c:
				sprintf(strbuf, "#%04X:\t$CB4C\tBIT\t1\tH\t\r\n", i);
				i += 2;
				break;
			case 0x4d:
				sprintf(strbuf, "#%04X:\t$CB4D\tBIT\t1\tL\t\r\n", i);
				i += 2;
				break;
			case 0x4e:
				sprintf(strbuf, "#%04X:\t$CB4E\tBIT\t1\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x4f:
				sprintf(strbuf, "#%04X:\t$CB4F\tBIT\t1\tA\t\r\n", i);
				i += 2;
				break;
			case 0x50:
				sprintf(strbuf, "#%04X:\t$CB50\tBIT\t2\tB\t\r\n", i);
				i += 2;
				break;
			case 0x51:
				sprintf(strbuf, "#%04X:\t$CB51\tBIT\t2\tC\t\r\n", i);
				i += 2;
				break;
			case 0x52:
				sprintf(strbuf, "#%04X:\t$CB52\tBIT\t2\tD\t\r\n", i);
				i += 2;
				break;
			case 0x53:
				sprintf(strbuf, "#%04X:\t$CB53\tBIT\t2\tE\t\r\n", i);
				i += 2;
				break;
			case 0x54:
				sprintf(strbuf, "#%04X:\t$CB54\tBIT\t2\tH\t\r\n", i);
				i += 2;
				break;
			case 0x55:
				sprintf(strbuf, "#%04X:\t$CB55\tBIT\t2\tL\t\r\n", i);
				i += 2;
				break;
			case 0x56:
				sprintf(strbuf, "#%04X:\t$CB56\tBIT\t2\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x57:
				sprintf(strbuf, "#%04X:\t$CB57\tBIT\t2\tA\t\r\n", i);
				i += 2;
				break;
			case 0x58:
				sprintf(strbuf, "#%04X:\t$CB58\tBIT\t3\tB\t\r\n", i);
				i += 2;
				break;
			case 0x59:
				sprintf(strbuf, "#%04X:\t$CB59\tBIT\t3\tC\t\r\n", i);
				i += 2;
				break;
			case 0x5a:
				sprintf(strbuf, "#%04X:\t$CB5A\tBIT\t3\tD\t\r\n", i);
				i += 2;
				break;
			case 0x5b:
				sprintf(strbuf, "#%04X:\t$CB5B\tBIT\t3\tE\t\r\n", i);
				i += 2;
				break;
			case 0x5c:
				sprintf(strbuf, "#%04X:\t$CB5C\tBIT\t3\tH\t\r\n", i);
				i += 2;
				break;
			case 0x5d:
				sprintf(strbuf, "#%04X:\t$CB5D\tBIT\t3\tL\t\r\n", i);
				i += 2;
				break;
			case 0x5e:
				sprintf(strbuf, "#%04X:\t$CB5E\tBIT\t3\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x5f:
				sprintf(strbuf, "#%04X:\t$CB5F\tBIT\t3\tA\t\r\n", i);
				i += 2;
				break;
			case 0x60:
				sprintf(strbuf, "#%04X:\t$CB60\tBIT\t4\tB\t\r\n", i);
				i += 2;
				break;
			case 0x61:
				sprintf(strbuf, "#%04X:\t$CB61\tBIT\t4\tC\t\r\n", i);
				i += 2;
				break;
			case 0x62:
				sprintf(strbuf, "#%04X:\t$CB62\tBIT\t4\tD\t\r\n", i);
				i += 2;
				break;
			case 0x63:
				sprintf(strbuf, "#%04X:\t$CB63\tBIT\t4\tE\t\r\n", i);
				i += 2;
				break;
			case 0x64:
				sprintf(strbuf, "#%04X:\t$CB64\tBIT\t4\tH\t\r\n", i);
				i += 2;
				break;
			case 0x65:
				sprintf(strbuf, "#%04X:\t$CB65\tBIT\t4\tL\t\r\n", i);
				i += 2;
				break;
			case 0x66:
				sprintf(strbuf, "#%04X:\t$CB66\tBIT\t4\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x67:
				sprintf(strbuf, "#%04X:\t$CB67\tBIT\t4\tA\t\r\n", i);
				i += 2;
				break;
			case 0x68:
				sprintf(strbuf, "#%04X:\t$CB68\tBIT\t5\tB\t\r\n", i);
				i += 2;
				break;
			case 0x69:
				sprintf(strbuf, "#%04X:\t$CB69\tBIT\t5\tC\t\r\n", i);
				i += 2;
				break;
			case 0x6a:
				sprintf(strbuf, "#%04X:\t$CB6A\tBIT\t5\tD\t\r\n", i);
				i += 2;
				break;
			case 0x6b:
				sprintf(strbuf, "#%04X:\t$CB6B\tBIT\t5\tE\t\r\n", i);
				i += 2;
				break;
			case 0x6c:
				sprintf(strbuf, "#%04X:\t$CB6C\tBIT\t5\tH\t\r\n", i);
				i += 2;
				break;
			case 0x6d:
				sprintf(strbuf, "#%04X:\t$CB6D\tBIT\t5\tL\t\r\n", i);
				i += 2;
				break;
			case 0x6e:
				sprintf(strbuf, "#%04X:\t$CB6E\tBIT\t5\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x6f:
				sprintf(strbuf, "#%04X:\t$CB6F\tBIT\t5\tA\t\r\n", i);
				i += 2;
				break;
			case 0x70:
				sprintf(strbuf, "#%04X:\t$CB70\tBIT\t6\tB\t\r\n", i);
				i += 2;
				break;
			case 0x71:
				sprintf(strbuf, "#%04X:\t$CB71\tBIT\t6\tC\t\r\n", i);
				i += 2;
				break;
			case 0x72:
				sprintf(strbuf, "#%04X:\t$CB72\tBIT\t6\tD\t\r\n", i);
				i += 2;
				break;
			case 0x73:
				sprintf(strbuf, "#%04X:\t$CB73\tBIT\t6\tE\t\r\n", i);
				i += 2;
				break;
			case 0x74:
				sprintf(strbuf, "#%04X:\t$CB74\tBIT\t6\tH\t\r\n", i);
				i += 2;
				break;
			case 0x75:
				sprintf(strbuf, "#%04X:\t$CB75\tBIT\t6\tL\t\r\n", i);
				i += 2;
				break;
			case 0x76:
				sprintf(strbuf, "#%04X:\t$CB76\tBIT\t6\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x77:
				sprintf(strbuf, "#%04X:\t$CB77\tBIT\t6\tA\t\r\n", i);
				i += 2;
				break;
			case 0x78:
				sprintf(strbuf, "#%04X:\t$CB78\tBIT\t7\tB\t\r\n", i);
				i += 2;
				break;
			case 0x79:
				sprintf(strbuf, "#%04X:\t$CB79\tBIT\t7\tC\t\r\n", i);
				i += 2;
				break;
			case 0x7a:
				sprintf(strbuf, "#%04X:\t$CB7A\tBIT\t7\tD\t\r\n", i);
				i += 2;
				break;
			case 0x7b:
				sprintf(strbuf, "#%04X:\t$CB7B\tBIT\t7\tE\t\r\n", i);
				i += 2;
				break;
			case 0x7c:
				sprintf(strbuf, "#%04X:\t$CB7C\tBIT\t7\tH\t\r\n", i);
				i += 2;
				break;
			case 0x7d:
				sprintf(strbuf, "#%04X:\t$CB7D\tBIT\t7\tL\t\r\n", i);
				i += 2;
				break;
			case 0x7e:
				sprintf(strbuf, "#%04X:\t$CB7E\tBIT\t7\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x7f:
				sprintf(strbuf, "#%04X:\t$CB7F\tBIT\t7\tA\t\r\n", i);
				i += 2;
				break;
			case 0x80:
				sprintf(strbuf, "#%04X:\t$CB80\tRES\t0\tB\t\r\n", i);
				i += 2;
				break;
			case 0x81:
				sprintf(strbuf, "#%04X:\t$CB81\tRES\t0\tC\t\r\n", i);
				i += 2;
				break;
			case 0x82:
				sprintf(strbuf, "#%04X:\t$CB82\tRES\t0\tD\t\r\n", i);
				i += 2;
				break;
			case 0x83:
				sprintf(strbuf, "#%04X:\t$CB83\tRES\t0\tE\t\r\n", i);
				i += 2;
				break;
			case 0x84:
				sprintf(strbuf, "#%04X:\t$CB84\tRES\t0\tH\t\r\n", i);
				i += 2;
				break;
			case 0x85:
				sprintf(strbuf, "#%04X:\t$CB85\tRES\t0\tL\t\r\n", i);
				i += 2;
				break;
			case 0x86:
				sprintf(strbuf, "#%04X:\t$CB86\tRES\t0\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x87:
				sprintf(strbuf, "#%04X:\t$CB87\tRES\t0\tA\t\r\n", i);
				i += 2;
				break;
			case 0x88:
				sprintf(strbuf, "#%04X:\t$CB88\tRES\t1\tB\t\r\n", i);
				i += 2;
				break;
			case 0x89:
				sprintf(strbuf, "#%04X:\t$CB89\tRES\t1\tC\t\r\n", i);
				i += 2;
				break;
			case 0x8a:
				sprintf(strbuf, "#%04X:\t$CB8A\tRES\t1\tD\t\r\n", i);
				i += 2;
				break;
			case 0x8b:
				sprintf(strbuf, "#%04X:\t$CB8B\tRES\t1\tE\t\r\n", i);
				i += 2;
				break;
			case 0x8c:
				sprintf(strbuf, "#%04X:\t$CB8C\tRES\t1\tH\t\r\n", i);
				i += 2;
				break;
			case 0x8d:
				sprintf(strbuf, "#%04X:\t$CB8D\tRES\t1\tL\t\r\n", i);
				i += 2;
				break;
			case 0x8e:
				sprintf(strbuf, "#%04X:\t$CB8E\tRES\t1\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x8f:
				sprintf(strbuf, "#%04X:\t$CB8F\tRES\t1\tA\t\r\n", i);
				i += 2;
				break;
			case 0x90:
				sprintf(strbuf, "#%04X:\t$CB90\tRES\t2\tB\t\r\n", i);
				i += 2;
				break;
			case 0x91:
				sprintf(strbuf, "#%04X:\t$CB91\tRES\t2\tC\t\r\n", i);
				i += 2;
				break;
			case 0x92:
				sprintf(strbuf, "#%04X:\t$CB92\tRES\t2\tD\t\r\n", i);
				i += 2;
				break;
			case 0x93:
				sprintf(strbuf, "#%04X:\t$CB93\tRES\t2\tE\t\r\n", i);
				i += 2;
				break;
			case 0x94:
				sprintf(strbuf, "#%04X:\t$CB94\tRES\t2\tH\t\r\n", i);
				i += 2;
				break;
			case 0x95:
				sprintf(strbuf, "#%04X:\t$CB95\tRES\t2\tL\t\r\n", i);
				i += 2;
				break;
			case 0x96:
				sprintf(strbuf, "#%04X:\t$CB96\tRES\t2\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x97:
				sprintf(strbuf, "#%04X:\t$CB97\tRES\t2\tA\t\r\n", i);
				i += 2;
				break;
			case 0x98:
				sprintf(strbuf, "#%04X:\t$CB98\tRES\t3\tB\t\r\n", i);
				i += 2;
				break;
			case 0x99:
				sprintf(strbuf, "#%04X:\t$CB99\tRES\t3\tC\t\r\n", i);
				i += 2;
				break;
			case 0x9a:
				sprintf(strbuf, "#%04X:\t$CB9A\tRES\t3\tD\t\r\n", i);
				i += 2;
				break;
			case 0x9b:
				sprintf(strbuf, "#%04X:\t$CB9B\tRES\t3\tE\t\r\n", i);
				i += 2;
				break;
			case 0x9c:
				sprintf(strbuf, "#%04X:\t$CB9C\tRES\t3\tH\t\r\n", i);
				i += 2;
				break;
			case 0x9d:
				sprintf(strbuf, "#%04X:\t$CB9D\tRES\t3\tL\t\r\n", i);
				i += 2;
				break;
			case 0x9e:
				sprintf(strbuf, "#%04X:\t$CB9E\tRES\t3\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0x9f:
				sprintf(strbuf, "#%04X:\t$CB9F\tRES\t3\tA\t\r\n", i);
				i += 2;
				break;
			case 0xa0:
				sprintf(strbuf, "#%04X:\t$CBA0\tRES\t4\tB\t\r\n", i);
				i += 2;
				break;
			case 0xa1:
				sprintf(strbuf, "#%04X:\t$CBA1\tRES\t4\tC\t\r\n", i);
				i += 2;
				break;
			case 0xa2:
				sprintf(strbuf, "#%04X:\t$CBA2\tRES\t4\tD\t\r\n", i);
				i += 2;
				break;
			case 0xa3:
				sprintf(strbuf, "#%04X:\t$CBA3\tRES\t4\tE\t\r\n", i);
				i += 2;
				break;
			case 0xa4:
				sprintf(strbuf, "#%04X:\t$CBA4\tRES\t4\tH\t\r\n", i);
				i += 2;
				break;
			case 0xa5:
				sprintf(strbuf, "#%04X:\t$CBA5\tRES\t4\tL\t\r\n", i);
				i += 2;
				break;
			case 0xa6:
				sprintf(strbuf, "#%04X:\t$CBA6\tRES\t4\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xa7:
				sprintf(strbuf, "#%04X:\t$CBA7\tRES\t4\tA\t\r\n", i);
				i += 2;
				break;
			case 0xa8:
				sprintf(strbuf, "#%04X:\t$CBA8\tRES\t5\tB\t\r\n", i);
				i += 2;
				break;
			case 0xa9:
				sprintf(strbuf, "#%04X:\t$CBA9\tRES\t5\tC\t\r\n", i);
				i += 2;
				break;
			case 0xaa:
				sprintf(strbuf, "#%04X:\t$CBAA\tRES\t5\tD\t\r\n", i);
				i += 2;
				break;
			case 0xab:
				sprintf(strbuf, "#%04X:\t$CBAB\tRES\t5\tE\t\r\n", i);
				i += 2;
				break;
			case 0xac:
				sprintf(strbuf, "#%04X:\t$CBAC\tRES\t5\tH\t\r\n", i);
				i += 2;
				break;
			case 0xad:
				sprintf(strbuf, "#%04X:\t$CBAD\tRES\t5\tL\t\r\n", i);
				i += 2;
				break;
			case 0xae:
				sprintf(strbuf, "#%04X:\t$CBAE\tRES\t5\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xaf:
				sprintf(strbuf, "#%04X:\t$CBAF\tRES\t5\tA\t\r\n", i);
				i += 2;
				break;
			case 0xb0:
				sprintf(strbuf, "#%04X:\t$CBB0\tRES\t6\tB\t\r\n", i);
				i += 2;
				break;
			case 0xb1:
				sprintf(strbuf, "#%04X:\t$CBB1\tRES\t6\tC\t\r\n", i);
				i += 2;
				break;
			case 0xb2:
				sprintf(strbuf, "#%04X:\t$CBB2\tRES\t6\tD\t\r\n", i);
				i += 2;
				break;
			case 0xb3:
				sprintf(strbuf, "#%04X:\t$CBB3\tRES\t6\tE\t\r\n", i);
				i += 2;
				break;
			case 0xb4:
				sprintf(strbuf, "#%04X:\t$CBB4\tRES\t6\tH\t\r\n", i);
				i += 2;
				break;
			case 0xb5:
				sprintf(strbuf, "#%04X:\t$CBB5\tRES\t6\tL\t\r\n", i);
				i += 2;
				break;
			case 0xb6:
				sprintf(strbuf, "#%04X:\t$CBB6\tRES\t6\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xb7:
				sprintf(strbuf, "#%04X:\t$CBB7\tRES\t6\tA\t\r\n", i);
				i += 2;
				break;
			case 0xb8:
				sprintf(strbuf, "#%04X:\t$CBB8\tRES\t7\tB\t\r\n", i);
				i += 2;
				break;
			case 0xb9:
				sprintf(strbuf, "#%04X:\t$CBB9\tRES\t7\tC\t\r\n", i);
				i += 2;
				break;
			case 0xba:
				sprintf(strbuf, "#%04X:\t$CBBA\tRES\t7\tD\t\r\n", i);
				i += 2;
				break;
			case 0xbb:
				sprintf(strbuf, "#%04X:\t$CBBB\tRES\t7\tE\t\r\n", i);
				i += 2;
				break;
			case 0xbc:
				sprintf(strbuf, "#%04X:\t$CBBC\tRES\t7\tH\t\r\n", i);
				i += 2;
				break;
			case 0xbd:
				sprintf(strbuf, "#%04X:\t$CBBD\tRES\t7\tL\t\r\n", i);
				i += 2;
				break;
			case 0xbe:
				sprintf(strbuf, "#%04X:\t$CBBE\tRES\t7\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xbf:
				sprintf(strbuf, "#%04X:\t$CBBF\tRES\t7\tA\t\r\n", i);
				i += 2;
				break;
			case 0xc0:
				sprintf(strbuf, "#%04X:\t$CBC0\tSET\t0\tB\t\r\n", i);
				i += 2;
				break;
			case 0xc1:
				sprintf(strbuf, "#%04X:\t$CBC1\tSET\t0\tC\t\r\n", i);
				i += 2;
				break;
			case 0xc2:
				sprintf(strbuf, "#%04X:\t$CBC2\tSET\t0\tD\t\r\n", i);
				i += 2;
				break;
			case 0xc3:
				sprintf(strbuf, "#%04X:\t$CBC3\tSET\t0\tE\t\r\n", i);
				i += 2;
				break;
			case 0xc4:
				sprintf(strbuf, "#%04X:\t$CBC4\tSET\t0\tH\t\r\n", i);
				i += 2;
				break;
			case 0xc5:
				sprintf(strbuf, "#%04X:\t$CBC5\tSET\t0\tL\t\r\n", i);
				i += 2;
				break;
			case 0xc6:
				sprintf(strbuf, "#%04X:\t$CBC6\tSET\t0\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xc7:
				sprintf(strbuf, "#%04X:\t$CBC7\tSET\t0\tA\t\r\n", i);
				i += 2;
				break;
			case 0xc8:
				sprintf(strbuf, "#%04X:\t$CBC8\tSET\t1\tB\t\r\n", i);
				i += 2;
				break;
			case 0xc9:
				sprintf(strbuf, "#%04X:\t$CBC9\tSET\t1\tC\t\r\n", i);
				i += 2;
				break;
			case 0xca:
				sprintf(strbuf, "#%04X:\t$CBCA\tSET\t1\tD\t\r\n", i);
				i += 2;
				break;
			case 0xcb:
				sprintf(strbuf, "#%04X:\t$CBCB\tSET\t1\tE\t\r\n", i);
				i += 2;
				break;
			case 0xcc:
				sprintf(strbuf, "#%04X:\t$CBCC\tSET\t1\tH\t\r\n", i);
				i += 2;
				break;
			case 0xcd:
				sprintf(strbuf, "#%04X:\t$CBCD\tSET\t1\tL\t\r\n", i);
				i += 2;
				break;
			case 0xce:
				sprintf(strbuf, "#%04X:\t$CBCE\tSET\t1\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xcf:
				sprintf(strbuf, "#%04X:\t$CBCF\tSET\t1\tA\t\r\n", i);
				i += 2;
				break;
			case 0xd0:
				sprintf(strbuf, "#%04X:\t$CBD0\tSET\t2\tB\t\r\n", i);
				i += 2;
				break;
			case 0xd1:
				sprintf(strbuf, "#%04X:\t$CBD1\tSET\t2\tC\t\r\n", i);
				i += 2;
				break;
			case 0xd2:
				sprintf(strbuf, "#%04X:\t$CBD2\tSET\t2\tD\t\r\n", i);
				i += 2;
				break;
			case 0xd3:
				sprintf(strbuf, "#%04X:\t$CBD3\tSET\t2\tE\t\r\n", i);
				i += 2;
				break;
			case 0xd4:
				sprintf(strbuf, "#%04X:\t$CBD4\tSET\t2\tH\t\r\n", i);
				i += 2;
				break;
			case 0xd5:
				sprintf(strbuf, "#%04X:\t$CBD5\tSET\t2\tL\t\r\n", i);
				i += 2;
				break;
			case 0xd6:
				sprintf(strbuf, "#%04X:\t$CBD6\tSET\t2\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xd7:
				sprintf(strbuf, "#%04X:\t$CBD7\tSET\t2\tA\t\r\n", i);
				i += 2;
				break;
			case 0xd8:
				sprintf(strbuf, "#%04X:\t$CBD8\tSET\t3\tB\t\r\n", i);
				i += 2;
				break;
			case 0xd9:
				sprintf(strbuf, "#%04X:\t$CBD9\tSET\t3\tC\t\r\n", i);
				i += 2;
				break;
			case 0xda:
				sprintf(strbuf, "#%04X:\t$CBDA\tSET\t3\tD\t\r\n", i);
				i += 2;
				break;
			case 0xdb:
				sprintf(strbuf, "#%04X:\t$CBDB\tSET\t3\tE\t\r\n", i);
				i += 2;
				break;
			case 0xdc:
				sprintf(strbuf, "#%04X:\t$CBDC\tSET\t3\tH\t\r\n", i);
				i += 2;
				break;
			case 0xdd:
				sprintf(strbuf, "#%04X:\t$CBDD\tSET\t3\tL\t\r\n", i);
				i += 2;
				break;
			case 0xde:
				sprintf(strbuf, "#%04X:\t$CBDE\tSET\t3\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xdf:
				sprintf(strbuf, "#%04X:\t$CBDF\tSET\t3\tA\t\r\n", i);
				i += 2;
				break;
			case 0xe0:
				sprintf(strbuf, "#%04X:\t$CBE0\tSET\t4\tB\t\r\n", i);
				i += 2;
				break;
			case 0xe1:
				sprintf(strbuf, "#%04X:\t$CBE1\tSET\t4\tC\t\r\n", i);
				i += 2;
				break;
			case 0xe2:
				sprintf(strbuf, "#%04X:\t$CBE2\tSET\t4\tD\t\r\n", i);
				i += 2;
				break;
			case 0xe3:
				sprintf(strbuf, "#%04X:\t$CBE3\tSET\t4\tE\t\r\n", i);
				i += 2;
				break;
			case 0xe4:
				sprintf(strbuf, "#%04X:\t$CBE4\tSET\t4\tH\t\r\n", i);
				i += 2;
				break;
			case 0xe5:
				sprintf(strbuf, "#%04X:\t$CBE5\tSET\t4\tL\t\r\n", i);
				i += 2;
				break;
			case 0xe6:
				sprintf(strbuf, "#%04X:\t$CBE6\tSET\t4\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xe7:
				sprintf(strbuf, "#%04X:\t$CBE7\tSET\t4\tA\t\r\n", i);
				i += 2;
				break;
			case 0xe8:
				sprintf(strbuf, "#%04X:\t$CBE8\tSET\t5\tB\t\r\n", i);
				i += 2;
				break;
			case 0xe9:
				sprintf(strbuf, "#%04X:\t$CBE9\tSET\t5\tC\t\r\n", i);
				i += 2;
				break;
			case 0xea:
				sprintf(strbuf, "#%04X:\t$CBEA\tSET\t5\tD\t\r\n", i);
				i += 2;
				break;
			case 0xeb:
				sprintf(strbuf, "#%04X:\t$CBEB\tSET\t5\tE\t\r\n", i);
				i += 2;
				break;
			case 0xec:
				sprintf(strbuf, "#%04X:\t$CBEC\tSET\t5\tH\t\r\n", i);
				i += 2;
				break;
			case 0xed:
				sprintf(strbuf, "#%04X:\t$CBED\tSET\t5\tL\t\r\n", i);
				i += 2;
				break;
			case 0xee:
				sprintf(strbuf, "#%04X:\t$CBEE\tSET\t5\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xef:
				sprintf(strbuf, "#%04X:\t$CBEF\tSET\t5\tA\t\r\n", i);
				i += 2;
				break;
			case 0xf0:
				sprintf(strbuf, "#%04X:\t$CBF0\tSET\t6\tB\t\r\n", i);
				i += 2;
				break;
			case 0xf1:
				sprintf(strbuf, "#%04X:\t$CBF1\tSET\t6\tC\t\r\n", i);
				i += 2;
				break;
			case 0xf2:
				sprintf(strbuf, "#%04X:\t$CBF2\tSET\t6\tD\t\r\n", i);
				i += 2;
				break;
			case 0xf3:
				sprintf(strbuf, "#%04X:\t$CBF3\tSET\t6\tE\t\r\n", i);
				i += 2;
				break;
			case 0xf4:
				sprintf(strbuf, "#%04X:\t$CBF4\tSET\t6\tH\t\r\n", i);
				i += 2;
				break;
			case 0xf5:
				sprintf(strbuf, "#%04X:\t$CBF5\tSET\t6\tL\t\r\n", i);
				i += 2;
				break;
			case 0xf6:
				sprintf(strbuf, "#%04X:\t$CBF6\tSET\t6\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xf7:
				sprintf(strbuf, "#%04X:\t$CBF7\tSET\t6\tA\t\r\n", i);
				i += 2;
				break;
			case 0xf8:
				sprintf(strbuf, "#%04X:\t$CBF8\tSET\t7\tB\t\r\n", i);
				i += 2;
				break;
			case 0xf9:
				sprintf(strbuf, "#%04X:\t$CBF9\tSET\t7\tC\t\r\n", i);
				i += 2;
				break;
			case 0xfa:
				sprintf(strbuf, "#%04X:\t$CBFA\tSET\t7\tD\t\r\n", i);
				i += 2;
				break;
			case 0xfb:
				sprintf(strbuf, "#%04X:\t$CBFB\tSET\t7\tE\t\r\n", i);
				i += 2;
				break;
			case 0xfc:
				sprintf(strbuf, "#%04X:\t$CBFC\tSET\t7\tH\t\r\n", i);
				i += 2;
				break;
			case 0xfd:
				sprintf(strbuf, "#%04X:\t$CBFD\tSET\t7\tL\t\r\n", i);
				i += 2;
				break;
			case 0xfe:
				sprintf(strbuf, "#%04X:\t$CBFE\tSET\t7\t(HL)\t\r\n", i);
				i += 2;
				break;
			case 0xff:
				sprintf(strbuf, "#%04X:\t$CBFF\tSET\t7\tA\t\r\n", i);
				i += 2;
				break;
			default:
				sprintf(strbuf, "#%04X:\t&%02X%02X\tNOP\r\n", i, binary[i], binary[i+1]);
				i += 2;
				break;
		}
		break;
	case 0xcc:
		sprintf(strbuf, "#%04X:\t$CC%02X%02X\tCALL\tZ\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xcd:
		sprintf(strbuf, "#%04X:\t$CD%02X%02X\tCALL\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xce:
		sprintf(strbuf, "#%04X:\t$CE%02X\tADC\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0xcf:
		sprintf(strbuf, "#%04X:\t$CF\tRST\t8\t\r\n", i);
		i += 1;
		break;
	case 0xd0:
		sprintf(strbuf, "#%04X:\t$D0\tRET\tNC\t\r\n", i);
		i += 1;
		break;
	case 0xd1:
		sprintf(strbuf, "#%04X:\t$D1\tPOP\tDE\t\r\n", i);
		i += 1;
		break;
	case 0xd2:
		sprintf(strbuf, "#%04X:\t$D2%02X%02X\tJP\tNC\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xd4:
		sprintf(strbuf, "#%04X:\t$D4%02X%02X\tCALL\tNC\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xd5:
		sprintf(strbuf, "#%04X:\t$D5\tPUSH\tDE\t\r\n", i);
		i += 1;
		break;
	case 0xd6:
		sprintf(strbuf, "#%04X:\t$D6%02X\tSUB\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0xd7:
		sprintf(strbuf, "#%04X:\t$D7\tRST\t16\t\r\n", i);
		i += 1;
		break;
	case 0xd8:
		sprintf(strbuf, "#%04X:\t$D8\tRET\tC\t\r\n", i);
		i += 1;
		break;
	case 0xd9:
		sprintf(strbuf, "#%04X:\t$D9\tRETI\t\r\n", i);
		i += 1;
		break;
	case 0xda:
		sprintf(strbuf, "#%04X:\t$DA%02X%02X\tJP\tC\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xdc:
		sprintf(strbuf, "#%04X:\t$DC%02X%02X\tCALL\tC\t$%02X%02X\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xde:
		sprintf(strbuf, "#%04X:\t$DE%02X\tSBC\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0xdf:
		sprintf(strbuf, "#%04X:\t$DF\tRST\t24\t\r\n", i);
		i += 1;
		break;
	case 0xe0:
		sprintf(strbuf, "#%04X:\t$E0%02X\tLDH\t(%02X)\tA\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0xe1:
		sprintf(strbuf, "#%04X:\t$E1\tPOP\tHL\t\r\n", i);
		i += 1;
		break;
	case 0xe2:
		sprintf(strbuf, "#%04X:\t$E2\tLDH\t(C)\tA\t\r\n", i);
		i += 1;
		break;
	case 0xe5:
		sprintf(strbuf, "#%04X:\t$E5\tPUSH\tHL\t\r\n", i);
		i += 1;
		break;
	case 0xe6:
		sprintf(strbuf, "#%04X:\t$E6%02X\tAND\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0xe7:
		sprintf(strbuf, "#%04X:\t$E7\tRST\t32\t\r\n", i);
		i += 1;
		break;
	case 0xe8:
		scconverter = (signed)binary[i+1];
		sprintf(strbuf, "#%04X:\t$E8%02X\tADD\tSP\t$%+02d\t\r\n", i, binary[i+1], scconverter);
		i += 2;
		break;
	case 0xe9:
		sprintf(strbuf, "#%04X:\t$E9\tLD\tPC\tHL\t\r\n", i);
		i += 1;
		break;
	case 0xea:
		sprintf(strbuf, "#%04X:\t$EA%02X%02X\tLD\t(%02X%02X)\tA\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xed:
		sprintf(strbuf, "#%04X:\t$ED\tNOP\t\r\n", i);
		i += 1;
		break;
	case 0xee:
		sprintf(strbuf, "#%04X:\t$EE%02X\tXOR\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0xef:
		sprintf(strbuf, "#%04X:\t$EF\tRST\t40\t\r\n", i);
		i += 1;
		break;
	case 0xf0:
		sprintf(strbuf, "#%04X:\t$F0%02X\tLDH\tA\t(%02X)\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0xf1:
		sprintf(strbuf, "#%04X:\t$F1\tPOP\tAF\t\r\n", i);
		i += 1;
		break;
	case 0xf2:
		sprintf(strbuf, "#%04X:\t$F2\tLDH\tA\t(C)\t\r\n", i);
		i += 1;
		break;
	case 0xf3:
		sprintf(strbuf, "#%04X:\t$F3\tDI\t\r\n", i);
		i += 1;
		break;
	case 0xf5:
		sprintf(strbuf, "#%04X:\t$F5\tPUSH\tAF\t\r\n", i);
		i += 1;
		break;
	case 0xf6:
		sprintf(strbuf, "#%04X:\t$F6%02X\tOR\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0xf7:
		sprintf(strbuf, "#%04X:\t$F7\tRST\t48\t\r\n", i);
		i += 1;
		break;
	case 0xf8:
		scconverter = (signed)binary[i+1];
		sprintf(strbuf, "#%04X:\t$F8%02X\tLD\tHL\t$%+02d\t\r\n", i, binary[i+1], scconverter);
		i += 2;
		break;
	case 0xf9:
		sprintf(strbuf, "#%04X:\t$F9\tLD\tSP\tHL\t\r\n", i);
		i += 1;
		break;
	case 0xfa:
		sprintf(strbuf, "#%04X:\t$FA%02X%02X\tLD\tA\t(%02X%02X)\t\r\n", i, binary[i+1], binary[i+2], binary[i+1+1], binary[i+1]);
		i += 3;
		break;
	case 0xfb:
		sprintf(strbuf, "#%04X:\t$FB\tEI\t\r\n", i);
		i += 1;
		break;
	case 0xfe:
		sprintf(strbuf, "#%04X:\t$FE%02X\tCP\t$%02X\t\r\n", i, binary[i+1], binary[i+1]);
		i += 2;
		break;
	case 0xff:
		sprintf(strbuf, "#%04X:\t$FF\tRST\t56\t\r\n", i);
		i += 1;
		break;
	default:
		sprintf(strbuf, "#%04X:\t&%02X\tNOP\t\r\n", i, binary[i]);
		i += 1;
		break;
}
