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

#include <svg_group.h>

using namespace SVG;

///////////////////////////////////////////////////////////////////////////////

Group::Group( void )
{
  last = NULL;
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
  if ( object->parrent_group != NULL ) {
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
    delete obj;
  }
}

void Group::DeleteBack( void )
{
  if ( objects.size() > 0 ) {
    Object* obj = objects.front();
    objects.pop_front();
    delete obj;
  }
}

void Group::LastToBack( void )
{
  if ( last == NULL ) {
    SVG_FATAL( "SVG::Group::LastToBack: operation on NULL object" );
  }
  objects.push_front( objects.back() );
  objects.pop_back();
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
    if ( bb.defined ) {
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

  indent.resize( indent.size() + 2, ' ' );

  for ( auto object : objects ) {
    object->GenSVG( oss, indent );
  }

  indent.resize( indent.size() - 2 );

  oss << indent << "</g>" << "\n";
}

///////////////////////////////////////////////////////////////////////////////
