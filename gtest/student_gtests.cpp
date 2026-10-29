#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strdup) {
    const char *original = "hello";
    char *copy = String::strdup(original);
    EXPECT_STREQ(copy, "hello");
    EXPECT_NE(copy, original);
    delete[] copy;

    char *empty = String::strdup("");
    EXPECT_STREQ(empty, "");
    delete[] empty;
}

TEST(StringFunction, strncpy) {
    char result[10];

    EXPECT_EQ(String::strncpy(result, "hello", 10), result);
    EXPECT_STREQ(result, "hello");

    EXPECT_EQ(String::strncpy(result, "abc", 4), result);
    EXPECT_STREQ(result, "abc");

    String::strcpy(result, "xxxxxxx");
    EXPECT_EQ(String::strncpy(result, "hello", 3), result);
    EXPECT_EQ(result[0], 'h');
    EXPECT_EQ(result[1], 'e');
    EXPECT_EQ(result[2], 'l');
    EXPECT_EQ(result[3], 'x');

    String::strcpy(result, "xxxxxxx");
    String::strncpy(result, "hello", 1);
    EXPECT_EQ(result[0], 'h');

    String::strcpy(result, "xxxxxxx");
    EXPECT_EQ(String::strncpy(result, "hello", 0), result);
    EXPECT_EQ(result[0], 'x');

    EXPECT_EQ(String::strncpy(result, "", 5), result);
    EXPECT_STREQ(result, "");

    String::strcpy(result, "xxxxxxx");
    EXPECT_EQ(String::strncpy(result, "hi", 2), result);
    EXPECT_EQ(result[0], 'h');
    EXPECT_EQ(result[1], 'i');
    EXPECT_EQ(result[2], 'x');

    char padded[8];
    for (int i = 0; i < 8; ++i) {
        padded[i] = 'z';
    }
    EXPECT_EQ(String::strncpy(padded, "hi", 6), padded);
    EXPECT_EQ(padded[0], 'h');
    EXPECT_EQ(padded[1], 'i');
    EXPECT_EQ(padded[2], '\0');
    EXPECT_EQ(padded[3], '\0');
    EXPECT_EQ(padded[4], '\0');
    EXPECT_EQ(padded[5], '\0');
    EXPECT_EQ(padded[6], 'z');
}

TEST(StringFunction, strcat) {
    char result[20];

    String::strcpy(result, "foo");
    EXPECT_EQ(String::strcat(result, "bar"), result);
    EXPECT_STREQ(result, "foobar");

    String::strcpy(result, "foo");
    String::strcat(result, "");
    EXPECT_STREQ(result, "foo");

    String::strcpy(result, "");
    String::strcat(result, "bar");
    EXPECT_STREQ(result, "bar");

    String::strcpy(result, "");
    String::strcat(result, "");
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strncat) {
    char result[20];

    String::strcpy(result, "foo");
    EXPECT_EQ(String::strncat(result, "bar", 2), result);
    EXPECT_STREQ(result, "fooba");

    String::strcpy(result, "foo");
    EXPECT_EQ(String::strncat(result, "bar", 10), result);
    EXPECT_STREQ(result, "foobar");

    String::strcpy(result, "foo");
    String::strncat(result, "bar", 3);
    EXPECT_STREQ(result, "foobar");

    String::strcpy(result, "foo");
    String::strncat(result, "bar", 0);
    EXPECT_STREQ(result, "foo");

    String::strcpy(result, "");
    String::strncat(result, "bar", 1);
    EXPECT_STREQ(result, "b");

    String::strcpy(result, "foo");
    String::strncat(result, "", 5);
    EXPECT_STREQ(result, "foo");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("abc", "abc"), 0);
    EXPECT_EQ(String::strcmp("", ""), 0);
    EXPECT_LT(String::strcmp("abc", "abd"), 0);
    EXPECT_GT(String::strcmp("abd", "abc"), 0);
    EXPECT_LT(String::strcmp("ab", "abc"), 0);
    EXPECT_GT(String::strcmp("abc", "ab"), 0);
    EXPECT_LT(String::strcmp("", "a"), 0);
    EXPECT_GT(String::strcmp("a", ""), 0);
    EXPECT_LT(String::strcmp("abc", "abcd"), 0);
    EXPECT_GT(String::strcmp("b", "a"), 0);
}

TEST(StringFunction, strncmp) {
    EXPECT_EQ(String::strncmp("abc", "abd", 2), 0);
    EXPECT_LT(String::strncmp("abc", "abd", 3), 0);
    EXPECT_EQ(String::strncmp("abc", "xyz", 0), 0);
    EXPECT_EQ(String::strncmp("hello", "hello", 10), 0);
    EXPECT_EQ(String::strncmp("", "", 5), 0);
    EXPECT_LT(String::strncmp("", "a", 1), 0);
    EXPECT_EQ(String::strncmp("ab", "a", 1), 0);
    EXPECT_GT(String::strncmp("ab", "a", 2), 0);
    EXPECT_GT(String::strncmp("help", "hello", 4), 0);
    EXPECT_EQ(String::strncmp("hello", "help", 3), 0);
}

TEST(StringFunction, reverse_cpy) {
    char result[10];

    String::reverse_cpy(result, "hello");
    EXPECT_STREQ(result, "olleh");

    String::reverse_cpy(result, "");
    EXPECT_STREQ(result, "");

    String::reverse_cpy(result, "a");
    EXPECT_STREQ(result, "a");

    String::reverse_cpy(result, "ab");
    EXPECT_STREQ(result, "ba");

    String::reverse_cpy(result, "racecar");
    EXPECT_STREQ(result, "racecar");
}

TEST(StringFunction, strchr) {
    const char *s = "hello";
    EXPECT_EQ(String::strchr(s, 'h'), s);
    EXPECT_EQ(String::strchr(s, 'e'), s + 1);
    EXPECT_EQ(String::strchr(s, 'o'), s + 4);
    EXPECT_EQ(String::strchr(s, 'x'), nullptr);
    EXPECT_EQ(String::strchr(s, '\0'), s + 5);

    EXPECT_EQ(String::strchr("", 'a'), nullptr);
    EXPECT_STREQ(String::strchr("", '\0'), "");

    const char *t = "banana";
    EXPECT_EQ(String::strchr(t, 'a'), t + 1);
    EXPECT_EQ(String::strchr(t, 'b'), t);
}

TEST(StringFunction, strstr) {
    const char *h = "hello world";
    EXPECT_EQ(String::strstr(h, "hello"), h);
    EXPECT_EQ(String::strstr(h, "world"), h + 6);
    EXPECT_EQ(String::strstr(h, "lo w"), h + 3);
    EXPECT_EQ(String::strstr(h, "o"), h + 4);
    EXPECT_EQ(String::strstr(h, ""), h);
    EXPECT_EQ(String::strstr(h, "xyz"), nullptr);
    EXPECT_EQ(String::strstr(h, "hello world!"), nullptr);

    EXPECT_STREQ(String::strstr("", ""), "");
    EXPECT_EQ(String::strstr("", "a"), nullptr);

    const char *overlap = "aaa";
    EXPECT_EQ(String::strstr(overlap, "aa"), overlap);
    EXPECT_EQ(String::strstr("abc", "abcd"), nullptr);

    const char *partial = "ababc";
    EXPECT_EQ(String::strstr(partial, "abc"), partial + 2);

    const char *mississippi = "mississippi";
    EXPECT_EQ(String::strstr(mississippi, "issip"), mississippi + 4);
}
