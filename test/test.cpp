///////////////////////////////////////////////////////////////////////////////

#include <svg_canvas.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

void grid( Group* g )
{
  int grid_n = 10;
  int grid_d = 50;
  g->Attr()->SetLineWidth( 0.5 )->SetLineDash( 3 );
  g->Attr()->LineColor()->Set( Black, 0.85 );
  for ( int x = -grid_n * grid_d; x <= grid_n * grid_d; x += grid_d ) {
    g->Add( new Line( x, -grid_n * grid_d, x, grid_n * grid_d ) );
    if ( x == 0 ) {
      g->Last()->Attr()->LineColor()->Set( Blue, 0.4 );
    } else
    if ( x / grid_d % 2 == 0 ) {
      g->Last()->Attr()->LineColor()->Set( Black, 0.75 );
    }
  }
  for ( int y = -grid_n * grid_d; y <= grid_n * grid_d; y += grid_d ) {
    g->Add( new Line( -grid_n * grid_d, y, grid_n * grid_d, y ) );
    if ( y == 0 ) {
      g->Last()->Attr()->LineColor()->Set( Blue, 0.4 );
    } else
    if ( y / grid_d % 2 == 0 ) {
      g->Last()->Attr()->LineColor()->Set( Black, 0.75 );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

void test01( Group* g )
{
  std::string str = "Hf0W1yH";
  Font font( "Courier New", 120 );
  font.SetBold();

  U w = font.GetWidth( str );
  U h = font.GetHeight();

  g->Attr()->TextFont()->Set( font );
  g->Attr()->FillColor()->Clear();
  g->Attr()->SetLineWidth( 5 )->LineColor()->Set( Black );
  g->Attr()->TextColor()->Set( Red );
  g->Attr()->SetTextOutlineWidth( 2 )->TextOutlineColor()->Set( Red, 0, 0.5 );
  g->Attr()->SetTextAnchorY( MinY );

  U x = 0;
  U y = 0;
  U m = 10;

  auto test = [&]( AnchorX anchor_x, AnchorY anchor_y, U dx, U dy )
  {
    g->Add( new Text( x + dx, y + dy, str ) );
    g->Last()->Attr()->SetTextAnchor( anchor_x, anchor_y );
    g->Add( new Rect( x, y, x + w, y + h ) );
    g->Add( new Circle( x + dx, y + dy, 5 ) );
    g->Last()->Attr()->SetLineWidth( 1 )->FillColor()->Set( Yellow );
  };

  test( MinX, MinY, 0  , 0   ); y += h + m;
  test( MidX, MinY, w/2, 0   ); y += h + m;
  test( MaxX, MinY, w  , 0   ); y -= 2 * (h + m); x += w + m;
  test( MinX, MidY, 0  , h/2 ); y += h + m;
  test( MidX, MidY, w/2, h/2 ); y += h + m;
  test( MaxX, MidY, w  , h/2 ); y -= 2 * (h + m); x += w + m;
  test( MinX, MaxY, 0  , h   ); y += h + m;
  test( MidX, MaxY, w/2, h   ); y += h + m;
  test( MaxX, MaxY, w  , h   ); y -= 2 * (h + m); x += w + m;
}

///////////////////////////////////////////////////////////////////////////////

void test02( Group* g )
{
  grid( g->AddNewGroup() );

  g->Attr()->FillColor()->Clear();
  g->Attr()->SetLineWidth( 2 );

  BoundaryBox bb;

  {
    g = g->AddNewGroup()->AddNewGroup();

    g->Add( new Rect( 50, 100, 250, 200 ) );
    g->Last()->Attr()->LineColor()->Set( Black, 0.7 );
    g->Add( new Rect( 50, 100, 250, 200 ) );
    g->Last()->Rotate( 45, MidX, MaxY );
    g->Last()->Move( 300, -200 );
    bb = g->Last()->GetBB();
    g->Add( new Rect( bb.min.x, bb.min.y, bb.max.x, bb.max.y, 50 ) );
    g->Last()->Attr()->SetLineWidth( 0.25 );

    g->Rotate( 40, MinX, MaxY );
    g->Move( -50, -200 );

    bb = g->GetBB();

    g = g->ParrentGroup();

    g->Add( new Rect( bb.min.x, bb.min.y, bb.max.x, bb.max.y ) );
    g->Last()->Attr()->LineColor()->Set( Yellow );

    g->MoveTo( MinX, MinY, 0, 0 );

    g = g->ParrentGroup();
  }

  {
    g = g->AddNewGroup()->AddNewGroup();

    g->Attr()->TextFont()->SetSize( 100 );
    g->Attr()->TextFont()->SetBold();
    g->Attr()->SetTextAnchorX( MaxX );
    g->Attr()->SetTextAnchorY( MinY );

    g->Add( new Text( 0, -300, "He|!X" ) );
    g->Last()->Attr()->TextColor()->Set( Black, 0.7 );
    bb = g->Last()->GetBB();
    g->Add( new Rect( bb.min.x, bb.min.y, bb.max.x, bb.max.y ) );

    g->Add( new Text( 0, -300, "He|!X" ) );
    g->Last()->Rotate( 20, MaxX, MaxY );

    bb = g->Last()->GetBB();
    g->Add( new Rect( bb.min.x, bb.min.y, bb.max.x, bb.max.y ) );
    g->Last()->Attr()->LineColor()->Set( Yellow );

    g->MoveTo( MaxX, MinY, -100, -200 );
    g->Rotate( -30, MaxX, MinY );

    g = g->ParrentGroup();

    bb = g->GetBB();
    g->Add( new Rect( bb.min.x, bb.min.y, bb.max.x, bb.max.y ) );
    g->Last()->Attr()->LineColor()->Set( Pink );

    g->MoveTo( MinX, MaxY, 100, -100 );

    g = g->ParrentGroup();
  }
}

///////////////////////////////////////////////////////////////////////////////

void test03( Group* g )
{
  int r = 20;
  g->Attr()->LineColor()->Clear();
  for ( int x = 0; x < r; x++ ) {
    for ( int y = 0; y < r; y++ ) {
      int d = 800 / r;
      g->Add( new Rect( x*d, y*d, x*d+d, y*d+d ) );
      g->Last()->Attr()->FillColor()->Set(
        Blue, x / (r - 1.0), y / (r - 1.0)
      );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

void test04( Group* g )
{
  grid( g->AddNewGroup() );

  g = g->AddNewGroup();

/*
  g->Add( new Circle( 0, 0, 400 ) );
  {
    Poly* poly = new Poly();
    int n = 3;
    int r = 400;
    double R = r / std::cos( M_PI / n );
    for ( int i = 0; i < n; i++ ) {
      double a = (i + 0.5) * 2 * M_PI / n;
      poly->Add( R * std::cos( a ), R * std::sin( a ) );
    }
    poly->Close();
    g->Add( poly );
  }
*/

  g->Add( new Circle( 400, -300, 600 ) );
  g->Last()->Rotate( 45, MinX, MaxY );

//  g->Add( new Rect( 400 - 600, -300 - 600, 400 + 600, -300 + 600 ) );
//  g->Last()->Rotate( 45, Start, End );

  g = g->ParrentGroup();

  g->Rotate( -30 );

  g = g->AddNewGroup();

  g->Add( new Poly( { 100, 100, 300, 200, 200, 400, 200, -200 } ) );
  dynamic_cast< Poly* >( g->Last() )->Add( -300, 100 );
  dynamic_cast< Poly* >( g->Last() )->Close();
  g->Last()->Attr()->FillColor()->Set( Yellow );
  g->Last()->Attr()->SetLineWidth( 8 );
  g->Last()->Rotate( -20, MinX, MidY );
  BoundaryBox bb = g->Last()->GetBB();
  g->Add( new Rect( bb.min.x, bb.min.y, bb.max.x, bb.max.y ) );
  g->Last()->Attr()->SetLineDash( 10 );

  g->Add( new Text( 0, -150, "100.10" ) );
  g->Last()->Attr()->SetTextAnchorX( MidX );
  g->Last()->Attr()->SetTextAnchorY( MidY );
  g->Last()->Attr()->TextFont()->SetBold();
  g->Last()->Attr()->TextFont()->SetSize( 16 );

  g->Add( new Circle( 400, -300, 600 ) );
  g->Add( new Rect( 400 - 300, -300 - 300, 400 + 300, -300 + 300 ) );
  g->Last()->Attr()->FillColor()->Set( Black, 0.9 );
  g->Last()->Attr()->SetLineDash( 10 );
  g->Last()->Rotate( 45, MinX, MaxY );

  g = g->ParrentGroup();

  g->Rotate( -30 );

}

///////////////////////////////////////////////////////////////////////////////

void test05( Group* g )
{
  grid( g->AddNewGroup() );

  Rect* rect;

  {
    g = g->AddNewGroup();

//    g->Add( new Rect( -200, -300, 100, 200 ) );
//    g->Last()->Rotate( 20, Start, Start );
//    g->Last()->Attr()->SetLineWidth( 3 )->LineColor()->Set( Green );

    rect = new Rect( -200, -300, 100, 200, 100 );
    g->Add( rect );
    g->Last()->Rotate( 20, MinX, MinY );
    BoundaryBox bb = g->Last()->GetBB();
    g->Add( new Rect( bb.min.x, bb.min.y, bb.max.x, bb.max.y, 50 ) );
    g = g->ParrentGroup();
  }
  g->Last()->Rotate( -20, MinX, MinY );
  BoundaryBox bb = g->Last()->GetBB();
  g->Add( new Rect( bb.min.x, bb.min.y, bb.max.x, bb.max.y ) );
  g->Last()->Attr()->LineColor()->Set( Blue );

// g->Last()->Rotate( 15, -100, 200 );
// g->Last()->Move( 100, -200 );

  g->Move( 5000, 1000000 );
}

///////////////////////////////////////////////////////////////////////////////

void test06( Group* g )
{
  grid( g->AddNewGroup() );

  auto test = [&]( int x, int y, int rx, int ry, int theta )
  {
    g = g->AddNewGroup();

    g->Attr()->TextFont()->SetSize( 16 );

    g->Add( new Ellipse( x, y, rx, ry ) );
    g->Last()->Attr()->SetLineWidth( 4 )->LineColor()->Set( Blue, 0.5 );
    g->Last()->Rotate( theta );

    int d = 15;
    BoundaryBox bb = g->Last()->GetBB();

    g->Add( new Line( bb.max.x + d, bb.min.y,  bb.min.x - d, bb.min.y ) );
    g->Last()->Attr()->SetLineWidth( 0.5 )->SetLineDash( 5 );
    g->Add( new Text( bb.max.x + d + 6, bb.min.y, "MinY" ) );
    g->Last()->Attr()->SetTextAnchorX( MinX );
    g->Last()->Attr()->SetTextAnchorY( MidY );

    g->Add( new Line( bb.max.x + d, bb.max.y,  bb.min.x - d, bb.max.y ) );
    g->Last()->Attr()->SetLineWidth( 0.5 )->SetLineDash( 5 );
    g->Add( new Text( bb.max.x + d + 6, bb.max.y, "MaxY" ) );
    g->Last()->Attr()->SetTextAnchorX( MinX );
    g->Last()->Attr()->SetTextAnchorY( MidY );

    g->Add( new Line( bb.min.x, bb.min.y - d,  bb.min.x, bb.max.y + d) );
    g->Last()->Attr()->SetLineWidth( 0.5 )->SetLineDash( 5 );
    g->Add( new Text( bb.min.x, bb.min.y - d, "MinX" ) );
    g->Last()->Attr()->SetTextAnchorX( MidX );
    g->Last()->Attr()->SetTextAnchorY( MaxY );

    g->Add( new Line( bb.max.x, bb.min.y - d,  bb.max.x, bb.max.y + d) );
    g->Last()->Attr()->SetLineWidth( 0.5 )->SetLineDash( 5 );
    g->Add( new Text( bb.max.x, bb.min.y - d, "MaxX" ) );
    g->Last()->Attr()->SetTextAnchorX( MidX );
    g->Last()->Attr()->SetTextAnchorY( MaxY );

    g = g->ParrentGroup();
  };

  test( +250, +250, 100, 150,   70 );
  test( -250, +250, 200,  50, -100 );
  test( -250, -250, 250,  20,  155 );
  test( +250, -250, 130, 200,  -15 );
}

///////////////////////////////////////////////////////////////////////////////

int main()
{
  Canvas* svg_canvas = new Canvas();

  test06( svg_canvas->TopGroup()->AddNewGroup() );

  svg_canvas->Background()->Set( Orange, 0.95, 0.0 );

  std::cout << svg_canvas->GenSVG( 25 );

  delete svg_canvas;

  return 0;
}
