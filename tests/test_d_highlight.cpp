// test_d_highlight.cpp
// Ported from DHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct DHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "d"); }
};

TEST_F(DHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("module foo;\nimport std.stdio;\nvoid main() {}");
    EXPECT_NE(html.find("<font CLASS=keyword>module</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>import</font>"), std::string::npos);
}

TEST_F(DHighlightTest, MoreKeywordsAreHighlighted) {
    auto html = hl("class Foo : Bar {\n  override void run() {}\n}");
    EXPECT_NE(html.find("<font CLASS=keyword>class</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>override</font>"), std::string::npos);
}

TEST_F(DHighlightTest, TypesAreHighlighted) {
    auto html = hl("int x = 0;\nstring s = \"hi\";\nbool b = true;");
    EXPECT_NE(html.find("<font CLASS=keytype>int</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>string</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
}

TEST_F(DHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"("hello d")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(DHighlightTest, BacktickStringIsHighlighted) {
    auto html = hl("`raw string`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(DHighlightTest, LineCommentIsHighlighted) {
    auto html = hl("int x = 1; // comment");
    EXPECT_NE(html.find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(DHighlightTest, BlockCommentPLIIsHighlighted) {
    auto html = hl("/* block comment */");
    EXPECT_NE(html.find("<font CLASS=comment>/* block comment */</font>"), std::string::npos);
}

TEST_F(DHighlightTest, BlockCommentDIsHighlighted) {
    auto html = hl("/+ nested\nblock comment +/");
    EXPECT_NE(html.find("<font CLASS=comment>/+"), std::string::npos) << "D block comment open not highlighted";
    EXPECT_NE(html.find("+/</font>"), std::string::npos) << "D block comment close not highlighted";
}

TEST_F(DHighlightTest, SymbolsAreHighlighted) {
    auto html = hl("int z = x + y;");
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(DHighlightTest, UnderscoreNumbersAreHighlighted) {
    auto html = hl("int n = 1_000_000;");
    EXPECT_NE(html.find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}
