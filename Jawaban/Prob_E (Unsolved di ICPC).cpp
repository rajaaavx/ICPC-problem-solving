#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <array>

using namespace std;

typedef struct node{
    array<int, 16> function;
}node;

int N, Q;
vector<node> segmentTree;
vector<char> operation;
vector<int> k;

node combineFunction(node& left, node& right){
    node result;
    for(int i = 0; i < 16; i++){
        result.function[i] = right.function[left.function[i]];
    }
    return result;
}

node buildNode(char operation, int number){
    node newNode;
    for(int i = 0; i < 16; i++){
        if(operation == '+'){
            newNode.function[i] = (i + number) % 16;
        }
        else{
            newNode.function[i] = i ^ number;
        }
    }
    return newNode;
}

void buildSegmentTree(int index, int left, int right){
    if(left == right){
        segmentTree[index] = buildNode(operation[left], k[left]);
        return;
    }
    
    int middle = (left + right) / 2;
    buildSegmentTree(index * 2, left, middle);
    buildSegmentTree(index * 2 + 1, middle + 1, right);

    segmentTree[index] = combineFunction(segmentTree[index * 2], segmentTree[index * 2 + 1]);
}

void updateModule(int index, int left, int right, int position, char operation, int number){
    if(left == right){
        segmentTree[index] = buildNode(operation, number);
        return;
    }

    int middle = (left + right) / 2;
    if(position <= middle){
        updateModule(index * 2, left, middle, position, operation, number);
    }
    else{
        updateModule(index * 2 + 1, middle + 1, right, position, operation, number);
    }

    segmentTree[index] = combineFunction(segmentTree[index * 2], segmentTree[index * 2 + 1]);
}

int main(){
    cin >> N >> Q;
    operation.resize(N);
    k.resize(N);
    segmentTree.resize(4 * N);

    for(int i = 0; i < N; i++){
        cin >> operation[i] >> k[i];
    }

    buildSegmentTree(1, 0, N - 1);

    for(int q = 0; q < Q; q++){
        int index;
        char newOperation;
        int newK;
        cin >> index >> newOperation>> newK;
        index = index - 1;

        updateModule(1, 0, N-1, index, newOperation, newK);
        cout << segmentTree[1].function[0] << endl;
    }

    return 0;
}