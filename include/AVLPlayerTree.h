#ifndef AVLPLAYERTREE_H
#define AVLPLAYERTREE_H

#include "Player.h"

// One box in the tree: one player + two child pointers.
class AVLNode {
public:
    Player data;
    AVLNode* left;
    AVLNode* right;
    int height;   // a leaf node has height 1

    AVLNode(Player p) : data(p), left(nullptr), right(nullptr), height(1) {}
};

class AVLPlayerTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node);
    int getBalanceFactor(AVLNode* node);
    void updateHeight(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insertNode(AVLNode* node, Player p, bool& inserted);
    AVLNode* searchNode(AVLNode* node, int id);
    void inOrder(AVLNode* node);
    void destroy(AVLNode* node);

public:
    AVLPlayerTree();
    ~AVLPlayerTree();

    bool insert(Player p);        // returns false if the ID already exists
    Player* searchByID(int id);   // returns nullptr if not found
    void displayInOrder();        // prints players sorted by ID
    int getTreeHeight();
};

#endif