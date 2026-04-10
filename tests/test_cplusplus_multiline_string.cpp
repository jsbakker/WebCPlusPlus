// test_cplusplus_multiline_string.cpp
// Ported from CPlusPlusMultilineStringTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct CPlusPlusMultilineStringTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "cpp"); }
};

TEST_F(CPlusPlusMultilineStringTest, TypeBeforeRawStringIsHighlighted) {
    auto html = hl(R"DELIM(int x; const char *s = R"(
content
)";)DELIM");
    EXPECT_NE(html.find("<font CLASS=keytype>int</font>"), std::string::npos);
}

TEST_F(CPlusPlusMultilineStringTest, KeywordBeforeRawStringIsHighlighted) {
    auto html = hl(R"DELIM(const char *s = R"(
content
)";)DELIM");
    EXPECT_NE(html.find("<font CLASS=keyword>const</font>"), std::string::npos);
}

TEST_F(CPlusPlusMultilineStringTest, KeywordsInsideRawStringAreNotHighlighted) {
    auto html = hl(R"DELIM(auto x = R"(
if else for while return
)";)DELIM");
    EXPECT_EQ(html.find("<font CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>for</font>"), std::string::npos);
}

TEST_F(CPlusPlusMultilineStringTest, NumbersInsideRawStringAreNotHighlighted) {
    auto html = hl(R"DELIM(auto x = R"(
42 3.14
)";)DELIM");
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(CPlusPlusMultilineStringTest, RawStringProducesOpenAndCloseTag) {
    auto html = hl(R"DELIM(auto x = R"(
content
)";)DELIM");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("</font>"), std::string::npos);
}
