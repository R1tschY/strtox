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

#include "xsd.h"

#include <boost/fusion/adapted.hpp>
#include <boost/spirit/home/x3.hpp>

#include "x3_utils.h"

using namespace strtox::xsd;

BOOST_FUSION_ADAPT_STRUCT(RawTime,
        (unsigned, hour)
        (unsigned, minute)
        (unsigned, second)
        (unsigned, millisecond)
        (unsigned, microsecond)
)

BOOST_FUSION_ADAPT_STRUCT(TimeZoneOffset,
        (int, offset_hours)
        (unsigned, offset_minutes)
)

BOOST_FUSION_ADAPT_STRUCT(RawDate,
        (int, year)
        (unsigned, mouth)
        (unsigned, day)
)

BOOST_FUSION_ADAPT_STRUCT(DateTime,
        (RawDate, date)
        (RawTime, time)
        (TimeZoneOffset, time_zone)
)

namespace strtox {
namespace xsd {

namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

namespace {

x3::rule<class RawTimeParser, RawTime> const RawTimeParser = "time";
auto const RawTimeParser_def =
  x3::uint_
  >> ':'
  >> x3::uint_
  >> ':'
  >> x3::uint_
  >> -x3::omit['.' >> +x3::digit] >> x3::attr(0) >> x3::attr(0);
BOOST_SPIRIT_DEFINE(RawTimeParser);

x3::rule<class TimeZoneOffsetParser, TimeZoneOffset> const TimeZoneOffsetParser = "$timeZoneOffset";
auto const TimeZoneOffsetParser_def =
  (
    ('Z' >> x3::attr(TimeZoneOffset{0, 0}))
    | x3x::as<TimeZoneOffset>[x3::int_ >> ':' >> x3::uint_]
  );
BOOST_SPIRIT_DEFINE(TimeZoneOffsetParser);

x3::rule<class RawDateParser, RawDate> const RawDateParser = "date";
auto const RawDateParser_def =
  x3::int_
  >> '-'
  >> x3::uint_
  >> '-'
  >> x3::uint_;
BOOST_SPIRIT_DEFINE(RawDateParser);

x3::rule<class DateTimeParser, DateTime> const DateTimeParser = "dateTime";
auto const DateTimeParser_def =
  RawDateParser
  >> 'T'
  >> -RawTimeParser
  >> TimeZoneOffsetParser;
BOOST_SPIRIT_DEFINE(DateTimeParser);

} // namespace

DateTime parse_dateTime(string_view x)
{
  auto iter = x.begin();
  const auto end = x.end();

  DateTime ast;
  bool r = x3::parse(iter, end, DateTimeParser, ast);
  if (!r || iter != end)
  {
      throw std::invalid_argument("strtox::xsd::parse_dateTime: no conversion");
  }

  return ast;
}

void convert(const DateTime& datetime, std::tm& result)
{
  // time
  result.tm_sec = datetime.time.second;
  result.tm_min = datetime.time.minute;
  result.tm_hour = datetime.time.hour;

  // date
  result.tm_mday = datetime.date.day;
  result.tm_mon = datetime.date.mouth - 1;
  result.tm_year = datetime.date.year - 1900;

  // no information
  result.tm_isdst = result.tm_yday = result.tm_wday = -1;

  // time zone
  result.tm_gmtoff = (
    datetime.time_zone.offset_hours * 60
    + datetime.time_zone.offset_minutes
  ) * 60;
  result.tm_zone = nullptr;
}

void convert(const DateTime& datetime, time_t& result)
{
  std::tm tm;
  convert(datetime, tm);
  result = timegm(&tm) - tm.tm_gmtoff;
}

} // namespace xsd
} // namespace strtox


