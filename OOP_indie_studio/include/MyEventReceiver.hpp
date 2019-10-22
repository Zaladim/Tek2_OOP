/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** MyEventReceiver
*/

#include <irrlicht/irrlicht.h>
#include "irrlicht/driverChoice.h"

#ifndef MYEVENTRECEIVER_HPP_
#define MYEVENTRECEIVER_HPP_

class MyEventReceiver : public irr::IEventReceiver {
	public:

        struct SMouseState {
            irr::core::position2di Position;
            bool LeftButtonDown;
            SMouseState() : LeftButtonDown(false) { }
        } MouseState;

		virtual bool OnEvent(const irr::SEvent& event)
        {
            if (event.EventType == irr::EET_KEY_INPUT_EVENT)
                KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
            if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
                switch(event.MouseInput.Event) {
                    case irr::EMIE_LMOUSE_PRESSED_DOWN:
                        MouseState.LeftButtonDown = true;
                        break;

                    case irr::EMIE_LMOUSE_LEFT_UP:
                        MouseState.LeftButtonDown = false;
                        break;

                    case irr::EMIE_MOUSE_MOVED:
                        MouseState.Position.X = event.MouseInput.X;
                        MouseState.Position.Y = event.MouseInput.Y;
                        break;
                    default:
                        break;
                }
            }
            return false;
        }

        virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
        {
            return KeyIsDown[keyCode];
        }
        
        const SMouseState & GetMouseState(void) const
        {
            return MouseState;
        }

        MyEventReceiver()
        {
            for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
                KeyIsDown[i] = false;
        }
    
    private:

        bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];

};

#endif /* !MYEVENTRECEIVER_HPP_ */
