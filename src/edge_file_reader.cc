#include "../include/edge_file_reader.h"
#include <cstdio>
namespace edge_file_reader {
template<typename GT1>
void Read(const char* file_name, double cutoff, std::map<std::pair<GT1, GT1>, WeightPair>* gene_pair_weight_pair_map) {
  throw std::exception("The edge_file_reader::Read method or operation is not implemented.");
}
template<> void Read<std::string>(const char* file_name, double cutoff, std::map<std::pair<std::string, std::string>, WeightPair>* gene_pair_weight_pair_map) {
  FILE* in;
  if ((in = fopen(file_name, "r")) == NULL) {
    fprintf(stderr, "***> Open error on input file_name %s", file_name);
    exit(-1);
  }
  double weight_u, weight_v;
  std::string vertix_u, vertix_v;
  char u[100], v[100], uu[100], vv[100];
  while (fscanf(in, "%s ", u) > 0) {
    sscanf(u, "%[^:]s", uu);
    vertix_u = uu;
    while (fscanf(in, "(%s", v) > 0) {
      std::replace(v, v + 100, ',', ' ');
      sscanf(v, "%s %lg %lg", vv, &weight_u, &weight_v);
      if (weight_u < cutoff && weight_v < cutoff) {
        vertix_v = vv;
        std::pair<std::string, std::string> set_pair(vertix_u, vertix_v);
        WeightPair weight_pair(weight_u, weight_v);
        (*gene_pair_weight_pair_map)[set_pair] = weight_pair; // TODO: Add pair
      }
      fscanf(in, "\t");
    }
  }
  fclose(in);
}
template<> void Read<int>(const char* file_name, double cutoff, std::map<std::pair<int, int>, WeightPair>* gene_pair_weight_pair_map) {
  FILE* in;
  if ((in = fopen(file_name, "r")) == NULL) {
    fprintf(stderr, "***> Open error on input file_name %s", file_name);
    exit(-1);
  }
  double weight_u, weight_v;
  int vertix_u, vertix_v;
  char u[100], v[100];
  int uu, vv;
  while (fscanf(in, "%s ", u) > 0) {
    sscanf(u, "%d:", &uu);
    vertix_u = uu;
    while (fscanf(in, "(%s", v) > 0) {
      std::replace(v, v + 100, ',', ' ');
      sscanf(v, "%d %lg %lg", &vv, &weight_u, &weight_v);
      if (weight_u < cutoff && weight_v < cutoff) {
        vertix_v = vv;
        std::pair<int, int> set_pair(vertix_u, vertix_v);
        WeightPair weight_pair(weight_u, weight_v);
        (*gene_pair_weight_pair_map)[set_pair] = weight_pair; // TODO: Add pair
      }
      fscanf(in, "\t");
    }
  }
  fclose(in);
}
}
