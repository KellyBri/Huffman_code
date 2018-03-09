// Huffman Coding
#include <stdio.h>
#include <stdlib.h>
#include <deque>
#include <algorithm>

using namespace std;

int answer[101][100];

struct huffman{
    int freq;
    int index;
    deque<int> num;
    huffman *left;
    huffman *right;
};
huffman *temp;
deque<huffman *> littleTree;
deque<int> code;

bool compare(huffman *a, huffman *b) {
    return a->freq<b->freq;
}

void assignTo_answer(huffman *ptr){
    int count, i=0;
    
    while (!ptr->num.empty()) {
        count=ptr->num.front();
        answer[ptr->index][i]=count;
        ptr->num.pop_front();
        i++;
    }
}

void inorder(huffman *ptr){
    
    code.push_back(0);
    if (ptr->left!=NULL) inorder(ptr->left);
    else code.pop_back();
    
    if (ptr->right!=NULL) {
        code.push_back(1);
        inorder(ptr->right);
    }
    ptr->num=code;
    assignTo_answer(ptr);
    if (!code.empty())code.pop_back();
}

int main() {
    
    int n, i, j;
    int f[101];
    
    scanf("%d",&n);
    for (i=0; i<=100; i++)
        for (j=0; j<=99; j++) answer[i][j]=9;
    
    
    //輸入頻率  把每個頻率都建成一個節點
    /*    freq,index
     /      \
     NULL    NULL
     */
    for (i=1; i<=n; i++) {
        scanf("%d",&f[i]);
        temp=new huffman;
        temp->freq=f[i];
        temp->index=i;
        temp->left=NULL;
        temp->right=NULL;
        littleTree.push_back(temp);
    }
    //排序後把兩個最小的取出來  合併成一個新節點
    for (i=1; i<=n-1; i++) {
        sort(littleTree.begin(), littleTree.end(), compare);
        temp=new huffman;
        temp->freq=littleTree[0]->freq+littleTree[1]->freq;
        temp->index=0;
        temp->left=littleTree[0];
        temp->right=littleTree[1];
        
        littleTree.pop_front();
        littleTree.pop_front();
        littleTree.push_back(temp);
    }//huffman tree = littleTree[0]
    
    inorder(littleTree[0]);
    
    printf("%d\n",n);
    for (i=1; i<=n; i++) {
        
        j=0;
        while (answer[i][j]!=9) {
            printf("%d",answer[i][j]);
            j++;
        }
        printf(" ");
    }
    
    return 0;
}