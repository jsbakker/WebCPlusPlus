// test_tcl_highlight.cpp
// Ported from TclHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct TclHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "tcl"); }
};

TEST_F(TclHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("after").find("<font CLASS=keyword>after</font>"), std::string::npos);
}

TEST_F(TclHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("binary").find("<font CLASS=keytype>binary</font>"), std::string::npos);
}

TEST_F(TclHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(TclHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(TclHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(TclHighlightTest, SingleQuotedStringsAreNotHighlighted) {
    EXPECT_EQ(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(TclHighlightTest, BacktickStringsAreNotHighlighted) {
    EXPECT_EQ(hl("`hello`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(TclHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(TclHighlightTest, ScalarVariablesAreHighlighted) {
    EXPECT_NE(hl("$variable").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(TclHighlightTest, DollarKeywordDollarDoesNotHang) {
    auto html = hl("$proc$ while");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>while</font>"), std::string::npos);
}

TEST_F(TclHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("# comment").find("<font CLASS=comment># comment</font>"), std::string::npos);
}

TEST_F(TclHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(TclHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(# Tcl comment
set x 42
set y 3.14
set s "hello"
set t 'world'
set $var value
puts $s
if {$x > 0} {
    binary scan $s a5 result
})");
    EXPECT_NE(html.find("<font CLASS=keyword>set</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>binary</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment># Tcl comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
}
