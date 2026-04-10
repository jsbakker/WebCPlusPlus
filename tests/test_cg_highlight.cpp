// test_cg_highlight.cpp
// Ported from CgHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct CgHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "cg"); }
};

TEST_F(CgHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("break").find("<font CLASS=keyword>break</font>"), std::string::npos);
}

TEST_F(CgHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("bool").find("<font CLASS=keytype>bool</font>"), std::string::npos);
}

TEST_F(CgHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(CgHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(CgHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CgHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(CgHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(CgHighlightTest, PreprocessorDirectivesAreHighlighted) {
    EXPECT_NE(hl("#define FOO").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(CgHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(CgHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(CgHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(CgHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
#include "helper.cg"
// Line comment
void main(float4 pos : POSITION) {
    bool flag = true;
    const int x = 42;
    float y = 3.14;
    float4 color = float4(1.0, 0.0, 0.0, 1.0);
    x = x + 1;
})");
    EXPECT_NE(html.find("<font CLASS=keyword>const</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
}
