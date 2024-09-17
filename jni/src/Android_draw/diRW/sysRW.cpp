#include "sysRW.h"


sysRW::sysRW(int pid) : mainRW(pid)
{
this->process_vm_readv_syscall = 270;
this->process_vm_writev_syscall = 271;
}

// 读取内存
bool sysRW::readv(uintptr_t address,void*buffer,size_t size)
{
	return pvm(reinterpret_cast<void*>(address),buffer,size,false);
}

// 写入内存
bool sysRW::writev(uintptr_t address,void*buffer,size_t size)
{
	return pvm(reinterpret_cast<void*>(address),buffer,size,true);
}


ssize_t sysRW::process_v(pid_t __pid,const struct iovec*__local_iov,uintptr_t __local_iov_count,
	const struct iovec*__remote_iov,uintptr_t __remote_iov_count,
	uintptr_t __flags,bool iswrite)
{
	return syscall((iswrite?process_vm_writev_syscall:process_vm_readv_syscall),__pid,
		__local_iov,__local_iov_count,__remote_iov,__remote_iov_count,__flags);
}

bool sysRW::pvm(void*address,void*buffer,size_t size,bool iswrite)
{
	struct iovec local[1];
	struct iovec remote[1];
	local[0].iov_base = buffer;
	local[0].iov_len = size;
	remote[0].iov_base = address;
	remote[0].iov_len = size;
	if(pid<0)
	{
		return false;
	}
	ssize_t bytes = process_v(pid,local,1,remote,1,0,iswrite);
	return bytes==size;
}
