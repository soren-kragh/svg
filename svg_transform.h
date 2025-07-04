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

#pragma once

#include <svg_boundary_box.h>

namespace SVG {

class Transform
{

public:

  Transform( void ) {
    translate_dx = 0;
    translate_dy = 0;
    rotate_theta = 0;
    rotate_anchor_defined = false;
    rotate_anchor_x = AnchorX::Mid;
    rotate_anchor_y = AnchorY::Mid;
    rotate_point = Point( 0, 0 );
  }

  void SetRotatePoint( const BoundaryBox& bb )
  {
    if ( !rotate_anchor_defined ) {
      SVG_FATAL( "SVG::Transform::SetRotatePoint: undefined anchor" );
    }
    switch ( rotate_anchor_x ) {
      case AnchorX::Min : rotate_point.x = bb.min.x; break;
      case AnchorX::Max : rotate_point.x = bb.max.x; break;
      default   : rotate_point.x = (bb.min.x + bb.max.x) / 2;
    }
    switch ( rotate_anchor_y ) {
      case AnchorY::Min : rotate_point.y = bb.min.y; break;
      case AnchorY::Max : rotate_point.y = bb.max.y; break;
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
