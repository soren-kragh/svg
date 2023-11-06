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

#pragma once

#include <inttypes.h>
#include <string>
#include <cmath>

#include <svg_common.h>

namespace SVG {

class U
{

public:

  U( void ) {}

  template <
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value>::type
  > U(T x) : value( static_cast<double>(x) ) {}

  operator double() const {
    return value;
  }

  U& operator +=(const U& other)
  {
    value += other.value;
    return *this;
  }

  U& operator -=(const U& other)
  {
    value -= other.value;
    return *this;
  }

  std::string SVG( bool quoted = true );

private:

  double value;

};

}
