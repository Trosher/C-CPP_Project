#include <stdio.h>
#include <ctype.h>
#include <getopt.h>

void s21_cat(int argc, char **path_flag);
int cat_flag_pars(int argc, char **path_flag);
void cat_print(FILE *file);

/*
        index 0 = b нумерует только непустые строки
        index 1 = e также отображает символы конца строки как $
        index 2 = n нумерует все выходные строки
        index 3 = s сжимает несколько смежных пустых строк
        index 4 = t также отображает табы как ^I
        index 5 = v печать непечатаемых символов
*/
int flag_target[] = {0, 0, 0, 0, 0, 0};

int main(int argc, char* argv[]) {
    if (argc) {
        if (argv[1]) { s21_cat(argc, argv); }
    }
    return 0;
}

void s21_cat(int argc, char **path_flag) {
    int error_target = 0;
    error_target = cat_flag_pars(argc, path_flag);
    if (error_target == 0) {
        FILE *file = NULL;
        path_flag += optind;
        for (; *path_flag != NULL; path_flag++) {
            if (!(file = fopen(*path_flag, "r"))) {
                printf("s21_cat: %s No such file or directory ", *path_flag);
            } else { cat_print(file);
            fclose(file);
            }
        }
    } else { printf("usage: %s [-f or --flag] [file ...]\n:", path_flag[0]);
        printf("All available flags: \n");
        printf("[-b -e -E -n -s -t -T -v or -benstv --number-nonblank --number --squeeze-blank]");
    }
}

int cat_flag_pars(int argc, char **path_flag) {
    int target_error = 0;
    static struct option long_options[] = {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank", 0, 0, 's'},
        {0, 0, 0, 0}
    };
    while (!target_error) {
        int char_buf_flag;
        char_buf_flag = getopt_long(argc, path_flag, "beEnstTv", long_options, NULL);
        if (char_buf_flag == -1) {
            break;
        } else {
            if (char_buf_flag == 'b') { flag_target[0] = flag_target[2] = 1;
            } else if (char_buf_flag == 'e') { flag_target[1] = flag_target[5] = 1;
            } else if (char_buf_flag == 'E') { flag_target[1] = 1;
            } else if (char_buf_flag == 'n') { flag_target[2] = 1;
            } else if (char_buf_flag == 's') { flag_target[3] = 1;
            } else if (char_buf_flag == 't') { flag_target[4] = flag_target[5] = 1;
            } else if (char_buf_flag == 'T') { flag_target[4] = 1;
            } else if (char_buf_flag == 'v') { flag_target[5] = 1;
            } else if (char_buf_flag == '?') {
            } else { target_error = 1; }
        }
    }
    return target_error;
}

void cat_print(FILE *file) {
    int last_char, char_buffer, str_void_target = 0;
    long unsigned line = 0;
    for (last_char = '\n'; (char_buffer = getc(file)) != EOF; last_char = char_buffer) {
        if (last_char == '\n') {
            if (flag_target[3]) {
                if (char_buffer == '\n') {
                    if (str_void_target) { continue; }
                str_void_target = 1;
                } else { str_void_target = 0; }
            }
            if (flag_target[2]) {
                 if (!flag_target[0] || char_buffer != '\n') { printf("%6lu\t", ++line); }
            }
        }
        if (char_buffer == '\n') { if (flag_target[1]) { printf("$"); }
        } else if (char_buffer == '\t') { if (flag_target[4]) { printf("^I");
                continue;
            }
        } else if (flag_target[5]) {
            if (iscntrl(char_buffer)) { printf("^%c", char_buffer == '\177' ? '?' : char_buffer | 0100);
                continue;
            }
        }
        printf("%c", char_buffer);
        }
}
