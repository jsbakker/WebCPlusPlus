// test_swift_highlight.cpp
// Ported from SwiftHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct SwiftHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "swift"); }
};

TEST_F(SwiftHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("@AppStorage").find("<font CLASS=keyword>@AppStorage</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("Any").find("<font CLASS=keytype>Any</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, SingleQuotedStringsAreNotHighlighted) {
    EXPECT_EQ(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, TripleQuotedStringsAreHighlighted) {
    const std::string source = "\"\"\"\ncontent\n\"\"\"";
    EXPECT_NE(hl(source).find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, InterpolationDoesNotBreakStringHighlighting) {
    EXPECT_NE(hl(R"SW("Hello, \(name)!")SW").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, IntegerInsideInterpolationIsHighlighted) {
    auto html = hl(R"SW("Value: \(42)")SW");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, SymbolInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"SW("Sum: \(a + b)")SW").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, KeywordInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"SW("Val: \(nil)")SW").find("<font CLASS=keyword>nil</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, TypeInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"SW("Cast: \(Int(x))")SW").find("<font CLASS=keytype>Int</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, IntegerInStringWithoutInterpolationIsNotHighlighted) {
    auto html = hl(R"("count is 42")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, MultilineTripleQuotedStringInterpolation) {
    // source: """\nvalue is \(42 + 1)\n"""
    const std::string source = "\"\"\"\\\nvalue is \\(42 + 1)\\\n\"\"\"";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(SwiftHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
// Line comment
actor MyActor {
    var x: Int = 42
    var pi: Double = 3.14
    func run() async {
        let s: String = "hello"
        let c: Character = "x"
        let flag: Any = true
        x = x + 1
    }
})");
    EXPECT_NE(html.find("<font CLASS=keyword>actor</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>async</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Any</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
}
