from distutils.core import setup, Extension

module1 = Extension('_Corpus_classify', 
                        sources=['dbscan_classify_wrap.cxx', 
                                 'dbscan_classify.cpp',		
                                 'dbscan.cpp',
                                 'editing_distance.cpp',
                                ],
                      )

setup(name = 'Corpus_classify',	
        version = '0.1',
        author = 'HJH',
        description = 'Corpus Classify Based on DBScan and Edistance',
        ext_modules = [module1], 
        py_modules = ['Corpus_classify'], 
    )
