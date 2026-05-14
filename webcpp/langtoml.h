// The TOML Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_TOML
#define LANG_DEF_TOML

#include "lang_rules.h"

class LangToml : public LanguageRules {

  public:
    LangToml();
    void initReservedWords() override;
};

#endif // LANG_DEF_TOML
