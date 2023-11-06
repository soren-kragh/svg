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
