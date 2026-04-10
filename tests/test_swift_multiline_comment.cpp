// test_swift_multiline_comment.cpp
// Ported from SwiftMultilineCommentTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct SwiftMultilineCommentTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "swift"); }
};

TEST_F(SwiftMultilineCommentTest, SingleLineMultilineCommentIsHighlighted) {
    auto html = hl("/* this is a comment */");
    EXPECT_NE(html.find("<font CLASS=comment>/* this is a comment */</font>"), std::string::npos);
}

TEST_F(SwiftMultilineCommentTest, MultilineMultilineCommentIsHighlighted) {
    auto html = hl("/* first line\n   second line\n   third line */");
    EXPECT_NE(html.find("<font CLASS=comment>/* first line"), std::string::npos);
    EXPECT_NE(html.find("third line */</font>"), std::string::npos);
}

TEST_F(SwiftMultilineCommentTest, InlineMultilineCommentInCodeIsHighlighted) {
    auto html = hl("let x = 1 /* inline */ + 2");
    EXPECT_NE(html.find("<font CLASS=comment>/* inline */</font>"), std::string::npos);
}

TEST_F(SwiftMultilineCommentTest, KeywordsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("/* if else for while\n   return func struct class */");
    EXPECT_EQ(html.find("<font CLASS=keyword>"), std::string::npos);
}

TEST_F(SwiftMultilineCommentTest, NumbersInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("/* 42 3.14\n   0xFF 100 */");
    EXPECT_EQ(html.find("<font CLASS=integer>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>"), std::string::npos);
}

TEST_F(SwiftMultilineCommentTest, StringsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("/* \"hello world\"\n   'c' */");
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(SwiftMultilineCommentTest, TripleQuoteInsideMultilineCommentDoesNotStartMultilineString) {
    auto html = hl("/* \"\"\"\n   this should still be a comment\n   \"\"\" */\nlet x = 42");
    EXPECT_NE(html.find("<font CLASS=keyword>let</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(SwiftMultilineCommentTest, TypesInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("/* Int String Bool\n   Double Array */");
    EXPECT_EQ(html.find("<font CLASS=keytype>"), std::string::npos);
}

TEST_F(SwiftMultilineCommentTest, SymbolsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("/* + - * = < >\n   -> => :: */");
    EXPECT_EQ(html.find("<font CLASS=symbols>"), std::string::npos);
}

TEST_F(SwiftMultilineCommentTest, SingleLineCommentInsideMultilineCommentDoesNotBreak) {
    auto html = hl("/* // not a line comment\n   still a block comment */");
    EXPECT_NE(html.find("<font CLASS=comment>/* // not a line comment"), std::string::npos);
    EXPECT_NE(html.find("still a block comment */</font>"), std::string::npos);
}
