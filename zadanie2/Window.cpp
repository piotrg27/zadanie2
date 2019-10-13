#include "Window.h"


Window::Window(int width, int height, std::string title, bool fullscreen)
{
	createWindow( width, height, title, fullscreen);
}

void Window::createWindow(int width, int height, std::string title, bool fullscreen)
{
	glfwInit();
    glfwSwapInterval(1);
	glfwWindowHint(GLFW_SAMPLES, 4);
	if(fullscreen == true)
	{
	wnd = glfwCreateWindow( width, height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
	wnd = glfwCreateWindow( width, height, title.c_str(), NULL, NULL);
	}
	
	glfwMakeContextCurrent(wnd);
	glfwSwapInterval(1);
	glewInit();
	std::cout << "Renderer: " << (char*)glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL" << (char*)glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL" << (char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

int Window::isRunning()
{
    if(glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
    return 1;
    }
    else
    {
	return glfwWindowShouldClose(wnd);
    }
}

GLFWwindow *Window::getWnd()
{
    return wnd;
}

Window::~Window()
{
	glfwTerminate();
}
