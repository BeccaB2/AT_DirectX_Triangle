#include <Windows.h>
#include <string>
#include <sstream>

// Custom windows procedure - parameters handle to an individual window (hWnd), the message ID (msg) and additional data that relates to the messages (l/w param)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Defining the window behaviour based on messages
	switch (msg)
	{
	case WM_CLOSE: // When window is closed
		PostQuitMessage(10);
		break;
	case WM_KEYDOWN: // On key press - can be used to trigger actions/events
		if (wParam == 'F') // In this instance wParam is the key pressed
		{
			SetWindowText(hWnd, "RESPECT GIVEN");
		}
		break; 
	case WM_KEYUP: // On key release
		if (wParam == 'F')
		{
			SetWindowText(hWnd,"RESPECT REVOKED");
		}
		break;
	//case WM_CHAR: // Used for specific keys that can be represented by text - Can handle upper/lower case - usually used for inputting/outputting text
	//	{
	//		static std::string title;
	//		title.push_back((char)wParam); // Adds characters to the end of the string - enables typing
	//		SetWindowText(hWnd, title.c_str()); // Changes the window text
	//	}
	//	break;
	//case WM_LBUTTONDOWN:
	//	{
	//		const POINTS pt = MAKEPOINTS(lParam); // Plots points
	//		std::ostringstream oss;
	//		oss << "(" << pt.x << "," << pt.y << ")";
	//		SetWindowText(hWnd, oss.str().c_str()); // Sets window title to the coordinates of the mouse when LMB is pressed
	//	}
	//	break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

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
	wc.lpfnWndProc = WndProc; // Handles the messages for the window - supports how window looks/behaves (Windows procedure - default behaviour)
	wc.cbClsExtra = 0; // Extra data space for the class 
	wc.cbWndExtra = 0; // Extra data for each window created for the class
	wc.hInstance = hInstance;
	wc.hIcon = nullptr; // Custom icon
	wc.hCursor = nullptr; // Customise cursor
	wc.hbrBackground = nullptr; // Customise backgorund
	wc.lpszMenuName = nullptr; // Sets a menu name
	wc.lpszClassName = pClassName; // Setting the name of the class
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc); // Registers a window class

	// Create a window instance - Controls visual elements of the window
	HWND hWnd = CreateWindowEx(
		0, pClassName,
		"Window Test",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);

	// Show the window
	ShowWindow(hWnd, SW_SHOW);

	// Handling messages
	MSG msg; // Message structure - holds the messages that need to be sent to the window
	BOOL getResult;

	while ((getResult = GetMessage(&msg, nullptr, 0, 0)) > 0) // Continuously process messages if not exiting - parameters control which windoes messages come from and enable message filtering
	{
		TranslateMessage(&msg); // Constant pointer to message - translate won't modify the processed message - allows char messages to be translated to screen
		DispatchMessage(&msg); // Pass message along to the window
	}

	// Error handling
	if (getResult == -1)
	{
		return -1; // GetMessage has errored
	}
	else
	{
		return msg.wParam; // Exit code
	}
}