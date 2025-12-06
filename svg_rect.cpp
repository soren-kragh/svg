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

#include <svg_rect.h>
#include <svg_canvas.h>

using namespace SVG;

////////////////////////////////////////////////////////////////////////////////

Rect::Rect(
  U x1, U y1,
  U x2, U y2,
  U corner_r
)
{
  if ( x1 > x2 ) std::swap( x1, x2 );
  if ( y1 > y2 ) std::swap( y1, y2 );
  new( &p1 ) Point( x1, y1 );
  new( &p2 ) Point( x2, y2 );
  this->corner_r = corner_r;
}

////////////////////////////////////////////////////////////////////////////////

void Rect::UpdateBB(
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
  if ( corner_r > 0 ) {
    U r = corner_r;
    U w = p2.x - p1.x;
    U h = p2.y - p1.y;
    if ( r > w/2 ) r = w/2;
    if ( r > h/2 ) r = h/2;
    Point c;
    c = TransformPoint( transforms, Point( p1.x + r, p1.y + r) );
    boundary_box.Update( c.x - r, c.y - r );
    boundary_box.Update( c.x + r, c.y + r );
    c = TransformPoint( transforms, Point( p2.x - r, p2.y - r) );
    boundary_box.Update( c.x - r, c.y - r );
    boundary_box.Update( c.x + r, c.y + r );
    c = TransformPoint( transforms, Point( p1.x + r, p2.y - r) );
    boundary_box.Update( c.x - r, c.y - r );
    boundary_box.Update( c.x + r, c.y + r );
    c = TransformPoint( transforms, Point( p2.x - r, p1.y + r) );
    boundary_box.Update( c.x - r, c.y - r );
    boundary_box.Update( c.x + r, c.y + r );
  } else {
    boundary_box.Update( TransformPoint( transforms, p1 ) );
    boundary_box.Update( TransformPoint( transforms, p2 ) );
    boundary_box.Update( TransformPoint( transforms, Point( p1.x, p2.y ) ) );
    boundary_box.Update( TransformPoint( transforms, Point( p2.x, p1.y ) ) );
  }
  transforms.pop_back();
}

////////////////////////////////////////////////////////////////////////////////

void Rect::GenSVG(
  std::ostringstream& oss,
  std::string& indent
)
{
  oss
    << indent << "<rect"
    << " x=" << U( p1.x ).SVG()
    << " y=" << U( canvas->settings.std_coor ? -p2.y : +p2.y ).SVG()
    << " width="  << U( p2.x - p1.x ).SVG()
    << " height=" << U( p2.y - p1.y ).SVG();
  if ( corner_r > 0 ) {
    oss << " rx=" << corner_r.SVG();
  }
  oss
    << Attr()->SVG()
    << " />" << "\n";
}

////////////////////////////////////////////////////////////////////////////////
