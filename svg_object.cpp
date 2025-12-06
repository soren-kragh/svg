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

#include <svg_object.h>
#include <svg_canvas.h>

using namespace SVG;

////////////////////////////////////////////////////////////////////////////////

void Object::CheckTop( std::string_view name )
{
  if ( is_top ) {
    SVG_FATAL( name << " not allowed on top group" );
  }
}

////////////////////////////////////////////////////////////////////////////////

Group* Object::ParentGroup( void )
{
  if ( parent_group == nullptr ) {
    SVG_FATAL( "SVG::Object::ParentGroup: object has no parent" );
  }
  return parent_group;
}

////////////////////////////////////////////////////////////////////////////////

Point Object::TransformPoint(
  const std::vector< Transform >& transforms, Point p
)
{
  if ( transform_enabled ) {
    for ( auto it = transforms.rbegin(); it != transforms.rend(); ++it ) {
      Point np = Point( it->translate_dx, it->translate_dy );
      double radians = it->rotate_theta * (M_PI / 180.0);
      double a = std::cos( radians );
      double b = std::sin( radians );
      Point rp = it->rotate_point;
      np.x += rp.x + (p.x - rp.x) * a - (p.y - rp.y) * b;
      np.y += rp.y + (p.x - rp.x) * b + (p.y - rp.y) * a;
      p = np;
    }
  }
  return p;
}

////////////////////////////////////////////////////////////////////////////////

BoundaryBox Object::GetBB( void )
{
  BoundaryBox bb;
  std::vector< Transform > transforms;
  UpdateBB( bb, true, transforms );
  if ( !bb.Defined() ) {
    SVG_FATAL( "SVG::Object::GetBB: empty group" );
  }
  return bb;
}

BoundaryBox Object::GetNoTransBB( void )
{
  std::vector< Transform > transforms;
  BoundaryBox bb;
  UpdateNoTransBB( bb, transforms );
  if ( !bb.Defined() ) {
    SVG_FATAL( "SVG::Object::GetNoTransBB: empty group" );
  }
  return bb;
}

BoundaryBox Object::GetAbsBB( void )
{
  std::vector< Object* > obj_path;
  auto obj = this;
  while ( obj->parent_group ) {
    obj_path.push_back( obj );
    obj = obj->parent_group;
  }
  BoundaryBox bb;
  std::vector< Transform > transforms;
  if ( obj_path.empty() ) {
    SVG_FATAL( "SVG::Object::GetAbsBB: detached object" );
  } else {
    if ( Group* g = dynamic_cast< Group* >( obj ) ) {
      g->UpdateAbsBB( bb, true, transforms, obj_path, obj_path.size() );
    }
  }
  if ( !bb.Defined() ) {
    SVG_FATAL( "SVG::Object::GetAbsBB: empty group" );
  }
  return bb;
}

//------------------------------------------------------------------------------

void Object::UpdateAbsBB(
  BoundaryBox& boundary_box,
  bool first, std::vector< Transform >& transforms,
  [[maybe_unused]] std::vector< Object* >& obj_path,
  [[maybe_unused]] size_t obj_idx
)
{
  UpdateBB( boundary_box, first, transforms );
}

void Object::UpdateNoTransBB(
  BoundaryBox& boundary_box, std::vector< Transform >& transforms
)
{
  transform_enabled = false;
  UpdateBB( boundary_box, false, transforms );
  transform_enabled = true;
}

////////////////////////////////////////////////////////////////////////////////

void Object::MoveTo(
  AnchorX anchor_x,
  AnchorY anchor_y,
  U x, U y
)
{
  CheckTop( "SVG::Object::MoveTo" );
  BoundaryBox bb = GetBB();
  Point p;
  switch ( anchor_x ) {
    case AnchorX::Min : p.x = bb.min.x; break;
    case AnchorX::Max : p.x = bb.max.x; break;
    default   : p.x = (bb.min.x + bb.max.x) / 2;
  }
  switch ( anchor_y ) {
    case AnchorY::Min : p.y = bb.min.y; break;
    case AnchorY::Max : p.y = bb.max.y; break;
    default   : p.y = (bb.min.y + bb.max.y) / 2;
  }
  transform.translate_dx += x - p.x;
  transform.translate_dy += y - p.y;
}

////////////////////////////////////////////////////////////////////////////////

std::string Object::TransSVG( void )
{
  std::ostringstream oss;

  if (
    transform.translate_dx != 0 || transform.translate_dy != 0 ||
    transform.rotate_theta != 0
  ) {
    std::string s = "";
    oss << " transform=\"";
    if ( transform.translate_dx != 0 || transform.translate_dy != 0 ) {
      oss
        << s
        << "translate("
        << U( +transform.translate_dx ).SVG( false ) << ' '
        << U( -transform.translate_dy ).SVG( false )
        << ')';
      s = " ";
    }
    if ( transform.rotate_theta != 0 ) {
      // transform.rotate_point is valid here since Canvas::GenSVG() calls
      // GetBB() on the top group as the first thing.
      oss
        << s
        << "rotate("
        << U( 360.0 - transform.rotate_theta).SVG( false ) << ' '
        << U( +transform.rotate_point.x ).SVG( false ) << ' '
        << U( -transform.rotate_point.y ).SVG( false )
        << ')';
      s = " ";
    }
    oss << '"';
  }

  return oss.str();
}

////////////////////////////////////////////////////////////////////////////////
