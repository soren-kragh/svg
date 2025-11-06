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

  // Used to set a gradient on individual objects. The relative coordinates and
  // stops are fractions, see SVG linearGradient for how this works. Note that
  // each letter in a text is considered a separate object for gradients.
  Color* SetGradient(
    Color* stop_color1, Color* stop_color2,
    float x1, float y1, float x2, float y2,
    float stop1 = 0.0, float stop2 = 1.0,
    bool group = false
  );

  // Like SetGradient() but the gradient is applied across all objects in a
  // group and the paint vector is relative to the group bounding box. Note that
  // the gradient effect is applied before any of the objects within the group
  // are moved or rotated, therefore, applying SetGroupGradient() on a group
  // with moved and/or rotated children will probably not result in the expected
  // effect.
  Color* SetGroupGradient(
    Color* stop_color1, Color* stop_color2,
    float x1, float y1, float x2, float y2,
    float stop1 = 0.0, float stop2 = 1.0
  )
  {
    return
      SetGradient(
        stop_color1, stop_color2, x1, y1, x2, y2, stop1, stop2, true
      );
  }

  // The opacity/transparency is a value in the range [0.0; 1.0]. Setting a
  // color deletes this attribute, so opacity/transparency should be set after
  // the color has been set.
  Color* SetOpacity( float opacity );
  Color* SetTransparency( float transparency )
  {
    return SetOpacity( 1.0 - transparency );
  }

  // Factor must be in the range [-1.0; 1.0]; a negative value applies opposite
  // effect. If this color is a gradient, both stop colors are affected.
  Color* Lighten( float f );
  Color* Darken( float f ) {
    return Lighten( -f );
  }

  // Factor must be in the range [-1.0; 1.0]; a negative value applies opposite
  // effect. If this color is a gradient, both stop colors are affected.
  Color* Opacify( float f );
  Color* Transparify( float f ) {
    return Opacify( -f );
  }

  Color* Undef();
  Color* Clear();

  bool IsDefined() const { return col1.rgb_defined; }
  bool IsClear() const { return col1.rgb_none; }
  bool IsGradient() const
  {
    return
      col1.rgb_defined && !col1.rgb_none &&
      col2.rgb_defined && !col2.rgb_none;
  }

  std::string SVG( std::string_view name );
  std::string SVG();

private:

  struct col_t {
    bool    rgb_defined = false;
    bool    rgb_none = true;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    float opacity = 1.0;        // Used only for gradient.

    std::string StopOffsetSVG();
  };

  col_t col1;
  col_t col2;   // Used only if gradient.

  struct grad_t {
    float    x1    = 0.0;
    float    y1    = 0.0;
    float    x2    = 1.0;
    float    y2    = 1.0;
    float    stop1 = 0.0;
    float    stop2 = 1.0;
    uint32_t id    = 0;
    bool     group = false;
  };

  grad_t grad;

  bool  opacity_defined = false;
  float opacity = 1.0;

public:

  // Return the perceived difference [0.0;1.0] between two colors.
  static float Diff( Color* color1, Color* color2 );

  bool operator==( const Color& other ) const;

};

}
