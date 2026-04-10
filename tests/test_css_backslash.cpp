// test_css_backslash.cpp
// Ported from CSSBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct CSSBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "css"); }
};

TEST_F(CSSBackslashTest, DblQuoteOpeningLineHasClosedFontTag) {
    auto html = hl("content: \"hello \\\nworld\";");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(CSSBackslashTest, DblQuoteContinuationLineIsColoured) {
    auto html = hl("content: \"hello \\\nworld\";");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CSSBackslashTest, SinQuoteOpeningLineHasClosedFontTag) {
    auto html = hl("content: 'hello \\\nworld';");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(CSSBackslashTest, SinQuoteContinuationLineIsColoured) {
    auto html = hl("content: 'hello \\\nworld';");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=sinquot>"), std::string::npos);
}
