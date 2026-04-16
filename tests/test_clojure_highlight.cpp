// test_clojure_highlight.cpp
// Ported from ClojureHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ClojureHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "clj"); }
};

TEST_F(ClojureHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("(defn greet [name] (str \"Hello\" name))");
    EXPECT_NE(html.find("<font CLASS=keyword>defn</font>"), std::string::npos);
}

TEST_F(ClojureHighlightTest, MoreKeywordsAreHighlighted) {
    auto html = hl("(let [x 1] (if x (do x) nil))");
    EXPECT_NE(html.find("<font CLASS=keyword>let</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>do</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>nil</font>"), std::string::npos);
}

TEST_F(ClojureHighlightTest, TypesAreHighlighted) {
    auto html = hl("(instance? String s)");
    EXPECT_NE(html.find("<font CLASS=keytype>String</font>"), std::string::npos);
}

TEST_F(ClojureHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"("hello clojure")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ClojureHighlightTest, LineCommentIsHighlighted) {
    auto html = hl("; this is a comment");
    EXPECT_NE(html.find("<font CLASS=comment>; this is a comment</font>"), std::string::npos);
}

TEST_F(ClojureHighlightTest, SymbolsAreHighlighted) {
    auto html = hl("(+ 1 2)");
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}
