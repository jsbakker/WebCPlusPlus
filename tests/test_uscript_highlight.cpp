// test_uscript_highlight.cpp
// Ported from UScriptHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct UScriptHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "uc"); }
};

TEST_F(UScriptHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("abstract").find("<font CLASS=keyword>abstract</font>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("Vector").find("<font CLASS=keytype>Vector</font>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, PreprocessorDirectivesAreHighlighted) {
    EXPECT_NE(hl("#define FOO").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(UScriptHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
#exec texture import name=MyTex
// Line comment
class MyActor extends Actor;
var Vector position;
var int x;
event Tick(float delta) {
    x = 42;
    local Plane p;
    local string s;
    s = "hello";
    x = x + 1;
label:
    Log(s);
})");
    EXPECT_NE(html.find("<font CLASS=keyword>class</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>extends</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Vector</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>#exec</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>label:</font>"), std::string::npos);
}
