// test_gherkin_highlight.cpp
// Ported from GherkinHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct GherkinHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "feature"); }
};

TEST_F(GherkinHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("Abstract").find("<font CLASS=keyword>Abstract</font>"), std::string::npos);
}

TEST_F(GherkinHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(GherkinHighlightTest, SingleQuotedStringsAreNotHighlighted) {
    EXPECT_EQ(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(GherkinHighlightTest, BacktickStringsAreNotHighlighted) {
    EXPECT_EQ(hl("`hello`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(GherkinHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(GherkinHighlightTest, ScalarVariablesAreHighlighted) {
    EXPECT_NE(hl("$variable").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(GherkinHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("# comment").find("<font CLASS=comment># comment</font>"), std::string::npos);
}

TEST_F(GherkinHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(# Gherkin comment
Feature: Login
  Background: User exists
  Scenario: Valid login
    Given a user "admin"
    When they enter 'password'
    Then they see $dashboard
    And the count is <total>)");
    EXPECT_NE(html.find("<font CLASS=keyword>Given</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>Feature</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment># Gherkin comment</font>"), std::string::npos);
}
