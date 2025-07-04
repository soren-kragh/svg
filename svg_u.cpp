//
//  MIT No Attribution License
//
//  Copyright 2025, Soren Kragh
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the
//  “Software”), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish,
//  distribute, sublicense, and/or sell copies of the Software, and to
//  permit persons to whom the Software is furnished to do so.
//

#include <svg_u.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

std::string U::SVG( bool quoted )
{
  std::ostringstream oss;
  if ( quoted ) oss << '"';
  int64_t x = std::llround( value * 1000.0 );
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
