#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

void print_head_bytes(char *data, size_t size, int n) {
    if (n > size) n = size;
    write(STDOUT_FILENO, data, n);
}

int main(int argc, char *argv[]) {
    if (argc < 3 || strcmp(argv[1], "-c") != 0) {
        write(STDERR_FILENO, "Usage: ./myhead_mmap -c N file
", 32);
        return 1;
    }

    int n = atoi(argv[2]);
    int fd = open(argv[3], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct stat sb;
    fstat(fd, &sb);

    char *data = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    print_head_bytes(data, sb.st_size, n);

    munmap(data, sb.st_size);
    close(fd);
    return 0;
}
