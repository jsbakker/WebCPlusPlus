// test_yaml_highlight.cpp

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct YamlHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "yaml"); }
};

TEST_F(YamlHighlightTest, BooleanKeywordsAreHighlighted) {
    auto html = hl("enabled: true\ndisabled: false");
    EXPECT_NE(html.find("<font CLASS=keyword>true</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>false</font>"), std::string::npos);
}

TEST_F(YamlHighlightTest, NullKeywordIsHighlighted) {
    auto html = hl("value: null");
    EXPECT_NE(html.find("<font CLASS=keyword>null</font>"), std::string::npos);
}

TEST_F(YamlHighlightTest, CaseInsensitiveBooleans) {
    auto html = hl("a: True\nb: FALSE\nc: Yes\nd: NO");
    EXPECT_NE(html.find("<font CLASS=keyword>True</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>FALSE</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>Yes</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>NO</font>"), std::string::npos);
}

TEST_F(YamlHighlightTest, OnOffKeywordsAreHighlighted) {
    auto html = hl("feature: on\nother: off");
    EXPECT_NE(html.find("<font CLASS=keyword>on</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>off</font>"), std::string::npos);
}

TEST_F(YamlHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"(name: "Alice")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(YamlHighlightTest, SingleQuoteStringIsHighlighted) {
    auto html = hl("path: 'some/path'");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(YamlHighlightTest, CommentIsHighlighted) {
    auto html = hl("port: 8080 # default");
    EXPECT_NE(html.find("<font CLASS=comment># default</font>"), std::string::npos);
}

TEST_F(YamlHighlightTest, IntegerIsHighlighted) {
    auto html = hl("count: 42");
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(YamlHighlightTest, YmlExtensionIsRecognized) {
    auto html = highlight("enabled: true", "yml");
    EXPECT_NE(html.find("<font CLASS=keyword>true</font>"), std::string::npos);
}
