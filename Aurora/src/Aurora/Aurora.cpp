#include<Aurora/Aurora.hpp>

Aurora Aurora::instance;

bool Aurora::iniEngine(const Configuration& config)
{
	if (!glfwInit())
		return false;

	if (config.mode == Configuration::DisplayMode::Wallpaper)
	{
		glfwWindowHint(GLFW_DECORATED, 0);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (config.multiSample)
	{
		glfwWindowHint(GLFW_SAMPLES, config.multiSample);
	}

	switch (config.mode)
	{
	case Configuration::DisplayMode::Normal:
		Graphics::screenWidth = config.screenWidth;
		Graphics::screenHeight = config.screenHeight;
		break;
	case Configuration::DisplayMode::Wallpaper:
		getSysResolution(Graphics::screenWidth, Graphics::screenHeight);
		break;
	case Configuration::DisplayMode::Record:
		Graphics::screenWidth = config.screenWidth;
		Graphics::screenHeight = config.screenHeight;
		break;
	default:
		break;
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

	if (config.multiSample)
	{
		glEnable(GL_MULTISAMPLE);
	}

	glLineWidth(1.5f);

	game = nullptr;

	srand((unsigned)time(nullptr));

	std::cout << "[" << typeid(*this).name() << "] " << "initiallize complete!\n";

	if (config.useAudio)
	{
		Music::ini();
	}

	Keyboard::ini();

	if (config.mode == Configuration::DisplayMode::Wallpaper)
	{
		HWND window = FindWindowA(NULL, config.title.c_str());
		HWND bg = get_wallpaper_window();
		SetParent(window, bg);
		MoveWindow(window, 0, 0, Graphics::screenWidth, Graphics::screenHeight, 0);
	}
	else if (config.mode == Configuration::DisplayMode::Record)
	{
		glfwSwapInterval(0);
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
		game->update(Graphics::deltaTime);
		game->render();
		glfwSwapBuffers(window);
		timeEnd = timer.now();
		Graphics::deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count() / 1000.f;
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

HWND get_wallpaper_window()
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

void getSysResolution(int& width, int& height)
{
	HMONITOR monitor = MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTONEAREST);
	MONITORINFO info;
	info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &info);
	width = info.rcMonitor.right - info.rcMonitor.left;
	height = info.rcMonitor.bottom - info.rcMonitor.top;
}
