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

#include <svg_point.h>
#include <svg_boundary_box.h>
#include <svg_transform.h>
#include <svg_attributes.h>

namespace SVG {

class Object
{
  friend class Canvas;
  friend class Group;
  friend class Attributes;

public:

  Object( void ) {}
  virtual ~Object( void ) {}

  Group* ParentGroup( void );

  Attributes* Attr( void ) { return &attr; }

  void Move( U dx, U dy )
  {
    CheckTop( "SVG::Object::Move" );
    transform.translate_dx += dx;
    transform.translate_dy += dy;
  }
  void MoveTo(
    AnchorX anchor_x,
    AnchorY anchor_y,
    U x, U y
  );
  void MoveTo(
    AnchorX anchor_x,
    AnchorY anchor_y,
    Point p
  ) {
    MoveTo( anchor_x, anchor_y, p.x, p.y );
  }

  void Rotate(
    double theta,
    AnchorX anchor_x = AnchorX::Mid,
    AnchorY anchor_y = AnchorY::Mid
  ) {
    CheckTop( "SVG::Object::Rotate" );
    transform.rotate_theta          = theta - 360.0 * std::floor(theta / 360.0);
    transform.rotate_anchor_defined = true;
    transform.rotate_anchor_x       = anchor_x;
    transform.rotate_anchor_y       = anchor_y;
  }
  void Rotate(
    double theta, U x, U y
  ) {
    CheckTop( "SVG::Object::Rotate" );
    transform.rotate_theta          = theta - 360.0 * std::floor(theta / 360.0);
    transform.rotate_anchor_defined = false;
    transform.rotate_point.x        = x;
    transform.rotate_point.y        = y;
  }

  // Returns true if the object is empty, i.e. has no defined coordinates.
  virtual bool Empty( void ) { return false; }

  // Recursively remove all empty objects; return true if this object thus
  // became empty itself.
  virtual bool Prune( void ) { return false; }

  // Return boundary box in parent group. GetBB() errors out when used on empty
  // object as there are no defined coordinates.
  BoundaryBox GetBB( void );

  // Like GetBB(), but returns the boundary box in absolute canvas coordinates.
  BoundaryBox GetAbsBB( void );

protected:

  void CheckTop( std::string_view name );

  // Get boundary box without applying transforms.
  BoundaryBox GetNoTransBB( void );

  virtual void UpdateBB(
    BoundaryBox& boundary_box,
    bool first, std::vector< Transform >& transforms
  ) = 0;

  virtual void UpdateAbsBB(
    BoundaryBox& boundary_box,
    bool first, std::vector< Transform >& transforms,
    std::vector< Object* >& obj_path, size_t obj_idx
  );

  virtual void UpdateNoTransBB(
    BoundaryBox& boundary_box, std::vector< Transform >& transforms
  );

  virtual void GenSVG(
    std::ostringstream& oss,
    std::string& indent
  ) = 0;

  bool is_top = false;

  Canvas* canvas = nullptr;
  Group* parent_group = nullptr;

  Attributes attr = Attributes( this );

  Transform transform;

  bool transform_enabled = true;

  Point TransformPoint(
    const std::vector< Transform >& transforms, Point p
  );

  std::string TransSVG( void );

};

}
