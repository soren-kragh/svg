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

#include <svg_circle.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////
