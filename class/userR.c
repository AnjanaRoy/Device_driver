#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 16

int main()
{
    int fd,rt;
    char buffR[SIZE];
    fd=open("/dev/Sample0",O_RDWR);
    if(fd<0)
    {
        perror("Error opening\n");
        return fd;
    }

    rt=read(fd, buffR, SIZE);

    printf("read bytes form kernel is :%d\n",rt);

    close(fd);
    return 0;
}