//
//  MIT No Attribution License
//
//  Copyright 2024, Soren Kragh
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the
//  “Software”), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish,
//  distribute, sublicense, and/or sell copies of the Software, and to
//  permit persons to whom the Software is furnished to do so.
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
