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
  top_group->Attr()->SetTextMathDigits( false );
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

std::string Canvas::GenSVG( U margin, const std::string& attr )
{
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

  indent.resize( indent.size() + 2, ' ' );

  if ( !Background()->IsClear() ) {
    Rect* rect = new Rect( boundary_box.min, boundary_box.max );
    rect->Attr()->FillColor()->Set( &background );
    rect->Attr()->LineColor()->Clear();
    rect->GenSVG( oss, indent );
  }
  top_group->Prune();
  top_group->GenSVG( oss, indent );

  indent.resize( indent.size() - 2 );

  oss << "</svg>" << "\n";

  return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
