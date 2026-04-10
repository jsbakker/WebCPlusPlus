// test_css_highlight.cpp
// Ported from CSSHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct CSSHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "css"); }
};

TEST_F(CSSHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("@charset").find("<font CLASS=keyword>@charset</font>"), std::string::npos);
}

TEST_F(CSSHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("align-content").find("<font CLASS=keytype>align-content</font>"), std::string::npos);
}

TEST_F(CSSHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(CSSHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(CSSHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CSSHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(CSSHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(CSSHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(CSSHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* CSS comment */
@import url("style.css");
body {
    color: red;
    margin: 42px;
    opacity: 3.14;
    font-family: 'serif';
})");
    EXPECT_NE(html.find("<font CLASS=keyword>@import</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>color</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* CSS comment */</font>"), std::string::npos);
}
