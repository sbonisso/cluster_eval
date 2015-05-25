require 'ClusterEval'

module ClusterEval
  
  class ConfusionMatrix
    #
    def initizlize(clst_h1, clst_h2)
      @cm = ClusterEval::ConfusionMatrix.new(clst_h1, clst_h2)      
    end
    #
    #
    #
    def get_rand_index()
      @cm.get_rand_index
    end
    #
    #
    #
    def get_jaccard_index()
      @cm.get_jaccard_index
    end
    
  end
  
end
