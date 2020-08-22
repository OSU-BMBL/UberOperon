#ifndef GOST_INT_SET_H_
#define GOST_INT_SET_H_

#include <set>
#include <string>
#include <utility>

typedef std::string gene_t;
typedef std::pair<gene_t, gene_t> gene_pair_t;
typedef std::set<gene_t> gene_set_t;

typedef int OperonId;

//typedef std::pair<gene_set_t, gene_set_t> GeneSetPair;
class GeneSetPair : public std::pair<gene_set_t, gene_set_t> {
public:
  GeneSetPair(const gene_set_t& g1, const gene_set_t& g2) : std::pair<gene_set_t, gene_set_t>(g1, g2) {}
  GeneSetPair(const GeneSetPair& graph_list_1, const GeneSetPair& graph_list_2) {
    Insert(graph_list_1);
    Insert(graph_list_2);
  }
//private:
  void Insert(const GeneSetPair& name_set_to_insert) {
    this->first.insert(name_set_to_insert.first.begin(), name_set_to_insert.first.end());
    this->second.insert(name_set_to_insert.second.begin(), name_set_to_insert.second.end());
  }
};

#endif // GOST_INT_SET_H_
