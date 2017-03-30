#coding:utf-8
import sys
reload(sys)
#sys.setdefaultencoding('utf8')
def Editing_d(str1,str2):
    str1 = str1.decode('utf-8')
    str2 = str2.decode('utf-8')
    m = len(str1)
    n = len(str2)
    mat = [[0 for col in xrange(n+1)] for row in xrange(m+1)]
    for i in xrange(m+1):
        mat[i][0] = i
    for j in xrange(1,n+1):
        mat[0][j] = j
    for i1 in xrange(1,m+1):
        for j1 in xrange(1,n+1):
            if str1[i1-1]==str2[j1-1]:
                cost = 0
            else:
                cost = 1
            mat[i1][j1] = min (mat[i1-1][j1]+1,mat[i1][j1-1]+1,mat[i1-1][j1-1]+cost)
    return mat[m][n]
