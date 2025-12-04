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

#include <svg_ellipse.h>

using namespace SVG;

////////////////////////////////////////////////////////////////////////////////

Ellipse::Ellipse(
  U cx, U cy, U rx, U ry
)
{
  center.x = cx;
  center.y = cy;
  this->rx = rx;
  this->ry = ry;
}

Ellipse::Ellipse(
  Point c, U rx, U ry
)
{
  center = c;
  this->rx = rx;
  this->ry = ry;
}

////////////////////////////////////////////////////////////////////////////////

void Ellipse::ComputeFocusPoints(
  Point& f1, Point& f2, U& a
)
{
  double ecc;
  if ( rx > ry ) {
    ecc = std::sqrt( rx*rx - ry*ry );
    f1.y = center.y; f1.x = center.x - ecc;
    f2.y = center.y; f2.x = center.x + ecc;
    a = rx;
  } else {
    ecc = std::sqrt( ry*ry - rx*rx );
    f1.x = center.x; f1.y = center.y - ecc;
    f2.x = center.x; f2.y = center.y + ecc;
    a = ry;
  }
}

////////////////////////////////////////////////////////////////////////////////

void Ellipse::UpdateBB(
  BoundaryBox& boundary_box,
  bool first, std::vector< Transform >& transforms
)
{
  if ( first && transform.rotate_anchor_defined ) {
    BoundaryBox bb;
    bb.Update( center.x - rx, center.y - ry );
    bb.Update( center.x + rx, center.y + ry );
    transform.SetRotatePoint( bb );
  }
  transforms.push_back( transform );
  Point f1;
  Point f2;
  U a;
  ComputeFocusPoints( f1, f2, a );
  f1 = TransformPoint( transforms, f1 );
  f2 = TransformPoint( transforms, f2 );
  double dx = f1.x - f2.x;
  double dy = f1.y - f2.y;
  double bx = std::sqrt( a*a - (dy*dy)/4 );
  double by = std::sqrt( a*a - (dx*dx)/4 );
  double cx = (f1.x + f2.x) / 2;
  double cy = (f1.y + f2.y) / 2;
  boundary_box.Update( cx - bx, cy - by );
  boundary_box.Update( cx + bx, cy + by );
  transforms.pop_back();
}

////////////////////////////////////////////////////////////////////////////////

void Ellipse::GenSVG(
  std::ostringstream& oss,
  std::string& indent
)
{
  oss
    << indent << "<ellipse"
    << " cx=" << U( +center.x ).SVG()
    << " cy=" << U( -center.y ).SVG()
    << " rx=" << U( rx ).SVG()
    << " ry=" << U( ry ).SVG()
    << Attr()->SVG()
    << " />" << "\n";
}

////////////////////////////////////////////////////////////////////////////////
