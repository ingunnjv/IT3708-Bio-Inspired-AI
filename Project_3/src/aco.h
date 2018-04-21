#ifndef PROJECT_3_ACO_H
#define PROJECT_3_ACO_H

#pragma once
#include "jssp.h"
#include "schedule_builder.h"

enum decidability_rules{ SPT = 0, LPT };

struct ant{
    std::vector<std::pair<task*,task*>> path;
    uint8_t decidability_rule;
    ant(uint8_t rule){
        this->decidability_rule = rule;
    }
};



class ACO {
private:
    JSSP* jssp;
    int swarm_size; // number of ants
    int cycles; // iterations of the algorithm
    double alpha; // influence weight of pheromone
    double beta; // influence weight of heuristic
    double rho; // evaporation rate of pheromone
    double Q; // constant factor in ant pheromone contribution
    double initial_pheromone; // initial pheromone for all edges
    double max_pheromone;
    double min_pheromone;
    std::vector<std::vector<double>> pheromone_trails; // pheromone on all edges

public:
    ACO(JSSP &jssp, int swarm_size, int cycles, double alpha, double beta, double rho, double initial_pheromone,
            double Q, double max_pheromone, double min_pheromone);
    void initializePheromoneTrails();
    void printPheromoneTrailsTable();
    std::vector <std::pair<task *, task *>> getStateTransitions(const std::vector<std::vector<int>> &tabu);
    std::vector<double> getStateTransitionProbs(std::vector<std::pair<task *, task *>> state_transitions, uint8_t decidability_rule);
    void addAntPheromoneContribution(std::vector<std::vector<double>> &pheromone_accumulator,
                                     std::vector<int> elites,
                                     const ant &ant, const int ant_nr, double makespan);
    void updatePheromoneTrails(const std::vector<std::vector<double>> &pheromone_accumulator);

    void runOptimization();

    template<typename T>
    void setMatrixToZero(std::vector<std::vector<T>> &matrix);
    bool isTabuFull(std::vector<std::vector<int>> &tabu);
    int chooseNextState(std::vector<double> &state_transistion_probs);
    void updateTabu(std::vector<std::vector<int>> &tabu, task* next_task);

};


#endif //PROJECT_3_ACO_H
