// The Groovy Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_GROOVY
#define LANG_DEF_GROOVY

#include "lang_rules.h"

class LangGroovy : public LanguageRules {

  public:
    LangGroovy();
    void initReservedWords() override;
};

#endif // LANG_DEF_GROOVY
