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

#include <svg_line.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Line::Line(
  U x1, U y1,
  U x2, U y2
)
{
  p1.x = x1;
  p1.y = y1;
  p2.x = x2;
  p2.y = y2;
}

Line::Line( Point p1, Point p2 )
{
  this->p1 = p1;
  this->p2 = p2;
}

///////////////////////////////////////////////////////////////////////////////

void Line::UpdateBB(
  BoundaryBox& boundary_box,
  bool first, std::vector< Transform >& transforms
)
{
  if ( first && transform.rotate_anchor_defined ) {
    BoundaryBox bb;
    bb.Update( p1 );
    bb.Update( p2 );
    transform.SetRotatePoint( bb );
  }
  transforms.push_back( transform );
  boundary_box.Update( TransformPoint( transforms, p1 ) );
  boundary_box.Update( TransformPoint( transforms, p2 ) );
  transforms.pop_back();
}

///////////////////////////////////////////////////////////////////////////////

void Line::GenSVG(
  std::ostringstream& oss,
  std::string& indent
)
{
  oss
    << indent << "<line"
    << " x1=" << U( +p1.x ).SVG()
    << " y1=" << U( -p1.y ).SVG()
    << " x2=" << U( +p2.x ).SVG()
    << " y2=" << U( -p2.y ).SVG()
    << Attr()->SVG()
    << " />" << "\n";
}

///////////////////////////////////////////////////////////////////////////////
