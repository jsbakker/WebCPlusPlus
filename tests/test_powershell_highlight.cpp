// test_powershell_highlight.cpp
// Ported from PowerShellHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct PowerShellHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "ps1"); }
};

TEST_F(PowerShellHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("function Get-Greeting {\n  param($Name)\n  return \"Hello\"\n}");
    EXPECT_NE(html.find("CLASS=keyword>function</font>"), std::string::npos);
    EXPECT_NE(html.find("CLASS=keyword>param</font>"), std::string::npos);
    EXPECT_NE(html.find("CLASS=keyword>return</font>"), std::string::npos);
}

TEST_F(PowerShellHighlightTest, ControlFlowKeywordsAreHighlighted) {
    auto html = hl("foreach ($item in $list) { if ($item) { break } }");
    EXPECT_NE(html.find("CLASS=keyword>foreach</font>"), std::string::npos);
    EXPECT_NE(html.find("CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_NE(html.find("CLASS=keyword>break</font>"), std::string::npos);
}

TEST_F(PowerShellHighlightTest, CaseInsensitiveKeywordsAreHighlighted) {
    auto html = hl("FUNCTION foo {}\nFOREACH ($x in $y) {}");
    EXPECT_NE(html.find("CLASS=keyword>FUNCTION</font>"), std::string::npos);
    EXPECT_NE(html.find("CLASS=keyword>FOREACH</font>"), std::string::npos);
}

TEST_F(PowerShellHighlightTest, ScalarVariableIsHighlighted) {
    auto html = hl("$Name = 'Alice'");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("CLASS=preproc>$Name</font>"), std::string::npos);
}

TEST_F(PowerShellHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"("Hello World")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PowerShellHighlightTest, SingleQuoteStringIsHighlighted) {
    auto html = hl("'literal string'");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(PowerShellHighlightTest, LineCommentIsHighlighted) {
    auto html = hl("$x = 1 # comment");
    EXPECT_NE(html.find("<font CLASS=comment># comment</font>"), std::string::npos);
}

TEST_F(PowerShellHighlightTest, BlockCommentIsHighlighted) {
    auto html = hl("<# this is\na block comment #>");
    EXPECT_NE(html.find("<font CLASS=comment>"), std::string::npos) << "block comment not highlighted";
}
