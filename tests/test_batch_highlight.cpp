// test_batch_highlight.cpp
// Ported from BatchHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct BatchHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "bat"); }
};

TEST_F(BatchHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("assoc").find("<font CLASS=keyword>assoc</font>"), std::string::npos);
}

TEST_F(BatchHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("at").find("<font CLASS=keytype>at</font>"), std::string::npos);
}

TEST_F(BatchHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(BatchHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(BatchHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(BatchHighlightTest, SingleQuotedStringsAreNotHighlighted) {
    EXPECT_EQ(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(BatchHighlightTest, BacktickStringsAreNotHighlighted) {
    EXPECT_EQ(hl("`hello`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(BatchHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(BatchHighlightTest, HashVariablesAreHighlighted) {
    EXPECT_NE(hl("%variable").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(BatchHighlightTest, PercentKeywordPercentDoesNotHang) {
    auto html = hl("echo %PATH% & set x=1");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>set</font>"), std::string::npos);
}

TEST_F(BatchHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("REM comment").find("<font CLASS=comment>REM comment</font>"), std::string::npos);
}

TEST_F(BatchHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(BatchHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(REM Batch comment
:: Another comment
@echo off
set x=42
set y=3.14
echo "Hello"
echo %PATH%
echo 'done')");
    EXPECT_NE(html.find("<font CLASS=keyword>echo</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>REM Batch comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>:: Another comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
}
