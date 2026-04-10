// test_scala_multiline_string.cpp
// Ported from ScalaMultilineStringTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ScalaMultilineStringTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "scala"); }
};

TEST_F(ScalaMultilineStringTest, BlockCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("val x = \"\"\"\n/* not a comment */\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=comment>/* not a comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ScalaMultilineStringTest, RegularBlockCommentIsHighlighted) {
    auto html = hl("/* this is a comment */");
    EXPECT_NE(html.find("<font CLASS=comment>/* this is a comment */</font>"), std::string::npos);
}

TEST_F(ScalaMultilineStringTest, MultilineBlockCommentIsHighlighted) {
    auto html = hl("/* first line\n   second line */");
    EXPECT_NE(html.find("<font CLASS=comment>/* first line"), std::string::npos);
    EXPECT_NE(html.find("second line */</font>"), std::string::npos);
}

TEST_F(ScalaMultilineStringTest, KeywordsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("val x = \"\"\"\nif else for while return\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>for</font>"), std::string::npos);
}

TEST_F(ScalaMultilineStringTest, NumbersInsideMultilineStringAreNotHighlighted) {
    auto html = hl("val x = \"\"\"\n42 3.14\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(ScalaMultilineStringTest, SingleLineCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("val x = \"\"\"\n// not a comment\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=comment>// not a comment</font>"), std::string::npos);
}

TEST_F(ScalaMultilineStringTest, TypesInsideMultilineStringAreNotHighlighted) {
    auto html = hl("val x = \"\"\"\nInt String Boolean Array\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=keytype>"), std::string::npos);
}

TEST_F(ScalaMultilineStringTest, SymbolsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("\"\"\"\n+ - * = < > => ::\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=symbols>"), std::string::npos);
}

TEST_F(ScalaMultilineStringTest, KeywordBeforeMultilineStringIsHighlighted) {
    auto html = hl("val x = \"\"\"\ncontent\n\"\"\"");
    EXPECT_NE(html.find("<font CLASS=keyword>val</font>"), std::string::npos);
}

TEST_F(ScalaMultilineStringTest, MultilineStringProducesOpenAndCloseTag) {
    auto html = hl("val x = \"\"\"\ncontent\n\"\"\"");
    EXPECT_NE(html.find("<font CLASS=dblquot>\"\"\""), std::string::npos);
    EXPECT_NE(html.find("\"\"\"</font>"), std::string::npos);
}
