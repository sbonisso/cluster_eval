#include "ConfusionMatrix.hpp"
/**
 *
 */
ConfusionMatrix::ConfusionMatrix() {
    a_ = 0;
    b_ = 0;
    c_ = 0;
    d_ = 0;   
}
/**
 *
 */
ConfusionMatrix::~ConfusionMatrix() {}
/**
 * each ruby hash are pairs of {read_id => clust_id}
 */
ConfusionMatrix::ConfusionMatrix(Rice::Hash c1_hsh, Rice::Hash c2_hsh) {
    a_ = 0;
    b_ = 0;
    c_ = 0;
    d_ = 0;   
    populate_vect(c1_hsh, clust_1_);
    populate_vect(c2_hsh, clust_2_);
    //
    int max_clust_1 = 0;
    for(int i = 0; i < (int)clust_1_.size(); i++) {
	if(clust_1_[i] > max_clust_1) { 
	    max_clust_1 = clust_1_[i]; 
	}
    }
    int max_clust_2 = 0;
    for(int i = 0; i < (int)clust_2_.size(); i++) {
	if(clust_2_[i] > max_clust_2) {
	    max_clust_2 = clust_2_[i]; 
	}
    }    
    // set up clust_id => [id_1, id_2, ...]
    clust_map_1_.resize(max_clust_1+1);
    clust_map_2_.resize(max_clust_2+1);
    //
    for(int i = 0; i < (int)clust_1_.size(); i++) {
    	clust_map_1_[clust_1_[i]].push_back(i);
    }
    for(int i = 0; i < (int)clust_2_.size(); i++) {
    	clust_map_2_[clust_2_[i]].push_back(i);
    }
    //
    compute_confusion_matrix();    
}
/**
 * given a ruby hash, populate a vector of read_id as index, cluster_id as value
 */
void ConfusionMatrix::populate_vect(Rice::Hash &hsh, 
				    std::vector<int> &clust_v) {
    int len = hsh.size();
    clust_v.resize(len);
    //
    Rice::Hash::iterator it = hsh.begin();
    Rice::Hash::iterator it_end = hsh.end();
    int i = 0;
    for(; it != it_end; ++it) {
	Rice::Hash::Entry en(*it);
	int x = FIX2INT(en.key);
	int y = FIX2INT(en.value.value());
	clust_v[x] = y;
	i++;
    }
}
/**
 *
 */
void ConfusionMatrix::print_matrix() {
    std::cout<<a_<<"\t"<<b_<<"\t"<<c_<<"\t"<<d_<<std::endl;
}
/**
 * return ruby array with contents of confusion matrix: [a, b, c, d]
 */
Rice::Array ConfusionMatrix::get_confusion_matrix() {
    Rice::Array ary;
    ary.push(a_);
    ary.push(b_);
    ary.push(c_);
    ary.push(d_);
    return ary;
}
/**
 * compute confusion matrix entries a, b, c, and d
 */
void ConfusionMatrix::compute_confusion_matrix() {
    std::pair<int,int> v1 = int_and_diff(clust_1_, clust_map_2_);
    std::pair<int,int> v2 = int_and_diff(clust_2_, clust_map_1_);
    //
    int n = (int)clust_1_.size();
    a_ = v1.first;
    c_ = v1.second;
    d_ = v2.second;
    b_ = ((n*(n-1))/2) - (a_+c_+d_);
}
/**
 * return Rand index: (a+b)/(a+b+c+d)
 */
double ConfusionMatrix::get_rand_index() {
    return (double)(a_+b_)/(double)(a_+b_+c_+d_);
}
/**
 * return Jaccard index: a/(a+c+d)
 */
double ConfusionMatrix::get_jaccard_index() {
    return (double)(a_)/(double)(a_+c_+d_);
}
/**
 * returns Fowlkes-Mallows (FM) index: a/sqrt((a+c)*(a+d))
 */
double ConfusionMatrix::get_fm_index() {
    double d1 = (double)(a_+c_);
    double d2 = (double)(a_+d_);
    return (double)a_/sqrt(d1*d2);
}
/**
 * get counts of: <intersection, difference> between the vector of 
 * cluster assignments (A) and cluster assignment groupings (B)
 */
std::pair<int,int> ConfusionMatrix::int_and_diff(std::vector<int> clust_v, 
						 std::vector<std::vector<int>> clust_map) {    
    //
    int intsect = 0;
    int diff = 0;
    for(int i = 0; i < (int)clust_map.size(); i++) {
	//
	std::vector<int> vs = clust_map[i];
	int len = (int) vs.size();
	for(int i = 0; i < len; i++) {
	    int val_i = vs[i];
	    for(int j = 0; j < len; j++) {
		if(i < j) {
		    int val_j = vs[j];
		    bool t1 = clust_v[val_i] == clust_v[val_j];
		    if(t1) { intsect++; }
		    else { diff++; }
		}
	    }
	}
    }
    //
    return std::pair<int,int>(intsect, diff);
}
/**
 * compute confusion matrix in naive N**2 time, used for comparing
 * (i.e., sanity check) testing results 
 */
Rice::Array ConfusionMatrix::get_confusion_matrix_naive() {    
    int len = (int)clust_1_.size();
    int a = 0; int b = 0; int c = 0; int d = 0;
    for(int i = 0; i < len; i++) {
	for(int j = 0; j < len; j++) {
	    if(i >= j) { continue; }
	    bool t1 = (clust_1_[i] == clust_1_[j]);
	    bool t2 = (clust_2_[i] == clust_2_[j]);
	    if(t1 && t2) { a += 1; }
	    else if(!t1 && !t2) { b += 1; }
	    else if(!t1 && t2) { c += 1; }
	    else if(t1 && !t2) { d += 1; }
	    else {}
	}
    }
    //
    Rice::Array ary;
    ary.push(a);
    ary.push(b);
    ary.push(c);
    ary.push(d);
    return ary;
}
