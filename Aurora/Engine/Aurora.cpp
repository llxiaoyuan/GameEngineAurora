#include"Aurora.hpp"

Aurora Aurora::instance;

bool Aurora::iniEngine(const Configuration& config)
{
	window = nullptr;

	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (config.mode == config.Normal)
	{
		Graphics::screenWidth = config.screenWidth;
		Graphics::screenHeight = config.screenHeight;
	}
	else
	{
		getSysResolution(Graphics::screenWidth, Graphics::screenHeight);
	}

	window = glfwCreateWindow(Graphics::screenWidth, Graphics::screenHeight, config.title.c_str(), NULL, NULL);

	if (!window)
	{
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	game = nullptr;

	srand((unsigned int)time(nullptr));

	std::cout << "[" << typeid(*this).name() << "] " << "initiallize complete!\n";

	Music::ini();

	Keyboard::ini();

	Mouse::ini();

	if (config.mode == config.Wallpaper)
	{
		HWND window = FindWindowA(NULL, config.title.c_str());
		HWND bg = get_wallpaper_window();
		SetParent(window, bg);
		SetWindowLongPtr(window, GWL_STYLE, WS_VISIBLE | WS_POPUP);
		MoveWindow(window, 0, 0, Graphics::screenWidth, Graphics::screenHeight, 0);
	}
	return true;
}

void Aurora::iniGame(Game* game)
{
	this->game = game->clone();
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	run();
}

void Aurora::run()
{
	while (!glfwWindowShouldClose(window))
	{
		timeStart = timer.now();
		game->update(Graphics::getDeltaTime());
		game->render();
		glfwSwapBuffers(window);
		timeEnd = timer.now();
		Graphics::setDeltaTime(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count() / 1000.f);
		glfwPollEvents();
	}
	glfwTerminate();
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	HWND p = FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL);
	HWND* ret = (HWND*)lParam;

	if (p)
	{
		// Gets the WorkerW Window after the current one.
		*ret = FindWindowEx(NULL, hwnd, L"WorkerW", NULL);
	}
	return true;
}

void getSysResolution(int& width, int& height)
{
	HMONITOR monitor = MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTONEAREST);
	MONITORINFO info;
	info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &info);
	width = info.rcMonitor.right - info.rcMonitor.left;
	height = info.rcMonitor.bottom - info.rcMonitor.top;
}

HWND Aurora::get_wallpaper_window()
{
	// Fetch the Progman window
	HWND progman = FindWindow(L"ProgMan", NULL);
	// Send 0x052C to Progman. This message directs Progman to spawn a 
	// WorkerW behind the desktop icons. If it is already there, nothing 
	// happens.
	SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
	// We enumerate all Windows, until we find one, that has the SHELLDLL_DefView 
	// as a child. 
	// If we found that window, we take its next sibling and assign it to workerw.
	HWND wallpaper_hwnd = nullptr;
	EnumWindows(EnumWindowsProc, (LPARAM)&wallpaper_hwnd);
	// Return the handle you're looking for.
	return wallpaper_hwnd;
}
