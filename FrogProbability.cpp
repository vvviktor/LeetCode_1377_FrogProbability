#include<vector>
#include<memory>
#include<iostream>

class Solution {
    struct TreeNode {
        TreeNode(int id) : id(id) {}
        int id = 0;
        int color = 0;
        std::vector<TreeNode*> neighbours;
    };

public:
    double frogPosition(int n, std::vector<std::vector<int>>& edges, int t, int target) {        
        nodes_ = std::vector<std::unique_ptr<TreeNode>>(n + 1);
        if (edges.empty()) {
            if (nodes_.size() > 1 && target == 1) {
                return 1;
            }
            else {
                return 0;
            }
        }
        BuildTree(edges);
        return Jump(nodes_[1].get(), t, 1, target, nullptr);
    }

private:
    std::vector<std::unique_ptr<TreeNode>> nodes_;

    void BuildTree(std::vector<std::vector<int>>& edges) {
        for (const auto& edge : edges) {
            if (!nodes_[edge[0]]) {
                nodes_[edge[0]] = std::unique_ptr<TreeNode>(new TreeNode(edge[0]));
            }
            if (!nodes_[edge[1]]) {
                nodes_[edge[1]] = std::unique_ptr<TreeNode>(new TreeNode(edge[1]));
            }
            nodes_[edge[0]]->neighbours.push_back(nodes_[edge[1]].get());
            nodes_[edge[1]]->neighbours.push_back(nodes_[edge[0]].get());
        }
    }

    double Jump(TreeNode* node, int jumps, double chanse, int target, TreeNode* parent) {
        if (node->color == -2 || jumps < 0) {
            return 0;
        }
        if (node->id == target) {
            if (parent != nullptr) {
                if (node->neighbours.size() > 1) {
                    return jumps == 0 ? chanse : 0;
                }
                else {
                    return chanse;
                }
            } 
            else {
                if (!node->neighbours.empty()) {
                    return jumps == 0 ? chanse : 0;
                }
                else {
                    return chanse;
                }
            }
        }        
        double ret = 0;
        if (node->color == 0) {
            int divider = parent != nullptr ? node->neighbours.size() - 1 : node->neighbours.size();
            for (auto& next_node : node->neighbours) {
                if (next_node == parent || !next_node) {
                    continue;
                }
                ret = Jump(next_node, jumps - 1, chanse / divider, target, node);
                if (ret != 0) {
                    break;
                }
            }
            node->color = -2;
        }
        return ret;
    }
};

int main() {
    std::vector<std::vector<int>> test{{2, 1},{3, 2},{4, 1},{5, 1},{6, 4},{7, 1},{8, 7}};
    Solution s;
    std::cout << s.frogPosition(8, test, 7, 7) << '\n';
}