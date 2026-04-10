// test_fortran_highlight.cpp
// Ported from FortranHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct FortranHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "f90"); }
};

TEST_F(FortranHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("ABSTRACT").find("<font CLASS=keyword>ABSTRACT</font>"), std::string::npos);
}

TEST_F(FortranHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("BYTE").find("<font CLASS=keytype>BYTE</font>"), std::string::npos);
}

TEST_F(FortranHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(FortranHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(FortranHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(FortranHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(FortranHighlightTest, PreprocessorDirectivesAreHighlighted) {
    EXPECT_NE(hl("#define FOO").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(FortranHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(FortranHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(FortranHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(! Fortran comment
/* Block comment */
PROGRAM Hello
    INTEGER :: x = 42
    REAL :: y = 3.14
    CHARACTER(len=5) :: s = "world"
    BYTE :: b
    IF (x > 0) THEN
        PRINT *, 'Hello'
    END IF
END PROGRAM)");
    EXPECT_NE(html.find("<font CLASS=keyword>PROGRAM</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>BYTE</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>! Fortran comment</font>"), std::string::npos);
}
