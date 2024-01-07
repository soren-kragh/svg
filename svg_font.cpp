//
//  MIT No Attribution License
//
//  Copyright 2024, Soren Kragh
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

Font* Font::Set( const Font& font )
{
  *this = font;
  return this;
}

Font* Font::SetFamily( const std::string family )
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
