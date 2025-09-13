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

#include <svg_object.h>

namespace SVG {

class Text : public Object
{

public:

  Text( U x, U y, std::string_view str );
  Text( std::string_view str ) : Text( 0, 0, str ) {}
  Text( Point p, std::string_view str ) : Text( p.x, p.y, str ) {}

  // Return length of the text (in UTF-8).
  size_t Length( void ) { return utf8_len; }

private:

  void UpdateBB(
    BoundaryBox& boundary_box,
    bool first, std::vector< Transform >& transforms
  );

  void GenSVG(
    std::ostringstream& oss,
    std::string& indent
  );

  Point p;

  std::string str;
  size_t utf8_len = 0;

  void CollectAttr( Attributes& final_attr );

  BoundaryBox GetMyBB( void );

public:

  // Parses the UTF-8 character identified by the index and advances the index
  // to the next UTF-8 character; returns true if the parsed character is valid.
  // If the index is at the end of the string, then it will not be advanced and
  // false will be returned. Unless the index is already at the end, the index
  // will always be advanced at least one byte.
  static bool UTF8_CharAdv( std::string_view s, size_t& idx );

  // Returns number of UTF-8 characters in the given string.
  static size_t UTF8_CharNum( std::string_view s );

};

}
