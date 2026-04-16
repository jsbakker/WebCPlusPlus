// The Dart Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langdart.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangDart::LangDart() {

    initReservedWords();

    doStringsSinQuote            = true;
    doSymbols                    = true;
    doUnderscoreNumbers          = true;
    doBlockCommentPLI            = true;  // /* */
    doInlineCommentDblSlash      = true;  // //
    doMultilineStrTripleDblQuote = true;  // """…"""
    // Dart string interpolation: "text ${expr}" or "text $name"
    doInterpolate  = true;
    interpolStart  = "${";
    interpolEnd    = '}';
}

void LangDart::initReservedWords() {

    // Dart 3.x keywords (reserved + built-in identifiers)
    string K[] = {
        "abstract",   "as",         "assert",     "async",      "await",
        "base",       "break",      "case",       "catch",      "class",
        "const",      "continue",   "covariant",  "default",    "deferred",
        "do",         "dynamic",    "else",       "enum",       "export",
        "extends",    "extension",  "external",   "factory",    "false",
        "final",      "finally",    "for",        "Function",   "get",
        "hide",       "if",         "implements", "import",     "in",
        "interface",  "is",         "late",       "library",    "mixin",
        "new",        "null",       "on",         "operator",   "override",
        "part",       "required",   "rethrow",    "return",     "sealed",
        "set",        "show",       "static",     "super",      "switch",
        "sync",       "this",       "throw",      "true",       "try",
        "typedef",    "var",        "void",       "when",       "while",
        "with",       "yield",
    };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));

    // Dart built-in types
    string T[] = {
        "bool",     "double",   "Duration", "Future",   "int",
        "Iterable", "Iterator", "List",     "Map",      "Never",
        "Null",     "num",      "Object",   "Record",   "Set",
        "Stream",   "String",   "Symbol",   "Type",
    };
    std::copy(std::cbegin(T), std::cend(T), std::back_inserter(types));
}
