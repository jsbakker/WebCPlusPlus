// test_java_highlight.cpp
// Ported from JavaHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct JavaHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "java"); }
};

TEST_F(JavaHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("@Deprecated").find("<font CLASS=keyword>@Deprecated</font>"), std::string::npos);
}

TEST_F(JavaHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("Boolean").find("<font CLASS=keytype>Boolean</font>"), std::string::npos);
}

TEST_F(JavaHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(JavaHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(JavaHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(JavaHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(JavaHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(JavaHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(JavaHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(JavaHighlightTest, TripleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("\"\"\"\ncontent\n\"\"\"").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(JavaHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(JavaHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(JavaHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(JavaHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
// Line comment
abstract class Example {
    Boolean flag;
    int x = 42;
    double pi = 3.14;
    void run() {
        String s = "hello";
        char c = 'x';
        x = x + 1;
label:
        System.out.println(x);
    }
})");
    EXPECT_NE(html.find("<font CLASS=keyword>abstract</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Boolean</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>label:</font>"), std::string::npos);
}
