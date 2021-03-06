#include <iostream>

#include "sprite_factory.h"
#include "rectangle.h"
#include "screen.h"
#include "current.h"

namespace sdl_platformer
{
   Rectangle::Rectangle(int pos_x, int pos_y,
         int width, int height, Color color)
      : GameObject(pos_x, pos_y, color)
   {
      m_rectangle.x = pos_x;
      m_rectangle.y = pos_y;
      m_rectangle.w = width;
      m_rectangle.h = height;

      m_source.x = 0;
   }

   Rectangle::Rectangle(int pos_x, int pos_y, int width, int height,
         SDL_Rect sprite)
      : GameObject( pos_x, pos_y, Color( 200, 200, 200, 255) )
   {
      m_source.x = sprite.x;
      m_source.y = sprite.y;
      m_source.w = sprite.w;
      m_source.h = sprite.h;

      m_rectangle.x = pos_x;
      m_rectangle.y = pos_y;
      m_rectangle.w = width;
      m_rectangle.h = height;
   }

   Rectangle::~Rectangle()
   {
   }

   void
   Rectangle::set_width(int new_width)
   {
      m_rectangle.w = new_width;
   }

   void
   Rectangle::set_height(int new_height)
   {
      m_rectangle.h = new_height;
   }

   int Rectangle::get_width() const { return m_rectangle.w; }

   int Rectangle::get_height() const { return m_rectangle.h; }

   void Rectangle::set_x(int new_x) { m_rectangle.x = new_x; }

   void Rectangle::set_y(int new_y) { m_rectangle.y = new_y; }

   int Rectangle::get_x() const { return m_rectangle.x; }

   int Rectangle::get_y() const { return m_rectangle.y; }

   void
   Rectangle::draw() const
   {
      Screen * current = Screen::current();
      if( current != NULL )
      {
         if( m_source.x == 0 )
         {
            SDL_SetRenderDrawColor( current->get_renderer(),
                  m_color.get_red(),
                  m_color.get_green(),
                  m_color.get_blue(),
                  m_color.get_alpha() );
            SDL_RenderFillRect( current->get_renderer(), &m_rectangle);
         }
         else
         {
            if (SDL_RenderCopy( current->get_renderer(),
                  SpriteFactory::current()->get_texture(), &m_source, &m_rectangle) != 0)
            {
               std::cout << SDL_GetError();
            }
         }
      }
      else
      {
         std::cout << "No current screen found.\n";
      }
   }

   void
   Rectangle::move( Vector & vec, float elapsed_time)
   {
      m_rectangle.x = vec.m_x * elapsed_time;
      m_rectangle.y = vec.m_y * elapsed_time;
   }

   int Rectangle::get_x_high() const { return m_rectangle.x + m_rectangle.w; }
   int Rectangle::get_y_high() const { return m_rectangle.y; }


   int Rectangle::get_x_middle() const { return m_rectangle.x + (m_rectangle.w / 2); }
   int Rectangle::get_y_middle() const { return m_rectangle.y + (m_rectangle.h / 2); }

   int Rectangle::get_x_low() const { return m_rectangle.x; }
   int Rectangle::get_y_low() const { return m_rectangle.y + m_rectangle.h; }

   int Rectangle::get_half_x_len() const { return get_x_middle() - m_rectangle.x; }
   int Rectangle::get_half_y_len() const { return get_y_middle() - m_rectangle.y; }

   SDL_Rect
   Rectangle::get_rect() const
   {
      return m_rectangle;
   }

   void
   Rectangle::move(float dx, float dy)
   {
      m_rectangle.x += dx;
      m_rectangle.y += dy;
   }
}// sdl_platformer
