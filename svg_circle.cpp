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

#include <svg_circle.h>

using namespace SVG;

////////////////////////////////////////////////////////////////////////////////

Circle::Circle( U cx, U cy, U radius )
{
  center.x = cx;
  center.y = cy;
  this->radius = radius;
}

Circle::Circle( Point c, U radius )
{
  center = c;
  this->radius = radius;
}

////////////////////////////////////////////////////////////////////////////////

void Circle::UpdateBB(
  BoundaryBox& boundary_box,
  bool first, std::vector< Transform >& transforms
)
{
  if ( first && transform.rotate_anchor_defined ) {
    BoundaryBox bb;
    bb.Update( center.x - radius, center.y - radius );
    bb.Update( center.x + radius, center.y + radius );
    transform.SetRotatePoint( bb );
  }
  transforms.push_back( transform );
  Point c = TransformPoint( transforms, center );
  boundary_box.Update( c.x - radius, c.y - radius );
  boundary_box.Update( c.x + radius, c.y + radius );
  transforms.pop_back();
}

////////////////////////////////////////////////////////////////////////////////

void Circle::GenSVG(
  std::ostringstream& oss,
  std::string& indent
)
{
  oss
    << indent << "<circle"
    << " cx=" << U( +center.x ).SVG()
    << " cy=" << U( -center.y ).SVG()
    << " r=" << U( radius ).SVG()
    << Attr()->SVG()
    << " />" << "\n";
}

////////////////////////////////////////////////////////////////////////////////
