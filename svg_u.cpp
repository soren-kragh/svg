//
//  Copyright (C) 2023, S. Kragh
//
//  This file is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This file is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//  See the GNU General Public License for more details.
//  <http://www.gnu.org/licenses/>.
//

#include <svg_u.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

std::string U::SVG( bool quoted )
{
  std::ostringstream oss;
  if ( quoted ) oss << '"';
  int64_t x = llround( value * 1000.0 );
  if ( x < 0 ) {
    oss << '-';
    x = -x;
  }
  oss << (x / 1000);
  x = x % 1000;
  if ( x > 0 ) {
    oss << '.';
  }
  while ( x > 0 ) {
    oss << (x / 100);
    x = x % 100;
    x = x * 10;
  }
  if ( quoted ) oss << '"';
  return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
