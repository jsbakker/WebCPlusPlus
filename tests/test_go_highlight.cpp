// test_go_highlight.cpp
// Ported from GoHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct GoHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "go"); }
};

TEST_F(GoHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("break").find("<font CLASS=keyword>break</font>"), std::string::npos);
}

TEST_F(GoHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("any").find("<font CLASS=keytype>any</font>"), std::string::npos);
}

TEST_F(GoHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(GoHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(GoHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(GoHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(GoHighlightTest, BacktickStringsAreHighlighted) {
    EXPECT_NE(hl("`hello\\nworld`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(GoHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(GoHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(GoHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(GoHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(GoHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(GoHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(GoHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(GoHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(GoHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
// Line comment
package main
func main() {
    var x int = 42
    var pi float64 = 3.14
    var s string = "hello"
    var c byte = 'x'
    var flag bool = true
    x = x + 1
})");
    EXPECT_NE(html.find("<font CLASS=keyword>func</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>int</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
}
