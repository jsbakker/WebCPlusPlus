// test_sql_highlight.cpp
// Ported from SQLHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct SQLHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "sql"); }
};

TEST_F(SQLHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("ADD").find("<font CLASS=keyword>ADD</font>"), std::string::npos);
}

TEST_F(SQLHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("BIGINT").find("<font CLASS=keytype>BIGINT</font>"), std::string::npos);
}

TEST_F(SQLHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(SQLHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(SQLHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(SQLHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(SQLHighlightTest, SingleQuoteInsideCommentIsNotHighlighted) {
    auto html = hl("-- it's a comment");
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>"), std::string::npos);
}

TEST_F(SQLHighlightTest, BacktickStringsAreHighlighted) {
    EXPECT_NE(hl("`table_name`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(SQLHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(SQLHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(SQLHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(SQLHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(SQLHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("-- comment").find("<font CLASS=comment>-- comment</font>"), std::string::npos);
}

TEST_F(SQLHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(SQLHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(-- SQL comment
/* Block comment */
SELECT name, age
FROM users
WHERE age > 42
AND salary = 3.14
AND status = 'active'
AND label = "tagged"
AND `table_name` IS NOT NULL
CAST(age AS BIGINT)
ORDER BY name;)");
    EXPECT_NE(html.find("<font CLASS=keyword>SELECT</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>FROM</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>BIGINT</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>-- SQL comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
}
