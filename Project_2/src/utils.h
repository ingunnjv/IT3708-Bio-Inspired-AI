#pragma once
#ifndef PROJECT_2_UTILS_H
#define PROJECT_2_UTILS_H

#include <Eigen/Dense>
#include <vector>
#include <cfloat>
#include <set>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>


struct pixel_t {
    int row;
    int col;
};

struct rgb_centroid_t{
    double r;
    double g;
    double b;
};

struct pairCmpLe
{
    bool operator ()(const std::pair<uint32_t, double> &a, const std::pair<uint32_t, double> &b) {
        return a.second <= b.second;
    }
};

struct pairCmpGe
{
    bool operator ()(const std::pair<uint32_t, double> &a, const std::pair<uint32_t, double> &b) {
        return a.second >= b.second;
    }
};

double rgbDistance(pixel_t x, pixel_t y, const Eigen::MatrixXi &red, const Eigen::MatrixXi &green,
                   const Eigen::MatrixXi &blue);
void setUserArgs(int argc, char **argv, double &mutation_rate, double &crossover_rate,
                 uint16_t &tournament_size, double &time_limit, uint16_t &generation_limit,
                 uint16_t &population_size, int &problem_num);
void printMST(std::vector<int> &parent, int num_pixels,
              const Eigen::MatrixXi &red, const Eigen::MatrixXi &green, const Eigen::MatrixXi &blue);

void thinningIteration(cv::Mat& img, int iter);
void thinning(const cv::Mat& src, cv::Mat& dst);

#endif //PROJECT_2_UTILS_H
