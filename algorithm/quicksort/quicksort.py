def qsort(L):
    n=len(L)
    while n<=1:
        return L
    p_idx=n/2
    pivot=L[p_idx]
    less=[]; greater=[]
    del L[p_idx]
    for x in L:
        if x<=pivot:
            less.append(x)
        else:
            greater.append(x)
    L=qsort(less)+[pivot]+qsort(greater)       
    return L




A=[3,5,3314,6,7,32]
B=[9, 23,13,45,5,6,9]
#AB=A+[1]+B
RetA = qsort(A)
RetB = qsort(B)
print A, RetA, B, RetB
