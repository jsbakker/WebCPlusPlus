// The WGSL (WebGPU Shading Language) definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langwgsl.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangWGSL::LangWGSL() {

    initReservedWords();

    doSymbols             = true;
    doUnderscoreNumbers   = true;
    doInlineCommentDblSlash = true;  // //
    doBlockCommentPLI     = true;    // /* */
}

void LangWGSL::initReservedWords() {

    // WGSL keywords and attributes (W3C WebGPU Shading Language spec)
    string K[] = {
        // Attributes (@ prefix like Swift)
        "@binding",      "@builtin",      "@compute",      "@const",
        "@fragment",     "@group",        "@id",           "@interpolate",
        "@invariant",    "@location",     "@must_use",     "@size",
        "@align",        "@vertex",       "@workgroup_size",
        // Control flow
        "break",         "case",          "const",         "const_assert",
        "continue",      "continuing",    "default",       "diagnostic",
        "discard",       "else",          "enable",        "fn",
        "for",           "if",            "let",           "loop",
        "override",      "requires",      "return",        "struct",
        "switch",        "type",          "var",           "while",
        // Address spaces and access modes
        "function",      "private",       "storage",       "uniform",
        "workgroup",     "read",          "read_write",    "write",
        // Value literals
        "false",         "true",
    };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));

    // WGSL types and built-in functions
    string T[] = {
        // Scalar types
        "bool",   "f16",    "f32",    "i32",    "u32",
        // Vector types
        "vec2",   "vec2f",  "vec2h",  "vec2i",  "vec2u",
        "vec3",   "vec3f",  "vec3h",  "vec3i",  "vec3u",
        "vec4",   "vec4f",  "vec4h",  "vec4i",  "vec4u",
        // Matrix types
        "mat2x2", "mat2x2f", "mat2x3", "mat2x3f", "mat2x4", "mat2x4f",
        "mat3x2", "mat3x2f", "mat3x3", "mat3x3f", "mat3x4", "mat3x4f",
        "mat4x2", "mat4x2f", "mat4x3", "mat4x3f", "mat4x4", "mat4x4f",
        // Other types
        "array",  "atomic", "ptr",    "sampler", "sampler_comparison",
        // Texture types
        "texture_1d",                "texture_2d",               "texture_2d_array",
        "texture_3d",                "texture_cube",             "texture_cube_array",
        "texture_depth_2d",          "texture_depth_2d_array",   "texture_depth_cube",
        "texture_depth_cube_array",  "texture_depth_multisampled_2d",
        "texture_external",          "texture_multisampled_2d",
        "texture_storage_1d",        "texture_storage_2d",
        "texture_storage_2d_array",  "texture_storage_3d",
        // Built-in functions (commonly used)
        "abs",      "acos",     "acosh",    "all",      "any",
        "arrayLength", "asin",  "asinh",    "atan",     "atan2",
        "atanh",    "ceil",     "clamp",    "cos",      "cosh",
        "cross",    "degrees",  "distance", "dot",      "exp",
        "exp2",     "faceForward", "floor", "fma",      "fract",
        "frexp",    "inverseSqrt", "ldexp", "length",   "log",
        "log2",     "max",      "min",      "mix",      "modf",
        "normalize","pow",      "radians",  "reflect",  "refract",
        "round",    "saturate", "select",   "sign",     "sin",
        "sinh",     "smoothstep", "sqrt",   "step",     "tan",
        "tanh",     "transpose","trunc",
        "storageBarrier", "textureBarrier", "workgroupBarrier", "workgroupUniformLoad",
    };
    std::copy(std::cbegin(T), std::cend(T), std::back_inserter(types));
}
