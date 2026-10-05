#include "InputManager.h"
InputManager::~InputManager()
{
	_bindings.clear();
}

int InputManager::RegisterAction(const vector<unsigned char>& keys, function<void()> callback)
{
	_bindings.push_back({keys,callback});

	return 0;
}

int InputManager::GetKey()
{
	const KEYCODE* pkey = g2_GetKeyboard();
	if (!pkey) return 0;

	for (const auto& bind : _bindings)
	{
		bool isTriggered = false;

		for (auto key : bind.keys)
		{
			if (pkey[key])
			{
				isTriggered = true;
				break;
			}


		}
		if (isTriggered) bind.callback();
	}

	return 0;
}

int InputManager::GetKeyDown()
{
	const KEYCODE* pkey = g2_GetKeyboard();
	if (!pkey) return 0;
	
	for (const auto& bind : _bindings)
	{
		bool isTriggered = false;

		for (auto key : bind.keys)
		{
			if (pkey[key] && !_preKeyUp[key])
			{
				isTriggered = true;
				break;
			}
		}

		if (isTriggered)
			bind.callback();
	}

	for (int i = 0; i < 256; ++i)
		_preKeyUp[i] = pkey[i];

	return 0;
}