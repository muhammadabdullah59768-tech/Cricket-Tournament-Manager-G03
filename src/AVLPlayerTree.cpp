#include "AVLPlayerTree.h"

AVLPlayerTree::AVLPlayerTree() {
    root = nullptr;
}

// Destructor: frees all nodes so there is no memory leak.
AVLPlayerTree::~AVLPlayerTree() {
    destroy(root);
}

// Delete the children first, then the node itself.
void AVLPlayerTree::destroy(AVLNode* node) {
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

// A missing child has height 0.
int AVLPlayerTree::getHeight(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Balance factor = left height - right height. Allowed values: -1, 0, 1.
int AVLPlayerTree::getBalanceFactor(AVLNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Height = 1 + height of the taller child.
void AVLPlayerTree::updateHeight(AVLNode* node) {
    int lh = getHeight(node->left);
    int rh = getHeight(node->right);
    if (lh > rh) node->height = 1 + lh;
    else node->height = 1 + rh;
}

// Used when the left side is too heavy. x moves up, y moves down-right.
AVLNode* AVLPlayerTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* middle = x->right;

    x->right = y;
    y->left = middle;

    updateHeight(y);   // y is lower now, so update it first
    updateHeight(x);
    return x;          // x is the new top
}

// Used when the right side is too heavy. Mirror of rotateRight.
AVLNode* AVLPlayerTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* middle = y->left;

    y->left = x;
    x->right = middle;

    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* AVLPlayerTree::insertNode(AVLNode* node, Player p, bool& inserted) {
    // 1. Normal BST insert
    if (node == nullptr) {
        inserted = true;
        return new AVLNode(p);
    }

    if (p.getID() < node->data.getID())
        node->left = insertNode(node->left, p, inserted);
    else if (p.getID() > node->data.getID())
        node->right = insertNode(node->right, p, inserted);
    else {
        inserted = false;   // duplicate ID
        return node;
    }

    // 2. Update height on the way back up
    updateHeight(node);

    // 3. Check balance and rotate if needed
    int balance = getBalanceFactor(node);

    if (balance > 1 && p.getID() < node->left->data.getID())       // LL
        return rotateRight(node);

    if (balance < -1 && p.getID() > node->right->data.getID())     // RR
        return rotateLeft(node);

    if (balance > 1 && p.getID() > node->left->data.getID()) {     // LR
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && p.getID() < node->right->data.getID()) {   // RL
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

bool AVLPlayerTree::insert(Player p) {
    bool inserted = false;
    root = insertNode(root, p, inserted);
    return inserted;
}

AVLNode* AVLPlayerTree::searchNode(AVLNode* node, int id) {
    if (node == nullptr) return nullptr;
    if (id == node->data.getID()) return node;
    if (id < node->data.getID()) return searchNode(node->left, id);
    return searchNode(node->right, id);
}

Player* AVLPlayerTree::searchByID(int id) {
    AVLNode* found = searchNode(root, id);
    if (found == nullptr) return nullptr;
    return &(found->data);
}

// In-order (left, node, right) gives sorted order.
void AVLPlayerTree::inOrder(AVLNode* node) {
    if (node == nullptr) return;
    inOrder(node->left);
    node->data.displayDetails();
    inOrder(node->right);
}

void AVLPlayerTree::displayInOrder() {
    if (root == nullptr) {
        cout << "No players in the tree." << endl;
        return;
    }
    inOrder(root);
}

int AVLPlayerTree::getTreeHeight() {
    return getHeight(root);
}