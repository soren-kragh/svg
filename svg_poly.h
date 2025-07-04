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

class Poly : public Object
{

public:

  Poly( void ) {}

  template< typename... Args >
  Poly( const Args&... args ) : point_list{ args... } {}

  Poly( std::initializer_list< U > coordinates );

  void Add( Point p )
  {
    point_list.push_back( p );
  }
  void Add( U x, U y )
  {
    point_list.emplace_back( x, y );
  }

  void Close( void ) { closed = true; }

private:

  void UpdateBB(
    BoundaryBox& boundary_box,
    bool first, std::vector< Transform >& transforms
  );

  void GenSVG(
    std::ostringstream& oss,
    std::string& indent
  );

  std::vector< Point > point_list;
  bool closed = false;

};

}
