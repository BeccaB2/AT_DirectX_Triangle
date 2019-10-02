#include <Windows.h>

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR	  lpCmdLine,
	int       nCmdShow )
{
	const auto pClassName = "DirectXTriangle";

	// Create window class
	WNDCLASSEX wc = {0}; // Creating a structure to hold configurations for the window
	wc.cbSize = sizeof(wc); // Sets the size of the above structure
	wc.style = CS_OWNDC; // Sets style of the class - allows multiple unique windows to be ran at once
	wc.lpfnWndProc = DefWindowProc; // Handles the messages for the window - supports how window looks/behaves
	wc.cbClsExtra = 0; // Extra data space for the class 
	wc.cbWndExtra = 0; // Extra data for each window created for the class
	wc.hInstance = hInstance;
	wc.hIcon = nullptr; // Custom icon
	wc.hCursor = nullptr; // Customise cursor
	wc.hbrBackground = nullptr; // Customise backgorund
	wc.lpszMenuName = nullptr; // Sets a menu name
	wc.lpszClassName = pClassName; // Setting the name of the class
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	// Create a window instance
	HWND hWnd = CreateWindowEx(
		0, pClassName,
		"Window Test",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);

	// Show the window
	ShowWindow(hWnd, SW_SHOW);
	//while (true);
	return 0;
}