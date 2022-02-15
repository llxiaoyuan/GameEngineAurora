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

	Graphics::screenWidth = config.screenWidth;
	Graphics::screenHeight = config.screenHeight;

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

	std::cout << "[Engine] initiallize complete!\n";

	Music::ini();

	Keyboard::ini();

	Mouse::ini();

	return true;
}

void Aurora::iniGame(Game* game)
{
	this->game = game;
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
	delete game;
	glfwTerminate();
}