// test_euphoria_highlight.cpp
// Ported from EuphoriaHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct EuphoriaHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "eu"); }
};

TEST_F(EuphoriaHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("and").find("<font CLASS=keyword>and</font>"), std::string::npos);
}

TEST_F(EuphoriaHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("atom").find("<font CLASS=keytype>atom</font>"), std::string::npos);
}

TEST_F(EuphoriaHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(EuphoriaHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(EuphoriaHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(EuphoriaHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("-- comment").find("<font CLASS=comment>-- comment</font>"), std::string::npos);
}

TEST_F(EuphoriaHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(EuphoriaHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(EuphoriaHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(-- Euphoria comment
integer x
x = 42
atom y
y = 3.14
sequence s
s = "hello"
if x > 0 then
    puts(1, 'c')
end if)");
    EXPECT_NE(html.find("<font CLASS=keyword>then</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>integer</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>atom</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>-- Euphoria comment</font>"), std::string::npos);
}
