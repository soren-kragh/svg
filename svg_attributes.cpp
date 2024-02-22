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
  line_cap_defined = false;
  line_cap = LineCap::Butt;
  line_join_defined = false;
  line_join = LineJoin::Sharp;
  text_anchor_x_defined = false;
  text_anchor_x = AnchorX::Min;
  text_anchor_y_defined = false;
  text_anchor_y = AnchorY::Min;
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

Attributes* Attributes::SetLineCap( LineCap cap )
{
  line_cap_defined = true;
  line_cap = cap;
  return this;
}

Attributes* Attributes::SetLineJoin( LineJoin join )
{
  line_join_defined = true;
  line_join = join;
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
  if ( !final_attr.line_cap_defined && line_cap_defined ) {
    final_attr.SetLineCap( line_cap );
  }
  if ( !final_attr.line_join_defined && line_join_defined ) {
    final_attr.SetLineJoin( line_join );
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
    if ( line_cap_defined ) {
      oss << " stroke-linecap=\"";
      switch ( line_cap ) {
        case LineCap::Butt   : oss << "butt\""; break;
        case LineCap::Round  : oss << "round\""; break;
        case LineCap::Square : oss << "square\""; break;
        default              : oss << "\"";
      }
    }
    if ( line_join_defined ) {
      oss << " stroke-linejoin=\"";
      switch ( line_join ) {
        case LineJoin::Sharp : oss << "miter\""; break;
        case LineJoin::Round : oss << "round\""; break;
        default              : oss << "\"";
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
