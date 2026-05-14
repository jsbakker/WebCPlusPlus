// The JSON Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langjson.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangJson::LangJson() {

    initReservedWords();

    doStringsDblQuote       = true;
    doNumbers               = true;
    doSymbols               = true;
    doInlineCommentDblSlash = true;  // JSONC / JSON5: //
    doBlockCommentPLI       = true;  // JSONC / JSON5: /* … */
}

void LangJson::initReservedWords() {

    string K[] = { "false", "null", "true" };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));
}
