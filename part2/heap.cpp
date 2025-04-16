#include "heap.h"
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <optional>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <tuple>

TreeNode* buildTreeRec(const std::vector<std::optional<int>>& arr, size_t i) {
    if (i >= arr.size() || !arr[i].has_value())
        return nullptr;

    TreeNode* node = new TreeNode(arr[i].value());
    node->left = buildTreeRec(arr, 2 * i + 1);
    node->right = buildTreeRec(arr, 2 * i + 2);
    return node;
}

TreeNode* buildTree(const std::vector<std::optional<int>>& arr) {
    if (arr.empty() || !arr[0].has_value())
        return nullptr;

    return buildTreeRec(arr, 0);
}

// �������� ������������ ����
bool isHeap(const std::vector<int>& arr, bool isMaxheap) {
    size_t n = arr.size();
    if (n <= 1)
        return true;

    std::function<bool(int, int)> compare;
    if (isMaxheap)
        compare = std::greater_equal<int>();
    else
        compare = std::less_equal<int>();

    // ��������� ������ ���������� ����
    for (size_t i = 0; i <= (n / 2) - 1; ++i) {
        size_t leftChildIdx = 2 * i + 1;
        size_t rightChildIdx = 2 * i + 2;

        if (leftChildIdx < n && !compare(arr[i], arr[leftChildIdx]))
            return false;

        if (rightChildIdx < n && !compare(arr[i], arr[rightChildIdx]))
            return false;
    }
    return true;
}

// �������� �� ������ �������� ������
bool isCompleteTree(TreeNode* root) {
    if (!root)
        return true;

    std::queue<TreeNode*> q;
    q.push(root);
    bool nullEncountered = false; // ���������� �� ��� null ����

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (current == nullptr) {
            nullEncountered = true;
        }
        else {
            if (nullEncountered)
                return false;

            q.push(current->left);
            q.push(current->right);
        }
    }
    return true;
}

// ����������� ��������������� ��������
std::vector<int> mergeKSortedArrays(const std::vector<std::vector<int>>& arrays) {
    // ��������, ������_�������, ������_��������
    using Element = std::tuple<int, size_t, size_t>;

    std::priority_queue<Element, std::vector<Element>, std::greater<Element>> minHeap;

    for (size_t i = 0; i < arrays.size(); ++i) {
        if (!arrays[i].empty())
            minHeap.push({ arrays[i][0], i, 0 });
    }

    std::vector<int> result;

    // ���������� ����������� ��������� �� ����
    while (!minHeap.empty()) {
        auto [value, arrayIdx, elementIdx] = minHeap.top();
        minHeap.pop();

        result.push_back(value);

        // ���� � ������� ������� ���� ��������� �������, ��������� ��� � ����
        size_t nextElementIdx = elementIdx + 1;
        if (nextElementIdx < arrays[arrayIdx].size()) {
            minHeap.push({ arrays[arrayIdx][nextElementIdx], arrayIdx, nextElementIdx });
        }
    }

    return result;
}

// K ���������� �������
std::optional<int> kthSmallest(TreeNode* root, int k) {
    if (k <= 0) return std::nullopt;

    std::stack<TreeNode*> s;
    TreeNode* current = root;
    int count = 0;

    while (current || !s.empty()) {
        // ���� ����� �� �����, �������� ���� � ����
        while (current) {
            s.push(current);
            current = current->left;
        }

        // ������� ���� �� �����
        current = s.top();
        s.pop();

        count++;
        if (count == k)
            return current->val;

        // ��������� � ������� ���������
        current = current->right;
    }

    return std::nullopt;
}

// K ���������� �������
std::optional<int> kthLargest(TreeNode* root, int k) {
    if (k <= 0) return std::nullopt;

    std::stack<TreeNode*> s;
    TreeNode* current = root;
    int count = 0;

    while (current || !s.empty()) {
        // ���� ������ �� �����, �������� ���� � ����
        while (current) {
            s.push(current);
            current = current->right;
        }

        // ������� ���� �� �����
        current = s.top();
        s.pop();

        count++;
        if (count == k)
            return current->val;

        // ��������� � ������ ���������
        current = current->left;
    }
    return std::nullopt;
}

int calculateHaBF(TreeNode* node) {
    if (!node)
        return -1;

    int leftHeight = calculateHaBF(node->left);
    int rightHeight = calculateHaBF(node->right);

    // ������������ � ��������� balance factor
    node->balance_factor = leftHeight - rightHeight;

    // ���������� ������ �������� ����
    return 1 + std::max(leftHeight, rightHeight);
}

// ������ Balance factor
void setBalanceFactors(TreeNode* root) {
    calculateHaBF(root);
}

// �������������� � ���������� ������
TreeNode* invertTree(TreeNode* root) {
    if (!root)
        return nullptr;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        // ����� ������ � ������� ��������
        std::swap(current->left, current->right);

        if (current->left)
            q.push(current->left);

        if (current->right)
            q.push(current->right);
    }
    return root;
}