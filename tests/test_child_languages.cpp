// test_child_languages.cpp
// Ported from ChildLanguageTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

TEST(ChildLanguageTest, CppInlineAsmHighlightsAssemblyKeywords) {
    auto html = highlight(R"(int x = 5;
asm {
    mov eax, 1
})", "cpp");
    EXPECT_NE(html.find("<font CLASS=keyword>mov</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>eax</font>"), std::string::npos);
}

TEST(ChildLanguageTest, CppInlineAsmPreservesParentHighlighting) {
    auto html = highlight(R"(int x = 5;
asm {
    mov eax, 1
}
int y = 10;)", "cpp");
    EXPECT_NE(html.find("<font CLASS=keytype>int</font> x"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>int</font> y"), std::string::npos);
}

TEST(ChildLanguageTest, HtmlInlineCssHighlightsCssRules) {
    auto html = highlight(R"(<html>
<style>
body { color: red; }
</style>
</html>)", "html");
    EXPECT_NE(html.find("<font CLASS=keytype>color</font>"), std::string::npos);
}

TEST(ChildLanguageTest, HtmlInlineJsHighlightsJsKeywords) {
    auto html = highlight(R"(<html>
<script>
const x = 42;
</script>
</html>)", "html");
    EXPECT_NE(html.find("<font CLASS=keyword>const</font>"), std::string::npos);
}

TEST(ChildLanguageTest, HtmlWithBothCssAndJsHighlightsAllThreeLanguages) {
    auto html = highlight(R"(<html>
<head>
<style>
body { color: red; }
</style>
<script>
const x = 42;
</script>
</head>
<body>
<p>Hello</p>
</body>
</html>)", "html");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>color</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>const</font>"), std::string::npos);
}
