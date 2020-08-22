// Copyright 2011 <Copyright ZHANG Yu>
// Author: Qin Ma <maqin@csbl.bmb.uga.edu>, May. 09, 2010
// Usage: used to load the input files: .out .operon .ptt
//
#include "../include/edge_set_matrix.h"
#include <stdio.h> // atof
#include <stdlib.h> // atof
#include <string.h> // strcmp etc.
#include <string>
#include <algorithm>
#include "../include/operons_in_genome.h"

void EdgeSetMatrix::Load(const std::map<gene_pair_t, WeightPair>& reader_map) {
  edge_map_ = reader_map; // TODO: A reference is enough?
}

void EdgeSetMatrix::Process(const std::map<gene_t, OperonId>& u, std::map<gene_t, OperonId>& v) {
  // go through all edges
  for (std::map<gene_pair_t, WeightPair>::const_iterator pos_s = this->edge_map_.begin(); pos_s != this->edge_map_.end(); ++pos_s)
    bipartite_graph_edge_set_map_matrix_[u.at(pos_s->first.first)][v.at(pos_s->first.second)].insert(*pos_s);
}
