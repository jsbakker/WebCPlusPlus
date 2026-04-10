// test_assembly_backslash.cpp
// Ported from AssemblyBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct AssemblyBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "asm"); }
};

TEST_F(AssemblyBackslashTest, DblQuoteOpeningLineHasClosedFontTag) {
    auto html = hl("msg db \"hello \\\nworld\", 0");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(AssemblyBackslashTest, DblQuoteContinuationLineIsColoured) {
    auto html = hl("msg db \"hello \\\nworld\", 0");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(AssemblyBackslashTest, SinQuoteOpeningLineHasClosedFontTag) {
    auto html = hl("msg db 'hello \\\nworld', 0");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(AssemblyBackslashTest, SinQuoteContinuationLineIsColoured) {
    auto html = hl("msg db 'hello \\\nworld', 0");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=sinquot>"), std::string::npos);
}
