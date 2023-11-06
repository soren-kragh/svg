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

#include <vector>

#include <svg_point.h>
#include <svg_attributes.h>
#include <svg_transform.h>
#include <svg_boundary_box.h>

namespace SVG {

class Canvas;
class Group;

class Object
{
  friend class Canvas;
  friend class Group;
  friend class Attributes;

public:

  Object( void );
  virtual ~Object( void ) {}

  Group* ParrentGroup( void );

  Attributes* Attr( void ) { return &attr; }

  void Move( U dx, U dy )
  {
    transform.translate_dx += dx;
    transform.translate_dy += dy;
  }
  void MoveTo(
    AnchorX anchor_x,
    AnchorY anchor_y,
    U x, U y
  );

  void Rotate(
    int theta,
    AnchorX anchor_x = MidX,
    AnchorY anchor_y = MidY
  ) {
    transform.rotate_theta          = (theta % 360 + 360) % 360;
    transform.rotate_anchor_defined = true;
    transform.rotate_anchor_x       = anchor_x;
    transform.rotate_anchor_y       = anchor_y;
  }
  void Rotate(
    int theta, U x, U y
  ) {
    transform.rotate_theta          = (theta % 360 + 360) % 360;
    transform.rotate_anchor_defined = false;
    transform.rotate_point.x        = x;
    transform.rotate_point.y        = y;
  }

  // Returns true if the object is empty, i.e. has not defined coordinates.
  virtual bool Empty( void ) { return false; }

  // GetBB() errors out when used on empty object as there are no defined
  // coordinates.
  BoundaryBox GetBB( void );

protected:

  virtual void UpdateBB(
    BoundaryBox& boundary_box,
    bool first, std::vector< Transform >& transforms
  ) = 0;

  virtual void GenSVG(
    std::ostringstream& oss,
    std::string& indent
  ) = 0;

  Group* parrent_group;

  Attributes attr = Attributes( this );

  Transform transform;

  Point TransformPoint(
    const std::vector< Transform >& transforms, Point p
  );

  std::string TransSVG( void );

};

}
