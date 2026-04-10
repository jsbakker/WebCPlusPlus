// test_modula2_multiline_comment.cpp
// Ported from Modula2MultilineCommentTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct Modula2MultilineCommentTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "mod"); }
};

TEST_F(Modula2MultilineCommentTest, SingleLineMultilineCommentIsHighlighted) {
    auto html = hl("(* this is a comment *)");
    EXPECT_NE(html.find("<font CLASS=comment>(* this is a comment *)</font>"), std::string::npos);
}

TEST_F(Modula2MultilineCommentTest, MultilineMultilineCommentIsHighlighted) {
    auto html = hl("(* first line\n   second line\n   third line *)");
    EXPECT_NE(html.find("<font CLASS=comment>(* first line"), std::string::npos);
    EXPECT_NE(html.find("third line *)</font>"), std::string::npos);
}

TEST_F(Modula2MultilineCommentTest, InlineMultilineCommentInCodeIsHighlighted) {
    auto html = hl("x := 1 (* inline *) + 2;");
    EXPECT_NE(html.find("<font CLASS=comment>(* inline *)</font>"), std::string::npos);
}

TEST_F(Modula2MultilineCommentTest, KeywordsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* MODULE PROCEDURE\n   BEGIN END TYPE *)");
    EXPECT_EQ(html.find("<font CLASS=keyword>"), std::string::npos);
}

TEST_F(Modula2MultilineCommentTest, NumbersInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* 42 3.14\n   0FFH 100 *)");
    EXPECT_EQ(html.find("<font CLASS=integer>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>"), std::string::npos);
}

TEST_F(Modula2MultilineCommentTest, TypesInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* INTEGER BOOLEAN\n   CARDINAL ARRAY *)");
    EXPECT_EQ(html.find("<font CLASS=keytype>"), std::string::npos);
}

TEST_F(Modula2MultilineCommentTest, StringsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* \"hello world\"\n   'test' *)");
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=squot>"), std::string::npos);
}
