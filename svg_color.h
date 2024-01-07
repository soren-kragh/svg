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

public:

  Color( void );
  Color( uint8_t r, uint8_t g, uint8_t b );
  Color( Color* color );

  void Set( uint8_t r, uint8_t g, uint8_t b );

  // lighten and darken must be in the range [0.0; 1.0].
  void Set( ColorName color, float lighten = 0.0, float darken = 0.0 );

  void Set( Color* color );

  // Factor must be in the range [0.0; 1.0].
  void Lighten( float f );
  void Darken( float f );

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
