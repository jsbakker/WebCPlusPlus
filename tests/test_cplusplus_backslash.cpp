// test_cplusplus_backslash.cpp
// Ported from CPlusPlusBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct CPlusPlusBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "cpp"); }
};

// MARK: Baseline
TEST_F(CPlusPlusBackslashTest, SingleLineStringIsHighlighted) {
    auto html = hl(R"("hello world";)");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("</font>"), std::string::npos);
}

// MARK: Continuation line coloring
TEST_F(CPlusPlusBackslashTest, ContinuationLineWithNoQuotesIsColored) {
    const std::string source = R"("hello \
no quotes here \
done";)";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>no quotes here"), std::string::npos);
}

TEST_F(CPlusPlusBackslashTest, ContinuationLineWithEscapedQuotesIsColored) {
    const std::string source = R"("hello \
world \"escaped\" text\
done";)";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>world"), std::string::npos);
    EXPECT_NE(html.find("</font>"), std::string::npos);
}

TEST_F(CPlusPlusBackslashTest, ContinuationAfterOpeningLineWithHTMLEntities) {
    const std::string source = R"(s = "<br>\n\
plain text here \
end";)";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>plain text here"), std::string::npos);
}

TEST_F(CPlusPlusBackslashTest, ContinuationAfterOpeningLineWithEscapeSequences) {
    // source: x = "abc\n\   (with real newlines for continuation)
    const std::string source = "x = \"abc\\n\\\nplain\\\ndone\";";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>plain"), std::string::npos);
}

// MARK: Other highlighters must not fire inside continuation lines
TEST_F(CPlusPlusBackslashTest, KeywordInsideContinuationIsNotHighlighted) {
    const std::string source = R"("start \
int return void \
end";)";
    auto html = hl(source);
    EXPECT_EQ(html.find("<font CLASS=keyword>int</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>return</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keyword>void</font>"), std::string::npos);
}

TEST_F(CPlusPlusBackslashTest, TypeInsideContinuationIsNotHighlighted) {
    const std::string source = R"("start \
bool char double float \
end";)";
    auto html = hl(source);
    EXPECT_EQ(html.find("<font CLASS=keytype>bool</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=keytype>char</font>"), std::string::npos);
}

TEST_F(CPlusPlusBackslashTest, NumberInsideContinuationIsNotHighlighted) {
    const std::string source = R"("start \
42 3.14 \
end";)";
    auto html = hl(source);
    EXPECT_EQ(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(CPlusPlusBackslashTest, CommentInsideContinuationIsNotHighlighted) {
    const std::string source = R"("start \
// not a comment \
end";)";
    auto html = hl(source);
    EXPECT_EQ(html.find("<font CLASS=comment>// not a comment</font>"), std::string::npos);
}

TEST_F(CPlusPlusBackslashTest, SymbolInsideContinuationIsNotHighlighted) {
    const std::string source = R"("start \
+ - = \
end";)";
    auto html = hl(source);
    EXPECT_EQ(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=symbols>-</font>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=symbols>=</font>"), std::string::npos);
}

// MARK: Code after string closes is highlighted normally
TEST_F(CPlusPlusBackslashTest, KeywordAfterClosingLineIsHighlighted) {
    const std::string source = R"("hello \
world";
return x;)";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=keyword>return</font>"), std::string::npos);
}

TEST_F(CPlusPlusBackslashTest, NumberAfterClosingLineIsHighlighted) {
    const std::string source = R"("hello \
world";
42)";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
}

// MARK: Opening line font tag must be closed
TEST_F(CPlusPlusBackslashTest, OpeningLineHasClosedFontTag) {
    const std::string source = "\"hello \\\nworld\";";
    auto html = hl(source);
    auto lines = splitLines(html);
    const std::string* openingLine = nullptr;
    for (const auto& l : lines) {
        if (l.find("<font CLASS=dblquot>") != std::string::npos && l.find("hello") != std::string::npos) {
            openingLine = &l;
            break;
        }
    }
    ASSERT_NE(openingLine, nullptr) << "Opening line should contain dblquot font tag";
    EXPECT_NE(openingLine->find("</font>"), std::string::npos)
        << "Opening line's font tag must be closed: " << *openingLine;
}

TEST_F(CPlusPlusBackslashTest, OpeningLineWithHTMLEntitiesHasClosedFontTag) {
    const std::string source = "made = \"<center>\\n<br>\\n\\\nsyntax highlighting by<br>\\n\\\nend\";";
    auto html = hl(source);
    auto lines = splitLines(html);

    const std::string* openingLine = findLine(lines, "&lt;center&gt;");
    ASSERT_NE(openingLine, nullptr) << "Should find line with &lt;center&gt;";
    EXPECT_NE(openingLine->find("<font CLASS=dblquot>"), std::string::npos)
        << "Opening line must start string highlighting";
    EXPECT_NE(openingLine->find("</font>"), std::string::npos)
        << "Opening line's font tag must be closed: " << *openingLine;

    const std::string* contLine1 = findLine(lines, "syntax highlighting");
    ASSERT_NE(contLine1, nullptr) << "Should find first continuation line";
    EXPECT_NE(contLine1->find("<font CLASS=dblquot>"), std::string::npos)
        << "First continuation must have dblquot tag: " << *contLine1;
    EXPECT_NE(contLine1->find("</font>"), std::string::npos)
        << "First continuation's font tag must be closed: " << *contLine1;
}

TEST_F(CPlusPlusBackslashTest, EndHtmlPatternFullFidelity) {
    const std::string source = R"(made = "<center>\n<hr size=4 width=95%>\n<br>\n\
syntax highlighting by<br><br>\n\
<table cellpadding=3 cellspacing=3 bgcolor=#000000><tr>\n\
</a></td></tr>\n</table>\n<br>\n</center>";)";
    auto html = hl(source);
    auto lines = splitLines(html);

    const std::string* openingLine = findLine(lines, "&lt;center&gt;");
    EXPECT_NE(openingLine, nullptr);
    if (openingLine) {
        EXPECT_NE(openingLine->find("<font CLASS=dblquot>"), std::string::npos)
            << "Opening line must have dblquot: " << *openingLine;
        EXPECT_NE(openingLine->find("</font>"), std::string::npos)
            << "Opening line font must be closed: " << *openingLine;
    }

    const std::string* contLine1 = findLine(lines, "syntax highlighting");
    EXPECT_NE(contLine1, nullptr);
    if (contLine1) {
        EXPECT_NE(contLine1->find("<font CLASS=dblquot>"), std::string::npos)
            << "Cont line 1 must have dblquot: " << *contLine1;
    }

    const std::string* contLine2 = findLine(lines, "cellpadding");
    EXPECT_NE(contLine2, nullptr);
    if (contLine2) {
        EXPECT_NE(contLine2->find("<font CLASS=dblquot>"), std::string::npos)
            << "Cont line 2 must have dblquot: " << *contLine2;
    }

    const std::string* closingLine = findLine(lines, "&lt;/center&gt;");
    EXPECT_NE(closingLine, nullptr);
    if (closingLine) {
        EXPECT_NE(closingLine->find("<font CLASS=dblquot>"), std::string::npos)
            << "Closing line must have dblquot: " << *closingLine;
    }
}

TEST_F(CPlusPlusBackslashTest, BegHtmlPatternWithEscapedQuotes) {
    const std::string source = "gen = \"\\\nPublic \\\"quoted\\\" text\\\nGet webcpp\";";
    auto html = hl(source);
    auto lines = splitLines(html);

    const std::string* openingLine = nullptr;
    for (const auto& l : lines) {
        if (l.find("gen") != std::string::npos && l.find("<font CLASS=dblquot>") != std::string::npos) {
            openingLine = &l;
            break;
        }
    }
    ASSERT_NE(openingLine, nullptr) << "Opening line must have dblquot tag";
    EXPECT_NE(openingLine->find("</font>"), std::string::npos)
        << "Opening line font tag must be closed: " << *openingLine;

    const std::string* contLine = findLine(lines, "Public");
    EXPECT_NE(contLine, nullptr);
    if (contLine) {
        EXPECT_NE(contLine->find("<font CLASS=dblquot>"), std::string::npos)
            << "Continuation with escaped quotes must have dblquot: " << *contLine;
    }
}

// MARK: Every continuation line in a long chain is coloured
TEST_F(CPlusPlusBackslashTest, FiveContinuationLinesAllColoured) {
    const std::string source = "\"line1 \\\nline2 \\\nline3 \\\nline4 \\\nline5 \\\nend\";";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=dblquot>\"line1"), std::string::npos)
        << "line1 must be inside dblquot span";
    for (int i = 2; i <= 5; ++i) {
        EXPECT_NE(html.find("<font CLASS=dblquot>line" + std::to_string(i)), std::string::npos)
            << "line" << i << " must be inside dblquot span";
    }
}

TEST_F(CPlusPlusBackslashTest, EveryLineHasBalancedFontTags) {
    const std::string source = "\"aaa \\\nbbb \\\nccc \\\nddd\";";
    auto html = hl(source);
    auto lines = splitLines(html);
    for (const auto& line : lines) {
        int opens  = countOccurrences(line, "<font CLASS=dblquot>");
        int closes = countOccurrences(line, "</font>");
        bool relevant = (opens > 0 && line.find("aaa") != std::string::npos)
                     || line.find("bbb") != std::string::npos
                     || line.find("ccc") != std::string::npos
                     || line.find("ddd") != std::string::npos;
        if (relevant) {
            EXPECT_LE(opens, closes) << "Unbalanced font tags on line: " << line;
        }
    }
}

// MARK: Single-quote continuation
TEST_F(CPlusPlusBackslashTest, SingleQuoteContinuationIsColoured) {
    const std::string source = "'hello \\\nworld';";
    auto html = hl(source);
    auto lines = splitLines(html);
    const std::string* openingLine = findLine(lines, "hello");
    ASSERT_NE(openingLine, nullptr);
    EXPECT_NE(openingLine->find("<font CLASS=sinquot>"), std::string::npos)
        << "Single-quote opening must have sinquot: " << *openingLine;
    EXPECT_NE(openingLine->find("</font>"), std::string::npos)
        << "Single-quote opening font must be closed: " << *openingLine;
}

// MARK: Opening line content is visually highlighted
TEST_F(CPlusPlusBackslashTest, OpeningLineContentAfterQuoteIsInsideFontSpan) {
    const std::string source = "x = \"<br>content here\\\nnext\";";
    auto html = hl(source);
    auto lines = splitLines(html);
    const std::string* pLine = findLine(lines, "content here");
    ASSERT_NE(pLine, nullptr);
    const std::string& ol = *pLine;

    auto fontStart  = ol.find("<font CLASS=dblquot>");
    auto contentPos = ol.find("content here");
    ASSERT_NE(fontStart,  std::string::npos) << "Must have opening font tag";
    ASSERT_NE(contentPos, std::string::npos) << "Must have content";
    auto fontEnd = ol.find("</font>", contentPos);
    ASSERT_NE(fontEnd, std::string::npos) << "Must have closing font tag after content";
    EXPECT_LE(fontStart + std::string("<font CLASS=dblquot>").size(), contentPos)
        << "Font tag must come before content";
    EXPECT_LE(contentPos + std::string("content here").size(), fontEnd)
        << "Content must come before closing font tag";
}
