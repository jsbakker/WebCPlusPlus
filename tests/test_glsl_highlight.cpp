// test_glsl_highlight.cpp
// Ported from GLSLHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct GLSLHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "glsl"); }
};

TEST_F(GLSLHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("attribute").find("<font CLASS=keyword>attribute</font>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("bool").find("<font CLASS=keytype>bool</font>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, SingleQuotedStringsAreNotHighlighted) {
    EXPECT_EQ(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, BacktickStringsAreNotHighlighted) {
    EXPECT_EQ(hl("`hello`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, PreprocessorDirectivesAreHighlighted) {
    EXPECT_NE(hl("#define FOO").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(GLSLHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
#version 330 core
// Line comment
uniform bool flag;
attribute vec3 position;
void main() {
    int x = 42;
    float y = 3.14;
    gl_Position = vec4(position, 1.0);
    x = x + 1;
})");
    EXPECT_NE(html.find("<font CLASS=keyword>attribute</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>#version</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
}
