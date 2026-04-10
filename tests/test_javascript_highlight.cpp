// test_javascript_highlight.cpp
// Ported from JavaScriptHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct JavaScriptHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "js"); }
};

TEST_F(JavaScriptHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("as").find("<font CLASS=keyword>as</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("Array").find("<font CLASS=keytype>Array</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, BacktickTemplateStringsAreHighlighted) {
    EXPECT_NE(hl("`hello world`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, InterpolationDoesNotBreakBacktickStringHighlighting) {
    EXPECT_NE(hl("`Hello, ${name}!`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, IntegerInsideInterpolationIsHighlighted) {
    auto html = hl("`Value: ${42}`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, SymbolInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl("`Sum: ${a + b}`").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, KeywordInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl("`Val: ${null}`").find("<font CLASS=keyword>null</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, TypeInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl("`Cast: ${Boolean(x)}`").find("<font CLASS=keytype>Boolean</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, IntegerInBacktickStringWithoutInterpolationIsNotHighlighted) {
    auto html = hl("`count is 42`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, DoubleQuotedStringDoesNotInterpolate) {
    auto html = hl(R"("${42}")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(JavaScriptHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
// Line comment
async function example() {
    const x = 42;
    let pi = 3.14;
    var s = "hello";
    var c = 'world';
    var arr = Array(x + 1);
    await fetch(s);
})");
    EXPECT_NE(html.find("<font CLASS=keyword>async</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>const</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Array</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
}
