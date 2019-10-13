#pragma once

#include "Includes.h"

struct ppmheader {
	std::string type;
	int w;
	int h;
	int max;
};

struct pixel {
	int r; 
	int g;
	int b;
};

struct ppmimage {
	ppmheader header;
	std::vector<pixel> pixels;
};

class PPMLoader
{
private:
	std::vector<pixel> parsePPM3(std::ifstream& fileStream, ppmheader header);
	std::vector<pixel> parsePPM6(std::ifstream& fileStream, ppmheader header);
public:
	PPMLoader();
	ppmimage parse(std::string filePath);
	~PPMLoader();
};

