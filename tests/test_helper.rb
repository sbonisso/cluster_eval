# minitest stuff
require 'rubygems'
gem 'minitest'
require 'minitest/autorun'

# minitest-reporters
require "minitest/reporters"
#Minitest::Reporters.use!
Minitest::Reporters.use! Minitest::Reporters::SpecReporter.new

def get_data_dir()
  "#{File.dirname(__FILE__)}/data/"
end

## if/when create a gem, remove this
$LOAD_PATH.unshift("#{File.dirname(__FILE__)}/../lib/")
$LOAD_PATH.unshift("#{File.dirname(__FILE__)}/../ext/")
