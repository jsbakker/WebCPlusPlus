// The Clojure Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_CLOJURE
#define LANG_DEF_CLOJURE

#include "lang_rules.h"

class LangClojure : public LanguageRules {

  public:
    LangClojure();
    void initReservedWords() override;
};

#endif // LANG_DEF_CLOJURE
