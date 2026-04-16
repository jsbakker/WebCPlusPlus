// The Clojure Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langclojure.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangClojure::LangClojure() {

    initReservedWords();

    doSymbols              = true;
    doInlineCommentSemiColon = true;  // ;
}

void LangClojure::initReservedWords() {

    // Clojure special forms and common macros
    string K[] = {
        "and",        "binding",   "case",       "catch",      "cond",
        "declare",    "def",       "defmacro",   "defmethod",  "defmulti",
        "defn",       "defprotocol", "defrecord", "defstruct", "deftype",
        "do",         "doseq",     "dotimes",    "doto",       "false",
        "finally",    "fn",        "for",        "future",     "if",
        "import",     "in-ns",     "let",        "letfn",      "loop",
        "new",        "nil",       "ns",         "or",         "proxy",
        "quote",      "recur",     "reify",      "set!",       "throw",
        "true",       "try",       "var",        "when",       "while",
    };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));

    // Clojure core types and Java interop classes
    string T[] = {
        "Atom",      "Boolean",   "Byte",       "Character",  "Class",
        "Double",    "Exception", "Float",       "Integer",    "Long",
        "Map",       "Number",    "Object",      "Short",      "String",
        "Thread",    "Throwable",
    };
    std::copy(std::cbegin(T), std::cend(T), std::back_inserter(types));
}
