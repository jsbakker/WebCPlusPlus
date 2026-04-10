// test_zig_highlight.cpp
// Ported from ZigHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ZigHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "zig"); }
};

TEST_F(ZigHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("addrspace").find("<font CLASS=keyword>addrspace</font>"), std::string::npos);
}

TEST_F(ZigHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("anyerror").find("<font CLASS=keytype>anyerror</font>"), std::string::npos);
}

TEST_F(ZigHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(ZigHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(ZigHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ZigHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(ZigHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(ZigHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(ZigHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(ZigHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(ZigHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(// Zig comment
const std = @import("std");
pub fn main() !void {
    var x: i32 = 42;
    var y: f64 = 3.14;
    const s: []const u8 = "hello";
    const c: u8 = 'x';
    const err: anyerror = undefined;
    x = x + 1;
})");
    EXPECT_NE(html.find("<font CLASS=keyword>const</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>pub</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>anyerror</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Zig comment</font>"), std::string::npos);
}
