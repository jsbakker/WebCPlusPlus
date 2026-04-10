// test_c_backslash.cpp
// Ported from CBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct CBackslashTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "c"); }
};

TEST_F(CBackslashTest, OpeningLineHasClosedFontTag) {
    const std::string source = "\"hello \\\nworld\";";
    auto html = hl(source);
    auto lines = splitLines(html);
    const std::string* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr) << "Opening line must have dblquot tag";
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos)
        << "Opening line must have dblquot tag: " << *opening;
    EXPECT_NE(opening->find("</font>"), std::string::npos)
        << "Opening line font tag must be closed: " << *opening;
}

TEST_F(CBackslashTest, ContinuationLineIsColoured) {
    const std::string source = "\"hello \\\nworld\";";
    auto html = hl(source);
    auto lines = splitLines(html);
    const std::string* cont = nullptr;
    for (const auto& l : lines) {
        if (l.find("world") != std::string::npos && l.find("\"world\"") == std::string::npos) {
            cont = &l;
            break;
        }
    }
    ASSERT_NE(cont, nullptr) << "Continuation line must have dblquot tag";
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos)
        << "Continuation line must have dblquot tag: " << *cont;
}

TEST_F(CBackslashTest, MultipleContiguousContinuationLinesAllColoured) {
    const std::string source = "\"line1 \\\nline2 \\\nline3\";";
    auto html = hl(source);
    auto lines = splitLines(html);
    for (const char* label : {"line1", "line2", "line3"}) {
        const std::string* line = findLine(lines, label);
        ASSERT_NE(line, nullptr) << label << " line not found";
        EXPECT_NE(line->find("<font CLASS=dblquot>"), std::string::npos)
            << label << " must be inside dblquot span: " << *line;
    }
}

TEST_F(CBackslashTest, CodeAfterStringHighlightsNormally) {
    const std::string source = "\"hello \\\nworld\";\nreturn 0;";
    auto html = hl(source);
    EXPECT_NE(html.find("<font CLASS=keyword>return</font>"), std::string::npos)
        << "Keyword after multi-line string must be highlighted";
}
