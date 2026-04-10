// test_vala_multiline_string.cpp
// Ported from ValaMultilineStringTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ValaMultilineStringTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "vala"); }
};

TEST_F(ValaMultilineStringTest, BlockCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("string x = \"\"\"\n/* not a comment */\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=comment>/* not a comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ValaMultilineStringTest, RegularBlockCommentIsHighlighted) {
    auto html = hl("/* this is a comment */");
    EXPECT_NE(html.find("<font CLASS=comment>/* this is a comment */</font>"), std::string::npos);
}

TEST_F(ValaMultilineStringTest, MultilineBlockCommentIsHighlighted) {
    auto html = hl("/* first line\n   second line */");
    EXPECT_NE(html.find("<font CLASS=comment>/* first line"), std::string::npos);
    EXPECT_NE(html.find("second line */</font>"), std::string::npos);
}

TEST_F(ValaMultilineStringTest, KeywordsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("string x = \"\"\"\nif else for while return\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>for</font>"), std::string::npos);
}

TEST_F(ValaMultilineStringTest, NumbersInsideMultilineStringAreNotHighlighted) {
    auto html = hl("string x = \"\"\"\n42 3.14\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(ValaMultilineStringTest, SingleLineCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("string x = \"\"\"\n// not a comment\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=comment>// not a comment</font>"), std::string::npos);
}

TEST_F(ValaMultilineStringTest, TypesInsideMultilineStringAreNotHighlighted) {
    auto html = hl("string x = \"\"\"\nbool int double float\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keytype>int</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keytype>double</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keytype>float</font>"), std::string::npos);
}

TEST_F(ValaMultilineStringTest, SymbolsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("\"\"\"\n+ - * = < > => ::\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=symbols>"), std::string::npos);
}

TEST_F(ValaMultilineStringTest, PreprocessorInsideMultilineStringIsNotHighlighted) {
    auto html = hl("string x = \"\"\"\n#if DEBUG\n#define FOO\n#endif\n\"\"\";");
    EXPECT_EQ(html.find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(ValaMultilineStringTest, TypeBeforeMultilineStringIsHighlighted) {
    auto html = hl("string x = \"\"\"\ncontent\n\"\"\";");
    EXPECT_NE(html.find("<font CLASS=keytype>string</font>"), std::string::npos);
}

TEST_F(ValaMultilineStringTest, MultilineStringProducesOpenAndCloseTag) {
    auto html = hl("string x = \"\"\"\ncontent\n\"\"\";");
    EXPECT_NE(html.find("<font CLASS=dblquot>\"\"\""), std::string::npos);
    EXPECT_NE(html.find("\"\"\"</font>"), std::string::npos);
}
