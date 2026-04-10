// test_xml_multiline_comment.cpp
// Ported from XMLMultilineCommentTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct XMLMultilineCommentTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "xml"); }
};

TEST_F(XMLMultilineCommentTest, SingleLineMultilineCommentIsHighlighted) {
    auto html = hl("<!-- this is a comment -->");
    EXPECT_NE(html.find("<font CLASS=comment>&lt;!-- this is a comment --&gt;</font>"), std::string::npos);
}

TEST_F(XMLMultilineCommentTest, MultilineMultilineCommentIsHighlighted) {
    auto html = hl("<!-- first line\n     second line\n     third line -->");
    EXPECT_NE(html.find("<font CLASS=comment>&lt;!-- first line"), std::string::npos);
    EXPECT_NE(html.find("third line --&gt;</font>"), std::string::npos);
}

TEST_F(XMLMultilineCommentTest, TagsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl(R"(<!-- <root attr="value">
     <child/>
     </root> -->)");
    EXPECT_NE(html.find("<font CLASS=comment>&lt;!-- &lt;root"), std::string::npos);
}

TEST_F(XMLMultilineCommentTest, NumbersInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("<!-- 42 3.14\n     0xFF 100 -->");
    EXPECT_EQ(html.find("<font CLASS=integer>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>"), std::string::npos);
}

TEST_F(XMLMultilineCommentTest, StringsInsideMultilineCommentAreNotHighlighted) {
    auto html = hl("<!-- \"hello world\"\n     'test string' -->");
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}
