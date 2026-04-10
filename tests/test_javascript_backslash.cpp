// test_javascript_backslash.cpp
// Ported from JavaScriptBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct JavaScriptBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "js"); }
};

TEST_F(JavaScriptBackslashTest, DblQuoteOpeningLineHasClosedFontTag) {
    auto html = hl("var s = \"hello \\\nworld\";");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(JavaScriptBackslashTest, DblQuoteContinuationLineIsColoured) {
    auto html = hl("var s = \"hello \\\nworld\";");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(JavaScriptBackslashTest, SinQuoteOpeningLineHasClosedFontTag) {
    auto html = hl("var s = 'hello \\\nworld';");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(JavaScriptBackslashTest, SinQuoteContinuationLineIsColoured) {
    auto html = hl("var s = 'hello \\\nworld';");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=sinquot>"), std::string::npos);
}
