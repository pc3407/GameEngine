#include "Common.h"
#include "Keyboard.h"

UINT g_keys[(UINT)Key::Last] =
{
	VK_F1,

	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,

	'W',
	'S',
	'A',
	'D',
};

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::init()
{
	for (UINT i = 0; i < (UINT)Key::Last; i++)
	{
		KeyInfo keyInfo;

		keyInfo.eState = KeyState::None;
		keyInfo.bPrevPush = false;

		m_keys.push_back(keyInfo);
	}
}

void Keyboard::update()
{
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (UINT i = 0; i < (UINT)m_keys.size(); i++)
		{
			if (GetAsyncKeyState(g_keys[i]) & 0x8000)
			{
				if (m_keys[i].bPrevPush)
				{
					m_keys[i].eState = KeyState::Press;
				}
				else
				{
					m_keys[i].eState = KeyState::Down;
				}

				m_keys[i].bPrevPush = true;
			}
			else
			{
				if (m_keys[i].bPrevPush)
				{
					m_keys[i].eState = KeyState::Up;
				}
				else
				{
					m_keys[i].eState = KeyState::None;
				}
			}
		}
		
	}
	else
	{
		for (UINT i = 0; i < (UINT)m_keys.size(); i++)
		{
			m_keys[i].bPrevPush = false;

			if (KeyState::Down == m_keys[i].eState || KeyState::Press == m_keys[i].eState)
			{
				m_keys[i].eState = KeyState::Up;
			}
			else if(KeyState::Up == m_keys[i].eState)
			{
				m_keys[i].eState = KeyState::None;
			}
		}
	}
}