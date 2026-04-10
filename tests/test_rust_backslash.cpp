// test_rust_backslash.cpp
// Ported from RustBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct RustBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "rs"); }
};

TEST_F(RustBackslashTest, OpeningLineHasClosedFontTag) {
    auto html = hl("let s = \"hello \\\n    world\";");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(RustBackslashTest, ContinuationLineIsColoured) {
    auto html = hl("let s = \"hello \\\n    world\";");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(RustBackslashTest, MultiLineContinuationAllColoured) {
    auto html = hl("let s = \"alpha \\\n    beta \\\n    gamma\";");
    auto lines = splitLines(html);
    for (const char* label : {"alpha", "beta", "gamma"}) {
        auto* line = findLine(lines, label);
        ASSERT_NE(line, nullptr) << "Line containing '" << label << "' not found";
        EXPECT_NE(line->find("<font CLASS=dblquot>"), std::string::npos)
            << label << " must be inside dblquot";
    }
}
