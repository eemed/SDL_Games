#include <iostream>
#include <fstream>

#include "render_context.h"
#include "json.hpp"

using json = nlohmann::json;

namespace sdl_platformer
{
   RenderContext::RenderContext(std::string filename)
   {
      if( !load_from_json(filename) )
      {
         std::cout << "Failed to parse json file\n";
      }
   }

   RenderContext::~RenderContext()
   {
   }

   void
   RenderContext::update(std::vector< Rectangle > n_sq,
         std::vector< Circle > n_circles )
   {
      m_squares = n_sq;
      m_circles = n_circles;
   }

   void
   RenderContext::update_circles(std::vector< Circle > n_circles)
   {
      m_circles = n_circles;
   }

   void
   RenderContext::update_squares(std::vector< Rectangle > n_sq)
   {
      m_squares = n_sq;
   }

   void
   RenderContext::draw() const
   {
      for( const auto & elem : m_squares)
      {
         elem.draw();
      }
      for( const auto & elem : m_circles)
      {
         elem.draw();
      }
   }

   bool
   RenderContext::load_from_json(std::string filename)
   {
      std::ifstream file_stream(filename);
      json parsed;
      file_stream >> parsed;
      for( auto & elem : parsed["squares"] )
      {
         m_squares.push_back(
              Rectangle( elem["x"], elem["y"],
                         elem["w"], elem["h"],
                         Color(200, 200, 200, 255) ) );
      }
      for( auto & elem : parsed["circles"] )
      {
         m_circles.push_back(
               Circle( elem["x"], elem["y"],
                       elem["r"], Color( 200, 200, 200, 255) ) );
      }
      return true;
   }

   void
   move(const float & dx, const float & dy)
   {
      if( dx == 0 && dy == 0 )
      {
         return;
      }
   }
}// sdl_platformer