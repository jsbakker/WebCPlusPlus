// The Dart Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_DART
#define LANG_DEF_DART

#include "lang_rules.h"

class LangDart : public LanguageRules {

  public:
    LangDart();
    void initReservedWords() override;
};

#endif // LANG_DEF_DART
