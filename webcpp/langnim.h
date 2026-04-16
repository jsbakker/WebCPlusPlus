// The Nim Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_NIM
#define LANG_DEF_NIM

#include "lang_rules.h"

class LangNim : public LanguageRules {

  public:
    LangNim();
    void initReservedWords() override;
};

#endif // LANG_DEF_NIM
