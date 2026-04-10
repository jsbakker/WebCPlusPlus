// test_ocaml_multiline_comment.cpp
// Ported from OCamlMultilineCommentTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct OCamlMultilineCommentTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "ml"); }
};

TEST_F(OCamlMultilineCommentTest, SingleLineMultilineCommentIsHighlighted) {
    auto html = hl("(* this is a comment *)");
    EXPECT_NE(html.find("<font CLASS=comment>(* this is a comment *)</font>"), std::string::npos);
}

TEST_F(OCamlMultilineCommentTest, MultilineMultilineCommentIsHighlighted) {
    auto html = hl("(* first line\n   second line\n   third line *)");
    EXPECT_NE(html.find("<font CLASS=comment>(* first line"), std::string::npos);
    EXPECT_NE(html.find("third line *)</font>"), std::string::npos);
}

TEST_F(OCamlMultilineCommentTest, InlineMultilineCommentInCodeIsHighlighted) {
    auto html = hl("let x = 1 (* inline *) + 2");
    EXPECT_NE(html.find("<font CLASS=comment>(* inline *)</font>"), std::string::npos);
}

TEST_F(OCamlMultilineCommentTest, KeywordsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* let rec match\n   module open type *)");
    EXPECT_EQ(html.find("<font CLASS=keyword>"), std::string::npos);
}

TEST_F(OCamlMultilineCommentTest, NumbersInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* 42 3.14\n   0xFF 100 *)");
    EXPECT_EQ(html.find("<font CLASS=integer>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>"), std::string::npos);
}

TEST_F(OCamlMultilineCommentTest, TypesInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* int string bool\n   float char *)");
    EXPECT_EQ(html.find("<font CLASS=keytype>"), std::string::npos);
}

TEST_F(OCamlMultilineCommentTest, SymbolsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* + - * = < >\n   -> |> :: *)");
    EXPECT_EQ(html.find("<font CLASS=symbols>"), std::string::npos);
}

TEST_F(OCamlMultilineCommentTest, StringsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("(* \"hello world\"\n   'c' *)");
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}
