// test_r_highlight.cpp
// Ported from RHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct RHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "r"); }
};

TEST_F(RHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("FALSE").find("<font CLASS=keyword>FALSE</font>"), std::string::npos);
}

TEST_F(RHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("array").find("<font CLASS=keytype>array</font>"), std::string::npos);
}

TEST_F(RHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(RHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(RHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(RHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(RHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(RHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("# comment").find("<font CLASS=comment># comment</font>"), std::string::npos);
}

TEST_F(RHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(RHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(# R comment
x <- 42
y <- 3.14
s <- "hello"
t <- 'world'
flag <- FALSE
v <- array(c(1, 2, 3))
result <- x + 1)");
    EXPECT_NE(html.find("<font CLASS=keyword>FALSE</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>array</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment># R comment</font>"), std::string::npos);
}
