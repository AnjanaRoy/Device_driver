#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    fd=open("/dev/Sample0",O_RDWR);
    if(fd<0)
    {
        perror("Error opening\n");
        return fd;
    }
    return 0;
}