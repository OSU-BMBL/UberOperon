#include "../include/matching_file_writer.h"
#include <cstdio>
namespace file_handler {
void WriteError(const char* file_name){
  fprintf(stderr, "Could not write to file: %s\n", file_name);
  exit(-1);
}
void WriteMatchingFile(const std::map<gene_pair_t, WeightPair>& reader, const std::set<gene_pair_t>& gp, const char* file_name) {
  FILE* out = fopen(file_name, "w");
  if (!out) WriteError(file_name);
  for (std::set<gene_pair_t>::iterator it = gp.begin() ; it != gp.end(); it++ ) {
    std::map<gene_pair_t, WeightPair>::const_iterator jt = reader.find(*it);
    if (jt != reader.end())
      fprintf(out, "%s,%s\t%lg,%lg\n", it->first.c_str(), it->second.c_str(), jt->second.first, jt->second.second);
  }
  fclose(out);
}
void WriteRichEdgeFile(const std::map<int, std::set<int> >& gost_edge, const char* file_name) {
  FILE* out = fopen(file_name, "w");
  if (!out) WriteError(file_name);
  fprintf(out, "(mclheader\nmcltype matrix\ndimensions %dx%d\n)\n", gost_edge.size(), gost_edge.size());
  fprintf(out, "(mcldoms\n");
  for (std::map<int, std::set<int> >::const_iterator it = gost_edge.begin(); it != gost_edge.end(); it++) {
    fprintf(out, "%d ", it->first);
  }
  fprintf(out, "$\n)\n");
  fprintf(out, "(mclmatrix\nbegin\n");
  for (std::map<int, std::set<int> >::const_iterator it = gost_edge.begin(); it != gost_edge.end(); it++) {
    fprintf(out, "%d\t", it->first);
    for (std::set<int>::const_iterator jt = it->second.begin(); jt != it->second.end(); jt++)
      fprintf(out, "%d:1 ", *jt);
    fprintf(out, "$\n");
  }
  fprintf(out, ")\n");
  fclose(out);
}

void WriteRichEdgeFile(const std::map<OperonId, std::map<OperonId, int> >& gost_edge, const char* file_name) {
  FILE* out = fopen(file_name, "w");
  if (!out) WriteError(file_name);
  fprintf(out, "(mclheader\nmcltype matrix\ndimensions %dx%d\n)\n", gost_edge.size(), gost_edge.size());
  fprintf(out, "(mcldoms\n");
  for (std::map<OperonId, std::map<OperonId, int> >::const_iterator it = gost_edge.begin(); it != gost_edge.end(); it++) {
    fprintf(out, "%d ", it->first);
  }
  fprintf(out, "$\n)\n");
  fprintf(out, "(mclmatrix\nbegin\n");
  for (std::map<OperonId, std::map<OperonId, int> >::const_iterator it = gost_edge.begin(); it != gost_edge.end(); it++) {
    fprintf(out, "%d\t", it->first);
    for (std::map<OperonId, int>::const_iterator jt = it->second.begin(); jt != it->second.end(); jt++)
      fprintf(out, "%d:%d ", jt->first, jt->second);
    fprintf(out, "$\n");
  }
  fprintf(out, ")\n");
  fclose(out);
}

void WriteEdgeFile(const std::set<std::set<int> >& gost_edge, const char* file_name) {
  FILE* out = fopen(file_name, "w");
  if (!out) WriteError(file_name);
  for (std::set<std::set<int> >::const_iterator it = gost_edge.begin(); it != gost_edge.end(); it++) {
    for (std::set<int>::const_iterator jt = it->begin(); jt != it->end(); jt++)
      fprintf(out, "%d\t", *jt);
    fprintf(out, "\n");
  }
  fclose(out);
}
void WriteEdgeFiles(std::map<OperonId, std::pair<std::set<OperonId>, std::set<OperonId> > >& gost_edge, const char* file_name_u, const char* file_name_v) {
  FILE* out_u = fopen(file_name_u, "w");
  if (!out_u) WriteError(file_name_u);
  FILE* out_v = fopen(file_name_v, "w");
  if (!out_v) WriteError(file_name_v);
  for (std::map<OperonId, std::pair<std::set<OperonId>, std::set<OperonId> > >::const_iterator it = gost_edge.begin(); it != gost_edge.end(); it++) {
    for (std::set<OperonId>::const_iterator jt = it->second.first.begin(); jt != it->second.first.end(); jt++)
      fprintf(out_u, "%d ", *jt + 1);
    for (std::set<OperonId>::const_iterator jt = it->second.second.begin(); jt != it->second.second.end(); jt++)
      fprintf(out_v, "%d ", *jt + 1);
    fprintf(out_u, "\n");
    fprintf(out_v, "\n");
  }
  fclose(out_u);
  fclose(out_v);
}
}
