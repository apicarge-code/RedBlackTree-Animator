#include "RBTree.h"
#include <cmath>
#include <string>

void RBTree::rotateLeft(RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBTree::rotateRight(RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void RBTree::insertFixup(RBNode* z) {
    while (z->parent && z->parent->color == RBColor::RED) {
        if (!z->parent->parent) break;
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if (y && y->color == RBColor::RED) {
                z->parent->parent->color = RBColor::RED;
                z->parent->color = RBColor::BLACK;
                y->color = RBColor::BLACK;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(z);
                }
                z->parent->color = RBColor::BLACK;
                z->parent->parent->color = RBColor::RED;
                rotateRight(z->parent->parent);
            }
        } else {
            RBNode* y = z->parent->parent->left;
            if (y && y->color == RBColor::RED) {
                z->parent->parent->color = RBColor::RED;
                z->parent->color = RBColor::BLACK;
                y->color = RBColor::BLACK;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(z);
                }
                z->parent->color = RBColor::BLACK;
                z->parent->parent->color = RBColor::RED;
                rotateLeft(z->parent->parent);
            }
        }
    }
    root->color = RBColor::BLACK;
}

void RBTree::insert(int val) {
    RBNode* z = new RBNode(val);
    RBNode* y = nullptr;
    RBNode* x = root;
    while (x) {
        y = x;
        if (z->data < x->data) x = x->left;
        else if (z->data > x->data) x = x->right;
        else { delete z; return; }
    }
    z->parent = y;
    if (!y) root = z;
    else if (z->data < y->data) y->left = z;
    else y->right = z;
    insertFixup(z);
}

void RBTree::clear() {
    if (root) {
        clear(root->left);
        clear(root->right);
        delete root;
        root = nullptr;
    }
}

void RBTree::clear(RBNode* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

int RBTree::getHeight(RBNode* node) {
    if (!node) return 0;
    int left = getHeight(node->left);
    int right = getHeight(node->right);
    return 1 + (left > right ? left : right);
}

void RBTree::renderNode(ImDrawList* draw_list, RBNode* node, float x, float y, float level_width, float node_radius) {
    if (!node) return;

    ImU32 node_color = (node->color == RBColor::RED) ? IM_COL32(220, 60, 60, 255) : IM_COL32(40, 40, 40, 255);
    ImU32 outline_color = (node->color == RBColor::RED) ? IM_COL32(255, 100, 100, 255) : IM_COL32(120, 120, 120, 255);

    draw_list->AddCircleFilled(ImVec2(x, y), node_radius, node_color);
    draw_list->AddCircle(ImVec2(x, y), node_radius, outline_color, 32, 2.0f);

    std::string label = std::to_string(node->data);
    ImVec2 text_size = ImGui::CalcTextSize(label.c_str());
    draw_list->AddText(ImVec2(x - text_size.x * 0.5f, y - text_size.y * 0.5f), IM_COL32(255, 255, 255, 255), label.c_str());

    float child_y = y + 60.0f;
    float half_width = level_width * 0.5f;

    if (node->left) {
        float child_x = x - half_width;
        draw_list->AddLine(ImVec2(x, y), ImVec2(child_x, child_y), IM_COL32(180, 180, 180, 200), 2.0f);
        renderNode(draw_list, node->left, child_x, child_y, half_width, node_radius);
    }
    if (node->right) {
        float child_x = x + half_width;
        draw_list->AddLine(ImVec2(x, y), ImVec2(child_x, child_y), IM_COL32(180, 180, 180, 200), 2.0f);
        renderNode(draw_list, node->right, child_x, child_y, half_width, node_radius);
    }
}

void RBTree::render(ImDrawList* draw_list, ImVec2 offset) {
    if (!root) {
        draw_list->AddText(ImVec2(offset.x - 100, 60.0f), IM_COL32(150, 150, 150, 255), "Insert a value to begin");
        return;
    }

    int height = getHeight(root);
    float start_x = offset.x; // 水平中心
    float start_y = 80.0f; // 从屏幕上方80像素开始
    float level_width = 200.0f;

    if (height > 3) {
        level_width = 200.0f * std::pow(2.0f, height - 3);
    }

    renderNode(draw_list, root, start_x, start_y, level_width, 22.0f);
}
