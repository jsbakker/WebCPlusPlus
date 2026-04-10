// test_pascal_highlight.cpp
// Ported from PascalHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct PascalHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "pas"); }
};

TEST_F(PascalHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("absolute").find("<font CLASS=keyword>absolute</font>"), std::string::npos);
}

TEST_F(PascalHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("AnsiChar").find("<font CLASS=keytype>AnsiChar</font>"), std::string::npos);
}

TEST_F(PascalHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(PascalHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(PascalHighlightTest, DoubleQuotedStringsAreNotHighlighted) {
    EXPECT_EQ(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PascalHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(PascalHighlightTest, BacktickStringsAreNotHighlighted) {
    EXPECT_EQ(hl("`hello`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(PascalHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PascalHighlightTest, SingleQuoteInsideDoubleQuoteIsNotHighlighted) {
    auto html = hl(R"("it's")");
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(PascalHighlightTest, HashVariablesAreHighlighted) {
    EXPECT_NE(hl("%variable").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(PascalHighlightTest, PercentKeywordPercentDoesNotHang) {
    auto html = hl("%begin% end");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>end</font>"), std::string::npos);
}

TEST_F(PascalHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("(* a comment *)").find("<font CLASS=comment>(* a comment *)</font>"), std::string::npos);
}

TEST_F(PascalHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(PascalHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(PascalHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(PascalHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"((* Block comment *)
// Line comment
program Hello;
var
    x : Integer;
    y : Real;
    s : AnsiString;
    c : AnsiChar;
begin
    x := 42;
    y := 3.14;
    s := 'hello';
    c := 'x';
end.)");
    EXPECT_NE(html.find("<font CLASS=keyword>program</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>AnsiString</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>(* Block comment *)</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
}
