// Efficient data structure and algorithm for computing Huffman code
// date: 2022/12/28

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

string FileName = "Lipsum100000"; // 壓縮的文件名

// 霍夫曼樹的節點
struct Node{
    int wieght=0;  // 字元出現次數
    char c = '\0'; // 字元
    int H=0; // 父節點
    int l,r; // 左右子節點
};

// 字元的霍夫曼編碼
struct Code {
  char c; // 字元
  string code; // 編碼
};

// 用以存儲霍夫曼編碼
vector<Code> Huffman;

// 生成霍夫曼樹
void generate(Node* root, string code,Node Tree[]) {
    // 如果遞歸到了節點，則將字元和它的編碼加入 Huffman 容器中
    if (root->c||root->c==EOF) {
        Huffman.push_back(Code{root->c, code});
        return;
    }
    // 否則，遞迴左右子節點
    generate(&Tree[root->l], code + "0",Tree);
    generate(&Tree[root->r], code + "1",Tree);
}

int main() {
    ifstream file(FileName+".txt"); // 讀入文件
    int f[128] = {0}; // 初始化字元出現的次數
    // 並統計字元的出現次數
    char c;
    while (file.get(c)) {
        f[c]++;
    }

    // 計算需要建立的節點數
    int n=0;
    for (int i = 0; i < 128; i++)
        n+= f[i]? 1:0;
    
    n+=1; // 加上 EOF 的節點
    
    Node Tree[(n<<1)-1]; // 建立霍夫曼樹
    
    int cc=0;
    // 生成霍夫曼樹
    for (int i = 0; i < (n<<1)-1; i++)
        {
        // 將有出現過的字元放入節點
        if (cc<128){
            while (!f[cc])
                cc++;
            if (cc<128){
                Tree[i].c=cc;
                Tree[i].wieght=f[cc];
                cc++;
                }
            else
                i--;
        }
        // 如果 cc 等於 128，則生成 EOF 節點
        else if (cc==128){
            Tree[i].c=EOF;
            Tree[i].wieght=1;
            cc++;
        }
        
        // 生成非字元節點
        // 找出最小且未使用的兩個節點相加
        else{
            int a=0,b=0,min1,min2,minw1,minw2;
            while (Tree[a].H)
                a++;
            min1=a; minw1=Tree[a].wieght;
            for (int j = 0; j < i; j++){
                if (Tree[j].H)
                    continue;
                else
                    if (Tree[j].wieght<minw1)
                        min1=j; minw1=Tree[j].wieght;
            }
            Tree[min1].H=i;
            while (Tree[b].H)
                b++;
            min2=b; minw2=Tree[b].wieght;
            for (int j = 0; j < i; j++){
                if (Tree[j].H)
                    continue;
                else
                    if (Tree[j].wieght<minw2)
                        min2=j; minw2=Tree[j].wieght;
            }
            Tree[min2].H=i;
            Tree[i].l=min1;Tree[i].r=min2;
            Tree[i].wieght=minw1+minw2;
        }
    }
    
    int r=(n<<1)-2; // 計算跟節點位置
    generate(&Tree[r], "",Tree); // 以根節點為起點，生成霍夫曼編碼表


    // 打開要讀取與寫入的文件(壓縮)
    ifstream infile(FileName+".txt");
    ofstream outfile(FileName+"_encode.dat", ios::binary);
    unsigned char code = 0;// 用於儲存生成的霍夫曼編碼
    int count = 0; // 計算已經生成的位數
    while (infile.get(c)) {
        // 從霍夫曼編碼表中取出對應的，並寫入檔案
        for (auto pair : Huffman) {
            if (pair.c == c) {
                for (char ch : pair.code) {
                    code = code << 1;
                    if (ch == '1') 
                        code = code | 1;
                    count++;
                    if (count == 8) {
                        outfile.write((char*)&code, 1);
                        code = 0;
                        count = 0;
                    }
                }
                break;
            }
        }
    }
    // 在結尾寫入EOF的霍夫曼編碼
    for (auto pair :Huffman){
        if (pair.c==EOF){
            for (char ch : pair.code) {
                code = code << 1;
                if (ch == '1')
                    code = code | 1;
                count++;
                if (count == 8) {
                    outfile.write((char*)&code, 1);
                    code = 0;
                    count = 0;
                }
            }
        }
        break;
    }
    // 如果還有剩餘的bits，則將它們補到 8 bits寫入
    if (count > 0) {
        code = code << (8 - count);
        outfile.write((char*)&code, 1);
    }
    // 關閉輸入和輸出的檔案
    infile.close();
    outfile.close();


    // 開啟需讀取與寫入的檔案(解壓縮)
    ifstream iinfile(FileName+"_encode.dat", ios::binary);
    ofstream ooutfile(FileName+"_decode.txt");
    unsigned char b;
    string s;
    // 將指針 p 指向樹的根節點
    Node* p = &Tree[r];
    while (iinfile.read((char*)&b, 1)) {
        for (int i = 0; i < 8; i++) {
            if (b & 128) 
                s += '1';
            else 
                s += '0';
            b = b << 1;
            // 如果到達終止符號，就終止程式
            if (p->c==EOF)
                return 0;
            // 如果找到葉節點，就輸出葉節點的字元，並將指標指向根節點
            if (p->c) {
                ooutfile << p->c;
                p = &Tree[r];
                // 如果 s 的最後一個字元是 '0'，就將指標指向左子節點
                if (s.back() == '0') {
                    p = &Tree[p->l];
                }
                // 否則，如果 s 的最後一個字元是 '1'，就將指標指向右子節點
                else if(s.back() == '1') {
                    p = &Tree[p->r];
                }
                // 清空 s
                s.clear();
            }
            // 如果沒有到達葉節點，就繼續沿著子節點向下搜尋
            else {
                if (s.back() == '0') {
                    p = &Tree[p->l];
                }
                else if(s.back() == '1') {
                    p = &Tree[p->r];
                }
            }
        }
    }
    iinfile.close();
    ooutfile.close();
    return 0;
}