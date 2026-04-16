// The D Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langd.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangD::LangD() {

    initReservedWords();

    doStringsBackTick        = true;   // `…` raw strings
    doSymbols                = true;
    doUnderscoreNumbers      = true;
    doInlineCommentDblSlash  = true;   // //
    doBlockCommentPLI        = true;   // /* */
    doBlockCommentD          = true;   // /+ … +/
}

void LangD::initReservedWords() {

    // D 2.x keywords
    string K[] = {
        "abstract",  "alias",      "align",      "asm",        "assert",
        "auto",      "break",      "case",       "cast",       "catch",
        "class",     "const",      "continue",   "debug",      "default",
        "delegate",  "deprecated", "do",         "else",       "enum",
        "export",    "extern",     "false",      "final",      "finally",
        "for",       "foreach",    "function",   "goto",       "if",
        "immutable", "import",     "in",         "inout",      "interface",
        "invariant", "is",         "lazy",       "mixin",      "module",
        "new",       "nothrow",    "null",       "out",        "override",
        "package",   "pragma",     "private",    "protected",  "public",
        "pure",      "ref",        "return",     "scope",      "shared",
        "static",    "struct",     "super",      "switch",     "synchronized",
        "template",  "this",       "throw",      "true",       "try",
        "typeid",    "typeof",     "union",      "unittest",   "version",
        "volatile",  "while",      "with",
    };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));

    // D built-in types
    string T[] = {
        "bool",    "byte",    "cdouble", "cent",    "cfloat",  "char",
        "creal",   "dchar",   "double",  "dstring", "float",   "idouble",
        "ifloat",  "int",     "ireal",   "long",    "real",    "short",
        "string",  "ubyte",   "ucent",   "uint",    "ulong",   "ushort",
        "void",    "wchar",   "wstring",
    };
    std::copy(std::cbegin(T), std::cend(T), std::back_inserter(types));
}
