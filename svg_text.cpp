//
//  Copyright (C) 2023, S. Kragh
//
//  This file is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This file is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//  See the GNU General Public License for more details.
//  <http://www.gnu.org/licenses/>.
//

#include <svg_text.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Text::Text(
  U x, U y,
  std::string str
)
{
  p.x = x;
  p.y = y;
  this->str = str;
}

///////////////////////////////////////////////////////////////////////////////

void Text::CollectAttr( Attributes& final_attr )
{
  Attr()->Collect( final_attr );

  if ( !final_attr.TextFont()->family_defined ) {
    SVG_FATAL( "SVG::Text::CollectAttr: failed to obtain font family" );
  }
  if ( !final_attr.TextFont()->size_defined ) {
    SVG_FATAL( "SVG::Text::CollectAttr: failed to obtain font size" );
  }
  if ( !final_attr.text_anchor_x_defined ) {
    SVG_FATAL( "SVG::Text::CollectAttr: failed to obtain text anchor x" );
  }
  if ( !final_attr.text_anchor_y_defined ) {
    SVG_FATAL( "SVG::Text::CollectAttr: failed to obtain text anchor y" );
  }
}

///////////////////////////////////////////////////////////////////////////////

// Boundary box of text before any rotation and translation.
BoundaryBox Text::GetMyBB( void )
{
  BoundaryBox bb;

  Attributes final_attr = Attributes( NULL );
  CollectAttr( final_attr );

  U w = final_attr.TextFont()->GetWidth( str );
  U h = final_attr.TextFont()->GetHeight();
  U x1 = p.x;
  U y1 = p.y;
  if ( final_attr.text_anchor_x == MidX ) x1 -= w / 2;
  if ( final_attr.text_anchor_x == MaxX ) x1 -= w;
  if ( final_attr.text_anchor_y == MidY ) y1 -= h / 2;
  if ( final_attr.text_anchor_y == MaxY ) y1 -= h;
  U x2 = x1 + w;
  U y2 = y1 + h;
  bb.Update( x1, y1 );
  bb.Update( x2, y2 );

  return bb;
}

void Text::UpdateBB(
  BoundaryBox& boundary_box,
  bool first, std::vector< Transform >& transforms
)
{
  BoundaryBox bb = GetMyBB();
  if ( first && transform.rotate_anchor_defined ) {
    transform.SetRotatePoint( bb );
  }
  transforms.push_back( transform );
  boundary_box.Update( TransformPoint( transforms, bb.min ) );
  boundary_box.Update( TransformPoint( transforms, bb.max ) );
  boundary_box.Update( TransformPoint( transforms, Point( bb.min.x, bb.max.y ) ) );
  boundary_box.Update( TransformPoint( transforms, Point( bb.max.x, bb.min.y ) ) );
  transforms.pop_back();
}

///////////////////////////////////////////////////////////////////////////////

void Text::GenSVG(
  std::ostringstream& oss,
  std::string& indent
)
{
  if ( str.length() == 0 ) return;
  U x = p.x;
  U y = p.y;
  U w;          // Width of one character.
  U h;          // Height of one character.
  { // Emulate text-anchor by adjusting the x- y-coordinates.
    Attributes final_attr = Attributes( NULL );
    CollectAttr( final_attr );
    h = final_attr.TextFont()->GetHeight();
    w = final_attr.TextFont()->GetWidth();
    if ( final_attr.text_anchor_x == MinX ) x += w / 2;
    if ( final_attr.text_anchor_x == MidX ) x -= w * (str.length() - 1.0) / 2;
    if ( final_attr.text_anchor_x == MaxX ) x -= w * (str.length() - 0.5);
    if ( final_attr.text_anchor_y == MidY ) y -= h / 2;
    if ( final_attr.text_anchor_y == MaxY ) y -= h;
    y += final_attr.TextFont()->GetBaseline();
  }
  oss
    << indent << "<g text-anchor=\"middle\""
    << Attr()->SVG( true ) << '>' << "\n";
  for ( char c : str ) {
    std::string s;
    if ( c < ' ' ) c = ' ';
    switch ( c ) {
      case '<' : s += "&lt;"; break;
      case '>' : s += "&gt;"; break;
      case '&' : s += "&amp;"; break;
      default  : s += c;
    }
    oss
      << indent << "  <text"
      << " x=" << U( +x ).SVG()
      << " y=" << U( -y ).SVG()
      << ">" << s << "</text>" << "\n";
    x += w;
  }
  oss << indent << "</g>" << "\n";
}

///////////////////////////////////////////////////////////////////////////////
