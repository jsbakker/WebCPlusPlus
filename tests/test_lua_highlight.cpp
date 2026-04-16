// test_lua_highlight.cpp
// Ported from LuaHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct LuaHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "lua"); }
};

TEST_F(LuaHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("local x = nil\nif x then return end");
    EXPECT_NE(html.find("<font CLASS=keyword>local</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>nil</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>then</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>return</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>end</font>"), std::string::npos);
}

TEST_F(LuaHighlightTest, BooleanLiteralsAreHighlighted) {
    auto html = hl("local a = true\nlocal b = false");
    EXPECT_NE(html.find("<font CLASS=keyword>true</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>false</font>"), std::string::npos);
}

TEST_F(LuaHighlightTest, StdlibTypesAreHighlighted) {
    auto html = hl("math.floor(1.5)\nstring.len(s)");
    EXPECT_NE(html.find("<font CLASS=keytype>math</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>string</font>"), std::string::npos);
}

TEST_F(LuaHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"("hello world")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(LuaHighlightTest, SingleQuoteStringIsHighlighted) {
    auto html = hl("'hello'");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(LuaHighlightTest, LineCommentIsHighlighted) {
    auto html = hl("x = 1 -- assign x");
    EXPECT_NE(html.find("<font CLASS=comment>-- assign x</font>"), std::string::npos);
}

TEST_F(LuaHighlightTest, IntegerIsHighlighted) {
    auto html = hl("x = 42");
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(LuaHighlightTest, BlockCommentIsHighlighted) {
    auto html = hl("--[[ this is\na block comment ]]");
    EXPECT_NE(html.find("<font CLASS=comment>--[["), std::string::npos) << "block comment open not highlighted";
    EXPECT_NE(html.find("]]</font>"), std::string::npos) << "block comment close not highlighted";
}

TEST_F(LuaHighlightTest, BlockCommentDoesNotConsumeInlineComment) {
    // A plain -- should still work as an inline comment when not followed by [[
    auto html = hl("x = 1 -- plain comment");
    EXPECT_NE(html.find("<font CLASS=comment>-- plain comment</font>"), std::string::npos);
}
