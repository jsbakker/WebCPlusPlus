// test_haskell_backslash.cpp
// Ported from HaskellBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct HaskellBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "hs"); }
};

TEST_F(HaskellBackslashTest, OpeningLineHasClosedFontTag) {
    auto html = hl("s = \"hello \\\n\\world\"");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(HaskellBackslashTest, ContinuationLineIsColoured) {
    auto html = hl("s = \"hello \\\n\\world\"");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos);
}
