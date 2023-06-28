#pragma once
#include "application/hid/human_interface_device.h"
#include "application/layer/layer.h"

/// @class PauseMenuLayer
///	@brief Represents the pause menu.
class PauseMenuLayer final : public Layer
{
public:

	void OnUpdate() override
	{
		// For now there is nothing to render.
		// That's why this method is empty.
	}

	void OnEvent(HumanInterfaceDevice& hid) override
	{
		if (hid.IsPressedOnce(KeyboardKey::escape))
		{
			if (IsLocked())
			{
				hid.DisableCursor();

				UnlockLayer();
				return;
			}

			hid.EnableCursor();
			LockLayer();
		}
	}
};
