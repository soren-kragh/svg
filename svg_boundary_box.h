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

  BoundaryBox( void );

  void Update( U x, U y );
  void Update( Point p )
  {
    Update( p.x, p.y );
  }
  void Update( const BoundaryBox& bb );

  void Reset( void );

  Point min;
  Point max;

  bool defined;

};

}
