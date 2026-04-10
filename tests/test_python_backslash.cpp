// test_python_backslash.cpp
// Ported from PythonBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct PythonBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "py"); }
};

TEST_F(PythonBackslashTest, DblQuoteOpeningLineHasClosedFontTag) {
    auto html = hl("s = \"hello \\\nworld\"");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(PythonBackslashTest, DblQuoteContinuationLineIsColoured) {
    auto html = hl("s = \"hello \\\nworld\"");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PythonBackslashTest, SinQuoteOpeningLineHasClosedFontTag) {
    auto html = hl("s = 'hello \\\nworld'");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(PythonBackslashTest, SinQuoteContinuationLineIsColoured) {
    auto html = hl("s = 'hello \\\nworld'");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=sinquot>"), std::string::npos);
}
