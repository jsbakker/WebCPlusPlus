// test_kotlin_highlight.cpp
// Ported from KotlinHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct KotlinHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "kt"); }
};

TEST_F(KotlinHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("abstract").find("<font CLASS=keyword>abstract</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("Any").find("<font CLASS=keytype>Any</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, BacktickStringsAreHighlighted) {
    EXPECT_NE(hl("`is`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, TripleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("\"\"\"\ncontent\n\"\"\"").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, InterpolationDoesNotBreakStringHighlighting) {
    EXPECT_NE(hl(R"("Hello, ${name}!")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, IntegerInsideInterpolationIsHighlighted) {
    auto html = hl(R"("Value: ${42}")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, SymbolInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"("Sum: ${a + b}")").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, KeywordInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"("Val: ${null}")").find("<font CLASS=keyword>null</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, TypeInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"("Cast: ${Int(x)}")").find("<font CLASS=keytype>Int</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, IntegerInStringWithoutInterpolationIsNotHighlighted) {
    auto html = hl(R"("count is 42")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, MultilineTripleQuotedStringInterpolation) {
    const std::string source = "\"\"\"\\\nvalue is ${42 + 1}\\\n\"\"\"";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(KotlinHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
// Line comment
abstract class Example {
    val flag: Boolean = true
    var x: Int = 42
    val pi: Double = 3.14
    fun run() {
        val s = "hello"
        val c = 'x'
        val arr: Array<Int> = arrayOf(x + 1)
    }
})");
    EXPECT_NE(html.find("<font CLASS=keyword>abstract</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Boolean</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
}
