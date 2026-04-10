// test_pascal_multiline_comment.cpp
// Ported from PascalMultilineCommentTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct PascalMultilineCommentTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "pas"); }
};

TEST_F(PascalMultilineCommentTest, SingleLineMultilineCommentIsHighlighted) {
    auto html = hl("(* this is a comment *)");
    EXPECT_NE(html.find("<font CLASS=comment>(* this is a comment *)</font>"), std::string::npos);
}

TEST_F(PascalMultilineCommentTest, MultilineMultilineCommentIsHighlighted) {
    auto html = hl("(* first line\n   second line\n   third line *)");
    EXPECT_NE(html.find("<font CLASS=comment>(* first line"), std::string::npos);
    EXPECT_NE(html.find("third line *)</font>"), std::string::npos);
}

TEST_F(PascalMultilineCommentTest, InlineMultilineCommentInCodeIsHighlighted) {
    auto html = hl("x := 1 (* inline *) + 2;");
    EXPECT_NE(html.find("<font CLASS=comment>(* inline *)</font>"), std::string::npos);
}

TEST_F(PascalMultilineCommentTest, KeywordsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* begin end procedure\n   function program unit *)");
    EXPECT_EQ(html.find("<font CLASS=keyword>"), std::string::npos);
}

TEST_F(PascalMultilineCommentTest, NumbersInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* 42 3.14\n   $FF 100 *)");
    EXPECT_EQ(html.find("<font CLASS=integer>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>"), std::string::npos);
}

TEST_F(PascalMultilineCommentTest, StringsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* 'hello world'\n   \"test\" *)");
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=squot>"), std::string::npos);
}

TEST_F(PascalMultilineCommentTest, TypesInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* Integer Boolean String\n   Byte Cardinal *)");
    EXPECT_EQ(html.find("<font CLASS=keytype>"), std::string::npos);
}

TEST_F(PascalMultilineCommentTest, HashVariablesInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* %variable\n   %hash *)");
    EXPECT_EQ(html.find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(PascalMultilineCommentTest, SingleLineCommentInsideMultilineCommentDoesNotBreak) {
    auto html = hl("(* // not a line comment\n   still a block comment *)");
    EXPECT_NE(html.find("<font CLASS=comment>(* // not a line comment"), std::string::npos);
    EXPECT_NE(html.find("still a block comment *)</font>"), std::string::npos);
}
