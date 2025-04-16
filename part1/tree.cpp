#include "tree.h"
#include <vector>
#include <optional>
#include <queue>
#include <algorithm>
#include <stdexcept>


TreeNode* buildTreeRec(const std::vector<std::optional<int>>& arr, size_t i) {
    if (i >= arr.size() || !arr[i].has_value()) {
        return nullptr; // Индекс вне границ или значение nullopt
    }

    TreeNode* root = new TreeNode(arr[i].value());
    root->left = buildTreeRec(arr, 2 * i + 1);
    root->right = buildTreeRec(arr, 2 * i + 2);
    return root;
}

// Сравнение двух деревьев
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    if (p->val != q->val) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

int dfsMirror(TreeNode* left, TreeNode* right) {
    if (!left || !right) {
        return 0;
    }
    int count = (left->val == right->val) ? 1 : 0;
    count += dfsMirror(left->left, right->right);
    count += dfsMirror(left->right, right->left);
    return count;
}

// Восстановление бинарного дерева из массива
TreeNode* buildTree(const std::vector<std::optional<int>>& arr) {
    if (arr.empty() || !arr[0].has_value()) {
        return nullptr; // Пустой массив или корень null
    }
    return buildTreeRec(arr, 0);
}

// Проверка на симметричность бинарного дерева
bool isSymmetric(TreeNode* root) {
    if (!root) {
        return true;
    }
    std::queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);

    while (!q.empty()) {
        TreeNode* t1 = q.front(); q.pop();
        TreeNode* t2 = q.front(); q.pop();

        if (!t1 && !t2) continue;
        if (!t1 || !t2) return false;
        if (t1->val != t2->val) return false;

        // Добавляем в очередь в зеркальном порядке
        q.push(t1->left);
        q.push(t2->right);
        q.push(t1->right);
        q.push(t2->left);
    }
    return true;
}

// Поиск минимальной глубины
int minDepth(TreeNode* root) {
    if (!root) {
        return 0;
    }
    std::queue<std::pair<TreeNode*, int>> q; // узел и его глубина
    q.push({ root, 1 });

    while (!q.empty()) {
        TreeNode* currentNode = q.front().first;
        int currentDepth = q.front().second;
        q.pop();

        // Проверяем, является ли узел листом
        if (!currentNode->left && !currentNode->right) {
            return currentDepth;
        }

        // Добавляем дочерние узлы в очередь
        if (currentNode->left) {
            q.push({ currentNode->left, currentDepth + 1 });
        }
        if (currentNode->right) {
            q.push({ currentNode->right, currentDepth + 1 });
        }
    }
    return 0;
}

// Поиск произведения минимального и максимального элементов
long long maxMinProduct(TreeNode* root) {
    if (!root) {
        throw std::invalid_argument("Дерево не должно быть пустым");
    }

    // Поиск минимального элемента
    TreeNode* minNode = root;
    while (minNode->left) {
        minNode = minNode->left;
    }

    // Поиск максимального элемента
    TreeNode* maxNode = root;
    while (maxNode->right) {
        maxNode = maxNode->right;
    }

    return static_cast<long long>(minNode->val) * maxNode->val;
}

// Является ли дерево В поддеревом для А
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!subRoot) return true;
    if (!root) return false;
    if (isSameTree(root, subRoot)) {
        return true;
    }
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

// Зеркальные узлы
int countMirrorNodes(TreeNode* root) {
    if (!root) {
        return 0;
    }
    return dfsMirror(root->left, root->right);
}
