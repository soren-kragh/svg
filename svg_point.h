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

#pragma once

#include <svg_u.h>

namespace SVG {

class Point
{

public:

  Point( void ) {};
  Point( U x, U y )
  {
    this->x = x;
    this->y = y;
  };

  U x;
  U y;

  bool operator==( const Point& other ) const {
    return x == other.x && y == other.y;
  }

  bool operator!=( const Point& other ) const {
    return !(*this == other);
  }

};

}
