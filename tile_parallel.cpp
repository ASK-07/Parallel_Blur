#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <opencv2/opencv.hpp>

#ifdef _OPENMP
#include <omp.h>
#endif

const int TILE_SIZE = 32;

//Kernel used for smoothing
const float GAUSS_KERNEL[3][3] = {
    {1/16.f, 2/16.f, 1/16.f},
    {2/16.f, 4/16.f, 2/16.f},
    {1/16.f, 2/16.f, 1/16.f}
};

// Pixel struct for rgb values
struct Pixel { float r, g, b; };

int main() { 

    cv::Mat img = cv::imread("input.jpg", cv::IMREAD_COLOR);
    if(img.empty()) {
        std::cerr << "Failed to upload image.\n";
        return -1;
    }

    img.convertTo(img, CV_32FC3, 1.0/255.0);

    int width = img.cols;
    int height = img.rows;

    // Framebuffer holds initial pixel values
    std::vector<Pixel> framebuffer(width * height);

    // Output stores blured image
    std::vector<Pixel> output(width * height);

    // Copies image data into framebuffer
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cv::Vec3f color = img.at<cv::Vec3f>(y,x);
            framebuffer[y*width + x] = { color[2], color[1], color[0] };
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Main tiling loop
    #pragma omp parallel for collapse(2)
    for (int ty = 0; ty < height; ty += TILE_SIZE) { 
        for (int tx = 0; tx < width; tx += TILE_SIZE){

            // Iterate over pixels in current tile
            for (int y = ty; y < std::min(ty + TILE_SIZE, height); y++) {
                for (int x = tx; x < std::min(tx + TILE_SIZE, width); x++) {
                    
                    float sum_r = 0.0f;
                    float sum_g = 0.0f;
                    float sum_b = 0.0f;

                    // Applies 3x3 Gaussian Kernel, ensures no out of bounds
                    for (int ky = -1; ky <= 1; ky++) {
                        for (int kx = -1; kx <= 1; kx++) {
                            int px = x + kx;
                            if (px < 0) px = 0;
                            if (px >= width) px = width -1;
                            int py = y + ky;
                            if (py < 0) py = 0;
                            if (py >= height) py = height -1;

                            Pixel p = framebuffer[py * width + px];
                            float k = GAUSS_KERNEL[ky + 1][kx + 1];
                            sum_r += p.r * k;
                            sum_g += p.g * k;
                            sum_b += p.b * k;
                        }
                    }
                    // Store blurred image
                    output[y * width + x] = {sum_r, sum_g, sum_b};
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Completion time: " << diff.count() << " seconds.\n";

    cv::Mat out_img(height, width, CV_32FC3);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel p = output[y * width + x];
            out_img.at<cv::Vec3f>(y, x) = cv::Vec3f(p.b, p.g, p.r);
        }
    }
    out_img.convertTo(out_img, CV_8UC3, 255.0);

    //Blurred image saved as blurred.jpg
    cv::imwrite("blurred.jpg", out_img);

    return 0;
}