// The Gherkin Language definition file for Web C Plus Plus

#ifndef LANG_DEF_GHERKIN
#define LANG_DEF_GHERKIN

#include "engine.h"

class LangGherkin : public Engine {

 public:
	LangGherkin();
	~LangGherkin() {IO->close();}
	virtual void fill();

};

#endif //LANG_DEF_GHERKIN
