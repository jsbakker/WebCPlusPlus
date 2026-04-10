// test_vala_backslash.cpp
// Ported from ValaBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ValaBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "vala"); }
};

TEST_F(ValaBackslashTest, OpeningLineHasClosedFontTag) {
    auto html = hl("string s = \"hello \\\nworld\";");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(ValaBackslashTest, ContinuationLineIsColoured) {
    auto html = hl("string s = \"hello \\\nworld\";");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ValaBackslashTest, MultiLineContinuationAllColoured) {
    auto html = hl("string s = \"line1 \\\nline2 \\\nline3\";");
    auto lines = splitLines(html);
    for (const char* label : {"line1", "line2", "line3"}) {
        auto* line = findLine(lines, label);
        ASSERT_NE(line, nullptr) << "Line containing '" << label << "' not found";
        EXPECT_NE(line->find("<font CLASS=dblquot>"), std::string::npos)
            << label << " must be inside dblquot";
    }
}
