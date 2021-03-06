#pragma once
#ifndef PROJECT_2_NSGA2_H
#define PROJECT_2_NSGA2_H

#include "utils.h"
#include "genotype.h"
#include <vector>
#include <Eigen/Dense>
#include <set>
#include <iostream>
#include <cfloat>


class Nsga2 {
private:
    std::vector<Genotype> population;

    double mutation_rate;
    double crossover_rate;
    double time_limit;
    uint16_t tournament_size;
    uint16_t generation_limit;
    uint16_t population_size;
    uint8_t use_weighted_sum;

public:
    // Constructors
    Nsga2();
    Nsga2(double mutation_rate, double crossover_rate, uint16_t tournament_size, double time_limit,
          uint16_t generation_limit, uint16_t population_size, uint8_t use_weighted_sum);

    /// Initializes a population using a MST as the basis for gene encoding
    void initializePopulationFromMst(const Eigen::MatrixXi &red, const Eigen::MatrixXi &green,
                                     const Eigen::MatrixXi &blue,
                                     std::vector<Genotype> &initial_pop);

    /// Creates a MST based on the distance in RGB space of a picture as basis for edges
    std::vector<int> primMST(const Eigen::MatrixXi &red, const Eigen::MatrixXi &green, const Eigen::MatrixXi &blue);
    std::vector<int> superMST(uint8_t threshold, const Eigen::MatrixXi &red, const Eigen::MatrixXi &green,
                                  const Eigen::MatrixXi &blue);

    /// Sorts the population based non-domination fronts
    void fastNonDominatedSort(std::vector<std::vector<Genotype*> > &fronts);

    /// Sorts a vector of genotypes based on the objective number i's value
    std::tuple<double, double> objectiveValueSort(std::vector<Genotype*> &front, int8_t obj_val_i);

    /// Sorts a front of genotypes based on their crowding distance (best to worst -> greatest to lowest)
    void crowdingDistanceSort(std::vector<Genotype*> &front);

    /// Assigns every genotype in a front a crowding_distance
    void crowdingDistanceAssignment(std::vector<Genotype*> &front);

    /// Creates a new offspring population using crossover and mutation
    void makeNewPop(const Eigen::MatrixXi &red, const Eigen::MatrixXi &green, const Eigen::MatrixXi &blue,
                    std::vector<Genotype> &parent_pop, std::vector<Genotype> &offspring_pop);
    /// Two binary tournaments selects two parents
    void tournamentSelection(std::vector<Genotype *> &selected_parents, std::vector<Genotype> &parent_pop);

    /// For each pixel in an offspring, inherit either from first parent or second parent, uniformly distributed
    void uniformCrossover(Genotype &offspring1, Genotype &offspring2);

    /// Selects a random gene in an individual and sets it to a new value randomly selected from {left, right, up, down, none}
    void mutation(Genotype &individual, const Eigen::MatrixXi &red, const Eigen::MatrixXi &green,
                  const Eigen::MatrixXi &blue);

    void initialMutation(Genotype &individual);

    /// Run the main loop of the algorithm
    void runMainLoop(const Eigen::MatrixXi &red, const Eigen::MatrixXi &green, const Eigen::MatrixXi &blue,
                     std::vector<Genotype> &initial_pop, cv::Mat &image);
};

#endif //PROJECT_2_NSGA_II_H
