#pragma once
#include <glc2d.h>
#include <functional>
#include <vector>

using std::vector;
using std::function;


class InputManager
{
public :
	struct ActionBinding
	{
		vector<unsigned char> keys;
		function<void()> callback;

		ActionBinding(const vector<unsigned char>& k,function<void()> cb)
			: keys(k),callback(cb) { }
	};

	~InputManager();

	int RegisterAction(const vector<unsigned char>& keys,function<void()> callback);
	int GetKey();
	int GetKeyDown();

private:
	vector<ActionBinding> _bindings;
	KEYCODE _preKeyUp[256]{};
};

