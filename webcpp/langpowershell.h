// The PowerShell Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_POWERSHELL
#define LANG_DEF_POWERSHELL

#include "lang_rules.h"

class LangPowerShell : public LanguageRules {

  public:
    LangPowerShell();
    void initReservedWords() override;
};

#endif // LANG_DEF_POWERSHELL
