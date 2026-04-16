// test_wgsl_highlight.cpp
// Ported from WGSLHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct WGSLHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "wgsl"); }
};

TEST_F(WGSLHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("fn main() -> void {\n  let x: f32 = 0.0;\n  return;\n}");
    EXPECT_NE(html.find("<font CLASS=keyword>fn</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>let</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>return</font>"), std::string::npos);
}

TEST_F(WGSLHighlightTest, StructAndVarAreHighlighted) {
    auto html = hl("struct Uniforms { model: mat4x4f }\nvar<uniform> u: Uniforms;");
    EXPECT_NE(html.find("<font CLASS=keyword>struct</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>var</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>uniform</font>"), std::string::npos);
}

TEST_F(WGSLHighlightTest, AttributesAreHighlighted) {
    auto html = hl("@vertex\nfn vs_main(@location(0) pos: vec4f) -> @builtin(position) vec4f {");
    EXPECT_NE(html.find("<font CLASS=keyword>@vertex</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>@location</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>@builtin</font>"), std::string::npos);
}

TEST_F(WGSLHighlightTest, ScalarTypesAreHighlighted) {
    auto html = hl("var x: f32;\nvar y: i32;\nvar z: u32;");
    EXPECT_NE(html.find("<font CLASS=keytype>f32</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>i32</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>u32</font>"), std::string::npos);
}

TEST_F(WGSLHighlightTest, VectorTypesAreHighlighted) {
    auto html = hl("var v: vec4f;\nvar u: vec2<f32>;");
    EXPECT_NE(html.find("<font CLASS=keytype>vec4f</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>vec2</font>"), std::string::npos);
}

TEST_F(WGSLHighlightTest, MatrixTypesAreHighlighted) {
    auto html = hl("var m: mat4x4f;");
    EXPECT_NE(html.find("<font CLASS=keytype>mat4x4f</font>"), std::string::npos);
}

TEST_F(WGSLHighlightTest, BuiltinFunctionsAreHighlighted) {
    auto html = hl("let n = normalize(v);\nlet d = dot(a, b);");
    EXPECT_NE(html.find("<font CLASS=keytype>normalize</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>dot</font>"), std::string::npos);
}

TEST_F(WGSLHighlightTest, LineCommentIsHighlighted) {
    auto html = hl("let x = 1.0; // a comment");
    EXPECT_NE(html.find("<font CLASS=comment>// a comment</font>"), std::string::npos);
}

TEST_F(WGSLHighlightTest, BlockCommentIsHighlighted) {
    auto html = hl("/* block */");
    EXPECT_NE(html.find("<font CLASS=comment>/* block */</font>"), std::string::npos);
}
