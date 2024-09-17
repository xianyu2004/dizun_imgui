#include "kernelRW.h"

    struct COPY_MEMORY {
        pid_t pid;
        uintptr_t addr;
        void* buffer;
        size_t size;
    };

    struct MODULE_BASE {
        pid_t pid;
        char* name;
        uintptr_t base;
    };

kernelRW::kernelRW(int pid) : mainRW(pid)
{
DEVICE_PATH = "/proc/version_debug";
fd = open(DEVICE_PATH, O_WRONLY);
if (fd == -1) {
printf("[-] 请先正确安装内核\n");
exit(1);
   }
}

bool kernelRW::readv(uintptr_t address, void *buffer, size_t size)
{
	COPY_MEMORY cm;
        cm.pid = this->pid;
        cm.addr = address;
        cm.buffer = buffer;
        cm.size = size;
        if (write(fd, &cm, sizeof(COPY_MEMORY)) != 0) {
            return false;
        }
        return true;
}

    bool kernelRW::writev(uintptr_t address, void *buffer, size_t size)
    {
		COPY_MEMORY cm;
        cm.pid = this->pid;
        cm.addr = address;
        cm.buffer = buffer;
        cm.size = size;
        if (write(fd, &cm, sizeof(COPY_MEMORY)) != 0) {
            return false;
        }
        return true;
}