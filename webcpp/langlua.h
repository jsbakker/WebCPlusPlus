// The Lua Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_LUA
#define LANG_DEF_LUA

#include "lang_rules.h"

class LangLua : public LanguageRules {

  public:
    LangLua();
    void initReservedWords() override;
};

#endif // LANG_DEF_LUA
