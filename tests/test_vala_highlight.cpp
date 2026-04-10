// test_vala_highlight.cpp
// Ported from ValaHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ValaHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "vala"); }
};

TEST_F(ValaHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("abstract").find("<font CLASS=keyword>abstract</font>"), std::string::npos);
}

TEST_F(ValaHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("bool").find("<font CLASS=keytype>bool</font>"), std::string::npos);
}

TEST_F(ValaHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(ValaHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(ValaHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ValaHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(ValaHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(ValaHighlightTest, PreprocessorDirectivesAreHighlighted) {
    EXPECT_NE(hl("#define FOO").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(ValaHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(ValaHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(ValaHighlightTest, TripleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("\"\"\"\ncontent\n\"\"\"").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ValaHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(ValaHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(ValaHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
#if HAVE_FEATURE
// Line comment
abstract class Example : Object {
    bool flag;
    int x = 42;
    double pi = 3.14;
    async void run() {
        string s = "hello";
        char c = 'x';
        x = x + 1;
    }
}
#endif)");
    EXPECT_NE(html.find("<font CLASS=keyword>abstract</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>async</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>#if</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
}
