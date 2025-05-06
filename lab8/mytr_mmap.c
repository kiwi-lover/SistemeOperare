#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        write(STDERR_FILENO, "Usage: ./mytr_mmap <input> <output> <from> <to>\n", 49);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], argv[2]) == 0) {
        write(STDERR_FILENO, "Input and output file must be different\n", 40);
        exit(EXIT_FAILURE);
    }

    int fd_input = open(argv[1], O_RDONLY);
    if (fd_input < 0) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (fstat(fd_input, &sb) == -1) {
        perror("Error getting file size");
        close(fd_input);
        exit(EXIT_FAILURE);
    }

    char *input_data = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd_input, 0);
    if (input_data == MAP_FAILED) {
        perror("Error mapping input file to memory");
        close(fd_input);
        exit(EXIT_FAILURE);
    }

    int fd_output = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd_output < 0) {
        perror("Error opening output file");
        munmap(input_data, sb.st_size);
        close(fd_input);
        exit(EXIT_FAILURE);
    }

    if (ftruncate(fd_output, sb.st_size) == -1) {
        perror("Error setting output file size");
        munmap(input_data, sb.st_size);
        close(fd_input);
        close(fd_output);
        exit(EXIT_FAILURE);
    }

    char *output_data = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_output, 0);
    if (output_data == MAP_FAILED) {
        perror("Error mapping output file to memory");
        munmap(input_data, sb.st_size);
        close(fd_input);
        close(fd_output);
        exit(EXIT_FAILURE);
    }

    char *from = argv[3];
    char *to = argv[4];

    for (off_t i = 0; i < sb.st_size; ++i) {
        char c = input_data[i];
        for (size_t j = 0; from[j] && to[j]; ++j) {
            if (c == from[j]) {
                c = to[j];
                break;
            }
        }
        output_data[i] = c;
    }

    munmap(input_data, sb.st_size);
    munmap(output_data, sb.st_size);
    close(fd_input);
    close(fd_output);
    return 0;
}
