///
/// Copyright (c) 2016 R1tschY
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to 
/// deal in the Software without restriction, including without limitation the 
/// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
/// sell copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.
///

#include <string>
#include <iostream>
#include <boost/spirit/home/x3.hpp>

#include "stringview.h"

namespace strtox {

namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

float parse_float(string_view x)
{
  float result = 0;
  auto iter = x.begin();
  bool r = x3::parse(iter, x.end(), x3::float_, result);
  if (!r || iter != x.end())
  {
    throw std::invalid_argument("strtox::parse_float: no conversion");
  }
  return result;
}

double parse_double(string_view x)
{
  double result = 0;
  auto iter = x.begin();
  bool r = x3::parse(iter, x.end(), x3::double_, result);
  if (!r || iter != x.end())
  {
    throw std::invalid_argument("strtox::parse_double: no conversion");
  }
  return result;
}

} // namespace strtox

