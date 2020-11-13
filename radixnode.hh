#ifndef RADIXNODE_HH
#define RADIXNODE_HH

#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <optional>

struct RadixNode {
    bool finalNode;
    std::vector<unsigned long> dirs;
    std::string content;
    std::unordered_map<char, RadixNode*> children;
    RadixNode* parent;

    RadixNode() = default;
    RadixNode(std::string s, RadixNode* p = 0):
        finalNode{false},
        content{s},
        parent{p} {}
    RadixNode(std::string s, unsigned long d):
        content(s),
        finalNode(true),
        parent{} {
        dirs = {d};
    }

    void add_child(RadixNode* child) {
        child->parent = this;
        children[child->content[0]] = child;
    }

    RadixNode* replace_parent(RadixNode* new_parent) {
        parent->add_child(new_parent);
        new_parent->add_child(this);
        return new_parent;
    }

    RadixNode* split(int i, std::optional<unsigned long> dir = std::nullopt) {
        RadixNode *node;
        if (dir.has_value())
            node = new RadixNode(content.substr(0, i), dir.value());
        else
            node = new RadixNode(content.substr(0, i));
        content = content.substr(i);
        return replace_parent(node);
    }
};

#endif