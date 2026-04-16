// The Lua Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langlua.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangLua::LangLua() {

    initReservedWords();

    doStringsSinQuote      = true;
    doSymbols              = true;
    doInlineCommentDblDash = true;  // --
    doBlockCommentLua      = true;  // --[[ … ]]
}

void LangLua::initReservedWords() {

    // Lua 5.4 keywords
    string K[] = {
        "and",    "break",    "do",     "else",   "elseif", "end",
        "false",  "for",      "function", "goto", "if",     "in",
        "local",  "nil",      "not",    "or",     "repeat", "return",
        "then",   "true",     "until",  "while",
    };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));

    // Lua 5.4 standard library modules and common globals
    string T[] = {
        "coroutine", "io",    "math",   "os",      "package", "string",
        "table",     "utf8",  "assert", "error",   "ipairs",  "load",
        "loadfile",  "next",  "pairs",  "pcall",   "print",   "rawequal",
        "rawget",    "rawlen", "rawset", "require", "select",  "setmetatable",
        "tostring",  "tonumber", "type", "unpack",  "warn",    "xpcall",
        "_ENV",      "_G",    "_VERSION",
    };
    std::copy(std::cbegin(T), std::cend(T), std::back_inserter(types));
}
