// test_ocaml_backslash.cpp
// Ported from OCamlBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct OCamlBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "ml"); }
};

TEST_F(OCamlBackslashTest, OpeningLineHasClosedFontTag) {
    auto html = hl("let s = \"hello \\\n  world\"");
    auto lines = splitLines(html);
    auto* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(opening->find("</font>"), std::string::npos);
}

TEST_F(OCamlBackslashTest, ContinuationLineIsColoured) {
    auto html = hl("let s = \"hello \\\n  world\"");
    auto lines = splitLines(html);
    auto* cont = findLine(lines, "world");
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos);
}
