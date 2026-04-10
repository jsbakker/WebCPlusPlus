// test_ruby_backslash.cpp
// Ported from RubyBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct RubyBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "rb"); }
};

TEST_F(RubyBackslashTest, DblQuoteOpeningLineHasClosedFontTag) {
    auto html = hl("s = \"hello \\\nworld\"");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(RubyBackslashTest, DblQuoteContinuationLineIsColoured) {
    auto html = hl("s = \"hello \\\nworld\"");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(RubyBackslashTest, BacktickOpeningLineHasClosedFontTag) {
    auto html = hl("result = `echo \\\nhello`");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "echo");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(RubyBackslashTest, BacktickContinuationLineIsColoured) {
    auto html = hl("result = `echo \\\nhello`");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "hello");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=preproc>"), std::string::npos);
}
