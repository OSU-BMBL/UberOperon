#ifndef GOST_OPERON_GENE_H_
#define GOST_OPERON_GENE_H_
#include <map>
#include <vector>
#include "gene_set_type.h"
struct OperonsGenes {
  std::map<gene_t, OperonId> gene2operon;
  std::vector<std::set<gene_t> > operon2gene;
};
#endif // GOST_OPERON_GENE_H_
