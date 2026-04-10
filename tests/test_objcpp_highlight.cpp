// test_objcpp_highlight.cpp
// Ported from ObjectiveCPPHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ObjectiveCPPHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "mm"); }
};

TEST_F(ObjectiveCPPHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocessorDirectivesAreHighlighted) {
    EXPECT_NE(hl("#define FOO").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocMacroNameIsHighlighted) {
    auto html = hl("#define MACRO_NAME");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>MACRO_NAME</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocMacroWithFloatValue) {
    auto html = hl("#define NUMBER 0.076");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>NUMBER</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>0.076</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocMacroBeforeEqualsIsHighlighted) {
    auto html = hl("#define NUMBER = 0.076");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>NUMBER</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=preproc>=</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocMacroWithFloatAndComment) {
    auto html = hl("#define LITERAL 0.076 // comment");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>LITERAL</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>0.076</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// comment"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocDoubleQuoteIncludeIsHighlighted) {
    auto html = hl(R"(#include "myheader.h")");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocAngleBracketIncludeIsHighlighted) {
    auto html = hl("#include <another_header.h>");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>&lt;another_header.h&gt;</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocIfdefGuardIsHighlighted) {
    auto html = hl("#ifdef GUARD");
    EXPECT_NE(html.find("<font CLASS=preproc>#ifdef</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>GUARD</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocEndifAloneHasNoSecondToken) {
    auto html = hl("#endif");
    EXPECT_NE(html.find("<font CLASS=preproc>#endif</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>"), 1);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocEndifWithCommentHasNoSecondPreprocToken) {
    auto html = hl("#endif // comment");
    EXPECT_NE(html.find("<font CLASS=preproc>#endif</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// comment"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>"), 1);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocIfOrOperatorHighlightsBothIdentifiers) {
    auto html = hl("#if defined(__APPLE__) || defined(__linux__)");
    EXPECT_NE(html.find("<font CLASS=preproc>#if</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 2);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocIfAndOperatorHighlightsBothIdentifiers) {
    auto html = hl("#if defined(X) && defined(Y)");
    EXPECT_NE(html.find("<font CLASS=preproc>#if</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 2);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocIfMultipleOperatorsHighlightAllIdentifiers) {
    auto html = hl("#if defined(A) || defined(B) || defined(C)");
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 3);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocWithLeadingSpacesIsHighlighted) {
    auto html = hl("    #define LOCAL_VAL 10");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>LOCAL_VAL</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocWithLeadingSpacesIfdefIsHighlighted) {
    auto html = hl("    #ifdef PLATFORM");
    EXPECT_NE(html.find("<font CLASS=preproc>#ifdef</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>PLATFORM</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, PreprocWithLeadingSpacesAngleBracketIncludeIsHighlighted) {
    auto html = hl("    #include <stdlib.h>");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>&lt;stdlib.h&gt;</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, RawStringsAreHighlighted) {
    EXPECT_NE(hl(R"CPP(R"(raw string)")CPP").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(ObjectiveCPPHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"CPP(/* Block comment */
#import <Foundation/Foundation.h>
// Line comment
class CppHelper {
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
        NSLog(@"%d", x);
    }
};)CPP");
    EXPECT_NE(html.find("<font CLASS=keyword>class</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>#import</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>/* Block comment */</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// Line comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>label:</font>"), std::string::npos);
}
