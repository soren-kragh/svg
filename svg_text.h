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

  void CollectAttr( Attributes& final_attr );

  BoundaryBox GetMyBB( void );

};

}
