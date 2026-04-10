// test_ocaml_highlight.cpp
// Ported from OCamlHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct OCamlHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "ml"); }
};

TEST_F(OCamlHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("and").find("<font CLASS=keyword>and</font>"), std::string::npos);
}

TEST_F(OCamlHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("bool").find("<font CLASS=keytype>bool</font>"), std::string::npos);
}

TEST_F(OCamlHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(OCamlHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(OCamlHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(OCamlHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(OCamlHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(OCamlHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("(* a comment *)").find("<font CLASS=comment>(* a comment *)</font>"), std::string::npos);
}

TEST_F(OCamlHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(OCamlHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(OCamlHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"((* Block comment *)
let x : int = 42
let pi : float = 3.14
let s : string = "hello"
let c : char = 'x'
let flag : bool = true
let result = x + 1)");
    EXPECT_NE(html.find("<font CLASS=keyword>let</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>(* Block comment *)</font>"), std::string::npos);
}
