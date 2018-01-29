#include <iostream>

#include "input_handler.h"
#include "game.h"
#include "menu.h"
#include "world.h"

namespace sdl_platformer
{
   //InputHandler * InputHandler::_current = NULL;

   InputHandler::InputHandler()
      : m_keyboard( SDL_GetKeyboardState(NULL) )
   {
      activate();
   }

   InputHandler::~InputHandler()
   {
      deactivate();
   }

   void
   InputHandler::update_events()
   {
      SDL_PumpEvents();
   }

   void
   InputHandler::process_menu_events()
   {

      SDL_Event event;
      while( SDL_PollEvent( &event ) )
      {
         if( event.type == SDL_QUIT )
         {
            Game::current()->terminate();
            break;
         }
         else if( event.type == SDL_KEYDOWN )
         {
            switch( event.key.keysym.sym )
            {
               case SDLK_q:
                  Game::current()->terminate();
                  break;
               case SDLK_UP:
                  Menu::current()->move_up();
                  break;
               case SDLK_DOWN:
                  Menu::current()->move_down();
                  break;
               case SDLK_SPACE:
                  Menu::current()->select();
                  break;
               default:
                  break;
            }
         }
      }
   }

   void
   InputHandler::process_player_events(const float & elapsed_time)
   {
      if( m_keyboard[SDL_SCANCODE_RIGHT] and m_keyboard[SDL_SCANCODE_A])
         World::current()->get_player().speed_right(elapsed_time);
      else if( m_keyboard[SDL_SCANCODE_RIGHT] )
         World::current()->get_player().move_right(elapsed_time);
      if( m_keyboard[SDL_SCANCODE_LEFT] and m_keyboard[SDL_SCANCODE_A])
         World::current()->get_player().speed_left(elapsed_time);
      else if( m_keyboard[SDL_SCANCODE_LEFT] )
         World::current()->get_player().move_left(elapsed_time);
      if( m_keyboard[SDL_SCANCODE_Q] )
         Game::current()->terminate();

      SDL_Event event;
      while( SDL_PollEvent( &event ) )
      {
         if( event.type == SDL_QUIT )
         {
            Game::current()->terminate();
            break;
         }
         else if( event.type == SDL_KEYDOWN )
         {
            switch( event.key.keysym.sym )
            {
               case SDLK_SPACE:
                  World::current()->get_player().jump();
                  break;
               default:
                  break;
            }
         }
      }
   }

   void
   InputHandler::process_events(const float & elapsed_time)
   {
      update_events();
      if( Menu::current() != NULL )
      {
         process_menu_events();
      }
      else if( World::current() != NULL )
      {
         process_player_events( elapsed_time );
      }
      else
      {
         SDL_Event event;
         while( SDL_PollEvent( &event ) )
         {
            if( event.type == SDL_QUIT )
            {
               Game::current()->terminate();
               break;
            }
            else if( event.type == SDL_KEYDOWN )
            {
               switch( event.key.keysym.sym )
               {
                  case SDLK_q:
                     Game::current()->terminate();
                     break;
                  default:
                     break;
               }
            }
         }
      }
   }

   //void
   //InputHandler::activate() { _current = this; }

   //void
   //InputHandler::deactivate() { _current = NULL; }

   //InputHandler *
   //InputHandler::current() { return _current; }
} // sdl_platformer
