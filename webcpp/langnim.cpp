// The Nim Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langnim.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangNim::LangNim() {

    initReservedWords();

    doSymbols                    = true;
    doUnderscoreNumbers          = true;
    doCaseKeys                   = false; // Nim identifiers are style-insensitive
    doInlineCommentHash          = true;  // #
    doBlockCommentNim            = true;  // #[ … ]#
    doMultilineStrTripleDblQuote = true;  // """…"""
}

void LangNim::initReservedWords() {

    // Nim 2.0 keywords
    string K[] = {
        "addr",      "and",       "as",        "asm",       "bind",
        "block",     "break",     "case",      "cast",      "concept",
        "const",     "continue",  "converter", "defer",     "discard",
        "distinct",  "div",       "do",        "elif",      "else",
        "end",       "enum",      "except",    "export",    "false",
        "finally",   "for",       "from",      "func",      "if",
        "import",    "in",        "include",   "interface", "is",
        "isnot",     "iterator",  "let",       "macro",     "method",
        "mixin",     "mod",       "nil",       "not",       "notin",
        "object",    "of",        "or",        "out",       "proc",
        "ptr",       "raise",     "ref",       "return",    "shl",
        "shr",       "static",    "template",  "true",      "try",
        "tuple",     "type",      "using",     "var",       "when",
        "while",     "xor",       "yield",
    };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));

    // Nim built-in types
    string T[] = {
        "bool",    "byte",    "char",    "cchar",   "cdouble", "cfloat",
        "cint",    "clong",   "cshort",  "cstring", "cuint",   "culong",
        "cushort", "float",   "float32", "float64", "int",     "int8",
        "int16",   "int32",   "int64",   "pointer", "seq",     "set",
        "string",  "uint",    "uint8",   "uint16",  "uint32",  "uint64",
        "void",
    };
    std::copy(std::cbegin(T), std::cend(T), std::back_inserter(types));
}
