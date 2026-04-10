// test_php_highlight.cpp
// Ported from PHPHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct PHPHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "php"); }
};

TEST_F(PHPHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("abstract").find("<font CLASS=keyword>abstract</font>"), std::string::npos);
}

TEST_F(PHPHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("array").find("<font CLASS=keytype>array</font>"), std::string::npos);
}

TEST_F(PHPHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(PHPHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(PHPHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PHPHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(PHPHighlightTest, BacktickStringsAreHighlighted) {
    EXPECT_NE(hl("`ls -la`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(PHPHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(PHPHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PHPHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(PHPHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(PHPHighlightTest, ScalarVariablesAreHighlighted) {
    EXPECT_NE(hl("$variable").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(PHPHighlightTest, DollarKeywordDollarDoesNotHang) {
    auto html = hl("$echo$ function");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>function</font>"), std::string::npos);
}

TEST_F(PHPHighlightTest, HeredocStringIsHighlighted) {
    auto html = hl("$text = <<<EOT\nhello world\nEOT;");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PHPHighlightTest, HeredocQuotedMarkerIsHighlighted) {
    auto html = hl("$text = <<<'EOT'\nraw text\nEOT;");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PHPHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(PHPHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(PHPHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(PHPHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(PHPHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
// Line comment
# Hash comment
<?php
$arr = array();
abstract class Example {
    public $name;
    function run() {
        $x = 42;
        $y = 3.14;
        $s = "hello";
        $t = 'world';
        $x = $x + 1;
    }
}
?>)");
    EXPECT_NE(html.find("<font CLASS=keyword>abstract</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>array</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment># Hash comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
}
