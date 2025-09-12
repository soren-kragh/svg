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

#pragma once

#include <svg_common.h>

namespace SVG {

class Color
{
  friend class Canvas;
  friend class Attributes;

public:

  Color( void );
  Color( uint8_t r, uint8_t g, uint8_t b );
  Color( ColorName color, float lighten = 0.0 );
  Color( std::string_view color_name, float lighten = 0.0 );
  Color( Color* color );

  Color* Set( uint8_t r, uint8_t g, uint8_t b );

  // The lighten value must be in the range [-1.0; 1.0]; a negative value
  // darkens the color.
  Color* Set( ColorName color, float lighten = 0.0 );

  // Can be any of the 147 named SVG color codes. Returns nullptr if an invalid
  // color name is given.
  Color* Set( std::string_view color_name, float lighten = 0.0 );

  Color* Set( Color* color );

  // Set color between two colors.
  Color* Set( Color* color1, Color* color2, float f = 0.5 );

  // opacity/transparency is a value in the range [0.0; 1.0]; default is
  // 1.0/0.0. Note that opacity/transparency may not be supported by all
  // viewers.
  Color* SetOpacity( float opacity );
  Color* SetTransparency( float transparency )
  {
    return SetOpacity( 1.0 - transparency );
  }

  // Factor must be in the range [-1.0; 1.0]; a negative value applies opposite
  // effect.
  Color* Lighten( float f );
  Color* Darken( float f );

  Color* Undef( void );
  Color* Clear( void );

  bool IsDefined( void ) { return rgb_defined; }
  bool IsClear( void ) { return rgb_none; }

  std::string SVG( std::string_view name = "" );

private:

  bool    rgb_defined;
  bool    rgb_none;
  uint8_t r;
  uint8_t g;
  uint8_t b;

  bool  opacity_defined;
  float opacity;

public:

  // Return the perceived difference [0.0;1.0] between two colors.
  static float Diff( Color* color1, Color* color2 );

  bool operator==( const Color& other ) const;

};

}
