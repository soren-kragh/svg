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

#include <svg_poly.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Poly::Poly( std::initializer_list< U > coordinates )
{
  for ( auto it = coordinates.begin(); it != coordinates.end(); ++it ) {
    U x = *it;
    if ( ++it == coordinates.end() ) break;
    U y = *it;
    point_list.emplace_back( x, y );
  }
}

///////////////////////////////////////////////////////////////////////////////

void Poly::UpdateBB(
  BoundaryBox& boundary_box,
  bool first, std::vector< Transform >& transforms
)
{
  if ( first && transform.rotate_anchor_defined ) {
    BoundaryBox bb;
    for ( Point p : point_list ) {
      bb.Update( p );
    }
    transform.SetRotatePoint( bb );
  }
  transforms.push_back( transform );
  for ( Point p : point_list ) {
    boundary_box.Update( TransformPoint( transforms, p ) );
  }
  transforms.pop_back();
}

///////////////////////////////////////////////////////////////////////////////

void Poly::GenSVG(
  std::ostringstream& oss,
  std::string& indent
)
{
  if ( point_list.size() > 0 ) {
    if ( closed ) {
      oss << indent << "<polygon points=";
    } else {
      oss << indent << "<polyline points=";
    }
    char c = '"';
    for ( Point p : point_list ) {
      oss << c << U( +p.x ).SVG( false ) << ',' << U( -p.y ).SVG( false );
      c = ' ';
    }
    oss << '"' << Attr()->SVG() << " />" << "\n";
  }
}

///////////////////////////////////////////////////////////////////////////////
