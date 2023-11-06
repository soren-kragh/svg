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

namespace SVG {

class Color
{

public:

  Color( void );
  Color( uint8_t r, uint8_t g, uint8_t b );
  Color( Color* color );

  void Set( uint8_t r, uint8_t g, uint8_t b );

  // lighten and darken must be in the range [0.0; 1.0].
  void Set( ColorName color, float lighten = 0.0, float darken = 0.0 );

  void Set( Color* color );

  void Clear( void );

  bool IsDefined();
  bool IsClear();

  std::string SVG( bool quoted = true );

private:

  bool defined;

  uint8_t r;
  uint8_t g;
  uint8_t b;

  bool invisible;

};

}
