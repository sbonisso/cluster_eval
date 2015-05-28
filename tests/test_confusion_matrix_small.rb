require_relative 'test_helper'
require 'cluster_eval'


class TestConfusionMatrixSmall < MiniTest::Test
  #
  def setup
    @h1= {0 => 0, 1 => 0, 2 => 1, 3 => 1, 4 => 1, 5 => 2, 6 => 2, 7 => 2}
    @h2= {0 => 0, 1 => 1, 2 => 1, 3 => 1, 4 => 1, 5 => 1, 6 => 2, 7 => 2}    
  end  
  #
  # test tiny example
  #
  def test_small_confusion_matrix()
    cm = ClusterEval::ConfusionMatrix.new(@h1,@h2)
    cm_ary = cm.get_confusion_matrix
    assert_equal(4, cm_ary[0], 'Incorrect num for a')
    assert_equal(3, cm_ary[1], 'Incorrect num for b')
    assert_equal(7, cm_ary[2], 'Incorrect num for c')
    assert_equal(14, cm_ary[3], 'Incorrect num for d')
    #
    cm_naive = cm.get_confusion_matrix_naive
    assert_equal(cm_ary, cm_naive, 'confusion matrices do not agree')
  end
  #
  #
  def test_small_jaccard()
    cm = ClusterEval::ConfusionMatrix.new(@h1,@h2)
    ji_val = cm.get_jaccard_index
    assert_in_delta(0.28571, ji_val, 0.0001, 'incorrect Jaccard index')
  end
  #
  #
  def test_small_rand()
    cm = ClusterEval::ConfusionMatrix.new(@h1,@h2)
    rand_val = cm.get_rand_index
    assert_in_delta(0.64285, rand_val, 0.0001, 'incorrect Rand index')
  end
  #
  #
  def test_small_fm()
    cm = ClusterEval::ConfusionMatrix.new(@h1,@h2)
    fm_val = cm.get_fm_index
    assert_in_delta(0.45584, fm_val, 0.0001, 'incorrect FM index')
  end

end
