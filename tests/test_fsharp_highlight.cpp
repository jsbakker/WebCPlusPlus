// test_fsharp_highlight.cpp
// Ported from FSharpHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct FSharpHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "fs"); }
};

TEST_F(FSharpHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("abstract").find("<font CLASS=keyword>abstract</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("bool").find("<font CLASS=keytype>bool</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, BacktickStringsAreHighlighted) {
    EXPECT_NE(hl("`hello`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("(* a comment *)").find("<font CLASS=comment>(* a comment *)</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, TripleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("\"\"\"\ncontent\n\"\"\"").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, InterpolationDoesNotBreakStringHighlighting) {
    EXPECT_NE(hl(R"($"Hello, {name}!")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, IntegerInsideInterpolationIsHighlighted) {
    auto html = hl(R"($"Value: {42}")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, SymbolInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"($"Sum: {a + b}")").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, KeywordInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"($"Val: {null}")").find("<font CLASS=keyword>null</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, TypeInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"($"Type: {int(x)}")").find("<font CLASS=keytype>int</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, IntegerInStringWithoutInterpolationIsNotHighlighted) {
    auto html = hl(R"("count is 42")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, MultilineTripleQuotedStringInterpolation) {
    const std::string source = "\"\"\"\\\nvalue is {42 + 1}\\\n\"\"\"";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(FSharpHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"((* Block comment *)
// Line comment
let abstract = false
let x : int = 42
let pi : float = 3.14
let s : string = "hello"
let c : char = 'x'
let b : bool = true
x + 1 |> ignore)");
    EXPECT_NE(html.find("<font CLASS=keyword>let</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>(* Block comment *)</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
}
