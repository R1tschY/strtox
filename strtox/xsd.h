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

// TODO:

#include <ctime>

#include "stringview.h"

namespace strtox {
namespace xsd {

struct RawDate
{
  int year = 0;
  unsigned mouth = 0;
  unsigned day = 0;
};

struct RawTime
{
  unsigned hour = 0;
  unsigned minute = 0;
  unsigned second = 0;
  unsigned millisecond = 0;
  unsigned microsecond = 0;
};

struct TimeZoneOffset
{
  int offset_hours = 0;
  unsigned offset_minutes = 0;
};

struct DateTime
{
  RawDate date;
  RawTime time;
  TimeZoneOffset time_zone;

  template<typename T>
  T to() const
  {
    T t;
    convert(*this, t);
    return t;
  }
};

constexpr class tag_t { } tag;

/// \brief parse xsd:dateTime
DateTime parse_dateTime(string_view str);

void convert(const DateTime& datetime, std::tm& tm);
void convert(const DateTime& datetime, time_t& time);

} // namespace xsd

/// \brief parse xsd:dateTime
inline
void parse(string_view x, xsd::DateTime& ref, xsd::tag_t)
{
  ref = xsd::parse_dateTime(x);
}

} // namespace strtox




