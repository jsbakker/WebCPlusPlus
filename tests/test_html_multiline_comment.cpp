// test_html_multiline_comment.cpp
// Ported from HTMLMultilineCommentTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct HTMLMultilineCommentTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "html"); }
};

TEST_F(HTMLMultilineCommentTest, SingleLineMultilineCommentIsHighlighted) {
    auto html = hl("<!-- this is a comment -->");
    EXPECT_NE(html.find("<font CLASS=comment>&lt;!-- this is a comment --&gt;</font>"), std::string::npos);
}

TEST_F(HTMLMultilineCommentTest, MultilineMultilineCommentIsHighlighted) {
    auto html = hl("<!-- first line\n     second line\n     third line -->");
    EXPECT_NE(html.find("<font CLASS=comment>&lt;!-- first line"), std::string::npos);
    EXPECT_NE(html.find("third line --&gt;</font>"), std::string::npos);
}

TEST_F(HTMLMultilineCommentTest, TagsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("<!-- <div class=\"test\">\n     <p>hello</p>\n     </div> -->");
    EXPECT_NE(html.find("<font CLASS=comment>&lt;!-- &lt;div"), std::string::npos);
}

TEST_F(HTMLMultilineCommentTest, NumbersInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("<!-- 42 3.14\n     0xFF 100 -->");
    EXPECT_EQ(html.find("<font CLASS=integer>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>"), std::string::npos);
}

TEST_F(HTMLMultilineCommentTest, StringsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("<!-- \"hello world\"\n     'test string' -->");
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}
