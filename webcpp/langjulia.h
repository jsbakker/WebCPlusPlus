// The Julia Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_JULIA
#define LANG_DEF_JULIA

#include "lang_rules.h"

class LangJulia : public LanguageRules {

  public:
    LangJulia();
    void initReservedWords() override;
};

#endif // LANG_DEF_JULIA
