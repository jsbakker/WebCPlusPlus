// test_renderman_highlight.cpp
// Ported from RenderManHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct RenderManHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "sl"); }
};

TEST_F(RenderManHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("and").find("<font CLASS=keyword>and</font>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("color").find("<font CLASS=keytype>color</font>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, SingleQuotedStringsAreNotHighlighted) {
    EXPECT_EQ(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, BacktickStringsAreNotHighlighted) {
    EXPECT_EQ(hl("`hello`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, PreprocessorDirectivesAreHighlighted) {
    EXPECT_NE(hl("#define FOO").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(RenderManHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
#include "helper.h"
// Line comment
displacement bumpy(float amount = 1.0) {
    color c;
    int x = 42;
    float y = 3.14;
    string s = "hello";
    x = x + 1;
})");
    EXPECT_NE(html.find("<font CLASS=keyword>displacement</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>color</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
}
