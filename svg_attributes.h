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

#pragma once

#include <svg_u.h>
#include <svg_color.h>
#include <svg_font.h>

namespace SVG {

class Object;

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

  Attributes* SetLineWidth( U width );
  Attributes* SetLineSolid();
  Attributes* SetLineDash( U dash );
  Attributes* SetLineDash( U dash, U hole );
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

private:

  // Collect the final attributes used for the object. It will trace upwards in
  // the group hierarchy to get the various attributes as needed. Some
  // attributes may fail to be collected, which can happen if Attr() is used on
  // detached objects or objects part of detached group hierarchies.
  void Collect( Attributes& final_attr );

  std::string SVG( bool text = false );

  Object* object;

  bool  line_width_defined;
  U     line_width;
  bool  line_dash_defined;
  U     line_dash;
  U     line_hole;
  Color line_color;

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

};

}
