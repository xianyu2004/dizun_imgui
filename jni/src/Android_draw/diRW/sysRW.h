#ifndef sysRW_H
#define sysRW_H

#include "mainRW.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <malloc.h>
#include <math.h>
#include <thread>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <locale>
#include <string>
#include <codecvt>
#include <dlfcn.h>


class sysRW : public mainRW
{
public:
sysRW(int pid);
bool readv(uintptr_t address, void *buffer, size_t size);
bool writev(uintptr_t address, void *buffer, size_t size);


protected:
int process_vm_readv_syscall;
int process_vm_writev_syscall;
ssize_t process_v(pid_t __pid, const struct iovec *__local_iov, unsigned long __local_iov_count,const struct iovec *__remote_iov, unsigned long __remote_iov_count,unsigned long __flags, bool iswrite);
bool pvm(void *address, void *buffer, size_t size, bool iswrite);


};

#endif