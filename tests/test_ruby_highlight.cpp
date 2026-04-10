// test_ruby_highlight.cpp
// Ported from RubyHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct RubyHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "rb"); }
};

TEST_F(RubyHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("BEGIN").find("<font CLASS=keyword>BEGIN</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("Array").find("<font CLASS=keytype>Array</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(RubyHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(RubyHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, ScalarVariablesAreHighlighted) {
    EXPECT_NE(hl("$variable").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(RubyHighlightTest, ArrayVariablesAreHighlighted) {
    EXPECT_NE(hl("@array").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(RubyHighlightTest, HashVariablesAreHighlighted) {
    EXPECT_NE(hl("%hash").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(RubyHighlightTest, DuplicateSigilsDoNotHang) {
    auto html = hl("%class% $if$ @end@ yield");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>yield</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, PercentQBracesWithInterpolationHighlightsClosingBrace) {
    auto html = hl(R"(%Q{HTTP \#{status} response})");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    // The closing } should be inside the highlighted region, not after the last </font>
    auto afterLastClose = html.substr(html.rfind("</font>") + 7);
    EXPECT_EQ(afterLastClose.find("response}"), std::string::npos)
        << "Closing } should be inside the string highlight, not after it";
}

TEST_F(RubyHighlightTest, PercentQLowercaseWithNestedBraces) {
    EXPECT_NE(hl(R"(%q{a {nested} value})").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(RubyHighlightTest, HeredocStringIsHighlighted) {
    EXPECT_NE(hl("text = <<HEREDOC\nhello world\nHEREDOC").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(RubyHighlightTest, HeredocIndentedMarkerIsHighlighted) {
    EXPECT_NE(hl("text = <<~END\n  hello\n  END").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(RubyHighlightTest, HeredocDashMarkerIsHighlighted) {
    EXPECT_NE(hl("text = <<-TAG\nhello\n  TAG").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(RubyHighlightTest, HeredocQuotedMarkerIsHighlighted) {
    EXPECT_NE(hl("x = <<'EOF'\nhello\nEOF").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(RubyHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(RubyHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(RubyHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(RubyHighlightTest, HashInsideStringIsNotComment) {
    auto html = hl(R"(x = "has # inside")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=comment>"), std::string::npos);
}

TEST_F(RubyHighlightTest, EscapedHashIsNotComment) {
    EXPECT_EQ(hl("\\# not a comment").find("<font CLASS=comment>"), std::string::npos);
}

TEST_F(RubyHighlightTest, InterpolationDoesNotBreakStringHighlighting) {
    EXPECT_NE(hl(R"("Hello, #{name}!")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(RubyHighlightTest, IntegerInsideInterpolationIsHighlighted) {
    auto html = hl(R"("Age: #{42}")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, FloatInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"("Pi: #{3.14}")").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, SymbolInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"("Sum: #{a + b}")").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, KeywordInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"("Val: #{nil}")").find("<font CLASS=keyword>nil</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, TypeInsideInterpolationIsHighlighted) {
    EXPECT_NE(hl(R"("Size: #{Array.new.size}")").find("<font CLASS=keytype>Array</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, MultipleInterpolationBlocksAreHighlighted) {
    auto html = hl(R"("#{42} and #{3.14}")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, NestedBracesInsideInterpolationAreHandled) {
    auto html = hl(R"("#{arr.select{|x| x > 0}.size}")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>0</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, EscapedInterpolationIsNotProcessed) {
    auto html = hl(R"("literal \#{expr}")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>expr</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, SingleQuotedStringDoesNotInterpolate) {
    auto html = hl(R"('not #{interpolated}')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>"), std::string::npos);
}

TEST_F(RubyHighlightTest, IntegerInStringWithoutInterpolationIsNotHighlighted) {
    auto html = hl(R"("count is 42")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, SymbolInStringWithoutInterpolationIsNotHighlighted) {
    auto html = hl(R"("a + b")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, InterpolationWithTypecast) {
    auto html = hl(R"("val: #{Integer(x) + 1}")");
    EXPECT_NE(html.find("<font CLASS=keytype>Integer</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>1</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, MultipleInterpolatedExpressionsOnOneLine) {
    auto html = hl(R"(greeting = "Hello, #{name}! You have #{count + 2} messages.")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>2</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, MultilineStringInterpolationHighlightsContentOnContinuationLine) {
    const std::string source = "\"first line\n  value is #{42 + 1} here\"";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>1</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>here</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, MultilineStringBodyOutsideInterpolationIsNotHighlighted) {
    const std::string source = "\"first line\n  nil and 42 inside string\"";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>nil</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("# comment").find("<font CLASS=comment># comment</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(RubyHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(# Ruby comment
class Example
    def run
        @instance = 42
        $global = 3.14
        %hash = {}
        s = "hello"
        t = 'world'
        arr = Array.new
        x = @instance + 1
    end
end)");
    EXPECT_NE(html.find("<font CLASS=keyword>class</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>def</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>Array</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment># Ruby comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
}
