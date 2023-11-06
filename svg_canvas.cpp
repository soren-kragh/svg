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

#include <svg_canvas.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Canvas::Canvas( void )
{
  background.Clear();
  top_group = new Group();
  top_group->Attr()->SetLineWidth( 1 );
  top_group->Attr()->SetLineSolid();
  top_group->Attr()->LineColor()->Set( Black );
  top_group->Attr()->FillColor()->Clear();
  top_group->Attr()->TextFont()->SetFamily( "Courier New" );
  top_group->Attr()->TextFont()->SetSize( 12 );
  top_group->Attr()->TextFont()->SetBold( false );
  top_group->Attr()->SetTextAnchorX( MinX );
  top_group->Attr()->SetTextAnchorY( MinY );
  top_group->Attr()->SetTextOutlineWidth( 0 );
  top_group->Attr()->TextOutlineColor()->Clear();
  top_group->Attr()->TextColor()->Set( Black );
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
    << " stroke-linecap=\"round\""
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
