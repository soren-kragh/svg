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

#pragma once

#include <svg_u.h>
#include <svg_point.h>
#include <svg_boundary_box.h>
#include <svg_attributes.h>

namespace SVG {

class Transform
{

public:

  Transform( void ) {
    translate_dx = 0;
    translate_dy = 0;
    rotate_theta = 0;
    rotate_anchor_defined = false;
    rotate_anchor_x = MidX;
    rotate_anchor_y = MidY;
    rotate_point = Point( 0, 0 );
  }

  void SetRotatePoint( const BoundaryBox& bb )
  {
    if ( !rotate_anchor_defined ) {
      SVG_FATAL( "SVG::Transform::SetRotatePoint: undefined anchor" );
    }
    switch ( rotate_anchor_x ) {
      case MinX : rotate_point.x = bb.min.x; break;
      case MaxX : rotate_point.x = bb.max.x; break;
      default   : rotate_point.x = (bb.min.x + bb.max.x) / 2;
    }
    switch ( rotate_anchor_y ) {
      case MinY : rotate_point.y = bb.min.y; break;
      case MaxY : rotate_point.y = bb.max.y; break;
      default   : rotate_point.y = (bb.min.y + bb.max.y) / 2;
    }
  }

  U translate_dx;
  U translate_dy;

  int     rotate_theta;
  bool    rotate_anchor_defined;
  AnchorX rotate_anchor_x;
  AnchorY rotate_anchor_y;
  Point   rotate_point;

};

}
