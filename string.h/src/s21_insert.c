#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *s = NULL;
    if (src && str) { s21_size_t len_src = s21_strlen(src);
        s21_size_t len_str = s21_strlen(str);
        if (start_index > len_src) { s = NULL;
        } else if (len_str == 0) { s = (char*)src;
        } else { s21_size_t new_len = len_src + len_str;
            s = (char *)malloc((new_len + 1) * sizeof(char));
            s21_size_t x = 0;  // src couner
            s21_size_t y = 0;  // str counter
            s21_size_t i = 0;
            while (i < new_len) { if (i < start_index) { while (i < start_index) {
                        s[i] = src[i];
                        i++;
                    }
                    x = i;
                } else if (i == start_index) { while (y < len_str) {
                        s[i] = str[y];
                        i++;
                        y++;
                    }
                } else { while (x < len_src) {
                        s[i] = src[x];
                        x++;
                        i++;
                    }
                }
            }
            s[i] = '\0';
        }
    }
    return (void *)s;
}
