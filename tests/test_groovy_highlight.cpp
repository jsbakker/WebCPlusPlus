// test_groovy_highlight.cpp
// Ported from GroovyHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct GroovyHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "groovy"); }
};

TEST_F(GroovyHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("def greet(String name) {\n  return \"Hello, ${name}\"\n}");
    EXPECT_NE(html.find("<font CLASS=keyword>def</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>return</font>"), std::string::npos);
}

TEST_F(GroovyHighlightTest, ClassKeywordsAreHighlighted) {
    auto html = hl("class Foo extends Bar implements Baz {}");
    EXPECT_NE(html.find("<font CLASS=keyword>class</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>extends</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>implements</font>"), std::string::npos);
}

TEST_F(GroovyHighlightTest, TraitKeywordIsHighlighted) {
    auto html = hl("trait Flyable {}");
    EXPECT_NE(html.find("<font CLASS=keyword>trait</font>"), std::string::npos);
}

TEST_F(GroovyHighlightTest, TypesAreHighlighted) {
    auto html = hl("String s\nInteger n\nList items");
    EXPECT_NE(html.find("<font CLASS=keytype>String</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Integer</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>List</font>"), std::string::npos);
}

TEST_F(GroovyHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"("hello groovy")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(GroovyHighlightTest, SingleQuoteStringIsHighlighted) {
    auto html = hl("'literal'");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(GroovyHighlightTest, LineCommentIsHighlighted) {
    auto html = hl("def x = 1 // comment");
    EXPECT_NE(html.find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(GroovyHighlightTest, BlockCommentIsHighlighted) {
    auto html = hl("/* block */");
    EXPECT_NE(html.find("<font CLASS=comment>/* block */</font>"), std::string::npos);
}
