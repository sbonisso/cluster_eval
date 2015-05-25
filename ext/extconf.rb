require 'mkmf-rice'

$CPPFLAGS << ' -std=c++11'
$CPPFLAGS << ' -Wno-deprecated'

$warnflags = $warnflags.split("-Wimplicit-function-declaration").join(" ")
$warnflags = $warnflags.split("-Wdeclaration-after-statement").join(" ")

create_makefile('ClusterEval')
