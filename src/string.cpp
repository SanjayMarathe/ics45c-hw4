# include "string.hpp"

# include <istream>
# include <ostream>
# include <utility>

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

char *String::strncpy(char *dest, const char *src, int n) {
    int i = 0;

    while(i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    while (i < n) {
        dest[i] = '\0';
        i++;
    }

    return dest;
}

char *String::strcat(char *dest, const char *src) {
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

char *String::strncat(char *dest, const char *src, int n) {
    int i = 0;
    int j = 0;

    while (dest[i] != '\0') {
        i++;
    }

    while (src[j] != '\0' && j < n) {
        dest[i] = src[j];

        i++;
        j++;

    }

    dest[i] = '\0';
    return dest;
}

int String::strcmp(const char *left, const char *right) {
    int i = 0;

    while (left[i] != '\0' && left[i] == right[i]) {
        i++;
    }

    return left[i] - right[i];
}

int String::strncmp(const char *left, const char *right, int n) {
    int i = 0;

    while (i < n && left[i] != '\0' && left[i] == right[i]) {
        i++;
    }

    if (i == n) {
        return 0;
    }

    return left[i] - right[i];
}

void String::reverse_cpy(char *dest, const char *src) {
    int len = 0;

    while (src[len] != '\0') {
        len++;
    }

    for (int i = 0; i < len; i++) {
        dest[i] = src[len - 1 - i];
    }

    dest[len] = '\0';
}

const char *String::strchr(const char *str, char c) {
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == c) {
            return str + i;
        }
        i++;
    }

    if (c == '\0') {
        return str + i;
    }

    return nullptr;
}

const char *String::strstr(const char *haystack, const char *needle) {
    if (needle[0] == '\0') {
        return haystack;
    }

    for (int i = 0; haystack[i] != '\0'; i++) {
        int j = 0;

        while (needle[j] != '\0' && haystack[i + j] == needle[j]) {
            j++;
        }

        if (needle[j] == '\0') {
            return haystack + i;
        }
    }

    return nullptr;
}

String::String(const char *s) : buf(strdup(s)) {}

String::String(const String &s) : buf(strdup(s.buf)) {}

String::String(String &&s) : buf(s.buf) {
    s.buf = nullptr;
}

String::String(int length) : buf(new char[length + 1]) {
    buf[length] = '\0';
}

String::~String() {
    delete[] buf;
}

void String::swap(String &s) {
    std::swap(buf, s.buf);
}

String &String::operator=(const String &s) {
    if (this != &s) {
        String copy(s);
        swap(copy);
    }
    return *this;
}

String &String::operator=(String &&s) {
    if (this != &s) {
        delete[] buf;
        buf = s.buf;
        s.buf = nullptr;
    }
    return *this;
}

char &String::operator[](int index) {
    return buf[index];
}

const char &String::operator[](int index) const {
    return buf[index];
}

int String::size() const {
    return strlen(buf);
}

void String::print(std::ostream &out) const {
    out << buf;
}

std::ostream &operator<<(std::ostream &out, const String &s) {
    s.print(out);
    return out;
}

String String::reverse() const {
    String result(size());
    reverse_cpy(result.buf, buf);
    return result;
}

int String::indexOf(char c) const {
    if (c == '\0') {
        return -1;
    }

    const char *found = strchr(buf, c);
    if (found == nullptr) {
        return -1;
    }

    return static_cast<int>(found - buf);
}

int String::indexOf(const String &s) const {
    const char *found = strstr(buf, s.buf);
    if (found == nullptr) {
        return -1;
    }

    return static_cast<int>(found - buf);
}

bool String::operator==(const String &s) const {
    return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(const String &s) const {
    return strcmp(buf, s.buf) != 0;
}

bool String::operator<(const String &s) const {
    return strcmp(buf, s.buf) < 0;
}

bool String::operator>(const String &s) const {
    return strcmp(buf, s.buf) > 0;
}

bool String::operator<=(const String &s) const {
    return strcmp(buf, s.buf) <= 0;
}

bool String::operator>=(const String &s) const {
    return strcmp(buf, s.buf) >= 0;
}

String String::operator+(const String &s) const {
    String result(size() + s.size());
    strcpy(result.buf, buf);
    strcat(result.buf, s.buf);
    return result;
}

String &String::operator+=(const String &s) {
    *this = *this + s;
    return *this;
}

void String::read(std::istream &in) {
    char temp[1024];
    if (in >> temp) {
        *this = String(temp);
    }
}

std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}

