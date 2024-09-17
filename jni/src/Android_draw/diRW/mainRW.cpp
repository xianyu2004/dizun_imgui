#include "mainRW.h"

mainRW::mainRW(int pid)
{
this->pid = pid;
}

int mainRW::getProcessPid()
{
return this->pid;
}

//获取F类型
float mainRW::getFloat(uintptr_t addr)
{
	float var = 0;
	readv(addr,&var,4);
	return(var);
}

// 获取D类内存
int mainRW::getDword(uintptr_t addr)
{
	int var = 0;
	readv(addr,&var,4);
	return(var);
}

bool mainRW::getBool(uintptr_t addr)
{
	bool var = false;
	readv(addr,&var,1);
	return(var);
}

// 获取指针(32位游戏)
uintptr_t mainRW::getPtr32(uintptr_t addr)
{
	unsigned int var = 0;
	readv(addr&0xFFFFFFFFFF,&var,4);
	return(var&0xFFFFFFFFFF);
}

// 获取指针(64位游戏)
uintptr_t mainRW::getPtr64(uintptr_t addr)
{
	uintptr_t var = 0;
	readv(addr&0xFFFFFFFFFF,&var,8);
	return(var&0xFFFFFFFFFF);
}

//获取字符串
char* mainRW::getUTF8(uintptr_t addr)
{
	static char buf[64];
	//不支持多次读写
	unsigned short buf16[16] = { 0 };
	readv(addr, buf16, 28);
	unsigned short *pTempUTF16 = buf16;
	char *pTempUTF8 = buf;
	char *pUTF8End = pTempUTF8 + 32;
	while (pTempUTF16 < pTempUTF16 + 28)
	{
		if (*pTempUTF16 <= 0x007F && pTempUTF8 + 1 < pUTF8End)
		{
			*pTempUTF8++ = (char) * pTempUTF16;
		}
		else if (*pTempUTF16 >= 0x0080 && *pTempUTF16 <= 0x07FF && pTempUTF8 + 2 < pUTF8End)
		{
			*pTempUTF8++ = (*pTempUTF16 >> 6) | 0xC0;
			*pTempUTF8++ = (*pTempUTF16 & 0x3F) | 0x80;
		}
		else if (*pTempUTF16 >= 0x0800 && *pTempUTF16 <= 0xFFFF && pTempUTF8 + 3 < pUTF8End)
		{
			*pTempUTF8++ = (*pTempUTF16 >> 12) | 0xE0;
			*pTempUTF8++ = ((*pTempUTF16 >> 6) & 0x3F) | 0x80;
			*pTempUTF8++ = (*pTempUTF16 & 0x3F) | 0x80;
		}
		else
		{
			break;
		}
		pTempUTF16++;
	}
	return buf;
}

// 写入F类内存
bool mainRW::writeFloat(uintptr_t addr,float data)
{
	return writev(addr,&data,4);
}

