// test_vhdl_highlight.cpp
// Ported from VHDLHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct VHDLHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "vhd"); }
};

TEST_F(VHDLHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("ABS").find("<font CLASS=keyword>ABS</font>"), std::string::npos);
}

TEST_F(VHDLHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("BIT").find("<font CLASS=keytype>BIT</font>"), std::string::npos);
}

TEST_F(VHDLHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(VHDLHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(VHDLHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(VHDLHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(VHDLHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("-- comment").find("<font CLASS=comment>-- comment</font>"), std::string::npos);
}

TEST_F(VHDLHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(VHDLHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(VHDLHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(VHDLHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(-- VHDL comment
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity counter is
    port(
        clk : in BIT;
        count : out BIT_VECTOR(7 downto 0)
    );
end counter;
architecture rtl of counter is
    signal x : INTEGER := 42;
    signal y : REAL := 3.14;
    signal s : STRING := "hello";
label1:
    process(clk)
    begin
        x <= x + 1;
    end process;
end rtl;)");
    EXPECT_NE(html.find("<font CLASS=keyword>entity</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>architecture</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>BIT</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>INTEGER</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>-- VHDL comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>label1:</font>"), std::string::npos);
}
