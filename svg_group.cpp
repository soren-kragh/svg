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

#include <svg_group.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Group::Group( void )
{
  last = nullptr;
}

///////////////////////////////////////////////////////////////////////////////

Group::~Group( void )
{
  for ( auto object : objects ) {
    delete object;
  }
}

///////////////////////////////////////////////////////////////////////////////

Object* Group::Add( Object* object )
{
  if ( object->parrent_group != nullptr ) {
    SVG_FATAL( "SVG::Group::Add: object cannot be added to a group more than once" );
  }
  object->parrent_group = this;
  objects.push_back( object );
  last = object;
  return object;
}

void Group::DeleteFront( void )
{
  if ( objects.size() > 0 ) {
    Object* obj = objects.back();
    objects.pop_back();
    if ( last == obj ) last = nullptr;
    delete obj;
  }
}

void Group::DeleteBack( void )
{
  if ( objects.size() > 0 ) {
    Object* obj = objects.front();
    objects.pop_front();
    if ( last == obj ) last = nullptr;
    delete obj;
  }
}

void Group::FrontToBack( void )
{
  if ( objects.size() > 0 ) {
    objects.push_front( objects.back() );
    objects.pop_back();
  }
}

Group* Group::AddNewGroup( void )
{
  Group* g = new Group();
  Add( g );
  return g;
}

bool Group::Empty( void )
{
  for ( auto object : objects ) {
    if ( !object->Empty() ) return false;
  }
  return true;
}

bool Group::Prune( void )
{
  for ( auto it = objects.begin(); it != objects.end(); ) {
    if ( (*it)->Prune() ) {
      if ( last == *it ) last = nullptr;
      delete *it;
      it = objects.erase( it );
    } else {
      ++it;
    }
  }
  return objects.empty();
}

///////////////////////////////////////////////////////////////////////////////

void Group::UpdateBB(
  BoundaryBox& boundary_box,
  bool first, std::vector< Transform >& transforms
)
{
  BoundaryBox bb;
  if ( first ) {
    for ( auto object : objects ) {
      object->UpdateBB( bb, true, transforms );
    }
    if ( transform.rotate_anchor_defined ) {
      transform.SetRotatePoint( bb );
    }
  }
  if ( first && transform.rotate_theta == 0 ) {
    if ( bb.Defined() ) {
      boundary_box.Update(
        bb.min.x + transform.translate_dx,
        bb.min.y + transform.translate_dy
      );
      boundary_box.Update(
        bb.max.x + transform.translate_dx,
        bb.max.y + transform.translate_dy
      );
    }
  } else {
    transforms.push_back( transform );
    for ( auto object : objects ) {
      object->UpdateBB( boundary_box, false, transforms );
    }
    transforms.pop_back();
  }
}

///////////////////////////////////////////////////////////////////////////////

void Group::GenSVG(
  std::ostringstream& oss,
  std::string& indent
)
{
  oss << indent << "<g" << Attr()->SVG() << ">" << "\n";

  if ( settings.indent ) indent.resize( indent.size() + 2, ' ' );

  for ( auto object : objects ) {
    object->GenSVG( oss, indent );
  }

  if ( settings.indent ) indent.resize( indent.size() - 2 );

  oss << indent << "</g>" << "\n";
}

///////////////////////////////////////////////////////////////////////////////
