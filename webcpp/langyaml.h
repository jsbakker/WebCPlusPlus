// The YAML Language definition file for Web C Plus Plus
// Webcpp Copyright (C)2001-2004, (C)2026 Jeffrey Bakker

#ifndef LANG_DEF_YAML
#define LANG_DEF_YAML

#include "lang_rules.h"

class LangYaml : public LanguageRules {

  public:
    LangYaml();
    void initReservedWords() override;
};

#endif // LANG_DEF_YAML
