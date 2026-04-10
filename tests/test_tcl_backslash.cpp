// test_tcl_backslash.cpp
// Ported from TclBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct TclBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "tcl"); }
};

TEST_F(TclBackslashTest, OpeningLineHasClosedFontTag) {
    auto html = hl("set s \"hello \\\nworld\"");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(TclBackslashTest, ContinuationLineIsColoured) {
    auto html = hl("set s \"hello \\\nworld\"");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos);
}
