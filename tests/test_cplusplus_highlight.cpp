// test_cplusplus_highlight.cpp
// Ported from CPlusPlusHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct CPlusPlusHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "cpp"); }
};

// MARK: Keywords
TEST_F(CPlusPlusHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("alignas");
    EXPECT_NE(html.find("<font CLASS=keyword>alignas</font>"), std::string::npos);
}

// MARK: Types
TEST_F(CPlusPlusHighlightTest, TypesAreHighlighted) {
    auto html = hl("bool");
    EXPECT_NE(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
}

// MARK: Numbers
TEST_F(CPlusPlusHighlightTest, IntegersAreHighlighted) {
    auto html = hl("42");
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, FloatsAreHighlighted) {
    auto html = hl("3.14");
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

// MARK: Strings
TEST_F(CPlusPlusHighlightTest, DoubleQuotedStringsAreHighlighted) {
    auto html = hl(R"("hello")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, SingleQuotedStringsAreHighlighted) {
    auto html = hl("'hello'");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
}

// MARK: Symbols
TEST_F(CPlusPlusHighlightTest, SymbolsAreHighlighted) {
    auto html = hl("x + y");
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

// MARK: Preprocessor
TEST_F(CPlusPlusHighlightTest, PreprocessorDirectivesAreHighlighted) {
    auto html = hl("#define FOO");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, PreprocMacroNameIsHighlighted) {
    auto html = hl("#define MACRO_NAME");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>MACRO_NAME</font>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, PreprocMacroWithFloatValue) {
    auto html = hl("#define NUMBER 0.076");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>NUMBER</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>0.076</font>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, PreprocMacroBeforeEqualsIsHighlighted) {
    auto html = hl("#define NUMBER = 0.076");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>NUMBER</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=preproc>=</font>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, PreprocMacroWithFloatAndComment) {
    auto html = hl("#define LITERAL 0.076 // comment");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>LITERAL</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>0.076</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// comment"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, PreprocDoubleQuoteIncludeIsHighlighted) {
    auto html = hl(R"(#include "myheader.h")");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, PreprocAngleBracketIncludeIsHighlighted) {
    auto html = hl("#include <another_header.h>");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>&lt;another_header.h&gt;</font>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, PreprocIfdefGuardIsHighlighted) {
    auto html = hl("#ifdef GUARD");
    EXPECT_NE(html.find("<font CLASS=preproc>#ifdef</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>GUARD</font>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, PreprocEndifAloneHasNoSecondToken) {
    auto html = hl("#endif");
    EXPECT_NE(html.find("<font CLASS=preproc>#endif</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>"), 1);
}

TEST_F(CPlusPlusHighlightTest, PreprocEndifWithCommentHasNoSecondPreprocToken) {
    auto html = hl("#endif // comment");
    EXPECT_NE(html.find("<font CLASS=preproc>#endif</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// comment"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>"), 1);
}

TEST_F(CPlusPlusHighlightTest, PreprocIfOrOperatorHighlightsBothIdentifiers) {
    auto html = hl("#if defined(__APPLE__) || defined(__linux__)");
    EXPECT_NE(html.find("<font CLASS=preproc>#if</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 2);
}

TEST_F(CPlusPlusHighlightTest, PreprocIfAndOperatorHighlightsBothIdentifiers) {
    auto html = hl("#if defined(X) && defined(Y)");
    EXPECT_NE(html.find("<font CLASS=preproc>#if</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 2);
}

TEST_F(CPlusPlusHighlightTest, PreprocIfMultipleOperatorsHighlightAllIdentifiers) {
    auto html = hl("#if defined(A) || defined(B) || defined(C)");
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 3);
}

// MARK: Indented Preprocessor
TEST_F(CPlusPlusHighlightTest, PreprocWithLeadingSpacesIsHighlighted) {
    auto html = hl("    #define LOCAL_VAL 10");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>LOCAL_VAL</font>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, PreprocWithLeadingSpacesIfdefIsHighlighted) {
    auto html = hl("    #ifdef PLATFORM");
    EXPECT_NE(html.find("<font CLASS=preproc>#ifdef</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>PLATFORM</font>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, PreprocWithLeadingSpacesAngleBracketIncludeIsHighlighted) {
    auto html = hl("    #include <stdlib.h>");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>&lt;stdlib.h&gt;</font>"), std::string::npos);
}

// MARK: Comments
TEST_F(CPlusPlusHighlightTest, BlockCommentsAreHighlighted) {
    auto html = hl("/* a comment */");
    EXPECT_NE(html.find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, InlineCommentsAreHighlighted) {
    auto html = hl("// comment");
    EXPECT_NE(html.find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

// MARK: Raw Strings
TEST_F(CPlusPlusHighlightTest, RawStringsAreHighlighted) {
    auto html = hl(R"CPP(R"(raw string)")CPP");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

// MARK: Labels
TEST_F(CPlusPlusHighlightTest, LabelsAreHighlighted) {
    auto html = hl("label:");
    EXPECT_NE(html.find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

// MARK: String escape edge cases
TEST_F(CPlusPlusHighlightTest, EscapedQuoteInStringDoesNotTerminate) {
    auto html = hl(R"("hello \"world\" end" + x)");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("</font> <font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, BacktickStringsAreNotHighlighted) {
    auto html = hl("`command`");
    EXPECT_EQ(html.find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, CommentDelimiterInsideStringIsIgnored) {
    auto html = hl(R"("has // inside")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=comment>"), std::string::npos);
}

// MARK: Tab handling
TEST_F(CPlusPlusHighlightTest, TabExpansionDoesNotBreakHighlighting) {
    auto html = highlight("\tint\tx\t=\t42;", "cpp", {"-t"});
    EXPECT_NE(html.find("<font CLASS=keytype>int</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    auto prePos = html.find("<pre>");
    auto endPos = html.find("</pre>");
    if (prePos != std::string::npos && endPos != std::string::npos) {
        auto content = html.substr(prePos + 5, endPos - prePos - 5);
        EXPECT_EQ(content.find('\t'), std::string::npos) << "Tabs should be converted to spaces";
    }
}

TEST_F(CPlusPlusHighlightTest, TabExpansionAlignsTabs) {
    auto html = highlight("a\tb", "cpp", {"-t"});
    auto prePos = html.find("<pre>");
    auto endPos = html.find("</pre>");
    if (prePos != std::string::npos && endPos != std::string::npos) {
        auto content = html.substr(prePos + 5, endPos - prePos - 5);
        EXPECT_NE(content.find("a "), std::string::npos) << "Tab should be expanded to spaces";
        EXPECT_EQ(content.find('\t'), std::string::npos);
    }
}

// MARK: Block comment regression
TEST_F(CPlusPlusHighlightTest, KeywordBetweenTwoBlockCommentsIsHighlighted) {
    auto html = hl("int /* unused int */, int /* unused */, int c");
    int intCount = countOccurrences(html, "<font CLASS=keytype>int</font>");
    EXPECT_EQ(intCount, 3) << "Expected 3 highlighted 'int' keywords, got " << intCount;
    EXPECT_NE(html.find("<font CLASS=comment>/* unused int */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* unused */</font>"), std::string::npos);
}

TEST_F(CPlusPlusHighlightTest, SingleBlockCommentDoesNotBreakKeywords) {
    auto html = hl("int /* comment */ x = 42;");
    EXPECT_NE(html.find("<font CLASS=keytype>int</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

// MARK: Underscore Numbers
TEST_F(CPlusPlusHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    auto html = hl("1_000");
    EXPECT_EQ(html.find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

// MARK: Comprehensive Snippet
TEST_F(CPlusPlusHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    // Note: use R"CPP(...)CPP" so the inner R"(raw string)" doesn't terminate the literal.
    auto html = hl(R"CPP(/* Block comment */
#include <iostream>
// Line comment
class Example {
public:
    bool flag = true;
    int x = 42;
    double pi = 3.14;
    void run() {
        auto s = "hello";
        char c = 'x';
        auto raw = R"(raw string)";
        x = x + 1;
label:
        std::cout << x;
    }
};)CPP");

    EXPECT_NE(html.find("<font CLASS=keyword>class</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
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
