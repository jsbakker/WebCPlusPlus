// The Groovy Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langgroovy.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangGroovy::LangGroovy() {

    initReservedWords();

    doStringsSinQuote            = true;
    doStringsBackTick            = true;
    doSymbols                    = true;
    doUnderscoreNumbers          = true;
    doBlockCommentPLI            = true;  // /* */
    doInlineCommentDblSlash      = true;  // //
    doMultilineStrTripleDblQuote = true;  // """…"""
    doScalars                    = true;  // $variable
    // Groovy string interpolation: "text ${expr}" or "text $name"
    doInterpolate  = true;
    interpolStart  = "${";
    interpolEnd    = '}';
    doRequireBackslashContinuation = false; // Groovy GStrings may span lines
}

void LangGroovy::initReservedWords() {

    // Groovy 4.x keywords
    string K[] = {
        "as",          "assert",    "break",      "case",      "catch",
        "class",       "const",     "continue",   "def",       "default",
        "do",          "else",      "enum",       "extends",   "false",
        "final",       "finally",   "for",        "goto",      "if",
        "implements",  "import",    "in",         "instanceof", "interface",
        "new",         "null",      "package",    "return",    "static",
        "super",       "switch",    "this",       "throw",     "throws",
        "trait",       "true",      "try",        "var",       "while",
    };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));

    // Groovy / JVM types
    string T[] = {
        "BigDecimal", "BigInteger", "Boolean",  "Byte",      "Character",
        "Closure",    "Date",       "Double",   "Float",     "GString",
        "HashMap",    "Integer",    "List",     "Long",      "Map",
        "Number",     "Object",     "Optional", "Short",     "String",
    };
    std::copy(std::cbegin(T), std::cend(T), std::back_inserter(types));
}
