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

#include <map>

#include <svg_color.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

struct RGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

static std::map< ColorName, RGB > color_table = {
  { ColorName::Black  , {0x00, 0x00, 0x00} },
  { ColorName::Red    , {0xFF, 0x00, 0x00} },
  { ColorName::Green  , {0x00, 0xFF, 0x00} },
  { ColorName::Blue   , {0x00, 0x00, 0xFF} },
  { ColorName::Yellow , {0xFF, 0xFF, 0x00} },
  { ColorName::Magenta, {0xFF, 0x00, 0xFF} },
  { ColorName::Cyan   , {0x00, 0xFF, 0xFF} },
  { ColorName::White  , {0xFF, 0xFF, 0xFF} },
  { ColorName::Brown  , {0x96, 0x4B, 0x00} },
  { ColorName::Orange , {0xFF, 0xA5, 0x00} },
  { ColorName::Purple , {0x80, 0x00, 0x80} },
  { ColorName::Pink   , {0xFF, 0xC0, 0xCB} }
};

Color::Color( void )
{
  rgb_defined = false;
  opacity_defined = false;
}

Color::Color( uint8_t r, uint8_t g, uint8_t b )
{
  Set( r, g, b );
  opacity_defined = false;
}

Color::Color( Color* color )
{
  Set( color );
}

//------------------------------------------------------------------------------

Color* Color::Set( uint8_t r, uint8_t g, uint8_t b )
{
  this->r = r;
  this->g = g;
  this->b = b;
  rgb_defined = true;
  rgb_none = false;
  return this;
}

Color* Color::Set( ColorName color, float lighten, float darken )
{
  RGB rgb = color_table[ color ];
  Set( rgb.r, rgb.g, rgb.b );
  Lighten( lighten );
  Darken( darken );
  return this;
}

Color* Color::Set( Color* color )
{
  *this = *color;
  return this;
}

void Color::SetOpacity( int opacity )
{
  if ( opacity < 0 ) opacity = 0;
  if ( opacity > 100 ) opacity = 100;
  this->opacity = opacity;
  opacity_defined = true;
}

void Color::Lighten( float f )
{
  r += (0xFF - r) * f;
  g += (0xFF - g) * f;
  b += (0xFF - b) * f;
}

void Color::Darken( float f )
{
  r *= 1 - f;
  g *= 1 - f;
  b *= 1 - f;
}

void Color::Clear( void )
{
  rgb_defined = true;
  rgb_none = true;
  opacity_defined = false;
}

std::string Color::SVG( const std::string name )
{
  std::ostringstream oss;
  if ( rgb_defined ) {
    oss << ' ' << name << '=';
    if ( rgb_none ) {
      oss << "\"none\"";
    } else {
      oss
        << "\"#"
        << std::hex << std::setfill( '0' ) << std::uppercase
        << std::setw( 2 ) << (0xFF & r)
        << std::setw( 2 ) << (0xFF & g)
        << std::setw( 2 ) << (0xFF & b)
        << '"';
    }
  }
  if ( opacity_defined && !(rgb_defined && rgb_none) ) {
    oss << std::dec << ' ' << name << "-opacity=" << '"' << opacity << "%\"";
  }
  return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
