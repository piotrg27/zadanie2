#include "Window.h"
#include "Quad.h"
#define _CRT_SECURE_NO_WARNINGS 1
#include "PPMLoader.h"
#include "jo_jpeg.h"
#include "jpgd.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#pragma comment(lib, "glfw3")
#pragma comment(lib, "glew32")
#pragma comment(lib, "opengl32")

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void saveToJpeg(char *filePath, Texture *textureToSave, int quality) {
	int width = textureToSave->getSize().x;
	int height = textureToSave->getSize().y;
	unsigned char *pixel = new unsigned char[width*height* 3];
	textureToSave->bind();
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel);
	jo_write_jpg(filePath, pixel, width, height, 3, quality);
}

void loadImage(std::string filePath, Texture* texture, PPMLoader ppmLoader)  {
	if (filePath.substr(filePath.find_last_of('.') + 1) == "jpg" ||
		filePath.substr(filePath.find_last_of('.') + 1) == "jpeg") {
		int width;
		int height;
		int comp;
		unsigned char* pixels = jpgd::decompress_jpeg_image_from_file(filePath.c_str(), &width, &height, &comp, 3);
		texture->create(glm::vec2(width, height), pixels);
	}
	else {
		ppmimage image = ppmLoader.parse(filePath);

		float* pixels = new float[image.header.w*image.header.h * 3];
		int index = 0;

		for (auto p : image.pixels) {
			pixels[index++] = p.r / 255.0;
			pixels[index++] = p.g / 255.0;
			pixels[index++] = p.b / 255.0;
		}
		texture->create(glm::vec2(image.header.w, image.header.h), pixels);
	}
}

int main()
{
	glewExperimental = GL_TRUE;

	auto wnd = std::shared_ptr<Window>(new Window(512,512, "zadanie1", false));
	glfwSetFramebufferSizeCallback(wnd->getWnd(), framebuffer_size_callback);
	glEnable(GL_TEXTURE_2D);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(wnd->getWnd(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	auto defaultShader = std::shared_ptr<Shader>(new Shader("shader.vert", "shader.frag"));

	int width = 512;
	int height = 512;

	Quad quad = Quad();
	Texture *texture = new Texture();
	quad.setup(glm::vec2(width, height), defaultShader->getShaderProgram(), texture);

	PPMLoader ppmLoader = PPMLoader();
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	int quality = 1;

	while (!wnd->isRunning()) {
		glfwPollEvents();

		glClearColor(0.2f, 0.5f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("Options");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::SliderInt("Quality", &quality, 1, 100);
			static char path[128] = "";
			ImGui::InputText("File path", path, IM_ARRAYSIZE(path));
			if (ImGui::Button("Load jpeg/ppm")) {
				loadImage(path, texture, ppmLoader);
			}
			if (ImGui::Button("Save to jpeg")) {
				saveToJpeg(path, texture, quality);
			}
			ImGui::End();
		}

		quad.draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(wnd->getWnd());
	}

	delete texture;

	return 0;
}