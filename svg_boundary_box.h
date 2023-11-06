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

#include <svg_common.h>
#include <svg_point.h>

namespace SVG {

class BoundaryBox
{

public:

  BoundaryBox( void );

  void Update( U x, U y );
  void Update( Point p )
  {
    Update( p.x, p.y );
  }

  void Reset( void );

  Point min;
  Point max;

  bool defined;

};

}
