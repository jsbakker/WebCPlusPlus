// test_asp_highlight.cpp
// Ported from ASPHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ASPHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "asp"); }
};

TEST_F(ASPHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("and").find("<font CLASS=keyword>and</font>"), std::string::npos);
}

TEST_F(ASPHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(ASPHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(ASPHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ASPHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("' comment").find("<font CLASS=comment>' comment</font>"), std::string::npos);
}

TEST_F(ASPHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(ASPHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(' This is an ASP comment
response.write "Hello"
select case x
case 42
    y = 3.14
end select)");
    EXPECT_NE(html.find("<font CLASS=keyword>select</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>case</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>"), std::string::npos);
}
