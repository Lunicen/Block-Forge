#pragma once
#include "Application/HID/HumanInterfaceDevice.h"
#include "Application/Layer/Layer.h"

class PauseMenuLayer final : public Layer
{
	HumanInterfaceDevice& _hid;

public:
	explicit PauseMenuLayer(HumanInterfaceDevice& hid) : _hid(hid)
	{
	}

	void OnUpdate() override
	{
	}

	void OnEvent() override
	{
		if (_hid.IsPressedOnce(KeyboardKey::escape))
		{
			if (IsLocked())
			{
				_hid.DisableCursor();

				UnlockLayer();
				return;
			}

			_hid.EnableCursor();
			LockLayer();
		}
	}
};
