// test_objc_backslash.cpp
// Ported from ObjectiveCBackslashContinuationTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct ObjectiveCBackslashTest : ::testing::Test {};

// MARK: Objective-C (.m)
TEST_F(ObjectiveCBackslashTest, ObjcOpeningLineHasClosedFontTag) {
    const std::string source = "NSString *s = @\"hello \\\nworld\";";
    auto html = highlight(source, "m");
    auto lines = splitLines(html);
    const std::string* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos)
        << "ObjC opening line must have dblquot: " << *opening;
    EXPECT_NE(opening->find("</font>"), std::string::npos)
        << "ObjC opening line font tag must be closed: " << *opening;
}

TEST_F(ObjectiveCBackslashTest, ObjcContinuationLineIsColoured) {
    const std::string source = "NSString *s = @\"hello \\\nworld\";";
    auto html = highlight(source, "m");
    auto lines = splitLines(html);
    const std::string* cont = nullptr;
    for (const auto& l : lines) {
        if (l.find("world") != std::string::npos && l.find("@") == std::string::npos) {
            cont = &l;
            break;
        }
    }
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos)
        << "ObjC continuation line must have dblquot: " << *cont;
}

// MARK: Objective-C++ (.mm)
TEST_F(ObjectiveCBackslashTest, ObjcppOpeningLineHasClosedFontTag) {
    const std::string source = "std::string s = \"hello \\\nworld\";";
    auto html = highlight(source, "mm");
    auto lines = splitLines(html);
    const std::string* opening = findLine(lines, "hello");
    ASSERT_NE(opening, nullptr);
    EXPECT_NE(opening->find("<font CLASS=dblquot>"), std::string::npos)
        << "ObjC++ opening line must have dblquot: " << *opening;
    EXPECT_NE(opening->find("</font>"), std::string::npos)
        << "ObjC++ opening line font tag must be closed: " << *opening;
}

TEST_F(ObjectiveCBackslashTest, ObjcppContinuationLineIsColoured) {
    const std::string source = "std::string s = \"hello \\\nworld\";";
    auto html = highlight(source, "mm");
    auto lines = splitLines(html);
    const std::string* cont = nullptr;
    for (const auto& l : lines) {
        if (l.find("world") != std::string::npos && l.find("std") == std::string::npos) {
            cont = &l;
            break;
        }
    }
    ASSERT_NE(cont, nullptr);
    EXPECT_NE(cont->find("<font CLASS=dblquot>"), std::string::npos)
        << "ObjC++ continuation line must have dblquot: " << *cont;
}
