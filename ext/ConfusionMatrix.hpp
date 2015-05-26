#ifndef CONFUSION_MATRIX_HPP
#define CONFUSION_MATRIX_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include "prettyprint.hpp"

#ifndef CPPPROG
#include "rice/String.hpp"
#include "rice/Array.hpp"
#include "rice/Hash.hpp"
#endif

class ConfusionMatrix {
protected:

    void compute_confusion_matrix();
    int a_;
    int b_;
    int c_;
    int d_;
    //
    std::vector<int> clust_1_;
    std::vector<int> clust_2_;
    //
    std::vector<std::vector<int> > clust_map_1_;
    std::vector<std::vector<int> > clust_map_2_;
    // fill in clust_vect from hash (ruby hash)
    void populate_vect(Rice::Hash &hsh, std::vector<int> &clust_v);
    
    std::pair<int,int> int_and_diff(std::vector<int> clust_v, 
				    std::vector<std::vector<int>> clust_map);

public:
    ConfusionMatrix();
    ConfusionMatrix(Rice::Hash c1_hsh, Rice::Hash c2_hsh);
    virtual ~ConfusionMatrix();
    
    void print_matrix();
    
    Rice::Array get_confusion_matrix();
    // for computing various indices
    double get_rand_index();
    double get_jaccard_index();
    double get_fm_index();
};

#endif
