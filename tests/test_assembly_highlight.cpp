// test_assembly_highlight.cpp
// Ported from AssemblyHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct AssemblyHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "asm"); }
};

TEST_F(AssemblyHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl(".abort").find("<font CLASS=keyword>.abort</font>"), std::string::npos);
}

TEST_F(AssemblyHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("ah").find("<font CLASS=keytype>ah</font>"), std::string::npos);
}

TEST_F(AssemblyHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(AssemblyHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(AssemblyHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(AssemblyHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(AssemblyHighlightTest, PreprocessorDirectivesAreHighlighted) {
    EXPECT_NE(hl("#define FOO").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(AssemblyHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(AssemblyHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("; comment").find("<font CLASS=comment>; comment</font>"), std::string::npos);
}

TEST_F(AssemblyHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(AssemblyHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(AssemblyHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(; Assembly comment
.section .text
.global _start
_start:
    mov eax, 42
    add eax, 3
    int 0x80
; check if eax > 0 before exit
/* block comment */)");
    EXPECT_NE(html.find("<font CLASS=keyword>mov</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>add</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>eax</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>; Assembly comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>.section</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>_start:</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>; check if eax &gt; 0 before exit</font>"), std::string::npos);
}
