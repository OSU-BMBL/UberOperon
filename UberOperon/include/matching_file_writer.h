#ifndef GOST_MATCHING_FILE_WRITER_H_
#define GOST_MATCHING_FILE_WRITER_H_
#include "gene_set_type.h"
#include <algorithm>
#include <map>
typedef std::pair<double, double> WeightPair;

namespace file_handler {
void WriteMatchingFile(const std::map<gene_pair_t, WeightPair>& reader, const std::set<gene_pair_t>& gp, const char* file_name);
void WriteEdgeFiles(std::map<OperonId, std::pair<std::set<OperonId>, std::set<OperonId> > >& gost_edge, const char* file_name_u, const char* file_name_v);
void WriteRichEdgeFile(const std::map<OperonId, std::map<OperonId, int> >& gost_edge, const char* file_name);
}
#endif // GOST_MATCHING_FILE_WRITER_H_
