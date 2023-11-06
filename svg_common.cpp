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

#include <svg_common.h>
#include <svg_object.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

bool SVG::Collides( Object* obj1, Object* obj2, U margin_x, U margin_y )
{
  if ( obj1 == NULL || obj2 == NULL ) return false;
  if ( obj1->Empty() || obj2->Empty() ) return false;
  BoundaryBox b1 = obj1->GetBB();
  BoundaryBox b2 = obj2->GetBB();

  b1.min.x -= margin_x;
  b1.max.x += margin_x;
  b1.min.y -= margin_y;
  b1.max.y += margin_y;

  if (
    b1.max.x <= b2.min.x || b1.min.x >= b2.max.x ||
    b1.max.y <= b2.min.y || b1.min.y >= b2.max.y
  )
    return false;

  return true;
}

bool SVG::Collides( Object* obj1, Object* obj2 )
{
  return Collides( obj1, obj2, 0, 0 );
}

///////////////////////////////////////////////////////////////////////////////
