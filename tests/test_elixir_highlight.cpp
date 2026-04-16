// test_elixir_highlight.cpp
// Ported from ElixirHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ElixirHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "ex"); }
};

TEST_F(ElixirHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("defmodule Foo do\n  def bar, do: nil\nend");
    EXPECT_NE(html.find("<font CLASS=keyword>defmodule</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>def</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>do</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>end</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>nil</font>"), std::string::npos);
}

TEST_F(ElixirHighlightTest, TypesAreHighlighted) {
    auto html = hl("is_binary(String.upcase(s))");
    EXPECT_NE(html.find("<font CLASS=keytype>String</font>"), std::string::npos);
}

TEST_F(ElixirHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"("hello elixir")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ElixirHighlightTest, SingleQuoteStringIsHighlighted) {
    auto html = hl("'charlist'");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(ElixirHighlightTest, LineCommentIsHighlighted) {
    auto html = hl("x = 1 # comment");
    EXPECT_NE(html.find("<font CLASS=comment># comment</font>"), std::string::npos);
}

TEST_F(ElixirHighlightTest, TripleQuoteStringIsHighlighted) {
    auto html = hl("\"\"\"\nhello\n\"\"\"");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ElixirHighlightTest, ModuleAttributeIsHighlighted) {
    auto html = hl("@moduledoc \"docs\"");
    EXPECT_NE(html.find("<font CLASS=preproc>@moduledoc</font>"), std::string::npos);
}

TEST_F(ElixirHighlightTest, SymbolsAreHighlighted) {
    auto html = hl("x = 1 + 2");
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(ElixirHighlightTest, UnderscoreNumbersAreHighlighted) {
    auto html = hl("x = 1_000_000");
    EXPECT_NE(html.find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}
