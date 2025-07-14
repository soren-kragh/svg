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

#include <vector>

#include <svg_u.h>
#include <svg_color.h>
#include <svg_font.h>

namespace SVG {

class Attributes
{
  friend class Line;
  friend class Rect;
  friend class Text;
  friend class Poly;
  friend class Circle;
  friend class Ellipse;
  friend class Group;

public:

  Attributes( Object* object );
  Attributes() : Attributes( nullptr ) {}

  // opacity/transparency is a value in the range [0.0; 1.0]; default is
  // 1.0/0.0. Note that opacity/transparency may not be supported by all
  // viewers.
  Attributes* SetOpacity( float opacity );
  Attributes* SetTransparency( float transparency )
  {
    return SetOpacity( 1.0 - transparency );
  }

  Attributes* SetLineWidth( U width );
  Attributes* SetLineSolid();
  Attributes* SetLineDash( U dash );
  Attributes* SetLineDash( U dash, U hole );
  Attributes* SetLineCap( LineCap cap );
  Attributes* SetLineJoin( LineJoin join );
  Color* LineColor( void ) { return &line_color; }

  Color* FillColor( void ) { return &fill_color; }

  Font* TextFont( void ) { return &text_font; }
  Attributes* SetTextAnchor( AnchorX anchor_x, AnchorY anchor_y );
  Attributes* SetTextAnchorX( AnchorX anchor );
  Attributes* SetTextAnchorY( AnchorY anchor );

  // Text outline not supported by all viewers.
  Attributes* SetTextOutlineWidth( U width );
  Color* TextOutlineColor( void ) { return &text_outline_color; }
  Color* TextColor( void ) { return &text_color; }

  // Causes the digit 0 to to be translated to an O, which may look better
  // as it avoids a crossed zero.
  Attributes* SetTextZeroToO( bool zero_to_o = true );

  // Collect the final attributes used for the object. It will trace upwards in
  // the group hierarchy to get the various attributes as needed. Some
  // attributes may fail to be collected, which can happen if Attr() is used on
  // detached objects or objects part of detached group hierarchies.
  void Collect( Attributes& final_attr );

  // Add SVG custom attributes. The given attr must include everything,
  // e.g. 'id="myId"'.
  void AddCustom( const std::string& attr ) {
    custom.push_back( attr );
  }

private:

  std::string SVG( bool text = false );

  Object* object;

  bool  opacity_defined;
  float opacity;

  bool     line_width_defined;
  U        line_width;
  bool     line_dash_defined;
  U        line_dash;
  U        line_hole;
  bool     line_cap_defined;
  LineCap  line_cap;
  bool     line_join_defined;
  LineJoin line_join;
  Color    line_color;

  Color fill_color;

  Font    text_font;
  bool    text_anchor_x_defined;
  AnchorX text_anchor_x;
  bool    text_anchor_y_defined;
  AnchorY text_anchor_y;
  bool    text_outline_width_defined;
  U       text_outline_width;
  Color   text_outline_color;
  Color   text_color;
  bool    text_zero_to_o_defined;
  bool    text_zero_to_o;

  std::vector< std::string > custom;
};

}
