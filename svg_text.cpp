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

#include <svg_text.h>

using namespace SVG;

////////////////////////////////////////////////////////////////////////////////

Text::Text( U x, U y, const std::string& str )
{
  p.x = x;
  p.y = y;
  this->str = str;
  utf8_len = Text::UTF8_CharNum( str );
}

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

// Boundary box of text before any rotation and translation.
BoundaryBox Text::GetMyBB( void )
{
  BoundaryBox bb;

  Attributes final_attr = Attributes( nullptr );
  CollectAttr( final_attr );

  U w = final_attr.TextFont()->GetWidth() * utf8_len;
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

////////////////////////////////////////////////////////////////////////////////

static const char MATH_SANS_DIGITS[ 10 ][ 4 ] = {
  { '\xF0', '\x9D', '\x9F', '\xA2' }, // 𝟢 (U+1D7E2)
  { '\xF0', '\x9D', '\x9F', '\xA3' }, // 𝟣 (U+1D7E3)
  { '\xF0', '\x9D', '\x9F', '\xA4' }, // 𝟤 (U+1D7E4)
  { '\xF0', '\x9D', '\x9F', '\xA5' }, // 𝟥 (U+1D7E5)
  { '\xF0', '\x9D', '\x9F', '\xA6' }, // 𝟦 (U+1D7E6)
  { '\xF0', '\x9D', '\x9F', '\xA7' }, // 𝟧 (U+1D7E7)
  { '\xF0', '\x9D', '\x9F', '\xA8' }, // 𝟨 (U+1D7E8)
  { '\xF0', '\x9D', '\x9F', '\xA9' }, // 𝟩 (U+1D7E9)
  { '\xF0', '\x9D', '\x9F', '\xAA' }, // 𝟪 (U+1D7EA)
  { '\xF0', '\x9D', '\x9F', '\xAB' }  // 𝟫 (U+1D7EB)
};

//------------------------------------------------------------------------------

void Text::GenSVG(
  std::ostringstream& oss,
  std::string& indent
)
{
  if ( utf8_len == 0 ) return;
  U x = p.x;
  U y = p.y;
  U w;          // Width of one character.
  U h;          // Height of one character.

  Attributes final_attr = Attributes( nullptr );
  CollectAttr( final_attr );

  // Emulate text-anchor by adjusting the x- y-coordinates.
  {
    h = final_attr.TextFont()->GetHeight();
    w = final_attr.TextFont()->GetWidth();
    if ( final_attr.text_anchor_x == AnchorX::Min ) x += w / 2;
    if ( final_attr.text_anchor_x == AnchorX::Mid ) x -= w * (utf8_len - 1.0) / 2;
    if ( final_attr.text_anchor_x == AnchorX::Max ) x -= w * (utf8_len - 0.5);
    if ( final_attr.text_anchor_y == AnchorY::Mid ) y -= h / 2;
    if ( final_attr.text_anchor_y == AnchorY::Max ) y -= h;
    y += final_attr.TextFont()->GetBaseline();
  }

  oss
    << indent << "<g text-anchor=\"middle\""
    << Attr()->SVG( true ) << '>' << '\n';

  auto cit = str.cbegin();
  while ( cit != str.cend() ) {
    auto oit = cit;
    if ( Text::UTF8_CharAdv( str, cit ) ) {
      std::string s;
      uint8_t b = *oit;
      switch ( b ) {
        case '<'  : s = "&lt;"; break;
        case '>'  : s = "&gt;"; break;
        case '&'  : s = "&amp;"; break;
        case '\'' : s = "&apos;"; break;
        case '"'  : s = "&quot;"; break;
        default : {
          if ( b < ' ' ) {
            s = ' ';
          } else
          if ( final_attr.text_math_digits && b >= '0' && b <= '9' ) {
            s.assign( MATH_SANS_DIGITS[ b - '0' ], 4 );
          } else
          {
            s.assign( oit, cit );
          }
        }
      }
      oss
        << indent << "  <text"
        << " x=" << U( +x ).SVG()
        << " y=" << U( -y ).SVG()
        << '>' << s << "</text>" << '\n';
      x += w;
    }
  }

  oss << indent << "</g>" << '\n';
}

////////////////////////////////////////////////////////////////////////////////

bool Text::UTF8_CharAdv(
  const std::string& s, std::string::const_iterator& it
)
{
  uint8_t b;
  uint32_t cp;

  auto do_cont = [&]( void ) {
    if ( it == s.cend() ) return false;
    b = *it;
    if ( (b & 0xC0) != 0x80 ) return false;
    ++it;
    cp = (cp << 6) | (b & 0x3F);
    return true;
  };

  if ( it == s.cend() ) return false;
  b = *(it++);

  if ( b < 0x80 ) {
    // 1-byte encoded code point.
    cp = b;
    return true;
  }

  if ( (b & 0xE0) == 0xC0 ) {
    // 2-byte encoded code point.
    cp = b & 0x1F;
    // 1 continuation byte and overlong check.
    return do_cont() && cp > 0x7F;
  }

  if ( (b & 0xF0) == 0xE0 ) {
    // 3-byte encoded code point.
    cp = b & 0x0F;
    // 2 continuation bytes and overlong and surrogate check.
    return do_cont() && do_cont() && cp > 0x7FF && (cp & 0xF800) != 0xD800;
  }

  if ( (b & 0xF8) == 0xF0 ) {
    // 4-byte encoded code point.
    cp = b & 0x07;
    // 3 continuation bytes and overlong and out-of-range check.
    return do_cont() && do_cont() && do_cont() && cp > 0xFFFF && cp < 0x110000;
  }

  // We do not have a valid UTF-8 start byte, skip over any additional
  // continuation bytes.
  while ( it != s.cend() ) {
    b = *it;
    if ( (b & 0xC0) != 0x80 ) break;
    ++it;
  }

  return false;
}

//------------------------------------------------------------------------------

size_t Text::UTF8_CharNum( const std::string& s )
{
  auto it = s.cbegin();
  size_t n = 0;
  while ( it != s.cend() ) {
    if ( Text::UTF8_CharAdv( s, it ) ) n++;
  }
  return n;
}

////////////////////////////////////////////////////////////////////////////////
