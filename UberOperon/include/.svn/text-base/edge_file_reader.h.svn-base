#ifndef GOST_EDGE_FILE_READER_H_
#define GOST_EDGE_FILE_READER_H_
#include "gene_set_type.h"
#include <algorithm>
#include <map>
typedef std::pair<double, double> WeightPair;

namespace edge_file_reader {
template<typename GT1> void Read(const char* file_name, double cutoff, std::map<std::pair<GT1, GT1>, WeightPair>* gene_pair_weight_pair_map);
template<> void Read<int>(const char* file_name, double cutoff, std::map<std::pair<int, int>, WeightPair>* gene_pair_weight_pair_map);
template<> void Read<gene_t>(const char* file_name, double cutoff, std::map<std::pair<gene_t, gene_t>, WeightPair>* gene_pair_weight_pair_map);
}
#endif // GOST_EDGE_FILE_READER_H_
