//
//  Copyright (C) 2023, S. Kragh
//
//  This file is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This file is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//  See the GNU General Public License for more details.
//  <http://www.gnu.org/licenses/>.
//

#include <svg_rect.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Rect::Rect(
  U x1, U y1,
  U x2, U y2,
  U corner_r
)
{
  if ( x1 < x2 ) {
    p1.x = x1;
    p2.x = x2;
  } else {
    p1.x = x2;
    p2.x = x1;
  }
  if ( y1 < y2 ) {
    p1.y = y1;
    p2.y = y2;
  } else {
    p1.y = y2;
    p2.y = y1;
  }
  this->corner_r = corner_r;
}

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////

void Rect::GenSVG(
  std::ostringstream& oss,
  std::string& indent
)
{
  oss
    << indent << "<rect"
    << " x=" << U( +p1.x ).SVG()
    << " y=" << U( -p2.y ).SVG()
    << " width="  << U( p2.x - p1.x ).SVG()
    << " height=" << U( p2.y - p1.y ).SVG();
  if ( corner_r > 0 ) {
    oss << " rx=" << corner_r.SVG();
  }
  oss
    << Attr()->SVG()
    << " />" << "\n";
}

///////////////////////////////////////////////////////////////////////////////
