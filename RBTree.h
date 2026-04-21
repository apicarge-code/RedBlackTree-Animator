#pragma once
#include "imgui/imgui.h"

enum class RBColor { RED, BLACK };

struct RBNode {
    int data;
    RBColor color;
    RBNode *left, *right, *parent;

    RBNode(int val)
        : data(val), color(RBColor::RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
public:
    RBTree() : root(nullptr) {}
    ~RBTree() { if (root) { clear(root->left); clear(root->right); delete root; } }

    void insert(int val);
    void clear();
    void render(ImDrawList* draw_list, ImVec2 offset);

private:
    RBNode* root;

    void rotateLeft(RBNode* x);
    void rotateRight(RBNode* y);
    void insertFixup(RBNode* z);
    void clear(RBNode* node);

    int getHeight(RBNode* node);
    void renderNode(ImDrawList* draw_list, RBNode* node,
                    float x, float y, float level_width, float node_radius);
};
