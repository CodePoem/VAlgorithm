#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

// 节点结构体
struct TreeNode{
    int value;
    TreeNode * left;
    TreeNode * right;
    TreeNode(int value):value(value),left(NULL),right(NULL){}
};

// 构建二叉树
void inertNode(TreeNode* node,int value){
    if(value <= node->value){
        if(!node->left){
            node->left = new TreeNode(value);
        }
        else{
            inertNode(node->left, value);
        }
    }
    else{
        if(!node->right){
            node->right = new TreeNode(value);
        }
        else{
            inertNode(node->right, value);
        }
    }
}

// 前序遍历递归实现
void preOrder(TreeNode* root){
    if(root){
        cout<<root->value<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// 前序遍历非递归实现
vector<int> preOrderStack(TreeNode *root){
    vector<int> result;
    stack<TreeNode*> stack;
    if(root == NULL){
        return result;
    }
    while (root || !stack.empty()) {
        while(root) {
            // 找到最左结点，并把路径上的所有结点一一访问并入栈
            // 先访问后入栈 确保了 根节点->左节点 顺序
            result.push_back(root->value);
            stack.push(root);
            root = root->left;
        }
        root = stack.top();
        stack.pop();
        // 访问右节点
        root = root->right;
    }
    return result;
}

// 中序遍历递归实现
void inOrder(TreeNode* root){
    if(root){
        inOrder(root->left);
        cout<<root->value<<" ";
        inOrder(root->right);
    }
}

// 中序遍历非递归实现
vector<int> inOrderStack(TreeNode* root){
    vector<int> result;
    stack<TreeNode*> stack;
    if(root == NULL){
        return result;
    }
    while (root || !stack.empty()) {
        while(root) {
            // 找到最左结点
            stack.push(root);
            root = root->left;
        }
        root = stack.top();
        stack.pop();
        // 先入栈后出栈访问 确保了 左节点->根节点 顺序
        result.push_back(root->value);
        // 访问右节点
        root = root->right;
    }
    return result;
}

// 后序遍历递归实现
void posOrder(TreeNode* root){
    if(root){
        posOrder(root->left);
        posOrder(root->right);
        cout<<root->value<<" ";
    }
}

// 后序遍历非递归实现
vector<int> posOrderStack(TreeNode* root){
    vector<int> result;
    stack<TreeNode*> stack;
    TreeNode* cur = root;
    TreeNode* pre = NULL;

    if (root == NULL) {
        return result;
    }

    while (cur) {
        // 走到最左节点
        stack.push(cur);
        cur = cur->left;
    }

    while (!stack.empty()) {
        cur = stack.top();
        if (cur->right == NULL || cur->right == pre) {
            // 当前结点的右孩子为空或者被访问过的时候则表示该结点可以被访问
            result.push_back(cur->value);
            pre = cur;
            stack.pop();
        } else {
            // 访问右节点
            cur = cur->right;
            while (cur)
            {
                stack.push(cur);
                cur = cur->left;
            }
        }
    }
    return result;
}

// 广度优先遍历
vector<int> broadOrder(TreeNode* root){
    vector<int> result;
    if(!root){
        return result;
    }
    queue<TreeNode*> qnodes;
    qnodes.push(root);
    while(!qnodes.empty()){
        TreeNode* temp=qnodes.front();
        qnodes.pop();
        result.push_back(temp->value);
        if(temp->left){
            qnodes.push(temp->left);
        }
        if(temp->right){
            qnodes.push(temp->right);
        }
    }
    return result;
}

int main(){
    TreeNode root(5);
    inertNode(&root, 4);
    inertNode(&root, 6);
    inertNode(&root, 3);
    inertNode(&root, 7);
    cout<<"preOrder is:";
    preOrder(&root);
    cout<<endl;
    cout<<"inOrder is:";
    inOrder(&root);
    cout<<endl;
    cout<<"PosOrder is:";
    posOrder(&root);
    cout<<endl;
    cout<<"PreOrder without recursion is:";
    vector<int> preOrderResult;
    preOrderResult = preOrderStack(&root);
    for (int i=0 ; i<preOrderResult.size(); i++) {
        cout<<preOrderResult[i]<<" ";
    }
    cout<<endl;
    cout<<"inOrder without recursion is:";
    vector<int> inOrderResult;
    inOrderResult = inOrderStack(&root);
    for (int i=0 ; i<inOrderResult.size(); i++) {
        cout<<inOrderResult[i]<<" ";
    }
    cout<<endl;
    cout<<"PosOrder without recursion is:";
    vector<int> posOrderResult;
    posOrderResult =posOrderStack(&root);
    for (int i=0 ; i<posOrderResult.size(); i++) {
        cout<<posOrderResult[i]<<" ";
    }
    cout<<endl;
    cout<<"BroadOrder is:";
    vector<int> broadOrderResult;
    broadOrderResult = broadOrder(&root);
    for (int i=0 ; i<broadOrderResult.size(); i++) {
        cout<<broadOrderResult[i]<<" ";
    }
}
