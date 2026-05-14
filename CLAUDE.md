# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**Webcpp** is a C++23 source-code-to-HTML syntax highlighter supporting 40+ languages. It converts source files into HTML with syntax highlighting and customizable color themes. Originally a SourceForge project (2001–2004), it was modernized in 2026 with CMake, Google Test, and C++23 features.

## Build Commands

```bash
cmake -B build                        # Configure
cmake --build build --parallel        # Compile
cmake --install build                 # Install system-wide (may need sudo)

# User-local install
cmake -B build -DCMAKE_INSTALL_PREFIX=~/.local
cmake --install build
```

## Test Commands

```bash
cmake --build build --target webcpp_tests   # Build tests only
ctest --test-dir build --output-on-failure  # Run all tests
ctest --test-dir build -R CPlusPlusHighlight --output-on-failure  # Run a specific suite
```

Tests live in `/tests/` (81 Google Test files). Each language typically has suites for keywords, strings, comments, multiline constructs, and backslash continuations.

## Architecture

The pipeline is: CLI args → `Driver` → `LangFactory` → `Engine`+`LanguageRules` → `HtmlWriter`+`Theme` → HTML output.

**Core components:**

- **`driver.cpp/h`** — Parses CLI args, detects language from extension, orchestrates the full pipeline.
- **`engine.cpp/h`** — Abstract tokenization engine. Subclasses override `doParsing()`. Handles strings, comments, keywords, numbers, symbols, and preprocessor directives. Compiled with `-fno-exceptions -O2`.
- **`lang_rules.h`** — Base class for language rules. Boolean flags select which parsing features to enable (e.g., `doStringsDblQuote`, `doInlineCommentDblSlash`). Holds keyword and type lists.
- **`lang_factory.cpp/h`** — Maps file extensions to language IDs; factory-creates the appropriate `LanguageRules` subclass.
- **`deflangs.h`** — Registry of all language constants (hex IDs) and `#include`s for every language header.
- **`theme.cpp/h`** — Loads `.Scs2` color scheme files from `webcpp/themes/` (59 included). Defines 14 CSS color slots (KEYWORD, COMMENT, STRING, etc.).
- **`html_writer.cpp/h`** — Generates the HTML output, wrapping tokens in `<font CLASS=...>` tags.
- **`cffile.cpp/h`** — Lightweight internal file I/O wrapper.

**Language class hierarchy (key examples):**
```
LanguageRules
├── LangC → LangCPlusPlus → LangObjectiveCpp
├── LangJScript → LangTypeScript
└── LangGLSL → LangHLSL
```

CMake builds a static library (`webcpp_lib`) from all `.cpp` files except `main.cpp`, which the main executable and tests both link against.

## Adding a New Language

1. Create `webcpp/langfoo.h` and `webcpp/langfoo.cpp`:
   - Inherit from `LanguageRules` (or another language class to reuse syntax)
   - Set boolean flags in the constructor
   - Implement `initReservedWords()` to populate `keys` and `types`
2. Add a hex constant and `#include "langfoo.h"` to `deflangs.h`
3. Add extension mappings and a switch case in `lang_factory.cpp`
4. CMake automatically picks up new `.cpp` files — no build file changes needed

## Color Schemes

`.Scs2` theme files live in `webcpp/themes/`. At runtime, the engine looks them up via the installed path (generated into `webcpp_paths.h` by CMake from `webcpp_paths.h.in`).

## CLI Reference

```
webcpp <infile> <outfile> [options]
  -c=<scheme>        Color scheme name
  -w=<scheme>        Full output: line numbers, anchors, hyperlinks, footer, theme
  -W=<scheme>        Like -w but with external CSS
  -x=<ext>           Force language (e.g., -x=cpp)
  -l                 Line numbers
  -a                 Anchor links to line numbers
  -h / -H            Hyperlink #include files (H = recursive)
  -s                 Snippet only (no full HTML document)
  -X                 External CSS
  -t=<n>             Expand tabs to N spaces
```
