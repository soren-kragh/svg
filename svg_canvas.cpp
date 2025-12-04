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

#include <svg_canvas.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Canvas::Canvas( void )
{
  background.Clear();
  top_group = new Group();
  top_group->Attr()->SetLineWidth( 1 );
  top_group->Attr()->SetLineSolid();
  top_group->Attr()->SetLineCap( LineCap::Butt );
  top_group->Attr()->SetLineJoin( LineJoin::Sharp );
  top_group->Attr()->LineColor()->Set( ColorName::black );
  top_group->Attr()->FillColor()->Clear();
  top_group->Attr()->TextFont()->SetFamily( "monospace" );
  top_group->Attr()->TextFont()->SetSize( 12 );
  top_group->Attr()->TextFont()->SetBold( false );
  top_group->Attr()->SetTextAnchorX( AnchorX::Min );
  top_group->Attr()->SetTextAnchorY( AnchorY::Min );
  top_group->Attr()->SetTextOutlineWidth( 0 );
  top_group->Attr()->SetTextZeroToO( false );
  top_group->Attr()->TextOutlineColor()->Set( ColorName::black );
  top_group->Attr()->TextOutlineColor()->SetOpacity( 1.0 );
  top_group->Attr()->TextColor()->Set( ColorName::black );
  top_group->Attr()->TextColor()->SetOpacity( 1.0 );
}

Canvas::~Canvas( void )
{
  delete top_group;
}

Group* Canvas::TopGroup( void )
{
  return top_group;
}

///////////////////////////////////////////////////////////////////////////////

Color* Canvas::Background( void )
{
  return &background;
}

///////////////////////////////////////////////////////////////////////////////

void Canvas::GenDefObject(
  std::ostringstream& oss, std::string& indent, Object* obj
)
{
  auto gen_stop =
    [&]( std::ostringstream& my_oss, Color::col_t& col )
    {
      my_oss
        << indent
        << "<stop"
        << col.StopOffsetSVG()
        << "/>\n";
      return;
    };

  auto gen_def = [&]( Color* color )
    {
      if ( color->IsGradient() ) {
        if ( grad_id == 0 ) {
          oss << indent << "<defs>" << "\n";
          if ( settings.indent ) indent.resize( indent.size() + 2, ' ' );
        }
        U x1{ color->grad.x1 };
        U x2{ color->grad.x2 };
        U y1{ 1.0 - color->grad.y1 };
        U y2{ 1.0 - color->grad.y2 };
        std::string extra;
        if ( color->grad.group ) {
          auto bb = obj->GetNoTransBB();
          x1 = +bb.min.x + (bb.max.x - bb.min.x) * color->grad.x1;
          x2 = +bb.min.x + (bb.max.x - bb.min.x) * color->grad.x2;
          y1 = -bb.min.y - (bb.max.y - bb.min.y) * color->grad.y1;
          y2 = -bb.min.y - (bb.max.y - bb.min.y) * color->grad.y2;
          if ( std::abs( x2 - x1 ) < 1e-2 && std::abs( y2 - y1 ) < 1e-2 ) {
            x1 = x2 = (bb.min.x + bb.max.x) * 0.5;
            y1 = y2 = (bb.min.y + bb.max.y) * 0.5;
            if ( color->grad.y1 == color->grad.y2 ) {
              x1 -= 1;
              x2 += 1;
              if ( color->grad.x2 < color->grad.x1 ) std::swap( x1, x2 );
            } else {
              y1 += 1;
              y2 -= 1;
              if ( color->grad.y2 < color->grad.y1 ) std::swap( y1, y2 );
            }
          }
          extra = " gradientUnits=\"userSpaceOnUse\"";
        }
        std::ostringstream my_oss;
        my_oss
          << " x1=" << x1.SVG()
          << " y1=" << y1.SVG()
          << " x2=" << x2.SVG()
          << " y2=" << y2.SVG()
          << extra
          << ">\n";
        if ( settings.indent ) indent.resize( indent.size() + 2, ' ' );
        for ( auto& col : color->col_list ) {
          gen_stop( my_oss, col );
        }
        if ( settings.indent ) indent.resize( indent.size() - 2 );
        grad_id++;
        auto [ it, inserted ] = grad_map.insert( { my_oss.str(), grad_id } );
        if ( inserted ) {
          oss
            << indent << "<linearGradient id=\"grad" << grad_id << '"'
            << it->first
            << indent << "</linearGradient>" << '\n';
          color->grad.id = grad_id;
        } else {
          grad_id--;
          color->grad.id = it->second;
        }
      }
      return;
    };

  gen_def( obj->Attr()->LineColor() );
  gen_def( obj->Attr()->FillColor() );
  gen_def( obj->Attr()->TextOutlineColor() );
  gen_def( obj->Attr()->TextColor() );
}

void Canvas::GenDefsGroup(
  std::ostringstream& oss, std::string& indent, Group* g
)
{
  GenDefObject( oss, indent, g );
  for ( auto* object : g->objects ) {
    if ( auto* group = dynamic_cast< Group* >( object ) ) {
      GenDefsGroup( oss, indent, group );
    } else {
      GenDefObject( oss, indent, object );
    }
  }
}

void Canvas::GenDefs( std::ostringstream& oss, std::string& indent )
{
  grad_id = 0;
  GenDefsGroup( oss, indent, top_group );
  if ( grad_id > 0 ) {
    if ( settings.indent ) indent.resize( indent.size() - 2 );
    oss << indent << "</defs>" << "\n";
  }
}

///////////////////////////////////////////////////////////////////////////////

std::string Canvas::GenSVG( U margin, std::string_view attr )
{
  top_group->Prune();

  std::ostringstream oss;
  std::string indent;
  BoundaryBox boundary_box = top_group->GetBB();

  boundary_box.min.x -= margin;
  boundary_box.min.y -= margin;
  boundary_box.max.x += margin;
  boundary_box.max.y += margin;
  U canvas_w = boundary_box.max.x - boundary_box.min.x;
  U canvas_h = boundary_box.max.y - boundary_box.min.y;
  U svg_min_x = +boundary_box.min.x;
  U svg_min_y = -boundary_box.max.y;

  oss
    << "<svg"
    << " xmlns=\"http://www.w3.org/2000/svg\""
    << " viewBox="
    << '"' << svg_min_x.SVG( false )
    << ' ' << svg_min_y.SVG( false )
    << ' ' << canvas_w.SVG( false )
    << ' ' << canvas_h.SVG( false ) << '"'
    << " width=" << canvas_w.SVG()
    << " height=" << canvas_h.SVG();
  if ( !attr.empty() ) {
    oss << ' ' << attr;
  }
  oss << '>' << "\n";

  if ( settings.indent ) indent.resize( indent.size() + 2, ' ' );

  GenDefs( oss, indent );

  if ( !Background()->IsClear() ) {
    Rect* rect = new Rect( boundary_box.min, boundary_box.max );
    rect->Attr()->FillColor()->Set( &background );
    rect->Attr()->LineColor()->Clear();
    rect->GenSVG( oss, indent );
  }
  top_group->GenSVG( oss, indent );

  if ( settings.indent ) indent.resize( indent.size() - 2 );

  oss << "</svg>" << "\n";

  return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
