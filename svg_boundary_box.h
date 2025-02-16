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

#include <svg_common.h>
#include <svg_point.h>

namespace SVG {

class BoundaryBox
{

public:

  Point min;
  Point max;

  friend std::ostream& operator<<( std::ostream& os, BoundaryBox const& bb ) {
    os
      << '(' << bb.min.x << ',' << bb.min.y << ')'
      << ' '
      << '(' << bb.max.x << ',' << bb.max.y << ')';
    return os;
  }

  BoundaryBox( void ) {
    Reset();
  }
  BoundaryBox( Point min, Point max ) : min( min ), max( max ) {}

  void Update( U x, U y );
  void Update( Point p )
  {
    Update( p.x, p.y );
  }
  void Update( const BoundaryBox& bb ) {
    Update( bb.min );
    Update( bb.max );
  }

  bool Defined( void ) {
    return min.x <= max.x;
  }

  void Reset( void ) {
    min.x = +1;
    max.x = -1;
  }

};

}
