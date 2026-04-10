// test_python_multiline_string.cpp
// Ported from PythonMultilineStringTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct PythonMultilineStringTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "py"); }
};

TEST_F(PythonMultilineStringTest, KeywordsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("x = \"\"\"\nif else for while return\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>for</font>"), std::string::npos);
}

TEST_F(PythonMultilineStringTest, NumbersInsideMultilineStringAreNotHighlighted) {
    auto html = hl("x = \"\"\"\n42 3.14\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(PythonMultilineStringTest, HashCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("x = \"\"\"\n# not a comment\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=comment># not a comment</font>"), std::string::npos);
}

TEST_F(PythonMultilineStringTest, RegularHashCommentIsHighlighted) {
    auto html = hl("# this is a comment");
    EXPECT_NE(html.find("<font CLASS=comment># this is a comment</font>"), std::string::npos);
}

TEST_F(PythonMultilineStringTest, TypesInsideMultilineStringAreNotHighlighted) {
    auto html = hl("x = \"\"\"\nint str float list\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=keytype>"), std::string::npos);
}

TEST_F(PythonMultilineStringTest, SymbolsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("\"\"\"\n+ - * = < > ** //\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=symbols>"), std::string::npos);
}

TEST_F(PythonMultilineStringTest, KeywordBeforeMultilineStringIsHighlighted) {
    auto html = hl("def f():\n    x = \"\"\"\n    content\n    \"\"\"\n    return x");
    EXPECT_NE(html.find("<font CLASS=keyword>def</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>return</font>"), std::string::npos);
}

TEST_F(PythonMultilineStringTest, MultilineStringProducesOpenAndCloseTag) {
    auto html = hl("x = \"\"\"\ncontent\n\"\"\"");
    EXPECT_NE(html.find("<font CLASS=dblquot>\"\"\""), std::string::npos);
    EXPECT_NE(html.find("\"\"\"</font>"), std::string::npos);
}
