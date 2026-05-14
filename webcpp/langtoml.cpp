// The TOML Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langtoml.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangToml::LangToml() {

    initReservedWords();

    doStringsDblQuote           = true;
    doStringsSinQuote           = true;   // literal strings: '…'
    doMultilineStrTripleDblQuote = true;  // multi-line basic strings: """…"""
    doNumbers                   = true;
    doUnderscoreNumbers         = true;   // 1_000_000
    doSymbols                   = true;
    doInlineCommentHash         = true;   // #
}

void LangToml::initReservedWords() {

    // TOML boolean literals and special float values
    string K[] = { "false", "inf", "nan", "true" };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));
}
