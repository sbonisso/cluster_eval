# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'cluster_eval/version'

Gem::Specification.new do |spec|
  spec.name          = "cluster_eval"
  spec.version       = ClusterEval::VERSION
  spec.authors       = ["sbonisso"]
  spec.email         = ["sbonisso@ucsd.edu"]

  # if spec.respond_to?(:metadata)
  #   spec.metadata['allowed_push_host'] = "TODO: Set to 'http://mygemserver.com' to prevent pushes to rubygems.org, or delete to allow pushes to any server."
  # end

  spec.summary       = %q{Evaluation of clusterings}
  spec.description   = %q{Evaluate partitionings of different clustering approaches. Provides different metrics to use.}
  spec.homepage      = "https://github.com/sbonisso/cluster_eval"
  spec.license       = "MIT"
  
  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "bin"
  #spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.executables = "cluster_eval"
  spec.require_paths = ["lib", "ext"]
  spec.extensions = ["ext/extconf.rb"]
  
  spec.add_dependency "thor", '~> 0.19'
  spec.add_dependency "rice", '~> 1.7'
  
  spec.add_development_dependency "bundler", "~> 1.8"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "minitest", "~> 5.4"
  spec.add_development_dependency "minitest-reporters", "~> 1.0"
end
