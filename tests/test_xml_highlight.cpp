// test_xml_highlight.cpp
// Ported from XMLHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct XMLHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "xml"); }
};

TEST_F(XMLHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("?xml").find("<font CLASS=keyword>?xml</font>"), std::string::npos);
}

TEST_F(XMLHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("encoding").find("<font CLASS=keytype>encoding</font>"), std::string::npos);
}

TEST_F(XMLHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(XMLHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(XMLHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(XMLHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(XMLHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("<!-- a comment -->").find("<font CLASS=comment>"), std::string::npos);
}

TEST_F(XMLHighlightTest, HtmlTagsAreHighlighted) {
    EXPECT_NE(hl("<div>").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(XMLHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- XML comment -->
<root>
    <item id='42'>
        <value>3.14</value>
    </item>
</root>)");
    EXPECT_NE(html.find("<font CLASS=keytype>encoding</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>"), std::string::npos);
}
