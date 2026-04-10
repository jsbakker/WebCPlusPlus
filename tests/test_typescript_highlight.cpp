// test_typescript_highlight.cpp
// Ported from TypeScriptHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct TypeScriptHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "ts"); }
};

TEST_F(TypeScriptHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("abstract").find("<font CLASS=keyword>abstract</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("Array").find("<font CLASS=keytype>Array</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, BacktickTemplateStringsAreHighlighted) {
    EXPECT_NE(hl("`hello world`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, InterpolationDoesNotBreakBacktickStringHighlighting) {
    EXPECT_NE(hl("`Hello, ${name}!`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, IntegerInsideInterpolationIsHighlighted) {
    auto html = hl("`Value: ${42}`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, SymbolInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl("`Sum: ${a + b}`").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, KeywordInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl("`Val: ${null}`").find("<font CLASS=keyword>null</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, TypeInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl("`Cast: ${Boolean(x)}`").find("<font CLASS=keytype>Boolean</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, IntegerInBacktickStringWithoutInterpolationIsNotHighlighted) {
    auto html = hl("`count is 42`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, DoubleQuotedStringDoesNotInterpolate) {
    auto html = hl(R"("${42}")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(TypeScriptHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
// Line comment
abstract class Example {
    async run(): Promise<void> {
        const x: number = 42;
        let pi: number = 3.14;
        let s: string = "hello";
        let c: string = 'world';
        let arr: Array<number> = [x + 1];
    }
})");
    EXPECT_NE(html.find("<font CLASS=keyword>abstract</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>async</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Array</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
}
