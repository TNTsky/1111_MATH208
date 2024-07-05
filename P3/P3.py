# Finding shortest path from the start cell s to the destination cell t in a maze
# date: 2022/11/02

import copy

# 四個相對方向的列表
direct = [(-1,0),(0,-1),(0,1),(1,0)]


# 根據輸入內容創建迷宮
def create():

    # 建立陣列
    size=input("\nSize: ").split(" ")
    size_x,size_y=int(size[0])+2,int(size[1])+2
    arr=[[" " for j in range(size_y)] for i in range(size_x)]

    # 填入起、終點以及障礙
    for i in range(int(size[0])):
        aaa=input(f'[{i+1}]: ').split(" ")
        for num in range(0,len(aaa)-1,2):
            arr[i+1][int(aaa[num])]=aaa[num+1]
            if aaa[num+1]=='s':
                s_x=i+1
                s_y=int(aaa[num])
            elif aaa[num+1]=='t':
                t_x=i+1
                t_y=int(aaa[num])

    # 增加外框
    for i in range(size_x):
        arr[i][0],arr[i][size_y-1]="x","x"
    for j in range(size_y):
        arr[0][j],arr[size_x-1][j]="x","x"

    # 回傳陣列與s,t之座標
    return(arr,size_x,size_y,s_x,s_y,t_x,t_y)


# 透過遞迴將所有可經的格子標上距離
def find(arr,xy,d):

    # 用於紀錄即將填入距離d之格子座標
    new_XY=[]
    for i in xy:
        x,y=i
        for dir in direct:
            X,Y=x+dir[0],y+dir[1]
            if arr[X][Y] ==' ':
                new_XY.append((X,Y))
    for i in new_XY:
        x,y=i
        arr[x][y]=str(d)

    # 若本次有格子進行填入(尚未全部填完)，傳入當前座標執行遞迴
    if new_XY:
        find(arr,new_XY,d+1)

    return(arr)


# 得到終點t的最短距離
def distant(arr,x,y):

    # 用於保存終點t之四周數字
    ddd=[]
    for dir in direct:
        X,Y=x+dir[0],y+dir[1]

        # 若出現起點s，則直接回傳距離為0 
        if arr[X][Y]=='s':
            return(0)
        elif arr[X][Y] not in [" ","x",'t']:
            ddd.append(arr[X][Y])

    # 回傳最小值(距離)
    D=min(ddd)
    return(int(D))


# 透過遞迴列印出所有最短路徑
def path(arr,x,y,d,Path,all):
    for dir in direct:
        X,Y=x+dir[0],y+dir[1]
        PPath=copy.deepcopy(Path)
        if arr[X][Y]=='s':
            PPath.insert(0,(X,Y))
            print(PPath)
            all.append(PPath)
        
        # 尚未回到起點s，傳入當前座標執行遞迴
        elif arr[X][Y]==str(d):
            PPath.insert(0,(X,Y))
            path(arr,X,Y,d-1,PPath,all)
    return(all)


# 將所有最短路徑之行經格子標上距離
def update(arr,Path):
    for i in Path:
        for j in range(1,len(i)-1):
            x,y=i[j]
            arr[x][y]=j
    return(arr)


# 印出指定陣列
def draw(arr):
    for i in range(size_x):
        for j in range(size_y):
            print(arr[i][j],end='\t')
        print("\n",end="")


# 重複執行，其中包含錯誤判斷
while(True):

    # 創建迷宮
    try:
        arr,size_x,size_y,s_x,s_y,t_x,t_y=create()
    except:
        print("輸入有誤，請重新輸入")
        continue
    
    # 排除輸入問題
    if [s_x,s_y]==[t_x,t_y]:
        print("s,t 不可在同位置，請重新輸入") 
        continue
    elif s_x>size_x-2 or s_y>size_y-2 or t_x>size_x-2 or t_y>size_y-2 :
        print("超出範圍啦，請重新輸入") 
        continue
    
    # 印出原始迷宮
    print("Maze:")
    draw(arr)

    # 先保存一份迷宮用於最後繪製最短路徑
    arr_1=copy.deepcopy(arr)

    # 將迷宮中所有格子填上距離
    arr=find(arr,[(s_x,s_y)],1)

    # 找出終點附近最段距離，若無即為無解
    try:
        d=distant(arr,t_x,t_y)
    except:
        print("此迷宮無解，請重新輸入")
        continue
    
    # 列出所有最段路徑
    print("Path:")
    Path=path(arr,t_x,t_y,d,[(t_x,t_y)],[])

    # 將最短路徑之距離填入先前保存之迷宮並印出
    arr_1=update(arr_1,Path)
    draw(arr_1)