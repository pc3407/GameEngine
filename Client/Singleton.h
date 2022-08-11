#pragma once
template <typename T>
class Singleton
{
public:
	static T* Get()
	{
		static T sInstance;
		return &sInstance;
	}
};