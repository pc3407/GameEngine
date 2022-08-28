#pragma once
#include "Singleton.h"

enum class Key
{
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

class KeyMgr : public Singleton<KeyMgr>
{
	friend class Singleton<KeyMgr>;

private:
	KeyMgr();
	~KeyMgr();

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
