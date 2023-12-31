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

#include <svg_attributes.h>
#include <svg_group.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Attributes::Attributes( Object* object )
{
  this->object = object;
  line_width_defined = false;
  line_width = 0;
  line_dash_defined = false;
  line_dash = 0;
  line_hole = 0;
  text_anchor_x_defined = false;
  text_anchor_x = MinX;
  text_anchor_y_defined = false;
  text_anchor_y = MinY;
  text_outline_width_defined = false;
  text_outline_width = 0;
}

///////////////////////////////////////////////////////////////////////////////

Attributes* Attributes::SetLineWidth( U width )
{
  line_width = width;
  line_width_defined = true;
  return this;
}

Attributes* Attributes::SetLineSolid()
{
  line_dash_defined = true;
  line_dash = 0;
  line_hole = 0;
  return this;
}

Attributes* Attributes::SetLineDash( U dash )
{
  line_dash_defined = true;
  line_dash = dash;
  line_hole = dash;
  return this;
}

Attributes* Attributes::SetLineDash( U dash, U hole )
{
  line_dash_defined = true;
  line_dash = dash;
  line_hole = hole;
  return this;
}

///////////////////////////////////////////////////////////////////////////////

Attributes* Attributes::SetTextAnchor( AnchorX anchor_x, AnchorY anchor_y )
{
  SetTextAnchorX( anchor_x );
  SetTextAnchorY( anchor_y );
  return this;
}

Attributes* Attributes::SetTextAnchorX( AnchorX anchor )
{
  text_anchor_x = anchor;
  text_anchor_x_defined = true;
  return this;
}

Attributes* Attributes::SetTextAnchorY( AnchorY anchor )
{
  text_anchor_y = anchor;
  text_anchor_y_defined = true;
  return this;
}

Attributes* Attributes::SetTextOutlineWidth( U width )
{
  text_outline_width = width;
  text_outline_width_defined = true;
  return this;
}

///////////////////////////////////////////////////////////////////////////////

void Attributes::Collect( Attributes& final_attr )
{
  if ( !final_attr.line_width_defined && line_width_defined ) {
    final_attr.SetLineWidth( line_width );
  }
  if ( !final_attr.line_dash_defined && line_dash_defined ) {
    final_attr.SetLineDash( line_dash, line_hole );
  }
  if ( !final_attr.line_color.IsDefined() && line_color.IsDefined() ) {
    final_attr.line_color.Set( &line_color );
  }

  if ( !final_attr.fill_color.IsDefined() && fill_color.IsDefined() ) {
    final_attr.fill_color.Set( &fill_color );
  }

  if ( !final_attr.text_font.family_defined && text_font.family_defined ) {
    final_attr.text_font.SetFamily( text_font.family );
  }
  if ( !final_attr.text_font.size_defined && text_font.size_defined ) {
    final_attr.text_font.SetSize( text_font.size );
  }
  if ( !final_attr.text_font.weight_defined && text_font.weight_defined ) {
    final_attr.text_font.SetBold( text_font.weight_bold );
  }
  if ( !final_attr.text_anchor_x_defined && text_anchor_x_defined ) {
    final_attr.SetTextAnchorX( text_anchor_x );
  }
  if ( !final_attr.text_anchor_y_defined && text_anchor_y_defined ) {
    final_attr.SetTextAnchorY( text_anchor_y );
  }
  if ( !final_attr.text_outline_width_defined && text_outline_width_defined ) {
    final_attr.SetTextOutlineWidth( text_outline_width );
  }
  if ( !final_attr.text_outline_color.IsDefined() && text_outline_color.IsDefined() ) {
    final_attr.text_outline_color.Set( &text_outline_color );
  }
  if ( !final_attr.text_color.IsDefined() && text_color.IsDefined() ) {
    final_attr.text_color.Set( &text_color );
  }

  if ( object->parrent_group != nullptr ) {
    object->parrent_group->Attr()->Collect( final_attr );
  }
}

///////////////////////////////////////////////////////////////////////////////

std::string Attributes::SVG( bool text )
{
  std::ostringstream oss;
  Attributes final_attr = Attributes( nullptr );

  Collect( final_attr );

  if ( text ) {
    // SVG does not have dedicated attributes for some text properties, so we
    // have to provide them for each text object.
    bool has_outline =
      final_attr.text_outline_width_defined
      && final_attr.text_outline_width > 0
      && final_attr.text_outline_color.IsDefined();
    if ( has_outline ) {
      if ( final_attr.text_outline_width_defined ) {
        oss << " stroke-width=" << final_attr.text_outline_width.SVG();
      }
      oss << " stroke-dasharray=\"none\"";
      oss << " stroke=" << final_attr.text_outline_color.SVG();
    } else {
      oss << " stroke=\"none\"";
    }
    if ( final_attr.text_color.IsDefined() ) {
      oss << " fill=" << final_attr.text_color.SVG();
    }
  } else {
    if ( line_width_defined ) {
      oss << " stroke-width=" << line_width.SVG();
    }
    if ( line_dash_defined ) {
      if ( line_hole == 0 ) {
        oss << " stroke-dasharray=\"none\"";
      } else {
        oss
          << " stroke-dasharray=\""
          << line_dash.SVG( false ) << ' ' << line_hole.SVG( false ) << '"';
      }
    }
    if ( line_color.IsDefined() ) {
      oss << " stroke=" << line_color.SVG();
    }
    if ( fill_color.IsDefined() ) {
      oss << " fill=" << fill_color.SVG();
    }
  }

  oss << text_font.SVG() << object->TransSVG();

  return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
