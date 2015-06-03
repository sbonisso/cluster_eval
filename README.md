# ClusterEval

Evaluates clusterings of a dataset using a variety of scores.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'cluster_eval'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install cluster_eval

Note, you will need a version of g++ installed that is compatible with [C++11](https://gcc.gnu.org/projects/cxx0x.html).

## Usage

This can be used as a library, or through the installed command line program `cluster_eval`.

```
$ cluster_eval help eval 
Usage:
  cluster_eval eval [options]

Options:
  -a, [--cluster-file-a=CLUSTER_FILE_A]  # cluster file A
  -b, [--cluster-file-b=CLUSTER_FILE_B]  # cluster file B
  -y, [--type=TYPE]                      # type of index to compute
```

The `type` argument specifies the index to compute either the [Rand index](http://en.wikipedia.org/wiki/Rand_index), [Jaccard index](http://en.wikipedia.org/wiki/Jaccard_index), [Fowlkes-Mallows index](http://en.wikipedia.org/wiki/Fowlkes%E2%80%93Mallows_index), or all. 
It can take on values of: [rand/jaccard/fm/all]

Each cluster file must contain two columns of integers, the first column representing the sample ID, the second column the cluster ID. The sample IDs need not be sorted, but must contain all sample IDs from 0 to n samples.

For example if we have two files clust_a.tab and clust_b.tab, we could run the following:

```
$ cluster_eval eval -a clust_a.tab -b clust_b.tab -y rand
0.643
$ cluster_eval eval -a clust_a.tab -b clust_b.tab -y jaccard
0.286
$ cluster_eval eval -a clust_a.tab -b clust_b.tab -y fm
0.456
$ cluster_eval eval -a clust_a.tab -b clust_b.tab -y all
rand	jaccard	fm
0.643	0.286	0.456
```


## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release` to create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

1. Fork it ( https://github.com/[my-github-username]/cluster_eval/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request
