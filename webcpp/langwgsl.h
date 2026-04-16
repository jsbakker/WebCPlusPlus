// The WGSL (WebGPU Shading Language) definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_WGSL
#define LANG_DEF_WGSL

#include "lang_rules.h"

class LangWGSL : public LanguageRules {

  public:
    LangWGSL();
    void initReservedWords() override;
};

#endif // LANG_DEF_WGSL
