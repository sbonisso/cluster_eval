require_relative 'test_helper'
require 'cluster_eval'
#
# test two random (small) clusterings
#
class TestConfusionMatrixSmallRandom < MiniTest::Test
  #
  def setup
    @h1 = {0 => 0, 1 => 1, 2 => 2, 3 => 0, 4 => 3, 5 => 4, 6 => 5, 7 => 1}
    @h2 = {0 => 1, 1 => 1, 2 => 0, 3 => 0, 4 => 2, 5 => 2, 6 => 2, 7 => 2}
  end
  #
  #  
  def test_small_rand_confusion_matrix()
    cm = ClusterEval::ConfusionMatrix.new(@h1,@h2)
    cm_ary = cm.get_confusion_matrix
    assert_equal(0, cm_ary[0], 'Incorrect num for a')
    assert_equal(2, cm_ary[1], 'Incorrect num for b')
    assert_equal(8, cm_ary[2], 'Incorrect num for c')
    assert_equal(18, cm_ary[3], 'Incorrect num for d')
    #
    cm_naive = cm.get_confusion_matrix_naive
    assert_equal(cm_ary, cm_naive, 'confusion matrices do not agree')
  end
  #
  #
  def test_small_rand_jaccard()
    cm = ClusterEval::ConfusionMatrix.new(@h1,@h2)
    ji_val = cm.get_jaccard_index
    assert_in_delta(0.000, ji_val, 0.0001, 'incorrect Jaccard index')
  end
  #
  #
  def test_small_rand_rand()
    cm = ClusterEval::ConfusionMatrix.new(@h1,@h2)
    rand_val = cm.get_rand_index
    assert_in_delta(0.64285, rand_val, 0.0001, 'incorrect Rand index')
  end
  #
  #
  def test_small_rand_fm()
    cm = ClusterEval::ConfusionMatrix.new(@h1,@h2)
    fm_val = cm.get_fm_index
    assert_in_delta(0.0000, fm_val, 0.0001, 'incorrect FM index')
  end
  #
  #
  def test_small_rand_adj_rand()
    cm = ClusterEval::ConfusionMatrix.new(@h1,@h2)
    rand_val = cm.get_adj_rand_index
    assert_in_delta(-0.129032, rand_val, 0.0001, 'incorrect adjusted Rand index')
  end

end
