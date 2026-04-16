// The D Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_D
#define LANG_DEF_D

#include "lang_rules.h"

class LangD : public LanguageRules {

  public:
    LangD();
    void initReservedWords() override;
};

#endif // LANG_DEF_D
