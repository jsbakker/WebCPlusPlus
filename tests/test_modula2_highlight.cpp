// test_modula2_highlight.cpp
// Ported from Modula2HighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct Modula2HighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "mod"); }
};

TEST_F(Modula2HighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("ABSTRACT").find("<font CLASS=keyword>ABSTRACT</font>"), std::string::npos);
}

TEST_F(Modula2HighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("ACHAR").find("<font CLASS=keytype>ACHAR</font>"), std::string::npos);
}

TEST_F(Modula2HighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(Modula2HighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(Modula2HighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(Modula2HighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(Modula2HighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("(* a comment *)").find("<font CLASS=comment>(* a comment *)</font>"), std::string::npos);
}

TEST_F(Modula2HighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(Modula2HighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"((* Block comment *)
MODULE Hello;
FROM InOut IMPORT WriteString;
VAR
    x : INTEGER;
    y : REAL;
    s : ARRAY [0..10] OF CHAR;
BEGIN
    x := 42;
    y := 3.14;
    s := "hello";
    WriteString('world');
END Hello.)");
    EXPECT_NE(html.find("<font CLASS=keyword>MODULE</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>INTEGER</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>(* Block comment *)</font>"), std::string::npos);
}
