// test_julia_highlight.cpp
// Ported from JuliaHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct JuliaHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "jl"); }
};

TEST_F(JuliaHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("function greet(name)\n  return \"Hello\"\nend");
    EXPECT_NE(html.find("<font CLASS=keyword>function</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>return</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>end</font>"), std::string::npos);
}

TEST_F(JuliaHighlightTest, TypesAreHighlighted) {
    auto html = hl("x::Int = 0\ny::Float64 = 1.0");
    EXPECT_NE(html.find("<font CLASS=keytype>Int</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Float64</font>"), std::string::npos);
}

TEST_F(JuliaHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"("hello julia")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(JuliaHighlightTest, TripleQuoteStringIsHighlighted) {
    auto html = hl("\"\"\"\nhello\n\"\"\"");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(JuliaHighlightTest, LineCommentIsHighlighted) {
    auto html = hl("x = 1 # comment");
    EXPECT_NE(html.find("<font CLASS=comment># comment</font>"), std::string::npos);
}

TEST_F(JuliaHighlightTest, BlockCommentIsHighlighted) {
    auto html = hl("#= this is\na block comment =#");
    EXPECT_NE(html.find("<font CLASS=comment>#="), std::string::npos) << "block comment open not highlighted";
    EXPECT_NE(html.find("=#</font>"), std::string::npos) << "block comment close not highlighted";
}

TEST_F(JuliaHighlightTest, SymbolsAreHighlighted) {
    auto html = hl("z = x + y");
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(JuliaHighlightTest, UnderscoreNumbersAreHighlighted) {
    auto html = hl("n = 1_000_000");
    EXPECT_NE(html.find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}
