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

#include <svg_font.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Font::Font( void )
{
  family_defined = false;
  size_defined = false;
  size = 0;
  weight_defined = false;
  weight_bold = false;
}

Font::Font( const std::string family )
{
  size_defined = false;
  size = 0;
  weight_defined = false;
  weight_bold = false;
  SetFamily( family );
}

Font::Font( const std::string family, U size )
{
  weight_defined = false;
  weight_bold = false;
  SetFamily( family );
  SetSize( size );
}

///////////////////////////////////////////////////////////////////////////////

void Font::Set( const Font& font )
{
  *this = font;
}

void Font::SetFamily( const std::string family )
{
  this->family = family;
  family_defined = true;
}

void Font::SetSize( U size )
{
  this->size = size;
  size_defined = true;
}

void Font::SetBold( bool bold )
{
  weight_bold = bold;
  weight_defined = true;
}

///////////////////////////////////////////////////////////////////////////////

U Font::GetWidth( const std::string str )
{
  return GetWidth( str.length() );
}

U Font::GetWidth( U length )
{
  if ( !family_defined ) {
    SVG_FATAL( "SVG::Font::GetWidth: font family not defined" );
  }
  if ( !size_defined ) {
    SVG_FATAL( "SVG::Font::GetWidth: font size not defined" );
  }
  return length * size * 0.52;
}

U Font::GetHeight( void )
{
  if ( !family_defined ) {
    SVG_FATAL( "SVG::Font::GetHeight: font family not defined" );
  }
  if ( !size_defined ) {
    SVG_FATAL( "SVG::Font::GetHeight: font size not defined" );
  }
  return size;
}

U Font::GetBaseline( void )
{
  if ( !family_defined ) {
    SVG_FATAL( "SVG::Font::GetBaseline: font family not defined" );
  }
  if ( !size_defined ) {
    SVG_FATAL( "SVG::Font::GetBaseline: font size not defined" );
  }
  return size * 0.22;
}

///////////////////////////////////////////////////////////////////////////////

std::string Font::SVG( void )
{
  std::ostringstream oss;

  if ( family_defined ) {
    oss << " font-family=\"" << family << "\"";
  }
  if ( size_defined ) {
    oss << " font-size=" << size.SVG();
  }
  if ( weight_defined ) {
    oss << " font-weight=";
    if ( weight_bold ) {
      oss << "\"bold\"";
    } else {
      oss << "\"normal\"";
    }
  }

  return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
