// test_shell_backslash.cpp
// Ported from ShellBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ShellBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "sh"); }
};

TEST_F(ShellBackslashTest, DblQuoteOpeningLineHasClosedFontTag) {
    auto html = hl("MSG=\"hello \\\nworld\"");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(ShellBackslashTest, DblQuoteContinuationLineIsColoured) {
    auto html = hl("MSG=\"hello \\\nworld\"");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ShellBackslashTest, BacktickOpeningLineHasClosedFontTag) {
    auto html = hl("OUT=`echo \\\nhello`");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "echo");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(ShellBackslashTest, BacktickContinuationLineIsColoured) {
    auto html = hl("OUT=`echo \\\nhello`");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "hello");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=preproc>"), std::string::npos);
}
