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

#pragma once

// TODO: error information (format error with position or range error with max/min value)
// TODO: range module (M,A-B,N-)

#include "stringview.h"

namespace strtox {

constexpr class std_tag_t { } std_tag;

/// \brief parse float
/// \details Parses a string range to a `float`. The string can any input
///  `std::stof` would also parse. Parsing is only successful if complete
///  string can be parsed. No whitespace is skipped.
/// \sa std::stof
float parse_float(string_view x);

inline
void parse(string_view x, float& ref, std_tag_t)
{
  ref = parse_float(x);
}

/// \brief parse double
/// \details Parses a string range to a `double`. The string can any input
///  `std::stof` would also parse. Parsing is only successful if complete
///  string can be parsed. No whitespace is skipped.
/// \sa std::stof
double parse_double(string_view x);

inline
void parse(string_view x, double& ref, std_tag_t)
{
  ref = parse_double(x);
}

template<typename T>
void parse(string_view x, T& ref)
{
  parse(x, ref, std_tag);
}

} // namespace strtox
