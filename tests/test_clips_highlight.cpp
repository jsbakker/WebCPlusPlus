// test_clips_highlight.cpp
// Ported from CLIPSHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct CLIPSHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "clp"); }
};

TEST_F(CLIPSHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("FALSE").find("<font CLASS=keyword>FALSE</font>"), std::string::npos);
}

TEST_F(CLIPSHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("ADDRESS").find("<font CLASS=keytype>ADDRESS</font>"), std::string::npos);
}

TEST_F(CLIPSHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(CLIPSHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(CLIPSHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CLIPSHighlightTest, SingleQuotedStringsAreNotHighlighted) {
    EXPECT_EQ(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(CLIPSHighlightTest, BacktickStringsAreNotHighlighted) {
    EXPECT_EQ(hl("`hello`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(CLIPSHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(CLIPSHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(CLIPSHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("; comment").find("<font CLASS=comment>; comment</font>"), std::string::npos);
}

TEST_F(CLIPSHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(CLIPSHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(; CLIPS comment
(defrule example
    (test (abs 42))
    =>
    (printout t "Hello" crlf)
    (bind ?x 'world')
    (assert (result TRUE))
))");
    EXPECT_NE(html.find("<font CLASS=keyword>TRUE</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>; CLIPS comment</font>"), std::string::npos);
    EXPECT_NE(html.find("&gt;"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=comment>&gt;"), std::string::npos);
}
