#include "../include/operons_in_genome.h"
#include <cstdio>
#include <cstdlib>
namespace file_handler { // TODO: Rename this file
int ReadOperonLineNumber(const char* line, int* offset_pointer) {
  int num;
  if (sscanf(line, " %d:%n", &num, offset_pointer) != 1) return 0;
  return num;
}
void ReadOperonFile(const char* file, OperonsGenes* operon_map) {
  // now load operons from the file
  FILE* in = fopen(file, "r");
  if (!in) {
    fprintf(stderr, "input file %s can't be opened.\n", file);
    exit(-1);
  }
  if (!ReadOperonStream(in, operon_map)) {
    fprintf(stderr, "input file %s is bad.\n", file);
    exit(-1);
  }
  fclose(in);
}
bool ReadOperonStream(FILE* in, OperonsGenes* operon_map) {
  const int kMaxLineSize = 8192;
  // read operon information
  char line[kMaxLineSize];
  int line_num = 0;
  while (fgets(line, kMaxLineSize, in)) {
    int offset;
    if (ReadOperonLineNumber(line, &offset) != line_num + 1) return false;
    ReadOperonLineData(line_num, line + offset, operon_map);
    line_num++;
  }
  return true;
}
void ReadOperonLineData(const int line_num, const char* data, OperonsGenes* operon_map) {
  gene_set_t gene_set;
  char gene_name[256];
  int offset;
  while (1 == sscanf(data, " %256s%n", gene_name, &offset)) {
    data += offset;
    gene_set.insert(gene_name);
    operon_map->gene2operon[gene_name] = line_num;
  }
  operon_map->operon2gene.push_back(gene_set);
}
}
