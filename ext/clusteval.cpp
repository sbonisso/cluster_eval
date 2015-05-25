#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Hash.hpp"
#include "ConfusionMatrix.hpp"

using namespace Rice;

extern "C"

void Init_ClusterEval() 
{
    Module rb_cModule = define_module("ClusterEval");    
    Data_Type<ConfusionMatrix> rb_cConfusionMatrix = 
	define_class_under<ConfusionMatrix>(rb_cModule,"ConfusionMatrix")
	.define_constructor(Constructor<ConfusionMatrix>())
	//.define_constructor(Constructor<ConfusionMatrix,std::string,std::string>())
	.define_constructor(Constructor<ConfusionMatrix,Hash,Hash>())
	.define_method("get_rand_index", &ConfusionMatrix::get_rand_index)
	.define_method("get_jaccard_index", &ConfusionMatrix::get_jaccard_index)
	.define_method("get_fm_index", &ConfusionMatrix::get_fm_index)
	.define_method("print_matrix", &ConfusionMatrix::print_matrix);
}
