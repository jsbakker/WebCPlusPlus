// The OCaml Language definition file for Web C Plus Plus

#ifndef LANG_DEF_OCAML
#define LANG_DEF_OCAML

#include "engine.h"

class LangOCaml : public Engine {

 public:
	LangOCaml();
	~LangOCaml() {IO->close();}
	virtual void fill();

};

#endif //LANG_DEF_OCAML
