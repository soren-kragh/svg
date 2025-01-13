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

#include <svg_object.h>

namespace SVG {

class Text : public Object
{

public:

  Text( U x, U y, const std::string& str );
  Text( const std::string& str ) : Text( 0, 0, str ) {}
  Text( Point p, const std::string& str ) : Text( p.x, p.y, str ) {}

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

  // Parses the UTF-8 character identified by the iterator and advances the
  // iterator to the next UTF-8 character; returns true if the parsed character
  // is valid. If the iterator is at the end of the string, then it will not be
  // advanced and false will be returned. Unless the iterator is already at the
  // end, the iterator will always be advanced at least one byte.
  static bool UTF8_CharAdv(
    const std::string& s, std::string::const_iterator& it
  );

  // Returns number of UTF-8 characters in the given string.
  static size_t UTF8_CharNum( const std::string& s );

};

}
