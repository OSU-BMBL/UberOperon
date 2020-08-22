#ifndef GOST_RBH_MY_RBH_H_
#define GOST_RBH_MY_RBH_H_
#include "rbh.h"
#include "../base_type/bipartite_graph_edge_set.h"

class MyRbh : public Rbh <GeneType, double> {
public:
  MyRbh(const char* file) {
    ReadFile(file);
  }
  void Output() {
    OutputFile(stdout);
  }
  void OutputFile(const char* file_name) {
    FILE* out;
    if ((out = fopen(file_name, "w")) == NULL) {
      fprintf(stderr, "***> Open error on output file_name %s", file_name);
      exit(-1);
    }
    OutputFile(out);
    fclose(out);
  }
private:
  void ReadFile(const char* file_name) {
    FILE* in;
    if ((in = fopen(file_name, "r")) == NULL) {
      fprintf(stderr, "input file_name %s can't be opened. Program died.\n", file_name);
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
        sscanf(v, "%s %lf %lf", vv, &weight_u, &weight_v);
        vertix_v = vv;
        this->Add(vertix_u, vertix_v, weight_u, weight_v);
        fscanf(in, "\t");
      }
    }
    fclose(in);
  }
  void OutputFile(FILE* out) {
    BipartiteGraphEdgeSet<std::string> edge_set;
    this->GetAllEdges(&edge_set);
    for (BipartiteGraphEdgeSet<std::string>::iterator it = edge_set.begin() ; it != edge_set.end(); it++ )
      fprintf(out, "%s,%s\n", it->left().c_str(), it->right().c_str());
  }
};

#endif // GOST_RBH_MY_RBH_H_