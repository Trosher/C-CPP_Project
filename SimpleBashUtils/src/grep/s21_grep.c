#include "s21_grep.h"

void grep_flag(int const *flag_target, const char *buffer,
                char *flag_buf, int const index_str);
void s21_grep(const char **path_flag, int argc);
int grep_flag_pars(int *flag_target, const char **path_flag,
                    int *index, struct node *filter, char *buffer);
void my_grep(int argc, int const *flag_target, const char **path,
            int index, struct node *filter);
void oh_my_grep(int const *flag_target, const char **path, struct node *filter,
                FILE *file, int i, int index, int argc);
void oh_my_grep_o(int const *flag_target, const char **path, struct node *filter,
                  FILE *file, int i, int index, int argc);
void file_str_count(int const *flag_target, const char **path, struct node *filter,
                    FILE *file, int i, int index, int argc);
void print_o(long long int start, long long int finish, char *str);
void path_to_filter(const char **path_flag, int **index, char *head);
void file_str_count_o(int const *flag_target, const char **path, struct node *filter, FILE *file,
                    int i, int index, int argc);

int main(int argc, const char* argv[]) {
    if (argv[1]) { s21_grep(argv, argc); }
    return 0;
}

void s21_grep(const char **path_flag, int argc) {
    /*
        index 0 = e Шаблон (Работает как флаг f только с шаблоном) *
        index 1 = i Игнорирует различия регистра. *
        index 2 = v Инвертирует смысл поиска соответствий. (Находит всё кромме вдедёного) *
        index 3 = c Выводит только количество совпадающих строк. *
        index 4 = l Выводит только совпадающие файлы. (Их название) *
        index 5 = n Предваряет каждую строку вывода номером строки из файла ввода. *
        (Добавляет имя файла без пробела перед найденой строкой, и номер строки в файле) *
        index 6 = h Выводит совпадающие строки, не предваряя их именами файлов.  *
        index 7 = s Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах. *
        index 8 = f file Получает регулярные выражения из файла. *
        index 9 = o Печатает только совпадающие (непустые) части совпавшей строки
    */
    int flag_target[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, error_target = 0, index = 1, crutch = 0;
    char buffer[600];
    struct node *rot = init();
    error_target = grep_flag_pars(flag_target, path_flag, &index, rot, buffer);
    if (flag_target[9] == 1) {
        rot = rot -> next;
        while (!error_target) {
            if (rot -> value[0] == '.' && !rot->value[1]) { crutch = 1; }
            if (rot -> next) { rot = rot->next;
            } else { error_target = 1; }
        }
        error_target = 0;
    }
    rot = rot -> start;
    rot = rot -> next;
    if (error_target == 0 && !crutch) { my_grep(argc, flag_target, path_flag, index, rot); }
    destroy(rot -> start);
}

void my_grep(int argc, int const *flag_target, const char **path, const int index, struct node *filter) {
    for (int i = index; path[i]; ++i) {
        FILE *file;
        if ((file = fopen(path[i], "r"))) {
            if (flag_target[9] == 1) {
                if (flag_target[3] == 1 || flag_target[4]) {
                    file_str_count_o(flag_target, path, filter, file, i, index, argc);
                } else { oh_my_grep_o(flag_target, path, filter, file, i, index, argc); }
            } else {
                if (flag_target[3] == 1 || flag_target[4]) {
                    file_str_count(flag_target, path, filter, file, i, index, argc);
                } else { oh_my_grep(flag_target, path, filter, file, i, index, argc); }
            }
            fclose(file);
        } else { if (flag_target[7] != 1) { printf("s21_grep: %s: No such file or directory\n", path[i]); } }
    }
}

void oh_my_grep(int const *flag_target, const char **path, struct node *filter, FILE *file,
                int i, int index, int argc) {
    int str_caunt = 1, target = 0;
    char buffer[600];
    while (fgets(buffer, 600, file)) {
        while (!target) { regex_t preg;
            int regerr = 0;
            if (flag_target[1] != 1) { regcomp (&preg, filter -> value, REG_EXTENDED);
            } else { regcomp(&preg, filter -> value, REG_ICASE); }
            regmatch_t pm;
            regerr = regexec(&preg, buffer, 0, &pm, 0);
            if (regerr == 0 && flag_target[2] != 1) {
                if (flag_target[6] != 1 && argc - index > 1) { printf("%s:", path[i]); }
                if (flag_target[5] == 1) { printf("%d:", str_caunt); }
                printf("%s", buffer);
                target = 1;
            } else if (regerr != 0 && flag_target[2] == 1 && !filter -> next) {
                if (flag_target[6] != 1 && argc - index > 1) { printf("%s:", path[i]); }
                if (flag_target[5] == 1) { printf("%d:", str_caunt); }
                    printf("%s", buffer);
                    target = 1;
            } else if (regerr == 0 && flag_target[2] == 1) { target = 1; }
            if (!filter -> next) { target = 1;
            } else { filter = filter -> next; }
            regfree(&preg);
        }
        filter = filter -> start;
        filter = filter -> next;
        target = 0;
        str_caunt += 1;
    }
}

void file_str_count(int const *flag_target, const char **path, struct node *filter, FILE *file,
                    int i, int index, int argc) { int str_caunt = 0, target = 0;
    char buffer[600];
    while (fgets(buffer, 600, file)) { while (!target) {
            int regerr = 0;
            regex_t preg;
            if (flag_target[1] != 1) { regcomp (&preg, filter -> value, REG_EXTENDED);
            } else { regcomp(&preg, filter -> value, REG_ICASE); }
            regmatch_t pm;
            regerr = regexec(&preg, buffer, 1, &pm, 0);
            if (regerr == 0 && flag_target[2] != 1) { ++str_caunt;
                target = 1;
            } else if (regerr != 0 && flag_target[2] == 1) {
                if (!filter -> next) { ++str_caunt; }
            } else if (!(regerr != 0 && flag_target[2] != 1)) { target = 1; }
            if (!filter -> next) { target = 1; }
            if (!target) { filter = filter -> next; }
            regfree(&preg);
        }
        filter = filter -> start;
        filter = filter -> next;
        target = 0;
    }
    if (flag_target[4] == 1) { if (flag_target[3] == 1) {
                if (flag_target[6] == 1 || argc - index < 2) {
                    printf("%d\n", str_caunt > 0 ? 1 : 0);
                    str_caunt > 0 ? printf("%s\n", path[i]) : 0;
                } else {
                    printf("%s:%d\n", path[i], str_caunt > 0 ? 1 : 0);
                    str_caunt > 0 ? printf("%s\n", path[i]) : 0;
                }
            } else { str_caunt > 0 ? printf("%s\n", path[i]) : 0; }
    } else if (flag_target[3] == 1) {
        if (flag_target[6] == 1 || argc - index == 1) { printf("%d\n", str_caunt);
        } else { printf("%s:%d\n", path[i], str_caunt); } }
}

void oh_my_grep_o(int const *flag_target, const char **path, struct node *filter, FILE *file,
                int i, int index, int argc) {
    int str_caunt = 1, target = 0;
    char buffer[600];
    while (fgets(buffer, 600, file)) { char *p_buf = buffer;
        int v_target = 0;
        if (buffer[0] == EOF) break;
        while (!target) { regex_t preg;
            int regerr = 0;
            int target_lup = 0;
            if (flag_target[1] != 1) { regcomp(&preg, filter -> value, REG_EXTENDED);
            } else { regcomp(&preg, filter -> value, REG_ICASE); }
            regmatch_t pm;
            while (!regerr && *p_buf && flag_target[2] != 1) { regerr = regexec(&preg, p_buf, 1, &pm, 0);
                if (!regerr) {
                    if ((flag_target[6] != 1 && argc - index > 1) && !target_lup) { printf("%s:", path[i]);
                    if (!flag_target[5]) { target_lup = 1; } }
                    if (flag_target[5] == 1 && !target_lup) { printf("%d:", str_caunt);
                    target_lup = 1; }
                    print_o(pm.rm_so, pm.rm_eo, p_buf);
                    p_buf += pm.rm_eo;
                } }
            while (flag_target[2] == 1 && !v_target) { regerr = regexec(&preg, p_buf, 1, &pm, 0);
                if (regerr && filter -> next) {
                    filter = filter -> next;
                    regfree(&preg);
                    if (flag_target[1] != 1) { regcomp(&preg, filter -> value, REG_EXTENDED);
                    } else { regcomp(&preg, filter -> value, REG_ICASE); }
                } else if (!regerr) { v_target = 1;
                } else { if ((flag_target[6] != 1 && argc - index > 1) && !target_lup) {
                    printf("%s:", path[i]);
                    if (!flag_target[5]) { target_lup = 1; } }
                    if (flag_target[5] == 1 && !target_lup) { printf("%d:", str_caunt);
                    target_lup = 1; }
                    printf("%s", p_buf);
                    v_target = 1; }
            }
            if (!filter -> next || !*p_buf || v_target) { target = 1;
            } else { filter = filter -> next; }
            regfree(&preg);
        }
        filter = filter -> start;
        filter = filter -> next;
        target = 0;
        str_caunt += 1;
    }
}

void file_str_count_o(int const *flag_target, const char **path, struct node *filter, FILE *file,
                    int i, int index, int argc) {
    int str_caunt = 0, target = 0;
    char buffer[600];
    while (fgets(buffer, 600, file)) { char *p_buf = buffer;
        int v_target = 0;
        while (!target) { regex_t preg;
            int regerr = 0;
            if (flag_target[1] != 1) { regcomp(&preg, filter -> value, REG_EXTENDED);
            } else { regcomp(&preg, filter -> value, REG_ICASE); }
            regmatch_t pm;
            while (!regerr && *p_buf && flag_target[2] != 1) { regerr = regexec(&preg, p_buf, 1, &pm, 0);
                if (!regerr) { str_caunt += 1;
                    regerr = 1;
                } }
            while (flag_target[2] == 1 && !v_target) { regerr = regexec(&preg, p_buf, 1, &pm, 0);
                if (regerr && filter -> next) { filter = filter -> next;
                    regfree(&preg);
                    if (flag_target[1] != 1) { regcomp (&preg, filter -> value, REG_EXTENDED);
                    } else { regcomp(&preg, filter -> value, REG_ICASE); }
                } else if (!regerr) { v_target = 1;
                } else { str_caunt += 1;
                    v_target = 1; }
            }
            if (!filter -> next || !*p_buf || v_target) { target = 1;
            } else { filter = filter -> next; }
            regfree(&preg);
        }
        filter = filter -> start;
        filter = filter -> next;
        target = 0;
    }
    if (flag_target[4] == 1) { if (flag_target[3] == 1) {
                if (flag_target[6] == 1 || argc - index < 2) { printf("%d\n", str_caunt > 0 ? 1 : 0);
                    str_caunt > 0 ? printf("%s\n", path[i]) : 0;
                } else { printf("%s:%d\n", path[i], str_caunt > 0 ? 1 : 0);
                    str_caunt > 0 ? printf("%s\n", path[i]) : 0;
                }
            } else { str_caunt > 0 ? printf("%s\n", path[i]) : 0; }
    } else if (flag_target[3] == 1) {
        if (flag_target[6] == 1 || argc - index == 1) { printf("%d\n", str_caunt);
        } else { printf("%s:%d\n", path[i], str_caunt); } }
}

int grep_flag_pars(int *flag_target, const char **path_flag,
                    int *index, struct node *filter, char *buffer) {
    int target_error = 0, target_flag_f = 0, target_f = 0;
    const char* Bufer_f;
    if (path_flag[*index][0] != '-') {
        Bufer_f = path_flag[*index];
        *index += 1;
        target_f = 1;
    }

    for (int i = 1; path_flag[*index][0] == '-' && path_flag[*index]; ++i) {
        if (path_flag[*index][i] == 'e') { flag_target[0] = 1;
            *index += 1;
            filter = add_list(filter, path_flag[*index]);
            *index += 1;
            i = 0;
        } else if (path_flag[*index][i] == 'i') { flag_target[1] = 1;
        } else if (path_flag[*index][i] == 'v') { flag_target[2] = 1;
        } else if (path_flag[*index][i] == 'c') { flag_target[3] = 1;
        } else if (path_flag[*index][i] == 'l') { flag_target[4] = 1;
        } else if (path_flag[*index][i] == 'n') { flag_target[5] = 1;
        } else if (path_flag[*index][i] == 'h') { flag_target[6] = 1;
        } else if (path_flag[*index][i] == 's') { flag_target[7] = 1;
        } else if (path_flag[*index][i] == 'f') { flag_target[8] = 1;
            FILE *file;
            *index += 1;
            if ((file = fopen(path_flag[*index], "r"))) {
                while (fgets(buffer, 600, file)) {;}
                filter = add_list(filter, buffer);
                *index += 1;
                fclose(file);
            }  else { if (flag_target[7] != 1) {
                printf("s21_grep: %s: No such file or directory\n", path_flag[*index]); }
                target_error = 1;
                *index += 1;
            }
        } else if (path_flag[*index][i] == 'o') { flag_target[9] = 1;
        } else if (i == 1) { if (flag_target[7] != 1) {
            printf("grep: invalid option -- '%c'\n", path_flag[*index][i]); }
            target_error = 1;
            break;
        } else { i = 0;
            *index += 1;
            continue; }
        if (!path_flag[*index][i + 1]) { i = 0;
            if (1 == target_flag_f) { *index += 2;
                target_flag_f = 0;
            } else { *index += 1; } } }
    if (flag_target[8] != 1 && flag_target[0] != 1 && !target_f) {
        filter = add_list(filter, path_flag[*index]);
        filter -> value = path_flag[*index];
        *index += 1;
    } else if (flag_target[8] != 1 && flag_target[0] != 1 && target_f) { filter = add_list(filter, Bufer_f);
        filter -> value = Bufer_f;
    }
    if ((flag_target[8] || flag_target[0]) && target_f) {
        printf("s21_grep: %s: No such file or directory\n", Bufer_f);
    }
    return target_error;
}

void print_o(long long int start, long long int finish, char *str) {
    for (long long int i = start; i < finish; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}
