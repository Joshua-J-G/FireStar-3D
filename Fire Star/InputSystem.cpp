#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::m_system;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
    InputSystem::m_system = nullptr;
}

void InputSystem::update()
{
    POINT current_mouse_Pos = {};
    ::GetCursorPos(&current_mouse_Pos);

    if (m_first_time)
    {
        m_old_mouse_pos = Point(current_mouse_Pos.x, current_mouse_Pos.y);
        m_first_time = false;
    }

    if (current_mouse_Pos.x != m_old_mouse_pos.m_x || current_mouse_Pos.y != m_old_mouse_pos.m_y)
    {
        std::unordered_set<InputListener*>::iterator it = m_map_listeners.begin();

        while (it != m_map_listeners.end())
        {
            (*it)->onMouseMove(Point(current_mouse_Pos.x, current_mouse_Pos.y));
            ++it;
        }
    }
    m_old_mouse_pos = Point(current_mouse_Pos.x, current_mouse_Pos.y);

    if (::GetKeyboardState(m_keys_state))
    {

        for (unsigned int i = 0; i < 256; i++)
        {
            // Check if key is down
            if (m_keys_state[i] & 0x80)
            {
                std::unordered_set<InputListener*>::iterator it = m_map_listeners.begin();

                while (it != m_map_listeners.end())
                {
                    if (i == VK_LBUTTON)
                    {
                        if (m_keys_state[i] != m_old_keys_state[i])
                            (*it)->OnLeftMouseDown(Point(current_mouse_Pos.x, current_mouse_Pos.y));
                    }
                    else if (i == VK_RBUTTON)
                    {
                        if (m_keys_state[i] != m_old_keys_state[i])
                            (*it)->OnRightMouseDown(Point(current_mouse_Pos.x, current_mouse_Pos.y));
                    }
                    else
                        (*it)->onKeyDown(i);

                    ++it;
                }
            }
            else // Key is up 
            {
                if (m_keys_state[i] != m_old_keys_state[i])
                {
                    std::unordered_set<InputListener*>::iterator it = m_map_listeners.begin();

                    while (it != m_map_listeners.end())
                    {
                        if (i == VK_LBUTTON)
                            (*it)->OnLeftMouseUp(Point(current_mouse_Pos.x, current_mouse_Pos.y));
                        else if (i == VK_RBUTTON)
                            (*it)->OnRightMouseUp(Point(current_mouse_Pos.x, current_mouse_Pos.y));
                        else
                            (*it)->onKeyUp(i);

                        ++it;
                    }
                }

            }
        }
        //set told keys to a buffer
        ::memcpy(m_old_keys_state, m_keys_state,sizeof(unsigned char)*256);

    }
}

void InputSystem::addListener(InputListener* listener)
{
    m_map_listeners.insert(listener);
}

void InputSystem::RemoveListener(InputListener* listener)
{
    m_map_listeners.erase(listener);
}

void InputSystem::setCursorPosition(const Point& pos)
{
    ::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::ShowCursor(bool show)
{
    ::ShowCursor(show);
}

InputSystem* InputSystem::get()
{
    static InputSystem system;

    return &system;
}

void InputSystem::create()
{
    if (InputSystem::m_system) throw std::exception("FAILED: Input SYstem Already Create");
    InputSystem::m_system = new InputSystem();
}

void InputSystem::release()
{
    if (!InputSystem::m_system) return;
    delete InputSystem::m_system;
}

