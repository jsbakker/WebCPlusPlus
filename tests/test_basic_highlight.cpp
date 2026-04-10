// test_basic_highlight.cpp
// Ported from BasicHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct BasicHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "bas"); }
};

TEST_F(BasicHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("ABS").find("<font CLASS=keyword>ABS</font>"), std::string::npos);
}

TEST_F(BasicHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(BasicHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(BasicHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(BasicHighlightTest, SingleQuotedStringsAreNotHighlighted) {
    EXPECT_EQ(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(BasicHighlightTest, BacktickStringsAreNotHighlighted) {
    EXPECT_EQ(hl("`hello`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(BasicHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(BasicHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("; comment").find("<font CLASS=comment>; comment</font>"), std::string::npos);
}

TEST_F(BasicHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(BasicHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(BasicHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(REM This is a BASIC remark
; Also a comment
DIM x AS INTEGER
x = 42
y = 3.14
PRINT "Hello"
IF x > 0 THEN
    PRINT 'greeting'
END IF
label1:
    GOTO label1)");
    EXPECT_NE(html.find("<font CLASS=keyword>PRINT</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>GOTO</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>REM"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>; Also a comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>label1:</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=comment>&gt;"), std::string::npos);
}
