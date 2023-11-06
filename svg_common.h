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

#include <sstream>
#include <iostream>
#include <iomanip>

#define SVG_FATAL( MSG_ ) \
  do \
  { \
    std::cerr << "*** SVG_FATAL: " << MSG_ << std::endl; \
    exit( 1 ); \
  } while ( 0 )

#define SVG_DBG( MSG_ ) \
  do \
  { \
    std::cerr << MSG_ << std::endl; \
  } while ( 0 )

namespace SVG {

  class U;
  class Object;

  typedef enum { MinX, MidX, MaxX } AnchorX;
  typedef enum { MinY, MidY, MaxY } AnchorY;

  typedef enum {
    Black, Red, Green, Blue, Yellow, Magenta, Cyan, White,
    Brown, Orange, Purple, Pink
  } ColorName;

  // Collision is determined by object boundary box alone, so it tends to be
  // quite conservative.
  bool Collides( Object* obj1, Object* obj2 );
  bool Collides( Object* obj1, Object* obj2, U margin_x, U margin_y );

}
