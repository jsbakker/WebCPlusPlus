// The F# Language definition file for Web C Plus Plus

#ifndef LANG_DEF_FSHARP
#define LANG_DEF_FSHARP

#include "engine.h"

class LangFSharp : public Engine {

 public:
	LangFSharp();
	~LangFSharp() {IO->close();}
	virtual void fill();

};

#endif //LANG_DEF_FSHARP
