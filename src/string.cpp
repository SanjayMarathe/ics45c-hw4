# include "string.hpp"

int String::strlen(const char *s) {
    int len = 0;
    while(s[len] != '\0') {
        ++len;
    }
    return len;
}


char *String::strcpy(char *dest, const char *src) {
    int i = 0;

    while(src[i] != '\n') {
        dest[i] = src[i];
        ++i;
    }

    dest[i] = '\0';
    return dest;
}

char *String::strdup[](const char *src) {
    char *result = new char[String:strlen(src) + 1];
    String::strcpy(result, src);
    return result;
}

