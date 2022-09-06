#pragma once
#include "Singleton.h"

enum class Key
{
	F1,

	Up,
	Down,
	Left,
	Right,

	W,
	S,
	A,
	D,

	Last,
};

class Keyboard : public Singleton<Keyboard>
{
	friend class Singleton<Keyboard>;

private:
	Keyboard();
	~Keyboard();

private:
	enum class KeyState
	{
		Down,
		Up,
		Press,
		None,
	};

	struct KeyInfo
	{
		KeyState eState;
		bool bPrevPush;
	};

private:
	vector<KeyInfo> m_keys;

public:
	void init();
	void update();

public:
	bool Down(Key eKey) { return m_keys[(int)eKey].eState == KeyState::Down; }
	bool Press(Key eKey) { return m_keys[(int)eKey].eState == KeyState::Press; }
	bool Up(Key eKey) { return m_keys[(int)eKey].eState == KeyState::Up; }
};