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

#include <svg_u.h>

namespace SVG {

class Font
{
  friend class Text;
  friend class Attributes;

public:

  Font( void );
  Font( std::string_view family );
  Font( std::string_view family, U size );

  Font* Set( const Font& font );
  Font* SetFamily( std::string_view family );
  Font* SetSize( U size );
  Font* SetBold( bool bold = true );

  // Used to increase/decrease the width/height/baseline by the given factor.
  // The font dimensions are normally determined based on the size and assuming
  // mono-space Latin letters, but if for example wider letters are used the
  // width can be scaled up.
  Font* SetWidthFactor( float factor );
  Font* SetHeightFactor( float factor );
  Font* SetBaselineFactor( float factor );

  U GetWidth( void );
  U GetHeight( void );
  U GetBaseline( void );

  std::string SVG( void );

private:

  bool        family_defined;
  std::string family;

  bool size_defined;
  U    size;

  bool  width_factor_defined;
  float width_factor;

  bool  height_factor_defined;
  float height_factor;

  bool  baseline_factor_defined;
  float baseline_factor;

  bool weight_defined;
  bool weight_bold;

};

}
