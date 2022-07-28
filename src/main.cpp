#include "Core/Log.h"
#include "Sandbox/Sandbox.h"

int main()
{
	// TODO integrate the Main Menu with Sandbox class 
	// MainMenu mainMenu = MainMenu();
	// mainMenu.Draw();

	const auto sandbox = new Sandbox("test.json");
	sandbox->Run();

	if (int x = 4)
	{
		;;
	}

	return 0;
}
