/// from GitHub Gist https://gist.github.com/sehe/8678988 from sehe
#pragma once

#include <set>
#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp> // for charset
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/variant.hpp>     // for tree nodes
#include <boost/optional.hpp>    // for multiplicity upperbound

#include "stringview.h"

namespace strtox {

namespace regex {

// copied from https://stackoverflow.com/a/21419351/1188453

struct multiplicity
{
  unsigned minoccurs_;
  boost::optional<unsigned> maxoccurs_;
  bool greedy_;

  multiplicity(unsigned minoccurs = 1, boost::optional<unsigned> maxoccurs = 1)
  : minoccurs_(minoccurs), maxoccurs_(maxoccurs), greedy_(true)
  { }

  bool unbounded() const { return !maxoccurs_; }
  bool repeating() const { return !maxoccurs_ || *maxoccurs_ > 1; }
};

struct charset
{
  bool negated_;

  using range   = boost::tuple<char, char>; // from, till
  using element = boost::variant<char, range>;

  std::vector<element> elements_;
  // TODO: single set for loose elements, simplify() method
};

struct start_of_match {};
struct end_of_match {};
struct any_char {};
struct group;

typedef boost::variant<   // unquantified expression
  start_of_match,
  end_of_match,
  any_char,
  charset,
  std::string,          // literal
  boost::recursive_wrapper<group> // sub expression
> simple;

struct atom               // quantified simple expression
{
  simple       expr_;
  multiplicity mult_;
};

using sequence    = std::vector<atom>;
using alternative = std::vector<sequence>;
using ast         = boost::variant<atom, sequence, alternative>;

struct group {
  alternative root_;

  group() = default;
  group(alternative root) : root_(std::move(root)) { }
};

} // namespace regex

/// \brief parse Regex to it's ast
bool parse_regex(string_view input, regex::ast& data);

} // namespace strtox
