#ifndef GOST_OPERONS_IN_GONOME_H_
#define GOST_OPERONS_IN_GONOME_H_

#include "operon_gene.h"
namespace file_handler {
void ReadOperonLineData(const int line_num, const char* data, OperonsGenes* operon_map);
bool ReadOperonStream(FILE* in, OperonsGenes* operon_map);
void ReadOperonFile(const char* file, OperonsGenes* operon_map);
}

#endif // GOST_OPERONS_IN_GONOME_H_
