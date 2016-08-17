#ifndef DEBDEEPPRJ_ENGINE_H
#define DEBDEEPPRJ_ENGINE_H

#include <algorithm>
#include <iomanip>
#include "core.h"
#include "opcodes.h"


/*
* @return 0 if sucessfully parsed
* non zero return value indicate error while parsing
* returns positive integer to indicate error thile parsing the nth nubiles
*/
//See about in xbin_parser.cpp
int hexcode_parse(CPU& cpu, std::istream& xbin_stream);

//Only this function directly interacts with user. see reploop.cpp file
void reploop(CPU& cpu); // read, evaluate, print loop

#endif // DEBDEEPPRJ_ENGINE_H
