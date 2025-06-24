#include <iostream>
using namespace std;

// Узел дерева
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;
};

// Создание нового узла
TreeNode* createNode(int key) {
    TreeNode* node = new TreeNode;
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Вставка по правилам BST
TreeNode* insert(TreeNode* root, int key) {
    if (!root)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

// Прямой обход (pre-order): корень → левое → правое
void preorder(TreeNode* root) {
    if (root) {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// Симметричный обход (in-order): левое → корень → правое
void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Обратный обход (post-order): левое → правое → корень
void postorder(TreeNode* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
    }
}

// Удаление узла с заданным значением
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return NULL;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Узел найден
        if (!root->left && !root->right) {
            delete root;
            return NULL;
        }
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        // Два потомка: ищем min в правом поддереве
        TreeNode* minNode = root->right;
        while (minNode->left)
            minNode = minNode->left;
        root->key = minNode->key;
        root->right = deleteNode(root->right, minNode->key);
    }
    return root;
}

// Удалить все отрицательные значения
TreeNode* deleteNegatives(TreeNode* root) {
    if (!root) return NULL;
    root->left = deleteNegatives(root->left);
    root->right = deleteNegatives(root->right);
    if (root->key < 0)
        root = deleteNode(root, root->key);
    return root;
}

// Очистка памяти
void freeTree(TreeNode* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

int main() {
    int data[] = { 10, -5, 20, -10, 0, 15, -3, 25, 7 };
    int n = sizeof(data) / sizeof(data[0]);

    TreeNode* root = NULL;

    // Создание дерева
    for (int i = 0; i < n; ++i)
        root = insert(root, data[i]);

    // Вывод исходного дерева
    cout << "Input Tree (pre-order): "; preorder(root); cout << endl;
    cout << "Input Tree (in-order):  "; inorder(root); cout << endl;
    cout << "Input Tree (post-order):"; postorder(root); cout << endl;

    // Удаление отрицательных значений
    root = deleteNegatives(root);

    // Повторный вывод
    cout << "\nUdalili otricatelnie kluchi:\n";
    cout << "pre-order: "; preorder(root); cout << endl;
    cout << "in-order:  "; inorder(root); cout << endl;
    cout << "post-order:"; postorder(root); cout << endl;

    // Очистка памяти
    freeTree(root);

    return 0;
}
