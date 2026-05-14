// The YAML Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langyaml.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangYaml::LangYaml() {

    initReservedWords();

    doCaseKeys          = false;  // YAML booleans are case-insensitive
    doStringsDblQuote   = true;
    doStringsSinQuote   = true;
    doNumbers           = true;
    doSymbols           = true;
    doInlineCommentHash = true;   // #
}

void LangYaml::initReservedWords() {

    // YAML 1.1/1.2 boolean and null literals (matched case-insensitively)
    string K[] = { "false", "no", "null", "off", "on", "true", "yes" };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));
}
