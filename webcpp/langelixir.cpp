// The Elixir Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langelixir.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangElixir::LangElixir() {

    initReservedWords();

    doStringsSinQuote            = true;  // charlists
    doSymbols                    = true;
    doUnderscoreNumbers          = true;
    doArrays                     = true;  // @module_attribute
    doInlineCommentHash          = true;  // #
    doMultilineStrTripleDblQuote = true;  // """…"""
    // Elixir string interpolation: "text #{expr}"
    doInterpolate  = true;
    interpolStart  = "#{";
    interpolEnd    = '}';
    doRequireBackslashContinuation = false; // Elixir strings may span lines
}

void LangElixir::initReservedWords() {

    // Elixir 1.16 keywords
    string K[] = {
        "after",        "alias",      "and",        "case",       "catch",
        "cond",         "def",        "defcallback","defdelegate","defexception",
        "defguard",     "defguardp",  "defimpl",    "defmacro",   "defmacrop",
        "defmodule",    "defoverridable","defp",     "defprotocol","defstruct",
        "do",           "else",       "end",        "false",      "fn",
        "for",          "if",         "import",     "in",         "nil",
        "not",          "or",         "quote",      "raise",      "receive",
        "rescue",       "require",    "super",      "throw",      "true",
        "try",          "unless",     "use",        "when",       "with",
    };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));

    // Elixir built-in types and modules
    string T[] = {
        "Atom",      "BitString", "Boolean",  "Exception", "Float",
        "Function",  "Integer",   "IO",        "Kernel",    "List",
        "Map",       "Module",    "PID",       "Port",      "Process",
        "Reference", "String",    "Tuple",
    };
    std::copy(std::cbegin(T), std::cend(T), std::back_inserter(types));
}
