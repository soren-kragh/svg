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

#include <svg_object.h>

namespace SVG {

class Rect : public Object
{
  friend Canvas;

public:

  Rect(
    U x1, U y1,
    U x2, U y2,
    U corner_r = 0
  );
  Rect( Point p1, Point p2, U corner_r = 0 ) :
    Rect( p1.x, p1.y, p2.x, p2.y, corner_r ) {}

private:

  void UpdateBB(
    BoundaryBox& boundary_box,
    bool first, std::vector< Transform >& transforms
  );

  void GenSVG(
    std::ostringstream& oss,
    std::string& indent
  );

  Point p1;
  Point p2;
  U corner_r;

};

}
