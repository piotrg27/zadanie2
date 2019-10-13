#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Includes.h"

class Window
{
private:
	GLFWwindow *wnd;
public:
	Window(int width, int height, std::string title, bool fullscreen);
	void createWindow(int width, int height, std::string title, bool fullscreen);
	int isRunning();
	GLFWwindow *getWnd();
	~Window();
};

#endif // _WINDOW_H_
