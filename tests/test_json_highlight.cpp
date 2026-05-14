// test_json_highlight.cpp

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct JsonHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "json"); }
};

TEST_F(JsonHighlightTest, KeywordsAreHighlighted) {
    auto html = hl(R"({"a": true, "b": false, "c": null})");
    EXPECT_NE(html.find("<font CLASS=keyword>true</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>false</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>null</font>"), std::string::npos);
}

TEST_F(JsonHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"("hello world")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(JsonHighlightTest, IntegerIsHighlighted) {
    auto html = hl(R"({"count": 42})");
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(JsonHighlightTest, NegativeNumberIsHighlighted) {
    auto html = hl("-1");
    EXPECT_NE(html.find("<font CLASS=integer>1</font>"), std::string::npos);
}

TEST_F(JsonHighlightTest, LineCommentIsHighlighted) {
    // JSONC-style comment
    auto html = hl(R"({"x": 1} // comment)");
    EXPECT_NE(html.find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(JsonHighlightTest, BlockCommentIsHighlighted) {
    auto html = hl("/* block comment */");
    EXPECT_NE(html.find("<font CLASS=comment>/* block comment */</font>"), std::string::npos);
}

TEST_F(JsonHighlightTest, JsoncExtensionIsRecognized) {
    auto html = highlight(R"({"a": true})", "jsonc");
    EXPECT_NE(html.find("<font CLASS=keyword>true</font>"), std::string::npos);
}

TEST_F(JsonHighlightTest, Json5ExtensionIsRecognized) {
    auto html = highlight(R"({"a": true})", "json5");
    EXPECT_NE(html.find("<font CLASS=keyword>true</font>"), std::string::npos);
}
