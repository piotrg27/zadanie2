#include "PPMLoader.h"

std::vector<pixel> PPMLoader::parsePPM3(std::ifstream& fileStream, ppmheader header)
{
	std::vector<pixel> pixels;
	std::string tmp_line;
	pixel tmp_pixel;

	int rowCounter = 0;

	while (std::getline(fileStream, tmp_line)) {
		if (rowCounter > header.h) {
			break;
		}
		if (tmp_line[0] == '#' || tmp_line.empty()) {
			continue;
		}

		std::stringstream ss(tmp_line);
		for (int i = 0; i < header.w; i++) {
			ss >> tmp_pixel.r;
			ss >> tmp_pixel.g;
			ss >> tmp_pixel.b;

			if (tmp_pixel.r < 0 || tmp_pixel.r > header.max ||
				tmp_pixel.g < 0 || tmp_pixel.g > header.max ||
				tmp_pixel.b < 0 || tmp_pixel.b > header.max) {
				std::cout << "Wrong pixel data!" << std::endl;
				throw std::runtime_error("Wrong pixel data!");
			}

			if (header.max != 255) {
				tmp_pixel.r = (tmp_pixel.r * 255) / header.max;
				tmp_pixel.g = (tmp_pixel.g * 255) / header.max;
				tmp_pixel.b = (tmp_pixel.b * 255) / header.max;
			}
			pixels.push_back(tmp_pixel);
		}

		rowCounter++;
	}

	return pixels;
}

std::vector<pixel> PPMLoader::parsePPM6(std::ifstream& fileStream, ppmheader header)
{
	std::vector<pixel> pixels;
	std::string tmp_line;
	pixel tmp_pixel;

	int rowCounter = 0;
	char color;
	while (std::getline(fileStream, tmp_line)) {
		if (rowCounter > header.h) {
			break;
		}
		if (tmp_line[0] == '#' || tmp_line.empty()) {
			continue;
		}

		std::stringstream ss(tmp_line);
		for (int i = 0; i < header.w; i++) {
			ss >> color;
			tmp_pixel.r = (int)color;
			ss >> color;
			tmp_pixel.g = (int)color;
			ss >> color;
			tmp_pixel.b = (int)color;

			std::cout << " R " << tmp_pixel.r << std::endl;
			std::cout << " G " << tmp_pixel.g << std::endl;
			std::cout << " B " << tmp_pixel.b << std::endl;

			if (header.max != 255) {
				tmp_pixel.r = (tmp_pixel.r * 255) / header.max;
				tmp_pixel.g = (tmp_pixel.g * 255) / header.max;
				tmp_pixel.b = (tmp_pixel.b * 255) / header.max;
			}
			pixels.push_back(tmp_pixel);
		}

		rowCounter++;
	}

	return pixels;
}

PPMLoader::PPMLoader()
{
}

ppmimage PPMLoader::parse(std::string filePath)
{
	std::ifstream fileStream(filePath.c_str());
	if (!fileStream.good()) {
		std::cout << filePath << " not found!" << std::endl;
	}

	ppmimage image;

	image.header.type = "";
	image.header.w = 0;
	image.header.h = 0;
	image.header.max = 0;

	std::string tmp_line;

	while (std::getline(fileStream, tmp_line)) {
		if (tmp_line[0] == '#' || tmp_line.empty()) {
			continue;
		}

		if (image.header.type == "") {
			image.header.type = tmp_line;
		} 
		else if (image.header.w == 0 && image.header.h == 0) {
			sscanf(tmp_line.c_str(), "%i %i", &image.header.w, &image.header.h);
		}
		else if (image.header.max == 0) {
			sscanf(tmp_line.c_str(), "%i", &image.header.max);
		}

		if (image.header.type != "" &&
			image.header.w != 0 &&
			image.header.h != 0 &&
			image.header.max != 0) {
			break;
		}
	}

	if (image.header.w <= 0 && image.header.h <= 0 && image.header.max <= 0) {
		throw std::runtime_error("wrong header params! : " + filePath);
	}
	
	if (image.header.type == "P3") {
		image.pixels = parsePPM3(fileStream, image.header);
	}
	else if (image.header.type == "P6") {
		image.pixels = parsePPM6(fileStream, image.header);
	}
	else {
		throw std::runtime_error("wrong type -> " + image.header.type + " : " + filePath);
	}
	fileStream.close();

	return image;
}

PPMLoader::~PPMLoader()
{
}
