#ifndef KERNELRW_HPP
#define KERNELRW_HPP


#include "mainRW.h"
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>



class kernelRW : public mainRW
{

	protected:
	int fd;
	const char* DEVICE_PATH;


public:
kernelRW(int pid);
bool readv(uintptr_t address, void *buffer, size_t size);
bool writev(uintptr_t address, void *buffer, size_t size);


};

#endif