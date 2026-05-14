// The JSON Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_JSON
#define LANG_DEF_JSON

#include "lang_rules.h"

class LangJson : public LanguageRules {

  public:
    LangJson();
    void initReservedWords() override;
};

#endif // LANG_DEF_JSON
