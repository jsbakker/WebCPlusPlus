// test_python_highlight.cpp
// Ported from PythonHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct PythonHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "py"); }
};

TEST_F(PythonHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("@abstractmethod").find("<font CLASS=keyword>@abstractmethod</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("Any").find("<font CLASS=keytype>Any</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PythonHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(PythonHighlightTest, BacktickStringsAreNotHighlighted) {
    EXPECT_EQ(hl("`hello`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(PythonHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(PythonHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PythonHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("# comment").find("<font CLASS=comment># comment</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, TripleQuotedStringsAreHighlighted) {
    const std::string source = "\"\"\"\ncontent\n\"\"\"";
    EXPECT_NE(hl(source).find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PythonHighlightTest, InterpolationDoesNotBreakStringHighlighting) {
    EXPECT_NE(hl(R"(f"Hello, {name}!")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PythonHighlightTest, IntegerInsideInterpolationIsHighlighted) {
    auto html = hl(R"(f"Value: {42}")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, SymbolInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"(f"Sum: {a + b}")").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, KeywordInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"(f"Val: {None}")").find("<font CLASS=keyword>None</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, TypeInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"(f"Cast: {int(x)}")").find("<font CLASS=keytype>int</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, IntegerInStringWithoutInterpolationIsNotHighlighted) {
    auto html = hl(R"("count is 42")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, MultilineTripleQuotedStringInterpolation) {
    // source: """\nvalue is {42 + 1}\n"""
    const std::string source = "\"\"\"\\\nvalue is {42 + 1}\\\n\"\"\"";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(PythonHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(# Python comment
class Example:
    def run(self):
        x: int = 42
        y: float = 3.14
        s: str = "hello"
        t: str = 'world'
        flag: bool = True
        x = x + 1
        result: Any = None)");
    EXPECT_NE(html.find("<font CLASS=keyword>class</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>def</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Any</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment># Python comment</font>"), std::string::npos);
}
