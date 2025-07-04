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

#include <svg_poly.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Poly::Poly( std::initializer_list< U > coordinates )
{
  for ( auto it = coordinates.begin(); it != coordinates.end(); ++it ) {
    U x = *it;
    if ( ++it == coordinates.end() ) break;
    U y = *it;
    point_list.emplace_back( x, y );
  }
}

///////////////////////////////////////////////////////////////////////////////

void Poly::UpdateBB(
  BoundaryBox& boundary_box,
  bool first, std::vector< Transform >& transforms
)
{
  if ( first && transform.rotate_anchor_defined ) {
    BoundaryBox bb;
    for ( Point p : point_list ) {
      bb.Update( p );
    }
    transform.SetRotatePoint( bb );
  }
  transforms.push_back( transform );
  for ( Point p : point_list ) {
    boundary_box.Update( TransformPoint( transforms, p ) );
  }
  transforms.pop_back();
}

///////////////////////////////////////////////////////////////////////////////

void Poly::GenSVG(
  std::ostringstream& oss,
  std::string& indent
)
{
  if ( point_list.size() > 0 ) {
    if ( closed ) {
      oss << indent << "<polygon points=";
    } else {
      oss << indent << "<polyline points=";
    }
    char c = '"';
    for ( Point p : point_list ) {
      oss << c << U( +p.x ).SVG( false ) << ',' << U( -p.y ).SVG( false );
      c = ' ';
    }
    oss << '"' << Attr()->SVG() << " />" << "\n";
  }
}

///////////////////////////////////////////////////////////////////////////////
