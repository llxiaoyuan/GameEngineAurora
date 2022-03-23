#include<Aurora/Aurora.hpp>

Aurora Aurora::instance;

bool Aurora::iniEngine(const Configuration& configuration)
{
	config = &configuration;

	if (!glfwInit())
		return false;

	std::cout << "[class Aurora] glfwInit complete!\n";

	if (config->mode == Configuration::DisplayMode::Wallpaper)
	{
		glfwWindowHint(GLFW_DECORATED, 0);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	if (config->multiSample && config->multiSample % 2 == 0)
	{
		std::cout << "[class Aurora] multisample level " << config->multiSample << "\n";
		glfwWindowHint(GLFW_SAMPLES, config->multiSample);
	}

	switch (config->mode)
	{
	case Configuration::DisplayMode::Normal:
		Graphics::screenWidth = config->screenWidth;
		Graphics::screenHeight = config->screenHeight;
		break;
	case Configuration::DisplayMode::Wallpaper:
		getSysResolution(Graphics::screenWidth, Graphics::screenHeight);
		break;
	case Configuration::DisplayMode::Record:
		Graphics::screenWidth = config->screenWidth;
		Graphics::screenHeight = config->screenHeight;
		break;
	default:
		break;
	}

	window = glfwCreateWindow(Graphics::screenWidth, Graphics::screenHeight, config->title.c_str(), nullptr, nullptr);

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
	
	std::cout << "[class Aurora] " << glGetString(GL_VERSION) << "\n";
	std::cout << "[class Aurora] " << glGetString(GL_RENDERER) << "\n";

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	if (config->multiSample)
	{
		glEnable(GL_MULTISAMPLE);
	}

	game = nullptr;

	srand((unsigned)time(nullptr));

	std::cout << "[" << typeid(*this).name() << "] " << "initiallize complete!\n";

	if (config->useAudio)
	{
		Music::ini();
	}

	Keyboard::ini();

	if (config->mode == Configuration::DisplayMode::Wallpaper)
	{
		HWND window = FindWindowA(nullptr, config->title.c_str());
		HWND bg = get_wallpaper_window();
		SetParent(window, bg);
		MoveWindow(window, 0, 0, Graphics::screenWidth, Graphics::screenHeight, 0);
	}
	else if (config->mode == Configuration::DisplayMode::Record)
	{
		glfwSwapInterval(0);
		glfwHideWindow(window);
	}
	
	return true;
}

void Aurora::iniGame(Game* game)
{
	this->game = game->clone();
	switch (config->mode)
	{
	case Configuration::DisplayMode::Normal:
		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		runGame();
		break;
	case Configuration::DisplayMode::Wallpaper:
		runWallpaper();
		break;
	case Configuration::DisplayMode::Record:
		runRecord();
		break;
	default:
		break;
	}
}

void Aurora::runGame()
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

void Aurora::runWallpaper()
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

void Aurora::runRecord()
{
	VideoRecorder recorder(config->screenWidth, config->screenHeight, Graphics::config.totalFrame, Graphics::config.frameRate);
	do
	{
		game->update(1 / (float)Graphics::config.frameRate);
		game->render();
		Graphics::deltaTime = 1 / (float)Graphics::config.frameRate;
	} while (recorder.record());
	glfwTerminate();
}



BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	HWND p = FindWindowEx(hwnd, nullptr, L"SHELLDLL_DefView", nullptr);
	HWND* ret = (HWND*)lParam;

	if (p)
	{
		// Gets the WorkerW Window after the current one.
		*ret = FindWindowEx(nullptr, hwnd, L"WorkerW", nullptr);
	}
	return true;
}

HWND get_wallpaper_window()
{
	// Fetch the Progman window
	HWND progman = FindWindow(L"ProgMan", nullptr);
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
