// test_emf_highlight.cpp
// Ported from EmfHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct EmfHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "emf"); }
};

TEST_F(EmfHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("!abort").find("<font CLASS=keyword>!abort</font>"), std::string::npos);
}

TEST_F(EmfHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(EmfHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(EmfHighlightTest, BacktickStringsAreHighlighted) {
    EXPECT_NE(hl("`hello`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(EmfHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(EmfHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(EmfHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(EmfHighlightTest, ScalarVariablesAreHighlighted) {
    EXPECT_NE(hl("$variable").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(EmfHighlightTest, ArrayVariablesAreHighlighted) {
    EXPECT_NE(hl("@array").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(EmfHighlightTest, HashVariablesAreHighlighted) {
    EXPECT_NE(hl("%hash").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(EmfHighlightTest, DuplicateSigilsDoNotHang) {
    auto html = hl("%define% $define$ @define@ !abort");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>!abort</font>"), std::string::npos);
}

TEST_F(EmfHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("; comment").find("<font CLASS=comment>; comment</font>"), std::string::npos);
}

TEST_F(EmfHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(EmfHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(; Emf comment
!force
$scalar = "hello"
@array = 'world'
%hash
; check $scalar > 0
label1:
    !bell)");
    EXPECT_NE(html.find("<font CLASS=keyword>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>; Emf comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>label1:</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>; check $scalar &gt; 0</font>"), std::string::npos);
}
