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
  Color( Color* color );

  Color* Set( uint8_t r, uint8_t g, uint8_t b );

  // lighten and darken must be in the range [0.0; 1.0].
  Color* Set( ColorName color, float lighten = 0.0, float darken = 0.0 );

  Color* Set( Color* color );

  // opacity/transparency is a percentage in the range [0; 100]; default is
  // 100/0. Note that opacity/transparency is not supported in all viewers.
  void SetOpacity( int opacity );
  void SetTransparency( int transparency )
  {
    SetOpacity( 100 - transparency );
  }

  // Factor must be in the range [0.0; 1.0].
  void Lighten( float f );
  void Darken( float f );

  void Clear( void );

private:

  std::string SVG( const std::string name );

  bool    rgb_defined;
  bool    rgb_none;
  uint8_t r;
  uint8_t g;
  uint8_t b;

  bool opacity_defined;
  int  opacity;

};

}
