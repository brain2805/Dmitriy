#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 16

///using namespace std;

void print_error(const char * str)
{
    int len = 0;
    while (str[len++]);

    write(2, str, len);
    _exit(1);
}

int main(int argc, char ** argv)
{
    int fd1, fd2;
    char buf[BUFSIZE];
    if (argc != 3)
        print_error("Usage: cp prom to");
    if ((fd1 = open(argv[1], O_RDONLY)) == -1)
        print_error("cp: can't open fromfile");
    if ((fd2 = open(argv[2], O_WRONLY | O_CREAT)) == -1)
        print_error("cp: can't open tofile");

    int readcnt;
    int writecnt;

    do
    {
        readcnt = read(fd1, buf, BUFSIZE);
        if (readcnt > 0)
        {
            writecnt = write(fd2, buf, BUFSIZE);
            if (readcnt != writecnt)
            {
                close(fd1);
                close(fd2);
                print_error("read-write problem");
            }
        }
        else if (readcnt < 0)
        {
            close(fd1);
            close(fd2);
            print_error("read-write problem");
        }
    } while (readcnt);


    close(fd1);
    close(fd2);
    return 0;
}
