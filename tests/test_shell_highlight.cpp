// test_shell_highlight.cpp
// Ported from ShellHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ShellHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "sh"); }
};

TEST_F(ShellHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("break").find("<font CLASS=keyword>break</font>"), std::string::npos);
}

TEST_F(ShellHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("apt").find("<font CLASS=keytype>apt</font>"), std::string::npos);
}

TEST_F(ShellHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(ShellHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(ShellHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ShellHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(ShellHighlightTest, ScalarVariablesAreHighlighted) {
    EXPECT_NE(hl("$variable").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(ShellHighlightTest, DollarKeywordDollarDoesNotHang) {
    auto html = hl("$if$ while");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>while</font>"), std::string::npos);
}

TEST_F(ShellHighlightTest, BacktickCommandSubstitutionIsHighlighted) {
    auto html = hl("result=`echo hello`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(ShellHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(ShellHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ShellHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(ShellHighlightTest, HeredocStringIsHighlighted) {
    auto html = hl("cat <<EOF\nhello world\nEOF");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ShellHighlightTest, HeredocQuotedMarkerIsHighlighted) {
    auto html = hl("cat <<'DONE'\nraw $text\nDONE");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ShellHighlightTest, HeredocAfterCommentIsNotTriggered) {
    auto html = hl("# use <<EOF for heredocs");
    EXPECT_NE(html.find("<font CLASS=comment>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ShellHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("# comment").find("<font CLASS=comment># comment</font>"), std::string::npos);
}

TEST_F(ShellHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(ShellHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(#!/bin/bash
# Shell comment
x=42
y=3.14
s="hello"
t='world'
echo $x
arr=(apt ar awk)
if [ $x -gt 0 ]; then
    echo "positive"
fi)");
    EXPECT_NE(html.find("<font CLASS=keytype>echo</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>apt</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment># Shell comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
}
