
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include<math.h>
using namespace std;

struct TreeNode *GetNewNode(int data[3][3]);
void addChild(TreeNode *node, int data[3][3]);
struct TreeNode
{
    int data[3][3];
    int fn;
    vector<TreeNode *> children;
};
TreeNode *root;
TreeNode *temp = root;
vector<TreeNode *> allNodes;
int flag1 = 0;
queue<TreeNode *>Q;
int cnt=0;
int no_of_function;

// vector<TreeNode *> childNodes;

map<int, TreeNode *> openList;
vector<TreeNode *> closedList;

int findFn(int puzzle[3][3]){
    int dist_manhat=0;
    int misplace=0;
    int goal[3][3] = {{1,2,3},
                      {4,5,6},
                      {7,8,0}};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(puzzle[i][j]!=0){
                 for(int k=0;k<3;k++){
                for(int l=0;l<3;l++){
                    
                    if (puzzle[i][j] == goal[k][l]){
                    int x=abs(i-k);
                    int y= abs(j-l);
                    dist_manhat=dist_manhat+(x+y);
                }
                }
            }
            }
           
           
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[i][j] != goal[i][j])
            {
                misplace++;
            }
        }
    }
    if(no_of_function==1){
        return misplace;
    }
    else if(no_of_function==2){
        return dist_manhat;
    }
    else if(no_of_function==3){
        return dist_manhat+misplace;
    }
    return dist_manhat+misplace;
    // return dist_manhat;
}
void getPos(int puzzle[3][3], int *posi, int *posj)
{
    int flag = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[i][j] == 0)
            {
                *posi = i;
                *posj = j;
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            break;
        }
    }
}
bool isVisited(TreeNode *node)
{
    int flagCheck = 0;
    for (int i = 0; i < allNodes.size(); i++)
    {
        // cout << "flagCheck===" << flagCheck;
        // cout << "\naniket\n";
        if (flagCheck == 0)
        {
            flagCheck = 1;
            // cout << "flagCheck1===" << flagCheck;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (allNodes[i]->data[j][k] != node->data[j][k])
                    {
                        flagCheck = 0;
                        break;
                    }
                }
                if (flagCheck == 0)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }
    if (flagCheck == 0)
    {
        allNodes.push_back(node);
        return false;
    }
    return true;
}

void up(TreeNode *temp, int puzzle[3][3], int posi, int posj)
{
    int newPuzzle[3][3];
    if (posi != 0)
    {

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                newPuzzle[i][j] = puzzle[i][j];
            }
        }
        int newPos = posi - 1;
        int temp = newPuzzle[newPos][posj];
        newPuzzle[newPos][posj] = 0;
        newPuzzle[posi][posj] = temp;
    }
    TreeNode *updatedPuzzle = GetNewNode(newPuzzle);
    if (!isVisited(updatedPuzzle))
    {
        cout << "up";
        addChild(temp, newPuzzle);
        Q.push(updatedPuzzle);
        cnt++;
        openList.insert(pair<int,TreeNode *>(findFn(newPuzzle),updatedPuzzle));
        
    }
    else{
        cout<<"visited!!!";
    }
}
void down(TreeNode *temp, int puzzle[3][3], int posi, int posj)
{
    int newPuzzle[3][3];
    if (posi != 2)
    {

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                newPuzzle[i][j] = puzzle[i][j];
            }
        }
        int newPos = posi + 1;
        int temp = newPuzzle[newPos][posj];
        newPuzzle[newPos][posj] = 0;
        newPuzzle[posi][posj] = temp;
    }
    TreeNode *updatedPuzzle = GetNewNode(newPuzzle);
    if (!isVisited(updatedPuzzle))
    {
        cout << "down";
        addChild(temp, newPuzzle);
        Q.push(updatedPuzzle);
        cnt++;
        openList.insert(pair<int,TreeNode *>(findFn(newPuzzle),updatedPuzzle));
        
    }
    else{
        cout<<"visited!!!";
    }
}
void right(TreeNode *temp, int puzzle[3][3], int posi, int posj)
{
    int newPuzzle[3][3];
    if (posj != 2)
    {

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                newPuzzle[i][j] = puzzle[i][j];
            }
        }
        int newPos = posj + 1;
        int temp = newPuzzle[posi][newPos];
        newPuzzle[posi][newPos] = 0;
        newPuzzle[posi][posj] = temp;
    }
    TreeNode *updatedPuzzle = GetNewNode(newPuzzle);

    if (!isVisited(updatedPuzzle))
    {
        cout << "right";
        addChild(temp, newPuzzle);
        Q.push(updatedPuzzle);
        openList.insert(pair<int,TreeNode *>(findFn(newPuzzle),updatedPuzzle));
        cnt++;
    }
    else{
        cout<<"visited!!!";
    }
}
void left(TreeNode *temp, int puzzle[3][3], int posi, int posj)
{
    int newPuzzle[3][3];
    if (posj != 0)
    {

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                newPuzzle[i][j] = puzzle[i][j];
            }
        }
        int newPos = posj - 1;
        int temp = newPuzzle[posi][newPos];
        newPuzzle[posi][newPos] = 0;
        newPuzzle[posi][posj] = temp;
    }
    TreeNode *updatedPuzzle = GetNewNode(newPuzzle);
    if (!isVisited(updatedPuzzle))
    {
        cout << "left";
        addChild(temp, newPuzzle);
        Q.push(updatedPuzzle);
        openList.insert(pair<int,TreeNode *>(findFn(newPuzzle),updatedPuzzle));
        cnt++;
    }
    else{
        cout<<"visited!!!";
    }
}
void findFunction(TreeNode *temp, int puzzle[3][3], int posi, int posj)
{
    switch (posi)
    {
    case 0:
        switch (posj)
        {
        case 0:
            right(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);
            
            break;
        case 1:
            right(temp, puzzle, posi, posj);
            left(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);

            break;
        case 2:
        left(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);
            
            

            break;
        default:
            break;
        }
        break;
    case 1:
        switch (posj)
        {
        case 0:
            right(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);

            break;
        case 1:
            right(temp, puzzle, posi, posj);
            left(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);

            break;
        case 2:

            left(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);
            break;
        default:
            break;
        }
        break;

    case 2:
        switch (posj)
        {
        case 0:
            right(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);

            break;
        case 1:
            
            right(temp, puzzle, posi, posj);
            left(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);

            break;
        case 2:
            left(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);

            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}
void printData(TreeNode *node)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << node->data[i][j];
        }
    }
    cout << "\n";
}
bool compareTwoArrays(TreeNode *node)
{
    int goal[3][3] = {{1,2,3},
                      {4,5,6},
                      {7,8,0}};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // cout << "\nnodeij=" << node->data[i][j];
            // cout << "\ngoalij=" << goal[i][j];
            if (node->data[i][j] != goal[i][j])
            {

                return false;
            }
        }
    }
    cout << "got answer!!!\n";
    cout<<"total state space="<<cnt;
    return true;
}

void checkAllPossibilties(TreeNode *temp, int *posi, int *posj)
{
    // while(!Q.empty())
    // {
        // cout << "comparing=" << !compareTwoArrays(temp->children[i]);
        while (!compareTwoArrays((*openList.begin()).second)&&flag1==0)
        {
            TreeNode *minNode=(*openList.begin()).second;
            openList.clear();
            getPos(minNode->data, posi, posj);
            cout<<"\nminnode=";
            printData(minNode);
            cout<<"\n";
            cout<<"children\n";
            findFunction(minNode, minNode->data, *posi, *posj);
            // sort(childNodes.begin(),childNodes.end());
            
            for (int j = 0; j < minNode->children.size(); j++)
            {
                printData(minNode->children[j]);
                cout<<"fn="<<findFn(minNode->children[j]->data)<<"\n";
                if (compareTwoArrays(minNode->children[j]))
                {
                    flag1 = 1;
                    break;
                }
                
            }
            cout<<"\n";
            if(flag1==1){
                    break;
                }
        }
        // Q.pop();
    // }
    
    
}

int main()
{
    int posi, posj,inversion=0;
    
    cout<<"choose heuristic function:\n"<<"1.misplace\n2.manhatton\n3.hamming\n";
    cin>>no_of_function;
    int puzzle[3][3] = {{1,2,3},
                        {4,5,6},
                        {0,7,8}};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for(int k=i;k<3;k++){
                for(int l=0;l<3;l++){
                    if(i==k&&l>j&&puzzle[k][l]!=0){
                        if(puzzle[i][j]>puzzle[k][l]){
                            // cout<<"inversion pair"<<puzzle[i][j]<<puzzle[k][l];
                            inversion++;
                        }
                    }
                    if(i!=k&&puzzle[k][l]!=0){
                        if(puzzle[i][j]>puzzle[k][l]){
                            // cout<<"inversion pair"<<puzzle[i][j]<<puzzle[k][l];
                            inversion++;
                        }
                    }
                }
            }
        }
    }
    if(inversion%2!=0){
        cout<<"Not Solvable";
    }
    else{
        cout<<"inversion="<<inversion;
        root = GetNewNode(puzzle);
    temp = root;
    allNodes.push_back(temp);
    // checkAllPossibilties(temp, &posi, &posj);

        cout << "root";
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {   
                
                cout << root->data[j][k];
                
            }
        }
        cout<<"\n";
    getPos(puzzle, &posi, &posj);
    cout<<"\nchildren\n";
    findFunction(temp, puzzle, posi, posj);
    
    for (int i = 0; i < root->children.size(); i++)
    {
        printData(root->children[i]);
        cout<<"fn="<<findFn(root->children[i]->data)<<"\n";
    }
    cout<<"\n";
    checkAllPossibilties(temp, &posi, &posj);
    }
    

    return 0;
}
// function to create new node
TreeNode *GetNewNode(int data[3][3])
{
    TreeNode *newNode = new TreeNode();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            newNode->data[i][j] = data[i][j];
        }
    }
    newNode->fn=findFn(data);
    return newNode;
}

// function to add a child to a specific node
void addChild(TreeNode *node, int data[3][3])
{
    TreeNode *newNode = GetNewNode(data);
    node->children.push_back(newNode);
}

