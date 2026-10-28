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

    String::strcpy(result, "xxxxxxx");
    String::strncpy(result, "hello", 1);
    EXPECT_EQ(result[0], 'h');

    String::strcpy(result, "xxxxxxx");
    EXPECT_EQ(String::strncpy(result, "hello", 0), result);
    EXPECT_EQ(result[0], 'x');

    EXPECT_EQ(String::strncpy(result, "", 5), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strcat) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strncat) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strcmp) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strncmp) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, reverse_cpy) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strchr) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strstr) {
    EXPECT_TRUE(false);
}
