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

#include <svg_boundary_box.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

BoundaryBox::BoundaryBox( void )
{
  Reset();
}

void BoundaryBox::Update( U x, U y )
{
  if ( defined ) {
    if ( min.x > x ) min.x = x;
    if ( min.y > y ) min.y = y;
    if ( max.x < x ) max.x = x;
    if ( max.y < y ) max.y = y;
  } else {
    min.x = x; min.y = y;
    max.x = x; max.y = y;
    defined = true;
  }
}

void BoundaryBox::Reset( void )
{
  defined = false;
  min.x = 0;
  min.y = 0;
  max.x = 0;
  max.y = 0;
}

///////////////////////////////////////////////////////////////////////////////
