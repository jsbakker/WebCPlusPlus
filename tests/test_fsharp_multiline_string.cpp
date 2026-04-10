// test_fsharp_multiline_string.cpp
// Ported from FSharpMultilineStringTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct FSharpMultilineStringTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "fs"); }
};

TEST_F(FSharpMultilineStringTest, PascalBlockCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("let x = \"\"\"\n(* not a comment *)\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=comment>(* not a comment *)</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(FSharpMultilineStringTest, RegularPascalBlockCommentIsHighlighted) {
    auto html = hl("(* this is a comment *)");
    EXPECT_NE(html.find("<font CLASS=comment>(* this is a comment *)</font>"), std::string::npos);
}

TEST_F(FSharpMultilineStringTest, MultilinePascalBlockCommentIsHighlighted) {
    auto html = hl("(* first line\n   second line *)");
    EXPECT_NE(html.find("<font CLASS=comment>(* first line"), std::string::npos);
    EXPECT_NE(html.find("second line *)</font>"), std::string::npos);
}

TEST_F(FSharpMultilineStringTest, KeywordsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("let x = \"\"\"\nif else for while match\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>for</font>"), std::string::npos);
}

TEST_F(FSharpMultilineStringTest, NumbersInsideMultilineStringAreNotHighlighted) {
    auto html = hl("let x = \"\"\"\n42 3.14\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(FSharpMultilineStringTest, SingleLineCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("let x = \"\"\"\n// not a comment\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=comment>// not a comment</font>"), std::string::npos);
}

TEST_F(FSharpMultilineStringTest, TypesInsideMultilineStringAreNotHighlighted) {
    auto html = hl("let x = \"\"\"\nint string bool float\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=keytype>"), std::string::npos);
}

TEST_F(FSharpMultilineStringTest, SymbolsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("\"\"\"\n+ - * = < > |> >>\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=symbols>"), std::string::npos);
}

TEST_F(FSharpMultilineStringTest, KeywordBeforeMultilineStringIsHighlighted) {
    auto html = hl("let x = \"\"\"\ncontent\n\"\"\"");
    EXPECT_NE(html.find("<font CLASS=keyword>let</font>"), std::string::npos);
}

TEST_F(FSharpMultilineStringTest, MultilineStringProducesOpenAndCloseTag) {
    auto html = hl("let x = \"\"\"\ncontent\n\"\"\"");
    EXPECT_NE(html.find("<font CLASS=dblquot>\"\"\""), std::string::npos);
    EXPECT_NE(html.find("\"\"\"</font>"), std::string::npos);
}
