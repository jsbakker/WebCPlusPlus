// test_java_multiline_string.cpp
// Ported from JavaMultilineStringTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct JavaMultilineStringTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "java"); }
};

TEST_F(JavaMultilineStringTest, BlockCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("String x = \"\"\"\n/* not a comment */\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=comment>/* not a comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(JavaMultilineStringTest, RegularBlockCommentIsHighlighted) {
    auto html = hl("/* this is a comment */");
    EXPECT_NE(html.find("<font CLASS=comment>/* this is a comment */</font>"), std::string::npos);
}

TEST_F(JavaMultilineStringTest, MultilineBlockCommentIsHighlighted) {
    auto html = hl("/* first line\n   second line */");
    EXPECT_NE(html.find("<font CLASS=comment>/* first line"), std::string::npos);
    EXPECT_NE(html.find("second line */</font>"), std::string::npos);
}

TEST_F(JavaMultilineStringTest, KeywordsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("String x = \"\"\"\nif else for while return\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>for</font>"), std::string::npos);
}

TEST_F(JavaMultilineStringTest, NumbersInsideMultilineStringAreNotHighlighted) {
    auto html = hl("String x = \"\"\"\n42 3.14\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(JavaMultilineStringTest, SingleLineCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("String x = \"\"\"\n// not a comment\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=comment>// not a comment</font>"), std::string::npos);
}

TEST_F(JavaMultilineStringTest, TypesInsideMultilineStringAreNotHighlighted) {
    auto html = hl("String x = \"\"\"\nBoolean Integer String\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=keytype>Boolean</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keytype>Integer</font>"), std::string::npos);
}

TEST_F(JavaMultilineStringTest, SymbolsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("\"\"\"\n+ - * = < > -> ::\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=symbols>"), std::string::npos);
}

TEST_F(JavaMultilineStringTest, TypeBeforeMultilineStringIsHighlighted) {
    auto html = hl("String x = \"\"\"\ncontent\n\"\"\";");
    EXPECT_NE(html.find("<font CLASS=keytype>String</font>"), std::string::npos);
}

TEST_F(JavaMultilineStringTest, MultilineStringProducesOpenAndCloseTag) {
    auto html = hl("String x = \"\"\"\ncontent\n\"\"\";");
    EXPECT_NE(html.find("<font CLASS=dblquot>\"\"\""), std::string::npos);
    EXPECT_NE(html.find("\"\"\"</font>"), std::string::npos);
}
