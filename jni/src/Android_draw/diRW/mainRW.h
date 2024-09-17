#ifndef mainRW_H
#define mainRW_H

#include <iostream>


class mainRW{
friend class sysRW;
friend class kernelRW;

protected:
mainRW(int pid);

private:
int pid;

public:
virtual bool readv(uintptr_t address, void *buffer, size_t size) = 0;//子类需要重写
virtual bool writev(uintptr_t address, void *buffer, size_t size) = 0;//子类需要重写
int getProcessPid();
float getFloat(uintptr_t addr);
int getDword(uintptr_t addr);
bool getBool(uintptr_t addr);
char* getUTF8(uintptr_t addr);
uintptr_t getPtr64(uintptr_t addr);
uintptr_t getPtr32(uintptr_t addr);
bool writeFloat(uintptr_t addr,float data);
};




#endif