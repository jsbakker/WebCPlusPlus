// test_nim_highlight.cpp
// Ported from NimHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct NimHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "nim"); }
};

TEST_F(NimHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("proc greet(name: string): string =\n  return \"Hello\"");
    EXPECT_NE(html.find("<font CLASS=keyword>proc</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>return</font>"), std::string::npos);
}

TEST_F(NimHighlightTest, CaseInsensitiveKeywordsAreHighlighted) {
    auto html = hl("PROC foo() =\n  VAR x = 1");
    EXPECT_NE(html.find("<font CLASS=keyword>PROC</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>VAR</font>"), std::string::npos);
}

TEST_F(NimHighlightTest, TypesAreHighlighted) {
    auto html = hl("var x: int = 0\nvar s: string = \"\"");
    EXPECT_NE(html.find("<font CLASS=keytype>int</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>string</font>"), std::string::npos);
}

TEST_F(NimHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"("hello nim")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(NimHighlightTest, TripleQuoteStringIsHighlighted) {
    auto html = hl("\"\"\"\nhello\n\"\"\"");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(NimHighlightTest, LineCommentIsHighlighted) {
    auto html = hl("var x = 1 # comment");
    EXPECT_NE(html.find("<font CLASS=comment># comment</font>"), std::string::npos);
}

TEST_F(NimHighlightTest, BlockCommentIsHighlighted) {
    auto html = hl("#[ this is\na block comment ]#");
    EXPECT_NE(html.find("<font CLASS=comment>#["), std::string::npos) << "block comment open not highlighted";
    EXPECT_NE(html.find("]#</font>"), std::string::npos) << "block comment close not highlighted";
}

TEST_F(NimHighlightTest, SymbolsAreHighlighted) {
    auto html = hl("z = x + y");
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(NimHighlightTest, UnderscoreNumbersAreHighlighted) {
    auto html = hl("n = 1_000_000");
    EXPECT_NE(html.find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}
