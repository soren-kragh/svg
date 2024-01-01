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
#include <svg_u.h>

namespace SVG {

class Font
{
  friend class Text;
  friend class Attributes;

public:

  Font( void );
  Font( const std::string family );
  Font( const std::string family, U size );

  Font* Set( const Font& font );
  Font* SetFamily( const std::string family );
  Font* SetSize( U size );
  Font* SetBold( bool bold = true );

  U GetWidth( const std::string str );
  U GetWidth( U length = 1 );
  U GetHeight( void );
  U GetBaseline( void );

  std::string SVG( void );

private:

  bool        family_defined;
  std::string family;

  bool size_defined;
  U    size;

  bool weight_defined;
  bool weight_bold;

};

}
