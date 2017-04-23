#coding:utf-8

from Corpus_classify import dbscan_classify

with open('test.txt','r ') as f:
    lst = f.readlines()
lst2 = [x.strip() for x in lst]
print dbscan_classify(lst2)