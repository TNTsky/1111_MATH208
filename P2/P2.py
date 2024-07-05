# Implement sorting algorithms and compare their performances.
# date: 2022/10/13

import random
import copy
import time
import matplotlib.pyplot as plt

data=[]
N_list=[1000,2000,5000,10000]
func_list=['QuickSort','HeapSort','MergeSort','SelectionSort','InsertionSort']
color=['red','orange','green','blue','purple']
for func in func_list:
    globals()[func+'_time']=[]

def InsertionSort(data1):
    n = len(data1)
    for i in range(n-1):
        while i >=0 and data1[i+1] < data1[i] :
                data1[i],data1[i+1] = data1[i+1],data1[i]
                i -= 1
    return data1

def SelectionSort(data1):
    n = len(data1)
    for i in range(len(data1)):
        min = i
        for j in range(i+1, n):
            if data1[j] < data1[min]:
                min = j
        if min != i:
            data1[i], data1[min] = data1[min], data1[i]
    return data1   

def QuickSort(data1, left, right):
    if left >= right :
        return
    i = left
    j = right
    key = data1[left]
    while i != j:                  
        while data1[j] > key and i < j:
            j -= 1
        while data1[i] <= key and i < j:
            i += 1
        if i < j:  
            data1[i], data1[j] = data1[j], data1[i] 
    data1[left],data1[i] = data1[i],data1[left]
    QuickSort(data1, left, i-1)
    QuickSort(data1, i+1, right)

def merge(left, right):
    output = []
    while left and right:
        if left[0] <= right[0]:
            output.append(left.pop(0))
        else:
            output.append(right.pop(0))
    if left:
        output += left
    if right:
        output += right
    return output

def MergeSort(date1):
    if len(date1) < 2:
        return date1
    mid = len(date1)//2
    left = date1[:mid]
    right = date1[mid:]
    return merge(MergeSort(left),MergeSort(right))

def HeapSort(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        maxHeapify(arr, n, i)
    for i in range(n-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        maxHeapify(arr, i, 0)
    return(arr)

def maxHeapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2
    if l < n and arr[i] < arr[l]:
        largest = l
    if r < n and arr[largest] < arr[r]:
        largest = r
    if largest != i:
        arr[i],arr[largest] = arr[largest],arr[i]
        maxHeapify(arr, n, largest)

def check(dd):
    for i in range(len(dd)-1):
        if dd[i]>dd[i+1]:
            return(False)
    return(True)

input=input('請輸入:\'排序算法執行數\' \'數列總量\' (可選)\'數列最大總量\' \'重複執行之間格\'\n')
input=input.split(" ")
FUN,N=int(input[0]),int(input[1])
if len(input)<3:
    print(f"\n N = {N}")
    data = [random.randint(-10000,10000) for i in range(N)]
    for i in range(FUN):
        print(f'{func_list[i]}')
        DATA=copy.deepcopy(data)
        if func_list[i]=="QuickSort":
            start = time.process_time()
            globals()[func_list[i]](DATA,0,len(DATA)-1)
        elif func_list[i]=="MergeSort":
            start = time.process_time()
            DATA=globals()[func_list[i]](DATA)
        else:
            start = time.process_time()
            globals()[func_list[i]](DATA)
        end = time.process_time()
        print(f"\t%.3fms \t{check(DATA)} "%((end-start)*1000))
        (globals()[func_list[i]+'_time']).append((end-start)*1000)
else:
    MAX,step=int(input[2]),int(input[3]) 
    for x in range(N,MAX+1,step):
        print(f"\n <N = {x}>")
        data = [random.randint(-10000,10000) for i in range(x)]
        for i in range(FUN):
            print(f'{func_list[i]}')
            DATA=copy.deepcopy(data)
            if func_list[i]=="QuickSort":
                start = time.process_time()
                globals()[func_list[i]](DATA,0,len(DATA)-1)
            elif func_list[i]=="MergeSort":
                start = time.process_time()
                DATA=globals()[func_list[i]](DATA)
            else:
                start = time.process_time()
                globals()[func_list[i]](DATA)
            end = time.process_time()
            print(f"\t%.3fms \t{check(DATA)} "%((end-start)*1000))
            (globals()[func_list[i]+'_time']).append((end-start)*1000)
    for i in range(FUN-1,-1,-1):
        plt.plot(range(N,MAX+1,step),globals()[f'{func_list[i]}_time'],label=func_list[i])
    plt.ylabel('(ms)')
    plt.xlabel('N') 
    plt.title("Performances")
    plt.legend()
    plt.show()