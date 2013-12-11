def qsort(L, start, end):
    if (start >= end): 
        return
    pivotIndex = partition(L, start, end)
    qsort(L, start, pivotIndex-1)
    qsort(L, pivotIndex+1, end)

def partition(L, start, end):
    if (start == end): 
        return start
    pivotValue=L[start]
    while (start < end):
        while (L[end] >= pivotValue and end > start):
            end=end-1
        L[start] = L[end]
        while (L[start] < pivotValue and end > start):
            start=start+1
        L[end]=L[start]
    L[start] = pivotValue
    return start

A=[3,5,3314,6,7,32]
B=[9, 23,13,45,5,6,9]
#AB=A+[1]+B
print A,B
qsort(A, 0, len(A)-1)
qsort(B, 0, len(B)-1)
print A, B
