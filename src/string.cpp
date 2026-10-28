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

    while(src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }

    dest[i] = '\0';
    return dest;
}

char *String::strdup(const char *src) {
    char *result = new char[String::strlen(src) + 1];
    String::strcpy(result, src);
    return result;
}

static char *String::strncpy(char *dest, const char *src, int n) {
    int i = 0;

    while(i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    while (i<n) {
        dest[i] = '\0';
        i++;
    }
}

char *String::strcat()(char *dest, const char *src) {
    int i = 0;
    int j = 0;

    while (dest[i] != '\0') {
        i++;
    }

    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    

    dest[i] = '\0';

    return dest;
}




