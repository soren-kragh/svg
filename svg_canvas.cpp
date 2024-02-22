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
  top_group->Attr()->LineColor()->Set( ColorName::Black );
  top_group->Attr()->FillColor()->Clear();
  top_group->Attr()->TextFont()->SetFamily( "Courier New" );
  top_group->Attr()->TextFont()->SetSize( 12 );
  top_group->Attr()->TextFont()->SetBold( false );
  top_group->Attr()->SetTextAnchorX( AnchorX::Min );
  top_group->Attr()->SetTextAnchorY( AnchorY::Min );
  top_group->Attr()->SetTextOutlineWidth( 0 );
  top_group->Attr()->TextOutlineColor()->Clear();
  top_group->Attr()->TextColor()->Set( ColorName::Black );
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

std::string Canvas::GenSVG( U margin )
{
  std::ostringstream oss;
  std::string indent;
  BoundaryBox boundary_box = top_group->GetBB();

  margin_x = margin;
  margin_y = margin;
  canvas_w = boundary_box.max.x - boundary_box.min.x + 2*margin_x;
  canvas_h = boundary_box.max.y - boundary_box.min.y + 2*margin_y;

  oss << "<?xml version=\"1.0\" standalone=\"no\"?>" << "\n";
  oss
    << "<svg"
    << " version=\"1.1\""
    << " xmlns=\"http://www.w3.org/2000/svg\""
    << " width=" << canvas_w.SVG()
    << " height=" << canvas_h.SVG()
    << '>' << "\n";

  indent.resize( indent.size() + 2, ' ' );

  if ( !Background()->IsClear() ) {
    Rect* rect = new Rect( 0, 0, canvas_w, -canvas_h );
    rect->Attr()->FillColor()->Set( &background );
    rect->Attr()->LineColor()->Clear();
    rect->GenSVG( oss, indent );
  }
  top_group->Move(
    +margin_x - boundary_box.min.x,
    -margin_y - boundary_box.max.y
  );
  top_group->GenSVG( oss, indent );

  indent.resize( indent.size() - 2 );

  oss << "</svg>" << "\n";

  return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
