// The R Language definition file for Web C Plus Plus

#ifndef LANG_DEF_R
#define LANG_DEF_R

#include "engine.h"

class LangR : public Engine {

 public:
	LangR();
	~LangR() {IO->close();}
	virtual void fill();

};

#endif //LANG_DEF_R
