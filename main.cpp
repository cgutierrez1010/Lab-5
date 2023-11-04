#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Pixel {
    float r;
    float g;
    float b;
    int x;
    int y;
};

std::vector<Pixel> pixel_list;

void pixeldatacam(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open the file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        Pixel pixel;

        for (int i = 0; std::getline(ss, token, ','); i++) {
            switch (i) {
                case 0: pixel.x = std::stoi(token); break;
                case 1: pixel.y = std::stoi(token); break;
                case 2: pixel.r = std::stof(token); break;
                case 3: pixel.g = std::stof(token); break;
                case 4: pixel.b = std::stof(token); break;
            }
        }
        pixel_list.push_back(pixel);
    }
}

void average_colors(std::vector<Pixel>& pixel_list) {
    float totalR = 0.0, totalG = 0.0, totalB = 0.0;
    
    for (const Pixel& pixel : pixel_list) {
        totalR += pixel.r;
        totalG += pixel.g;
        totalB += pixel.b;
    }
    
    int pixelCount = pixel_list.size();
    
    float avgR = totalR / pixelCount;
    float avgG = totalG / pixelCount;
    float avgB = totalB / pixelCount;

    std::cout << "Average R: " << avgR << ", G: " << avgG << ", B: " << avgB << std::endl;
}

void flip_vertically(std::vector<Pixel>& pixel_list) {
    int maxY = 255; 
    
    for (Pixel& pixel : pixel_list) {
        pixel.y = maxY - pixel.y; 
    }
}

void savePixelData(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open the file for writing." << std::endl;
        return;
    }

    for (const Pixel& pixel : pixel_list) {
        file << pixel.x << "," << pixel.y << "," << pixel.r << "," << pixel.g << "," << pixel.b << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = "flipped.dat";

    pixeldatacam(inputFileName);
    average_colors(pixel_list);
    flip_vertically(pixel_list);
    savePixelData(outputFileName);

    return 0;
}
