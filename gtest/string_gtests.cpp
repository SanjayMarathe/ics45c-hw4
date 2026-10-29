#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>

#include "string.hpp"

using namespace std;

TEST(StringClass, Constructors) {
    String s("hello");
    EXPECT_EQ(s.size(), 5);

    String t(s);
    EXPECT_EQ(t.size(), 5);
    EXPECT_EQ(s.size(), 5);
}

TEST(StringClass, Print) {
    String s("foo");
    stringstream out;
    s.print(out);
    EXPECT_STREQ(out.str().c_str(), "foo");

    stringstream out2;
    String().print(out2);
    EXPECT_STREQ(out2.str().c_str(), "");

    stringstream out3;
    out3 << s << s << String("bar");
    EXPECT_STREQ(out3.str().c_str(), "foofoobar");
}

TEST(StringClass, Comparisons) {
    EXPECT_LT(String("aaaa"), String("aaab"));
    EXPECT_LE(String("aaaa"), String("aaab"));
    EXPECT_GT(String("aaab"), String("aaaa"));
    EXPECT_GE(String("aaab"), String("aaaa"));
    EXPECT_GE(String("foo"), String("foo"));
    EXPECT_LE(String("foo"), String("foo"));
    EXPECT_EQ(String("foo"), String("foo"));
    EXPECT_NE(String("foo"), String("fooo"));
    EXPECT_LT(String(""), String("a"));
    EXPECT_GT(String("abc"), String("ab"));
    EXPECT_EQ(String(""), String());
}

TEST(StringClass, Assignment) {
    String s("test"), t("foo");

    s = t;
    EXPECT_EQ(s.size(), t.size());
    EXPECT_EQ(s, t);

    s = s;
    EXPECT_EQ(s.size(), t.size());
    EXPECT_EQ(s, t);

    s = String();
    EXPECT_EQ(s, String());
    EXPECT_EQ(s.size(), 0);
}

TEST(StringClass, IndexOf) {
    String s("hello");
    EXPECT_EQ(s.indexOf('h'), 0);
    EXPECT_EQ(s.indexOf('l'), 2);
    EXPECT_EQ(s.indexOf('o'), 4);
    EXPECT_EQ(s.indexOf('x'), -1);
    EXPECT_EQ(s.indexOf('\0'), -1);
    EXPECT_EQ(String().indexOf('a'), -1);

    EXPECT_EQ(s.indexOf(String("ell")), 1);
    EXPECT_EQ(s.indexOf(String("hello")), 0);
    EXPECT_EQ(s.indexOf(String("lo")), 3);
    EXPECT_EQ(s.indexOf(String("")), 0);
    EXPECT_EQ(s.indexOf(String("world")), -1);
    EXPECT_EQ(String().indexOf(String("")), 0);
    EXPECT_EQ(String().indexOf(String("a")), -1);
}

TEST(StringClass, Reverse) {
    EXPECT_EQ(String("hello").reverse(), String("olleh"));
    EXPECT_EQ(String("").reverse(), String());
    EXPECT_EQ(String("a").reverse(), String("a"));
    EXPECT_EQ(String("ab").reverse(), String("ba"));

    String s("hello");
    EXPECT_EQ(s.reverse(), String("olleh"));
    EXPECT_EQ(s, String("hello"));
}

TEST(StringClass, Concat) {
    EXPECT_EQ(String("foo") + String("bar"), String("foobar"));
    EXPECT_EQ(String("foo") + String(), String("foo"));
    EXPECT_EQ(String() + String("bar"), String("bar"));
    EXPECT_EQ(String() + String(), String());

    String s("foo");
    s += String("bar");
    EXPECT_EQ(s, String("foobar"));
    s += String();
    EXPECT_EQ(s, String("foobar"));

    String empty;
    empty += String("x");
    EXPECT_EQ(empty, String("x"));
}

TEST(StringClass, Read) {
    stringstream in("alpha beta");
    String s("old");
    s.read(in);
    EXPECT_EQ(s, String("alpha"));

    String t;
    in >> t;
    EXPECT_EQ(t, String("beta"));

    stringstream empty_in("");
    String u("keep");
    u.read(empty_in);
    EXPECT_EQ(u, String("keep"));
}
