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
  Set( 0, 0, 0 );
  defined = false;
}

Color::Color( uint8_t r, uint8_t g, uint8_t b )
{
  Set( r, g, b );
}

Color::Color( Color* color )
{
  Set( color );
}

void Color::Set( ColorName color, float lighten, float darken )
{
  RGB rgb = color_table[ color ];
  Set( rgb.r, rgb.g, rgb.b );
  Lighten( lighten );
  Darken( darken );
}

void Color::Set( uint8_t r, uint8_t g, uint8_t b )
{
  this->r = r;
  this->g = g;
  this->b = b;
  invisible = false;
  defined = true;
}

void Color::Set( Color* color )
{
  *this = *color;
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
  invisible = true;
  defined = true;
}

bool Color::IsDefined()
{
  return defined;
}

bool Color::IsClear()
{
  return invisible;
}

std::string Color::SVG( bool quoted )
{
  std::ostringstream oss;
  if ( quoted ) oss << "\"";
  if ( defined ) {
    if ( invisible ) {
      oss << "none";
    } else {
      oss
        << "#"
        << std::hex << std::setfill( '0' ) << std::uppercase
        << std::setw( 2 ) << (0xFF & r)
        << std::setw( 2 ) << (0xFF & g)
        << std::setw( 2 ) << (0xFF & b);
    }
  }
  if ( quoted ) oss << "\"";
  return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
