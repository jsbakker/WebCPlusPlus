# Adding a New Rule Type to the Engine

When a language needs a comment or string syntax not covered by any existing flag,
you must add it across **four files**: `lang_rules.h`, `engine.h`, `engine.cpp`
(twice: the inline wrapper and the `doParsing()` dispatch).

The existing `parseBlockComment(start, end, state, css)` and `parseInlineComment(marker)`
primitives handle the actual work — you only need to plumb a new flag and wrapper through.

---

## Example 1 — New Block Comment: `#!` … `!#`

Hypothetical language "Bar" uses `#!` to open a block comment and `!#` to close it.
No existing block-comment flag covers this pair.

### `webcpp/lang_rules.h`

Add the new flag in the protected section, next to the other `doBlockComment*` booleans.
Also initialise it to `false` in the constructor.

```cpp
// In the constructor, with the other block-comment initialisers:
doBlockCommentBar = false;

// In the protected section:
bool doBlockCommentBar;
```

### `webcpp/engine.h`

Add a private inline wrapper next to the other `parseBlockComment*` inlines:

```cpp
inline void parseBlockCommentBar() {
    parseBlockComment("#!", "!#", state.inComment);
}
```

### `webcpp/engine.cpp` — `doParsing()`

Dispatch the new wrapper in the block-comment section of `doParsing()`, alongside
the other `doBlockComment*` dispatches:

```cpp
if (rules->doBlockCommentBar)
    parseBlockCommentBar();
```

### `webcpp/langbar.cpp` — opt in

```cpp
doBlockCommentBar = true;   // #! … !#
```

---

## Example 2 — New Inline Comment: `%%`

Hypothetical language "Baz" uses `%%` as its end-of-line comment marker.
No existing inline-comment flag covers this token.

### `webcpp/lang_rules.h`

```cpp
// In the constructor:
doInlineCommentDblPercent = false;

// In the protected section:
bool doInlineCommentDblPercent;
```

### `webcpp/engine.h`

Add the inline wrapper next to the other `parseInlineComment*` methods:

```cpp
inline void parseInlineCommentDblPercent() { parseInlineComment("%%"); }
```

### `webcpp/engine.cpp` — `doParsing()`

Add the dispatch next to the other `doInlineComment*` dispatches:

```cpp
if (rules->doInlineCommentDblPercent) {
    parseInlineCommentDblPercent();
}
```

### `webcpp/langbaz.cpp` — opt in

```cpp
doInlineCommentDblPercent = true;   // %%
```

---

## Test the New Rule

Write a focused test in the language's test file:

```cpp
// Example 1
TEST_F(BarHighlightTest, BlockCommentBarIsHighlighted) {
    auto html = hl("#! block comment !#");
    EXPECT_NE(html.find("<font CLASS=comment>#!"), std::string::npos);
    EXPECT_NE(html.find("!#</font>"), std::string::npos);
}

// Example 2
TEST_F(BazHighlightTest, DblPercentCommentIsHighlighted) {
    auto html = hl("x = 1 %% comment");
    EXPECT_NE(html.find("<font CLASS=comment>%% comment</font>"), std::string::npos);
}
```
