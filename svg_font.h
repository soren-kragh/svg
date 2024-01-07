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
#include <svg_u.h>

namespace SVG {

class Font
{
  friend class Text;
  friend class Attributes;

public:

  Font( void );
  Font( const std::string family );
  Font( const std::string family, U size );

  Font* Set( const Font& font );
  Font* SetFamily( const std::string family );
  Font* SetSize( U size );
  Font* SetBold( bool bold = true );

  U GetWidth( const std::string str );
  U GetWidth( U length = 1 );
  U GetHeight( void );
  U GetBaseline( void );

  std::string SVG( void );

private:

  bool        family_defined;
  std::string family;

  bool size_defined;
  U    size;

  bool weight_defined;
  bool weight_bold;

};

}
