#include "BDT.h"
#include "parameters.h"
#include "TrackQualityTop.h"
#include "TrackQualityMemory.h"
#include "TracktoFeature.h"

void TrackQualityTop(const TTTrack& Track,score_arr_t score,score_t tree_scores[BDT::fn_classes(n_classes) * n_trees]){
    input_arr_t x;
    FeatureTransform(Track,x);
    #pragma HLS array_partition variable=score
    #pragma HLS array_partition variable=x
	#pragma HLS pipeline
	#pragma HLS unroll
    bdt.decision_function(x, score, tree_scores);
}
