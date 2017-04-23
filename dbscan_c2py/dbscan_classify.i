%module Corpus_classify
%{
#include "dbscan_classify.h"
%}

%include "std_string.i"
%include "std_vector.i"

namespace std {
%template(IntVector) vector<int>;
%template(StringVector) vector<string>;
}

%include "dbscan_classify.h"
