// test_html_highlight.cpp
// Ported from HTMLHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct HTMLHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "html"); }
};

TEST_F(HTMLHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("?").find("<font CLASS=keyword>?</font>"), std::string::npos);
}

TEST_F(HTMLHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("ACCEPT").find("<font CLASS=keytype>ACCEPT</font>"), std::string::npos);
}

TEST_F(HTMLHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(HTMLHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(HTMLHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(HTMLHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(HTMLHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("<!-- a comment -->").find("<font CLASS=comment>"), std::string::npos);
}

TEST_F(HTMLHighlightTest, HtmlTagsAreHighlighted) {
    EXPECT_NE(hl("<div>").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(HTMLHighlightTest, QuotedAttributeInsideTagIsHighlighted) {
    auto html = hl(R"(<div class="main">)");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(HTMLHighlightTest, SingleQuotedAttributeInsideTagIsHighlighted) {
    auto html = hl("<div id='content'>");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(HTMLHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(HTMLHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(<!-- HTML comment -->
<!DOCTYPE html>
<html>
<head>
    <title>Test 42</title>
</head>
<body class="main" id='content'>
    <p>Value is 3.14</p>
</body>
</html>)");
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>"), std::string::npos);
}
