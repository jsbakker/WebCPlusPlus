---
name: add-language
description: Use this skill when the user asks to add a new language to webcpp, support a new file extension, or highlights a language that is missing from the syntax highlighter. Guides the full end-to-end process of adding language support including header, implementation, deflangs registration, factory wiring, driver help text, README table, and tests.
argument-hint: <LanguageName> [ext1 ext2 ...]
allowed-tools: [Read, Write, Edit, Glob, Grep, Bash]
---

# Adding a New Language to Webcpp

Arguments provided by the user: $ARGUMENTS

The pipeline is: flag booleans in `LanguageRules` → `Engine::doParsing()` dispatches
to the matching `parse*()` helper → HTML with `<font CLASS=...>` tags.

There are **seven** touch points for every new language. Complete them all.

---

## Step 1 — Create `webcpp/langfoo.h`

```cpp
// The Foo Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_FOO
#define LANG_DEF_FOO

#include "lang_rules.h"

class LangFoo : public LanguageRules {

  public:
    LangFoo();
    void initReservedWords() override;
};

#endif // LANG_DEF_FOO
```

## Step 2 — Create `webcpp/langfoo.cpp`

```cpp
// The Foo Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#include "langfoo.h"

#include <algorithm>
#include <iterator>
#include <string>

using std::string;

LangFoo::LangFoo() {

    initReservedWords();

    // Set boolean flags for this language's syntax features.
    // See references/rule-flags.md for the full catalogue.
    doInlineCommentDblSlash = true;   // //
    doBlockCommentPLI       = true;   // /* … */
    doSymbols               = true;
}

void LangFoo::initReservedWords() {

    string K[] = { "break", "continue", "else", "for", "if", "return", "while" };
    std::copy(std::cbegin(K), std::cend(K), std::back_inserter(keys));

    string T[] = { "bool", "float", "int", "string", "void" };
    std::copy(std::cbegin(T), std::cend(T), std::back_inserter(types));
}
```

**CMake picks up new `.cpp` files automatically — no build file changes needed.**

## Step 3 — Register in `webcpp/deflangs.h`

Add the `#include` at the bottom of the include block, and a hex constant in
`namespace lang`. Pick the next unused value after the current last entry.

```cpp
// In the #include block:
#include "langfoo.h"

// In namespace lang { … }:
inline constexpr std::uint8_t FOO_FILE = 0x4B;   // next available value
```

## Step 4 — Wire up `webcpp/lang_factory.cpp`

**4a.** Add extension(s) to the `extensionMap` initialiser:

```cpp
{"foo", lang::FOO_FILE},   {"foobar", lang::FOO_FILE},
```

**4b.** Add a `case` in `createFromFilename()`:

```cpp
case (lang::FOO_FILE):
    return {make_unique<LangFoo>(), id, "Foo file"};
```

## Step 5 — Update the help text in `webcpp/driver.cpp`

The driver contains a multi-line string literal listing all supported languages,
shown by `webcpp --help`. Entries must be kept in **alphabetical order**.
Each entry is tab-separated: `Name\t\t*.ext1,*.ext2\n\`.

```cpp
// Example — insert "Foo" alphabetically between "Fortran" and "Gherkin":
"Fortran\t\t*.f,*.f77,*.f90,*.for,*.ftn\n\
Foo\t\t*.foo,*.foobar\n\
Gherkin\t\t*.feature\n\
```

Use a single tab (`\t\t`) after short names and one (`\t`) after longer ones to
keep the columns roughly aligned — match the spacing style of surrounding entries.

## Step 6 — Update the language table in `README.md`

Add a row to the **Supported Languages / Detected Filetypes** table in
**alphabetical order** by language name:

```markdown
|Foo                  |.foo, .foobar|
```

## Step 7 — Write tests in `tests/test_foo_highlight.cpp`

Use the `highlight(src, "ext")` helper. Cover at minimum:
keywords, types, strings, comments, and any language-unique constructs.

```cpp
#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct FooHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "foo"); }
};

TEST_F(FooHighlightTest, KeywordsAreHighlighted) {
    auto html = hl("if (x) return;");
    EXPECT_NE(html.find("<font CLASS=keyword>if</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>return</font>"), std::string::npos);
}

TEST_F(FooHighlightTest, TypesAreHighlighted) {
    auto html = hl("int x = 0;");
    EXPECT_NE(html.find("<font CLASS=keytype>int</font>"), std::string::npos);
}

TEST_F(FooHighlightTest, DoubleQuoteStringIsHighlighted) {
    auto html = hl(R"("hello")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(FooHighlightTest, LineCommentIsHighlighted) {
    auto html = hl("int x = 1; // comment");
    EXPECT_NE(html.find("<font CLASS=comment>// comment</font>"), std::string::npos);
}

TEST_F(FooHighlightTest, BlockCommentIsHighlighted) {
    auto html = hl("/* block comment */");
    EXPECT_NE(html.find("<font CLASS=comment>/* block comment */</font>"), std::string::npos);
}
```

Build and run:

```bash
cmake --build build --parallel && ctest --test-dir build -R FooHighlight --output-on-failure
```

---

## Adding a Brand-New Rule Type to the Engine

When a language uses a comment or string syntax **not yet covered** by any existing
flag (see `references/rule-flags.md` for what exists), add a new rule to the three
engine files. See [references/adding-new-rules.md](references/adding-new-rules.md)
for the full procedure with two worked examples.
