#ifndef GOST_SET_PAIR_CALC_H_
#define GOST_SET_PAIR_CALC_H_

#include <algorithm>
#include <set>

namespace set_pair_calc {
template<typename T> bool Assoicated(const std::pair<std::set<T>, std::set<T> >& s1, const std::pair<std::set<T>, std::set<T> >& s2) {
  typename std::set<T>::const_iterator pos_s;
  for (pos_s = s1.first.begin(); pos_s != s1.first.end(); ++pos_s) if (s2.first.count(*pos_s) > 0) return true;
  for (pos_s = s1.second.begin(); pos_s != s1.second.end(); ++pos_s) if (s2.second.count(*pos_s) > 0) return true;
  return false;
}
template<typename T> bool Includes(const std::pair<std::set<T>, std::set<T> >& s1, const std::pair<std::set<T>, std::set<T> >& s2) {
  return (std::includes(s1.first.begin(), s1.first.end(), s2.first.begin(), s2.first.end()) &&
          std::includes(s1.second.begin(), s1.second.end(), s2.second.begin(), s2.second.end()));
}
};

#endif // GOST_SET_PAIR_CALC_H_
