// The Scala Language definition file for Web C Plus Plus

#ifndef LANG_DEF_SCALA
#define LANG_DEF_SCALA

#include "engine.h"

class LangScala : public Engine {

 public:
	LangScala();
	~LangScala() {IO->close();}
	virtual void fill();

};

#endif //LANG_DEF_SCALA
