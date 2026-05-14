// test_toml_highlight.cpp

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct TomlHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "toml"); }
};

TEST_F(TomlHighlightTest, BooleanKeywordsAreHighlighted) {
    auto html = hl("enabled = true\ndisabled = false");
    EXPECT_NE(html.find("<font CLASS=keyword>true</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>false</font>"), std::string::npos);
}

TEST_F(TomlHighlightTest, SpecialFloatKeywordsAreHighlighted) {
    auto html = hl("x = inf\ny = nan");
    EXPECT_NE(html.find("<font CLASS=keyword>inf</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>nan</font>"), std::string::npos);
}

TEST_F(TomlHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"(name = "Alice")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(TomlHighlightTest, SingleQuoteStringIsHighlighted) {
    auto html = hl("path = 'C:\\Users\\Alice'");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(TomlHighlightTest, InlineCommentIsHighlighted) {
    auto html = hl("port = 8080 # default port");
    EXPECT_NE(html.find("<font CLASS=comment># default port</font>"), std::string::npos);
}

TEST_F(TomlHighlightTest, IntegerIsHighlighted) {
    auto html = hl("count = 42");
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(TomlHighlightTest, UnderscoreNumberIsHighlighted) {
    auto html = hl("big = 1_000_000");
    EXPECT_NE(html.find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(TomlHighlightTest, MultilineStringIsHighlighted) {
    auto html = hl("msg = \"\"\"\nhello\n\"\"\"");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}
