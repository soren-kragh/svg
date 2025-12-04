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

#include <svg_font.h>

using namespace SVG;

////////////////////////////////////////////////////////////////////////////////

Font::Font( void )
{
  family_defined = false;
  size_defined = false;
  size = 0;
  width_factor_defined = false;
  width_factor = 1.0;
  height_factor_defined = false;
  height_factor = 1.0;
  baseline_factor_defined = false;
  baseline_factor = 1.0;
  weight_defined = false;
  weight_bold = false;
}

Font::Font( std::string_view family ) : Font()
{
  SetFamily( family );
}

Font::Font( std::string_view family, U size ) : Font()
{
  SetFamily( family );
  SetSize( size );
}

////////////////////////////////////////////////////////////////////////////////

Font* Font::Set( const Font& font )
{
  *this = font;
  return this;
}

Font* Font::SetFamily( std::string_view family )
{
  this->family = family;
  family_defined = true;
  return this;
}

Font* Font::SetSize( U size )
{
  this->size = size;
  size_defined = true;
  return this;
}

Font* Font::SetBold( bool bold )
{
  weight_bold = bold;
  weight_defined = true;
  return this;
}

Font* Font::SetWidthFactor( double factor )
{
  width_factor_defined = true;
  width_factor = factor;
  return this;
}

Font* Font::SetHeightFactor( double factor )
{
  height_factor_defined = true;
  height_factor = factor;
  return this;
}

Font* Font::SetBaselineFactor( double factor )
{
  baseline_factor_defined = true;
  baseline_factor = factor;
  return this;
}

////////////////////////////////////////////////////////////////////////////////

U Font::GetWidth( void )
{
  if ( !family_defined ) {
    SVG_FATAL( "SVG::Font::GetWidth: font family not defined" );
  }
  if ( !size_defined ) {
    SVG_FATAL( "SVG::Font::GetWidth: font size not defined" );
  }
  return size * 0.54 * width_factor;
}

U Font::GetHeight( void )
{
  if ( !family_defined ) {
    SVG_FATAL( "SVG::Font::GetHeight: font family not defined" );
  }
  if ( !size_defined ) {
    SVG_FATAL( "SVG::Font::GetHeight: font size not defined" );
  }
  return size * height_factor;
}

U Font::GetBaseline( void )
{
  if ( !family_defined ) {
    SVG_FATAL( "SVG::Font::GetBaseline: font family not defined" );
  }
  if ( !size_defined ) {
    SVG_FATAL( "SVG::Font::GetBaseline: font size not defined" );
  }
  return size * height_factor * 0.22 * baseline_factor;
}

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
