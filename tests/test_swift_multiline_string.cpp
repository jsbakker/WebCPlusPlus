// test_swift_multiline_string.cpp
// Ported from SwiftMultilineStringTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct SwiftMultilineStringTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "swift"); }
};

TEST_F(SwiftMultilineStringTest, BlockCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("let x = \"\"\"\n/* not a comment */\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=comment>/* not a comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, BlockCommentInsideIndentedMultilineStringIsNotHighlighted) {
    auto html = hl("func f() {\n    let x = \"\"\"\n        /* not a comment */\n        \"\"\"\n}");
    EXPECT_EQ(html.find("<font CLASS=comment>/* not a comment */</font>"), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, RegularBlockCommentIsHighlighted) {
    auto html = hl("/* this is a comment */");
    EXPECT_NE(html.find("<font CLASS=comment>/* this is a comment */</font>"), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, MultilineBlockCommentIsHighlighted) {
    auto html = hl("/* first line\n   second line */");
    EXPECT_NE(html.find("<font CLASS=comment>/* first line"), std::string::npos);
    EXPECT_NE(html.find("second line */</font>"), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, InlineBlockCommentInCodeIsHighlighted) {
    auto html = hl("_ = nums.map { (/* unused */ _: Int) in 0 }");
    EXPECT_NE(html.find("<font CLASS=comment>/* unused */</font>"), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, KeywordsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("let x = \"\"\"\nif else for while return\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>for</font>"), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, NumbersInsideMultilineStringAreNotHighlighted) {
    auto html = hl("let x = \"\"\"\n42 3.14\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, SingleLineCommentInsideMultilineStringIsNotHighlighted) {
    auto html = hl("let x = \"\"\"\n// not a comment\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=comment>// not a comment</font>"), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, TypesInsideMultilineStringAreNotHighlighted) {
    auto html = hl("let x = \"\"\"\nInt String Bool Double\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=keytype>"), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, SymbolsInsideMultilineStringAreNotHighlighted) {
    auto html = hl("\"\"\"\n+ - * = < > -> =>\n\"\"\"");
    EXPECT_EQ(html.find("<font CLASS=symbols>"), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, KeywordBeforeMultilineStringIsHighlighted) {
    auto html = hl("let x = \"\"\"\ncontent\n\"\"\"");
    EXPECT_NE(html.find("<font CLASS=keyword>let</font>"), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, MultipleKeywordsBeforeMultilineStringAreHighlighted) {
    auto html = hl(
        "let user = \"Alice\"\n"
        "let behavior = \"wonderland\"\n"
        "\n"
        "// Multiline string example\n"
        "let story = \"\"\"\n"
        "content\n"
        "\"\"\"\n"
        "\n"
        "print(story)");
    EXPECT_NE(html.find("<font CLASS=keyword>let</font> user"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>let</font> story"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>let</font> behavior"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>\"\"\""), std::string::npos);
}

TEST_F(SwiftMultilineStringTest, MultilineStringProducesOpenAndCloseTag) {
    auto html = hl("let x = \"\"\"\ncontent\n\"\"\"");
    EXPECT_NE(html.find("<font CLASS=dblquot>\"\"\""), std::string::npos);
    EXPECT_NE(html.find("\"\"\"</font>"), std::string::npos);
}
