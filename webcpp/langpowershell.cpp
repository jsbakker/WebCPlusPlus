// The PowerShell Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langpowershell.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangPowerShell::LangPowerShell() {

    initReservedWords();

    doStringsSinQuote          = true;
    doSymbols                  = true;
    doScalars                  = true;   // $variable
    doCaseKeys                 = false;  // PowerShell is case-insensitive
    doInlineCommentHash        = true;   // #
    doBlockCommentPowerShell   = true;   // <# … #>
    doRequireBackslashContinuation = false; // PowerShell uses backtick, not backslash
}

void LangPowerShell::initReservedWords() {

    // PowerShell 7.x keywords (case-insensitive)
    string K[] = {
        "begin",        "break",        "catch",       "class",
        "continue",     "data",         "define",      "do",
        "dynamicparam", "else",         "elseif",      "end",
        "enum",         "exit",         "filter",      "finally",
        "for",          "foreach",      "from",        "function",
        "hidden",       "if",           "in",          "inlinescript",
        "param",        "process",      "return",      "static",
        "switch",       "throw",        "trap",        "try",
        "until",        "using",        "var",         "while",
    };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));

    // PowerShell common type accelerators and automatic variables
    string T[] = {
        "bool",           "byte",         "char",       "datetime",
        "decimal",        "double",       "float",      "guid",
        "hashtable",      "int",          "int16",      "int32",
        "int64",          "long",         "object",     "ordered",
        "pscustomobject", "psobject",     "regex",      "sbyte",
        "scriptblock",    "securestring", "single",     "string",
        "switch",         "timespan",     "uint16",     "uint32",
        "uint64",         "uri",          "void",       "xml",
        "$false",         "$null",        "$true",
        "$Args",          "$Error",       "$Home",      "$Host",
        "$Input",         "$LastExitCode", "$Matches",  "$MyInvocation",
        "$PSBoundParameters", "$PSCommandPath", "$PSScriptRoot",
        "$PSVersionTable",    "$Pwd",          "$ShellId",
    };
    std::copy(std::cbegin(T), std::cend(T), std::back_inserter(types));
}
