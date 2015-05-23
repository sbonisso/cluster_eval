# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'cluster_eval/version'

Gem::Specification.new do |spec|
  spec.name          = "cluster_eval"
  spec.version       = ClusterEval::VERSION
  spec.authors       = ["TODO: Write your name"]
  spec.email         = ["stefano.rb@gmail.com"]

  # if spec.respond_to?(:metadata)
  #   spec.metadata['allowed_push_host'] = "TODO: Set to 'http://mygemserver.com' to prevent pushes to rubygems.org, or delete to allow pushes to any server."
  # end

  spec.summary       = %q{Evaluation of clusterings}
  spec.description   = %q{Evaluate partitionings of different clustering approaches. Provides different metrics to use.}
  spec.homepage      = "https://github.com/sbonisso/cluster_eval"
  spec.license       = "MIT"
  
  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "bin"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  
  spec.add_dependency "thor", '~> 0.19'
  
  spec.add_development_dependency "bundler", "~> 1.8"
  spec.add_development_dependency "rake", "~> 10.0"
end
