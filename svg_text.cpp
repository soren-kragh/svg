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

#include <svg_text.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Text::Text( U x, U y, const std::string& str )
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

  Attributes final_attr = Attributes( nullptr );
  CollectAttr( final_attr );

  U w = final_attr.TextFont()->GetWidth( str );
  U h = final_attr.TextFont()->GetHeight();
  U x1 = p.x;
  U y1 = p.y;
  if ( final_attr.text_anchor_x == AnchorX::Mid ) x1 -= w / 2;
  if ( final_attr.text_anchor_x == AnchorX::Max ) x1 -= w;
  if ( final_attr.text_anchor_y == AnchorY::Mid ) y1 -= h / 2;
  if ( final_attr.text_anchor_y == AnchorY::Max ) y1 -= h;
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
    Attributes final_attr = Attributes( nullptr );
    CollectAttr( final_attr );
    h = final_attr.TextFont()->GetHeight();
    w = final_attr.TextFont()->GetWidth();
    if ( final_attr.text_anchor_x == AnchorX::Min ) x += w / 2;
    if ( final_attr.text_anchor_x == AnchorX::Mid ) x -= w * (str.length() - 1.0) / 2;
    if ( final_attr.text_anchor_x == AnchorX::Max ) x -= w * (str.length() - 0.5);
    if ( final_attr.text_anchor_y == AnchorY::Mid ) y -= h / 2;
    if ( final_attr.text_anchor_y == AnchorY::Max ) y -= h;
    y += final_attr.TextFont()->GetBaseline();
  }
  oss
    << indent << "<g text-anchor=\"middle\""
    << Attr()->SVG( true ) << '>' << "\n";
  for ( unsigned char c : str ) {
    std::string s;
    switch ( c ) {
      case '<'  : s += "&lt;"; break;
      case '>'  : s += "&gt;"; break;
      case '&'  : s += "&amp;"; break;
      case 0xE6 : s += "&#956;"; break;
      default : {
        if ( c < ' ' || c > 0x7E ) c = ' ';
        s += c;
      }
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
