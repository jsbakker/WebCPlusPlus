// test_haskell_highlight.cpp
// Ported from HaskellHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct HaskellHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "hs"); }
};

TEST_F(HaskellHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("ANN").find("<font CLASS=keyword>ANN</font>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("Alternative").find("<font CLASS=keytype>Alternative</font>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'x'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, SingleQuoteInsideCommentIsNotHighlighted) {
    auto html = hl("-- it's a comment");
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, BacktickStringsAreHighlighted) {
    EXPECT_NE(hl("`elem`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("{- a comment -}").find("<font CLASS=comment>{- a comment -}</font>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("-- comment").find("<font CLASS=comment>-- comment</font>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(HaskellHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"({- Block comment -}
-- Line comment
module Main where
import Data.List
main :: IO ()
main = do
    let x = 42
    let y = 3.14
    putStrLn "hello"
    let c = 'x'
    let z = x + 1
    let r = x `div` 2)");
    EXPECT_NE(html.find("<font CLASS=keyword>module</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>IO</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>{- Block comment -}</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>-- Line comment</font>"), std::string::npos);
}
