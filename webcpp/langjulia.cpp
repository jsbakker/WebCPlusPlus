// The Julia Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langjulia.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangJulia::LangJulia() {

    initReservedWords();

    doSymbols                    = true;
    doUnderscoreNumbers          = true;
    doInlineCommentHash          = true;  // #
    doBlockCommentJulia          = true;  // #= … =#
    doMultilineStrTripleDblQuote = true;  // """…"""
    // Julia string interpolation: "text $(expr)"
    doInterpolate  = true;
    interpolStart  = "$(";
    interpolEnd    = ')';
}

void LangJulia::initReservedWords() {

    // Julia 1.10 keywords
    string K[] = {
        "abstract",  "baremodule", "begin",    "break",    "catch",
        "const",     "continue",   "do",       "else",     "elseif",
        "end",       "export",     "false",    "finally",  "for",
        "function",  "global",     "if",       "import",   "in",
        "let",       "local",      "macro",    "module",   "mutable",
        "new",       "outer",      "primitive","quote",    "return",
        "struct",    "true",       "try",      "type",     "using",
        "where",     "while",
    };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));

    // Julia built-in types
    string T[] = {
        "AbstractArray",  "AbstractFloat",  "AbstractMatrix", "AbstractString",
        "AbstractVector", "Any",            "Array",          "BitArray",
        "Bool",           "Char",           "Complex",        "Dict",
        "Float16",        "Float32",        "Float64",        "Function",
        "Int",            "Int8",           "Int16",          "Int32",
        "Int64",          "Int128",         "Integer",        "Matrix",
        "Missing",        "Nothing",        "Number",         "Pair",
        "Real",           "Set",            "String",         "Symbol",
        "Task",           "Tuple",          "Type",           "UInt",
        "UInt8",          "UInt16",         "UInt32",         "UInt64",
        "UInt128",        "Union",          "Vector",
    };
    std::copy(std::cbegin(T), std::cend(T), std::back_inserter(types));
}
