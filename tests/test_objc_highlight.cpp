// test_objc_highlight.cpp
// Ported from ObjectiveCHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ObjectiveCHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "m"); }
};

TEST_F(ObjectiveCHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("__block").find("<font CLASS=keyword>__block</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("BOOL").find("<font CLASS=keytype>BOOL</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, PreprocessorDirectivesAreHighlighted) {
    EXPECT_NE(hl("#define FOO").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, PreprocMacroNameIsHighlighted) {
    auto html = hl("#define MACRO_NAME");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>MACRO_NAME</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, PreprocMacroWithFloatValue) {
    auto html = hl("#define NUMBER 0.076");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>NUMBER</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>0.076</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, PreprocMacroBeforeEqualsIsHighlighted) {
    auto html = hl("#define NUMBER = 0.076");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>NUMBER</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=preproc>=</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, PreprocMacroWithFloatAndComment) {
    auto html = hl("#define LITERAL 0.076 // comment");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>LITERAL</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>0.076</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// comment"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, PreprocDoubleQuoteIncludeIsHighlighted) {
    auto html = hl(R"(#include "myheader.h")");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, PreprocAngleBracketIncludeIsHighlighted) {
    auto html = hl("#include <another_header.h>");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>&lt;another_header.h&gt;</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, PreprocIfdefGuardIsHighlighted) {
    auto html = hl("#ifdef GUARD");
    EXPECT_NE(html.find("<font CLASS=preproc>#ifdef</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>GUARD</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, PreprocEndifAloneHasNoSecondToken) {
    auto html = hl("#endif");
    EXPECT_NE(html.find("<font CLASS=preproc>#endif</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>"), 1);
}

TEST_F(ObjectiveCHighlightTest, PreprocEndifWithCommentHasNoSecondPreprocToken) {
    auto html = hl("#endif // comment");
    EXPECT_NE(html.find("<font CLASS=preproc>#endif</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment>// comment"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>"), 1);
}

TEST_F(ObjectiveCHighlightTest, PreprocIfOrOperatorHighlightsBothIdentifiers) {
    auto html = hl("#if defined(__APPLE__) || defined(__linux__)");
    EXPECT_NE(html.find("<font CLASS=preproc>#if</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 2);
}

TEST_F(ObjectiveCHighlightTest, PreprocIfAndOperatorHighlightsBothIdentifiers) {
    auto html = hl("#if defined(X) && defined(Y)");
    EXPECT_NE(html.find("<font CLASS=preproc>#if</font>"), std::string::npos);
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 2);
}

TEST_F(ObjectiveCHighlightTest, PreprocIfMultipleOperatorsHighlightAllIdentifiers) {
    auto html = hl("#if defined(A) || defined(B) || defined(C)");
    EXPECT_EQ(countOccurrences(html, "<font CLASS=preproc>defined</font>"), 3);
}

TEST_F(ObjectiveCHighlightTest, PreprocWithLeadingSpacesIsHighlighted) {
    auto html = hl("    #define LOCAL_VAL 10");
    EXPECT_NE(html.find("<font CLASS=preproc>#define</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>LOCAL_VAL</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, PreprocWithLeadingSpacesIfdefIsHighlighted) {
    auto html = hl("    #ifdef PLATFORM");
    EXPECT_NE(html.find("<font CLASS=preproc>#ifdef</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>PLATFORM</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, PreprocWithLeadingSpacesAngleBracketIncludeIsHighlighted) {
    auto html = hl("    #include <stdlib.h>");
    EXPECT_NE(html.find("<font CLASS=preproc>#include</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>&lt;stdlib.h&gt;</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, BlockCommentsAreHighlighted) {
    EXPECT_NE(hl("/* a comment */").find("<font CLASS=comment>/* a comment */</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("// comment").find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, UnderscoreNumbersAreNotFullyHighlighted) {
    EXPECT_EQ(hl("1_000").find("<font CLASS=integer>1_000</font>"), std::string::npos);
}

TEST_F(ObjectiveCHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(/* Block comment */
#import <Foundation/Foundation.h>
// Line comment
@interface Example : NSObject
@property BOOL flag;
@end
@implementation Example
- (void)run {
    self.flag = YES;
    CGFloat pi = 3.14;
    NSInteger x = 42;
    NSString *s = @"hello";
    char c = 'x';
    x = x + 1;
label:
    NSLog(@"%ld", (long)x);
}
@end)");
    EXPECT_NE(html.find("<font CLASS=keyword>self</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>BOOL</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>CGFloat</font>"), std::string::npos);
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
