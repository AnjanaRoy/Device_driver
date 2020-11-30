#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 16

int main()
{
    int fd,rt;
    char buffW[]= "fromuser";
    fd=open("/dev/Sample0",O_RDWR);
    if(fd<0)
    {
        perror("Error opening\n");
        return fd;
    }

    rt = write(fd, buffW, sizeof(buffW));

    printf("write bytes form kernel is :%d\n",rt);

    return 0;
}