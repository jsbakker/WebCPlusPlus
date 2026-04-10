// test_ada_highlight.cpp
// Ported from AdaHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct AdaHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "adb"); }
};

TEST_F(AdaHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("abort").find("<font CLASS=keyword>abort</font>"), std::string::npos);
}

TEST_F(AdaHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("Address").find("<font CLASS=keytype>Address</font>"), std::string::npos);
}

TEST_F(AdaHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(AdaHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(AdaHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(AdaHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(AdaHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("-- comment").find("<font CLASS=comment>-- comment</font>"), std::string::npos);
}

TEST_F(AdaHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(AdaHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(AdaHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(AdaHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(with Ada.Text_IO; use Ada.Text_IO;
-- This is an Ada comment
procedure Hello is
   Count : Integer := 42;
   Rate  : Float   := 3.14;
   Name  : String  := "world";
   Ch    : Character := 'x';
   Flag  : Boolean := True;
label_one:
   Put_Line("Hello " & Name);
   Count := Count + 1;
end Hello;)");
    EXPECT_NE(html.find("<font CLASS=keyword>procedure</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Integer</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Boolean</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>-- This is an Ada comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>label_one:</font>"), std::string::npos);
}
