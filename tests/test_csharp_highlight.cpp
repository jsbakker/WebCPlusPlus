// test_csharp_highlight.cpp
// Ported from CSharpHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct CSharpHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "cs"); }
};

TEST_F(CSharpHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("abstract").find("<font CLASS=keyword>abstract</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("Action").find("<font CLASS=keytype>Action</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, PreprocessorDirectivesAreHighlighted) {
    EXPECT_NE(hl("#define FOO").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, TripleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("\"\"\"\ncontent\n\"\"\"").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, InterpolationDoesNotBreakStringHighlighting) {
    EXPECT_NE(hl(R"($"Hello, {name}!")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, IntegerInsideInterpolationIsHighlighted) {
    auto html = hl(R"($"Value: {42}")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, SymbolInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"($"Sum: {a + b}")").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, KeywordInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"($"Val: {null}")").find("<font CLASS=keyword>null</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, TypeInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"($"Cast: {(int)x}")").find("<font CLASS=keytype>int</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, IntegerInStringWithoutInterpolationIsNotHighlighted) {
    auto html = hl(R"("count is 42")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, MultilineTripleQuotedStringInterpolation) {
    const std::string source = "\"\"\"\\\nvalue is {42 + 1}\\\n\"\"\"";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(CSharpHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
#region MyRegion
// Line comment
abstract class Example {
    Action callback;
    int x = 42;
    double pi = 3.14;
    void Run() {
        string s = "hello";
        char c = 'x';
        x = x + 1;
label:
        Console.WriteLine(x);
    }
}
#endregion)");
    EXPECT_NE(html.find("<font CLASS=keyword>abstract</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Action</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>#region</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>label:</font>"), std::string::npos);
}
