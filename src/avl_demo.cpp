#include <iostream>
#include "Player.h"
using namespace std;

class AVLNode {
public:
    Player data;
    AVLNode* left;
    AVLNode* right;
    int height;   // a leaf has height 1
    AVLNode(Player p) : data(p), left(nullptr), right(nullptr), height(1) {}
};

class AVLPlayerTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* n) {
        if (n == nullptr) return 0;
        return n->height;
    }

    int getBalance(AVLNode* n) {
        if (n == nullptr) return 0;
        return getHeight(n->left) - getHeight(n->right);
    }

    void updateHeight(AVLNode* n) {
        int lh = getHeight(n->left);
        int rh = getHeight(n->right);
        if (lh > rh) n->height = 1 + lh;
        else n->height = 1 + rh;
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);   // y is lower now, update it first
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* insertNode(AVLNode* n, Player p, bool& inserted) {
        if (n == nullptr) {
            inserted = true;
            return new AVLNode(p);
        }
        if (p.getID() < n->data.getID())
            n->left = insertNode(n->left, p, inserted);
        else if (p.getID() > n->data.getID())
            n->right = insertNode(n->right, p, inserted);
        else {
            inserted = false;   // duplicate ID
            return n;
        }

        updateHeight(n);
        int bal = getBalance(n);

        if (bal > 1 && p.getID() < n->left->data.getID())        // LL
            return rotateRight(n);
        if (bal < -1 && p.getID() > n->right->data.getID())      // RR
            return rotateLeft(n);
        if (bal > 1 && p.getID() > n->left->data.getID()) {      // LR
            n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        if (bal < -1 && p.getID() < n->right->data.getID()) {    // RL
            n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    void inOrder(AVLNode* n) {
        if (n == nullptr) return;
        inOrder(n->left);
        n->data.displayDetails();
        inOrder(n->right);
    }

    void destroy(AVLNode* n) {
        if (n == nullptr) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    AVLPlayerTree() { root = nullptr; }
    ~AVLPlayerTree() { destroy(root); }

    bool insert(Player p) {
        bool inserted = false;
        root = insertNode(root, p, inserted);
        return inserted;
    }

    Player* searchByID(int id) {
        AVLNode* cur = root;
        while (cur != nullptr) {
            if (id == cur->data.getID()) return &(cur->data);
            if (id < cur->data.getID()) cur = cur->left;
            else cur = cur->right;
        }
        return nullptr;
    }

    void displayInOrder() { inOrder(root); }
    int treeHeight() { return getHeight(root); }
};

int main() {
    AVLPlayerTree tree;
    tree.insert(Player(10, "Babar Azam", "Batsman"));
    tree.insert(Player(20, "Shaheen Afridi", "Bowler"));
    tree.insert(Player(30, "Mohammad Rizwan", "Wicketkeeper"));
    tree.insert(Player(40, "Shadab Khan", "All-rounder"));
    tree.insert(Player(50, "Fakhar Zaman", "Batsman"));
    tree.insert(Player(25, "Haris Rauf", "Bowler"));

    cout << "--- Players in sorted ID order ---" << endl;
    tree.displayInOrder();
    cout << "Tree height: " << tree.treeHeight() << endl;

    cout << "\n--- Search ID 30 ---" << endl;
    Player* p = tree.searchByID(30);
    if (p != nullptr) p->displayDetails();

    cout << "\n--- Search ID 99 ---" << endl;
    if (tree.searchByID(99) == nullptr) cout << "Player not found" << endl;

    cout << "\n--- Duplicate ID ---" << endl;
    if (!tree.insert(Player(30, "Fake", "Batsman")))
        cout << "Duplicate ID rejected" << endl;

    AVLPlayerTree big;
    for (int i = 1; i <= 1000; i++) big.insert(Player(i, "P", "Batsman"));
    cout << "\nHeight after 1000 sorted inserts: " << big.treeHeight() << endl;
    return 0;
}