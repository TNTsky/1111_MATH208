// Finding the maximum elements in the interval.
// date: 2022/12/21

#include<iostream>
#include<time.h>
#include <vector>
using namespace std;

vector<int> straight(int m,vector<int> v,vector<int> lj,vector<int> rj){
    vector<int> Max; // 儲存每個區間的最大值
    for (int i = 0; i < m; i++){
        int max = v[lj[i]]; // 將 max 的初始值設置為數組中的第一個元素
        for (int j = lj[i] ; j <= rj[i]; j++)
            max =  v[j]>max? v[j]:max; // 取出最大值
        Max.push_back(max); // 將最大值添加到結果列表中
    }
    return Max; // 返回結果列表
}

// 建立結構體，用於建立節點
struct Node{
	int l, r; // 節點的左右範圍
	int value; // 節點的值
	Node *left, *right; // 節點的左右子節點
};

void build(Node *rt, int l, int r,vector<int> v){
    // 初始化節點的左右子節點為空
    rt->left = NULL;
    rt->right = NULL;
	rt->l = l; rt->r = r; // 設置節點的左右範圍
	if(l == r){ //若範圍只包含一個數字
		rt->value = v[l]; // 設置節點的值
		return ; // 將函數退出
	}
	// 否則，建立左右子節點
	rt->left = new Node();
	rt->right = new Node();

	int m = (l + r) >> 1; // 求出節點的中間位置
	build(rt->left, l, m,v); // 建立左子節點
	build(rt->right, m + 1, r,v); // 建立右子節點
	rt->value = max(rt->left->value, rt->right->value); // 將節點的值設置為左右子節點的最大值
}

int query(Node *rt, int l, int r) {
    // 如果查詢的區間範圍與節點的左右範圍相同，則返回節點的值
    if (rt->l == l && rt->r == r) {
        return rt->value;
    }
    int m = (rt->l + rt->r) >> 1; // 求出節點的中間位置
    int Max = 0; // 初始化最大值為 0
    // 如果查詢的範圍在節點的左半部分
    if (r <= m) {
        Max = query(rt->left, l, r); // 在左子節點中查詢
    } 
    // 如果查詢的範圍在節點的右半部分
    else if (l > m) {
        Max = query(rt->right, l, r); // 在右子節點中查詢
    } 
    // 如果查詢的範圍被節點的區間所包含
    else {
        Max = max(query(rt->left, l, m), query(rt->right, m + 1, r)); // 在左右子節點中各自查詢並取最大值
    }
    return Max; // 返回最大值
}

int main(){
    srand(time(NULL)); // 生成隨機種子
    long long n; // 宣告數組總量n
    cout<<"n:";
    cin>>n; 
    vector<int> v; // 用於儲存數組
    for (int i = 0; i < n; i++)
        v.push_back(rand()); // 隨機生成數組內元素

    long long m; // 宣告待查詢的區間總數m
    cout<<"m:";
    cin>>m; 
    vector<int> lj,rj; // 用於儲存查詢範圍
    for (int i = 0; i < m; i++){
        int l,r;
        l = rand()%n; // 隨機生成查詢範圍的左端點
        r = rand()%(n-l)+l; // 隨機生成查詢範圍的右端點
        lj.push_back(l);
        rj.push_back(r);
    }

    // 紀錄直接比較大小的結果並輸出所需時間
    double START,END;
    START = clock();
    vector<int> MAX1 = straight(m,v,lj,rj);
	END = clock();
    cout <<"Straightforward:\n\t> "<< (END - START) / CLOCKS_PER_SEC<<"s" << endl;
    
    // 建立線段樹並輸出所需時間
    Node *tree = new Node(); // 宣告樹結構
    START = clock();
    build(tree,0,n-1,v);
	END = clock();
    cout <<"SegmentTree:\t(Build: "<< (END - START) / CLOCKS_PER_SEC<<"s)" << endl;

    // 紀錄透過線段樹查詢的結果並輸出所需時間
    vector<int> MAX2; // 用於儲存線段樹查詢的結果
    START = clock();
    for (long long i = 0; i < m; i++)
        MAX2.push_back(query(tree, lj[i], rj[i])); // 紀錄線段樹查詢的結果
	END = clock();
    cout <<"\t> "<< (END - START) / CLOCKS_PER_SEC<<"s" << endl;

    // 紀錄透過建立表查詢的結果並輸出所需時間
    START = clock();
    int **table = new int*[n];  //動態分配記憶體
    for (int i = 0; i < n; i++){
        table[i] = new int[n];
        table[i][i] = v[i];
        for (int j = i+1;j<n;j++)   //依序比較以建立此表
            table[i][j]= v[j]>table[i][j-1]? v[j]:table[i][j-1];
    }
	END = clock();
    cout <<"Table:\t\t(Build: "<< (END - START) / CLOCKS_PER_SEC<<"s)" << endl;

    START = clock();
    vector<int> MAX3; // 用於儲存查詢的結果
    for (int i = 0; i < m; i++)
        MAX3.push_back(table[lj[i]][rj[i]]); //直接從矩陣中取出結果
    END = clock();
    cout <<"\t> "<< (END - START) / CLOCKS_PER_SEC<<"s" << endl;
    for (int i = 0; i < n; i++) //釋放空間
        delete [] table[i];
    delete [] table;

    // 比較三者的結果是否一致
    if (MAX1==MAX2&&MAX2==MAX3)
        cout<<"Correct!!"<<endl;
    else
        cout<<"Incorrect!!"<<endl;
}