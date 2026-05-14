# Language Rule Flags

Every `LanguageRules` subclass constructor sets these booleans to opt in to parsing
features. All default to `false` except `doStringsDblQuote`, `doNumbers`,
`doKeywords`, `doCaseKeys`, and `doRequireBackslashContinuation`, which default `true`.

## String Literals

| Flag | Engine method | Syntax |
|---|---|---|
| `doStringsDblQuote` | `parseStringDoubleQuote()` | `"…"` |
| `doStringsSinQuote` | `parseStringSingleQuote()` | `'…'` |
| `doStringsBackTick` | `parseStringBackQuote()` | `` `…` `` |
| `doRequireBackslashContinuation` | (guard) | `false` = strings may span lines without `\` (Ruby, Perl, Shell, PHP, Tcl) |

## Multiline Strings / Heredocs

| Flag | Engine method | Syntax |
|---|---|---|
| `doMultilineStrTripleDblQuote` | `parseMultilineStrTripleDblQuote()` | `"""…"""` |
| `doMultilineStrRaw` | `parseMultilineStrRaw()` | `R"(…)"` (C++) |
| `doMultilineStrHeredoc` | `parseMultilineStrHeredocDblLt()` | `<<MARKER` |
| `doMultilineStrHeredocTpl` | `parseMultilineStrHeredocTplLt()` | `<<<MARKER` (PHP) |
| `doMultilineStrPercentQ` | `parseMultilineStrUpperQBlock()` + `parseMultilineStrLowerQBlock()` | `%Q{…}` / `%q{…}` (Ruby) |

## Inline (End-of-Line) Comments

| Flag | Engine method | Syntax |
|---|---|---|
| `doInlineCommentDblSlash` | `parseInlineCommentDblSlash()` | `//` |
| `doInlineCommentHash` | `parseInlineCommentHash()` | `#` |
| `doInlineCommentDblDash` | `parseInlineCommentDblDash()` | `--` |
| `doInlineCommentSemiColon` | `parseInlineCommentSemiColon()` | `;` |
| `doInlineCommentDblColon` | `parseInlineCommentDblColon()` | `::` |
| `doInlineCommentSingleQuote` | `parseInlineCommentSingleQuote()` | `'` |
| `doInlineCommentRem` | `parseInlineCommentRem()` | `REM` / `rem` |
| `doInlineCommentExclamation` | (part of Fortran block below) | `!` |

## First-Character-of-Line Comments

| Flag | Engine method | Syntax |
|---|---|---|
| `doFirstCharCommentHash` | `parseFirstCharCommentHash()` | `#` at column 0 |
| `doFirstCharCommentFortran` | `parseFirstCharCommentFortran()` + `parseInlineCommentExclamation()` | `C`, `c`, or `*` at col 0; `!` anywhere |

## Block Comments

| Flag | Engine method | Syntax |
|---|---|---|
| `doBlockCommentPLI` | `parseBlockCommentPLI()` | `/* … */` |
| `doBlockCommentPascal` | `parseBlockCommentPascal()` | `(* … *)` |
| `doBlockCommentMarkup` | `parseBlockCommentMarkup()` | `<!-- … -->` |
| `doBlockCommentHaskell` | `parseBlockCommentHaskell()` | `{- … -}` |
| `doBlockCommentLua` | `parseBlockCommentLua()` | `--[[ … ]]` |
| `doBlockCommentPowerShell` | `parseBlockCommentPowerShell()` | `<# … #>` |
| `doBlockCommentJulia` | `parseBlockCommentJulia()` | `#= … =#` |
| `doBlockCommentNim` | `parseBlockCommentNim()` | `#[ … ]#` |
| `doBlockCommentD` | `parseBlockCommentD()` | `/+ … +/` |

## Other Features

| Flag | Engine method | Notes |
|---|---|---|
| `doKeywords` | `parseKeywordsAndTypes()` | Highlight `keys` list as `keyword` CSS class |
| `doCaseKeys` | (guard in keyword parser) | `false` = case-insensitive keyword matching |
| `doNumbers` | `parseNum()` | Integer and float literals |
| `doUnderscoreNumbers` | (guard in `parseNum`) | `1_000_000` style |
| `doSymbols` | `parseSymbol()` | Operators and punctuation |
| `doLabels` | `parseLabel()` | `label:` constructs |
| `doPreProc` | `parsePreProc()` | `#include`, `#define`, etc. |
| `doScalars` | `parseVariable("$")` | `$var` |
| `doArrays` | `parseVariable("@")` | `@arr` |
| `doHashes` | `parseVariable("%")` | `%hash` |
| `doInterpolate` | `markInterpolations()` | String interpolation (also set `interpolStart`, `interpolEnd`, `interpolCssClass`) |
| `doHtmlTags` | `parseHtmlTags()` | `<tag>` highlighting inside HTML/XML child languages |
