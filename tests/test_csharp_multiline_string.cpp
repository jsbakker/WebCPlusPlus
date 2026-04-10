// test_csharp_multiline_string.cpp
// Ported from CSharpMultilineStringTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct CSharpMultilineStringTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "cs"); }
};

TEST_F(CSharpMultilineStringTest, BlockCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("var x = \"\"\"\n/* not a comment */\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=comment>/* not a comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CSharpMultilineStringTest, RegularBlockCommentIsHighlighted) {
    auto html = hl("/* this is a comment */");
    EXPECT_NE(html.find("<font CLASS=comment>/* this is a comment */</font>"), std::string::npos);
}

TEST_F(CSharpMultilineStringTest, MultilineBlockCommentIsHighlighted) {
    auto html = hl("/* first line\n   second line */");
    EXPECT_NE(html.find("<font CLASS=comment>/* first line"), std::string::npos);
    EXPECT_NE(html.find("second line */</font>"), std::string::npos);
}

TEST_F(CSharpMultilineStringTest, KeywordsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("var x = \"\"\"\nif else for while return\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>for</font>"), std::string::npos);
}

TEST_F(CSharpMultilineStringTest, NumbersInsideMultilineStringAreNotHighlighted) {
    auto html = hl("var x = \"\"\"\n42 3.14\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(CSharpMultilineStringTest, SingleLineCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("var x = \"\"\"\n// not a comment\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=comment>// not a comment</font>"), std::string::npos);
}

TEST_F(CSharpMultilineStringTest, TypesInsideMultilineStringAreNotHighlighted) {
    auto html = hl("var x = \"\"\"\nBoolean Int32 String\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=keytype>"), std::string::npos);
}

TEST_F(CSharpMultilineStringTest, SymbolsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("\"\"\"\n+ - * = < > => ::\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=symbols>"), std::string::npos);
}

TEST_F(CSharpMultilineStringTest, PreprocessorInsideMultilineStringIsNotHighlighted) {
    auto html = hl("var x = \"\"\"\n#if DEBUG\n#define FOO\n#endif\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(CSharpMultilineStringTest, KeywordBeforeMultilineStringIsHighlighted) {
    auto html = hl("var x = \"\"\"\ncontent\n\"\"\";");
    EXPECT_NE(html.find("<font CLASS=keyword>var</font>"), std::string::npos);
}

TEST_F(CSharpMultilineStringTest, MultilineStringProducesOpenAndCloseTag) {
    auto html = hl("var x = \"\"\"\ncontent\n\"\"\";");
    EXPECT_NE(html.find("<font CLASS=dblquot>\"\"\""), std::string::npos);
    EXPECT_NE(html.find("\"\"\"</font>"), std::string::npos);
}
