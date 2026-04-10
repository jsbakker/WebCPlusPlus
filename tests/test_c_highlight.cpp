// test_c_highlight.cpp
// Ported from CHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct CHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "c"); }
};

TEST_F(CHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("break").find("<font CLASS=keyword>break</font>"), std::string::npos);
}

TEST_F(CHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("auto").find("<font CLASS=keytype>auto</font>"), std::string::npos);
}

TEST_F(CHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(CHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(CHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(CHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(CHighlightTest, PreprocessorDirectivesAreHighlighted) {
    EXPECT_NE(hl("#define FOO").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(CHighlightTest, PreprocMacroNameIsHighlighted) {
    auto html = hl("#define MACRO_NAME");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>MACRO_NAME</font>"), std::string::npos);
}

TEST_F(CHighlightTest, PreprocMacroWithFloatValue) {
    auto html = hl("#define NUMBER 0.076");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>NUMBER</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>0.076</font>"), std::string::npos);
}

TEST_F(CHighlightTest, PreprocMacroBeforeEqualsIsHighlighted) {
    auto html = hl("#define NUMBER = 0.076");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>NUMBER</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=preproc>=</font>"), std::string::npos);
}

TEST_F(CHighlightTest, PreprocMacroWithFloatAndComment) {
    auto html = hl("#define LITERAL 0.076 // comment");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>LITERAL</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>0.076</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// comment"), std::string::npos);
}

TEST_F(CHighlightTest, PreprocDoubleQuoteIncludeIsHighlighted) {
    auto html = hl(R"(#include "myheader.h")");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CHighlightTest, PreprocAngleBracketIncludeIsHighlighted) {
    auto html = hl("#include <another_header.h>");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>&lt;another_header.h&gt;</font>"), std::string::npos);
}

TEST_F(CHighlightTest, PreprocIfdefGuardIsHighlighted) {
    auto html = hl("#ifdef GUARD");
    EXPECT_NE(html.find("<font CLASS=preproc>#ifdef</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>GUARD</font>"), std::string::npos);
}

TEST_F(CHighlightTest, PreprocEndifAloneHasNoSecondToken) {
    auto html = hl("#endif");
    EXPECT_NE(html.find("<font CLASS=preproc>#endif</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>"), 1);
}

TEST_F(CHighlightTest, PreprocEndifWithCommentHasNoSecondPreprocToken) {
    auto html = hl("#endif // comment");
    EXPECT_NE(html.find("<font CLASS=preproc>#endif</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// comment"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>"), 1);
}

TEST_F(CHighlightTest, PreprocIfOrOperatorHighlightsBothIdentifiers) {
    auto html = hl("#if defined(__APPLE__) || defined(__linux__)");
    EXPECT_NE(html.find("<font CLASS=preproc>#if</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 2);
}

TEST_F(CHighlightTest, PreprocIfAndOperatorHighlightsBothIdentifiers) {
    auto html = hl("#if defined(X) && defined(Y)");
    EXPECT_NE(html.find("<font CLASS=preproc>#if</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 2);
}

TEST_F(CHighlightTest, PreprocIfMultipleOperatorsHighlightAllIdentifiers) {
    auto html = hl("#if defined(A) || defined(B) || defined(C)");
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 3);
}

TEST_F(CHighlightTest, PreprocWithLeadingSpacesIsHighlighted) {
    auto html = hl("    #define LOCAL_VAL 10");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>LOCAL_VAL</font>"), std::string::npos);
}

TEST_F(CHighlightTest, PreprocWithLeadingSpacesIfdefIsHighlighted) {
    auto html = hl("    #ifdef PLATFORM");
    EXPECT_NE(html.find("<font CLASS=preproc>#ifdef</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>PLATFORM</font>"), std::string::npos);
}

TEST_F(CHighlightTest, PreprocWithLeadingSpacesAngleBracketIncludeIsHighlighted) {
    auto html = hl("    #include <stdlib.h>");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>&lt;stdlib.h&gt;</font>"), std::string::npos);
}

TEST_F(CHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(CHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(CHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(CHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(CHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
#include <stdio.h>
// Line comment
int main(void) {
    auto x = 42;
    double pi = 3.14;
    char *s = "hello";
    char c = 'x';
    x = x + 1;
label:
    printf("%d\n", x);
    return 0;
})");
    EXPECT_NE(html.find("<font CLASS=keyword>return</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>double</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>auto</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>label:</font>"), std::string::npos);
}
