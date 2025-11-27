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

#include <vector>

#include <svg_common.h>

namespace SVG {

class Color
{
  friend class Canvas;
  friend class Attributes;

public:

  Color( void );
  Color( uint8_t r, uint8_t g, uint8_t b );
  Color( ColorName color, double lighten = 0.0 );
  Color( std::string_view color_name, double lighten = 0.0 );
  Color( const Color* color );

  Color* Set( uint8_t r, uint8_t g, uint8_t b );

  // The lighten value must be in the range [-1.0; 1.0]; a negative value
  // darkens the color.
  Color* Set( ColorName color, double lighten = 0.0 );

  // Can be any of the 147 named SVG color codes. Returns nullptr if an invalid
  // color name is given.
  Color* Set( std::string_view color_name, double lighten = 0.0 );

  Color* Set( const Color* color );

  // Set color between two colors.
  Color* Set( const Color* color1, const Color* color2, double f = 0.5 );

  // Used to add gradient stop points (see SVG linearGradient for how this
  // works), if the stop offset is outside the allowed [0.0;1.0] range it is
  // automatically assigned an equidistant value. If no color is given the
  // current color set by Set() is used.
  Color* AddGradientStop( const Color* color, double stop_ofs = -1.0 );
  Color* AddGradientStop( const Color& color, double stop_ofs = -1.0 )
  {
    return AddGradientStop( &color, stop_ofs );
  }
  Color* AddGradientStop( double stop_ofs = -1.0 )
  {
    return AddGradientStop( this, stop_ofs );
  }

  // Define or redefine gradient direction; the values are relative meaning that
  // 0.0 corresponds to the min object coordinate and 1.0 corresponds to the max
  // object coordinate. The group flag indicates if the gradient is applied
  // across the entire group, if not, the gradient is applied individually on
  // each leaf object within the hierarchy. Note that the group gradient effect
  // is applied before any of the objects within the group are moved or rotated,
  // therefore, setting the group flag on a group with moved and/or rotated
  // children will probably not result in the expected effect, unless you know
  // exactly what you're doing.
  Color* SetGradientDir( double x1, double y1, double x2, double y2, bool group );
  Color* SetGradientDir( double x1, double y1, double x2, double y2 );

  // Define or redefine the stop offset for gradient color number i.
  Color* SetStopOfs( size_t i, double stop_ofs );

  // The opacity/transparency is a value in the range [0.0; 1.0]. Setting a
  // color deletes this attribute, so opacity/transparency should be set after
  // the color has been set. If the gradient flag is set, then the individual
  // gradient colors are affected instead of the overall opacity/transparency
  // (for gradients, the two different opacity contributions compound).
  Color* SetOpacity( double opacity, bool gradient = false );
  Color* SetTransparency( double transparency, bool gradient = false )
  {
    return SetOpacity( 1.0 - transparency, gradient );
  }
  double GetOpacity()
  {
    return opacity_defined ? opacity : 1.0;
  }
  double GetTransparency()
  {
    return 1.0 - GetOpacity();
  }

  // Factor must be in the range [-1.0; 1.0]; a negative value applies opposite
  // effect. If this color is a gradient, both stop colors are affected.
  Color* Lighten( double f );
  Color* Darken( double f ) {
    return Lighten( -f );
  }

  // Factor must be in the range [-1.0; 1.0]; a negative value applies opposite
  // effect. If this color is a gradient, both stop colors are affected. If the
  // gradient flag is set, then the individual gradient colors are affected
  // instead of the overall opacity/transparency (for gradients, the two
  // different opacity contributions compound).
  Color* Opacify( double f, bool gradient = false );
  Color* Transparify( double f, bool gradient = false ) {
    return Opacify( -f, gradient );
  }

  Color* Undef();
  Color* Clear();

  bool IsDefined() const { return col.rgb_defined; }
  bool IsClear() const { return col.rgb_none; }
  bool IsGradient() const
  {
    return !col_list.empty();
  }

  std::string SVG( std::string_view name );
  std::string SVG();

private:

  void ComputeAutoStopOfs();

  struct col_t {
    bool    rgb_defined = false;
    bool    rgb_none = true;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    // Used only for gradient.
    bool  stop_ofs_auto = true;
    double stop_ofs = 0.0;
    double stop_opacity = 1.0;

    std::string StopOffsetSVG();

    bool operator==( const col_t& other ) const;
    bool operator!=( const col_t& other ) const
    {
      return !(*this == other);
    }
  };
  col_t col;

  // Used only for gradient.
  std::vector< col_t > col_list;

  // Used only for gradient.
  struct grad_t {
    double   x1    = 0.0;
    double   y1    = 0.0;
    double   x2    = 1.0;
    double   y2    = 1.0;
    bool     group = false;
    uint32_t id    = 0;
  };
  grad_t grad;

  bool   opacity_defined = false;
  double opacity = 1.0;

public:

  // Return the perceived difference [0.0;1.0] between two colors.
  static double Diff( const Color* color1, const Color* color2 );

  bool operator==( const Color& other ) const;
  bool operator!=( const Color& other ) const
  {
    return !(*this == other);
  }

};

}
