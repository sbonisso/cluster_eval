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
 * each ruby hash are pairs of {read_id => clust_id}
 */
ConfusionMatrix::ConfusionMatrix(Rice::Hash c1_hsh, Rice::Hash c2_hsh) {
    a_ = 0;
    b_ = 0;
    c_ = 0;
    d_ = 0;   
    populate_vect(c1_hsh, clust_1_);
    populate_vect(c2_hsh, clust_2_);
    int max_clust_1 = 0;
    for(int i = 0; i < (int)clust_1_.size(); i++) {
	if(clust_1_[i] > max_clust_1) { max_clust_1 = clust_1_[i]; }
	// std::cout<<clust_1_[i]<<" ";
    }
    // std::cout<<"\n";
    int max_clust_2 = 0;
    for(int i = 0; i < (int)clust_2_.size(); i++) {
	if(clust_2_[i] > max_clust_2) { max_clust_2 = clust_2_[i]; }
	// std::cout<<clust_2_[i]<<" ";
    }
    // std::cout<<"\n";
    // set up clust_id => [id_1, id_2, ...]
    clust_map_1_.resize(max_clust_1+1);
    clust_map_2_.resize(max_clust_2+1);
    // std::cout<<"MAX:\t"<<max_clust_1<<std::endl;
    for(int i = 0; i < (int)clust_1_.size(); i++) {
	// std::cout<<i<<"\t"<<clust_1_[i]<<"\n";
    	clust_map_1_[clust_1_[i]].push_back(i);
    }
    for(int i = 0; i < (int)clust_2_.size(); i++) {
    	clust_map_2_[clust_2_[i]].push_back(i);
    }
    // std::cout<<clust_map_1_<<std::endl;
    // std::cout<<clust_map_2_<<std::endl;

    compute_confusion_matrix();    
}
/**
 * 
 */
void ConfusionMatrix::populate_vect(Rice::Hash &hsh, 
				    std::vector<int> &clust_v) {
    int len = hsh.size();
    clust_v.resize(len);
    // std::cout<<"LEN:\t"<<len<<"\n";
    Rice::Hash::iterator it = hsh.begin();
    Rice::Hash::iterator it_end = hsh.end();
    int i = 0;
    for(; it != it_end; ++it) {
	Rice::Hash::Entry en(*it);
	int x = FIX2INT(en.key);
	int y = FIX2INT(en.value.value());
	//std::cout<<en.key<<"\t"<<en.value.value()<<"\t"<<x<<"\t"<<y<<"\n";
	//clust_v[i] = std::pair<int,int>(x,y);
	clust_v[x] = y;
	i++;
    }
}
/**
 * compute confusion matrix entries a, b, c, and d
 */
void ConfusionMatrix::compute_confusion_matrix() {
    std::pair<int,int> v1 = int_and_diff(clust_1_, clust_map_2_);
    std::pair<int,int> v2 = int_and_diff(clust_2_, clust_map_1_);
    //std::cout<<v1<<"\t"<<v2<<"\n";
    int n = (int)clust_1_.size();
    a_ = v1.first;
    c_ = v1.second;
    d_ = v2.first;
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
