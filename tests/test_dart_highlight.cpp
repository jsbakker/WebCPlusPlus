// test_dart_highlight.cpp
// Ported from DartHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct DartHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "dart"); }
};

TEST_F(DartHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("class Foo extends Bar implements Baz {\n  final int x;\n}");
    EXPECT_NE(html.find("<font CLASS=keyword>class</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>extends</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>implements</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>final</font>"), std::string::npos);
}

TEST_F(DartHighlightTest, AsyncKeywordsAreHighlighted) {
    auto html = hl("Future<void> load() async {\n  await fetch();\n}");
    EXPECT_NE(html.find("<font CLASS=keyword>async</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>await</font>"), std::string::npos);
}

TEST_F(DartHighlightTest, NullSafetyKeywordsAreHighlighted) {
    auto html = hl("late String? name;");
    EXPECT_NE(html.find("<font CLASS=keyword>late</font>"), std::string::npos);
}

TEST_F(DartHighlightTest, TypesAreHighlighted) {
    auto html = hl("int x = 0;\nString s = '';\nList<int> items = [];");
    EXPECT_NE(html.find("<font CLASS=keytype>int</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>String</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>List</font>"), std::string::npos);
}

TEST_F(DartHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"("hello dart")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(DartHighlightTest, SingleQuoteStringIsHighlighted) {
    auto html = hl("'hello'");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(DartHighlightTest, LineCommentIsHighlighted) {
    auto html = hl("var x = 1; // comment");
    EXPECT_NE(html.find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(DartHighlightTest, BlockCommentIsHighlighted) {
    auto html = hl("/* block */");
    EXPECT_NE(html.find("<font CLASS=comment>/* block */</font>"), std::string::npos);
}
