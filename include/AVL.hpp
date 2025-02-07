
#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <string>
#include <stdint.h>
#include <memory>
#include <queue>
#include <initializer_list>

#include <windows.h>

#include "Owe.h"

OWE_NAMESPACE_BEGIN
TREE_NAMESPACE_BEGIN

/// @brief AVL-自平衡二叉搜索树
/// @tparam _T 
template <typename _T>
class AVLTree {
public:
    enum class TraversalType {
        PREORDER,
        INORDER,
        POSTORDER
    };

    AVLTree(void) : m_root(nullptr), m_nodeNum(0) {}

    AVLTree(const std::initializer_list<_T>& _initList)
        : m_nodeNum(0) {
        for (const _T& value : _initList) {
            insert(value);
        }
    }

    /// @brief 插入节点
    /// @param _key 
    void insert(const _T& _key) {
        m_nodeNum++;
        m_root = m_insert(m_root, _key);
    }

    /// @brief 遍历节点（三种模式：前序、中序、后序）
    /// @param _type 
    void traverse(const TraversalType& _type) const {
        m_traverse(m_root, _type);
        std::cout << std::endl;
    }

    /// @brief 层级遍历
    /// @param  
    void levelOrderTraversal(void) const {
        m_levelOrderTraversal(m_root);
        std::cout << std::endl;
    }

    /// @brief 查找子节点
    /// @param _target 目标节点
    /// @return 如果找到目标节点，返回true；反之，返回false
    bool find(const _T& _target) const {
        return m_find(m_root, _target);
    }

    /// @brief 获取子节点路径
    /// @param _target 目标节点
    /// @return 从根节点到目标节点的路径
    std::string findPosition(const _T& _target) const {
        std::string path = m_findPosition(m_root, _target, "");
        return path;
    }

    /// @brief 删除节点
    /// @param _key 
    void erase(const _T& _key) {
        if (!find(_key)) {
            std::cerr << "No found node " << _key << "!\n";
            return;
        }
        m_nodeNum--;
        m_root = m_delete(m_root, _key);
    }

    /// @brief 打印树
    /// @param  
    void printTree(void) const {
        if (m_root == nullptr) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }
        std::cout << "Root: " << m_root->key << std::endl;
        std::cout << "Number of Nodes: " << getNodesNum() << std::endl;
        std::system("chcp 65001");
        m_printTree(m_root, "·", true);
    }

    /// @brief 获取深度
    /// @param  
    /// @return 该树的深度
    int32_t getDepth(void) const {
        return m_getDepth(m_root);
    }

    uint32_t getNodesNum(void) const {
        return m_nodeNum != 0 ? m_nodeNum : 1;
    }
private:
    struct Node {
        _T key;
        int32_t height;
        std::shared_ptr<Node> LNode;
        std::shared_ptr<Node> RNode;
        Node(_T _object)
            : key(_object), LNode(nullptr), RNode(nullptr), height(1) {
        }
    };

    std::shared_ptr<Node> m_root;

    uint32_t m_nodeNum;

    /// @brief 获取高度
    /// @param _node 
    /// @return 
    int32_t getHeight(const std::shared_ptr<Node>& _node) const {
        return _node ? _node->height : 0;
    }

    /// @brief 检查是否平衡
    /// @param _node 
    /// @return 
    int32_t getBalance(const std::shared_ptr<Node>& _node) const {
        return _node ? getHeight(_node->LNode) - getHeight(_node->RNode) : 0;
    }

    /// @brief 右旋
    /// @param y 
    /// @return 
    std::shared_ptr<Node> rightRotate(std::shared_ptr<Node>& y) {
        auto x = y->LNode;
        auto T2 = x->RNode;

        x->RNode = y;
        y->LNode = T2;

        y->height = std::max(getHeight(y->LNode), getHeight(y->RNode)) + 1;
        x->height = std::max(getHeight(x->LNode), getHeight(x->RNode)) + 1;

        return x;
    }

    /*
     *       x          y
     *      / \        / \
     *     y   3 =>  1   x
     *    / \            / \
     *   1   2          2   3
     */

     /// @brief 左旋
     /// @param x 
     /// @return 
    std::shared_ptr<Node> leftRotate(std::shared_ptr<Node>& x) {
        auto y = x->RNode;
        auto T2 = y->LNode;

        y->LNode = x;
        x->RNode = T2;

        x->height = std::max(getHeight(x->LNode), getHeight(x->RNode)) + 1;
        y->height = std::max(getHeight(y->LNode), getHeight(y->RNode)) + 1;

        return y;
    }

    /// @brief 插入操作
    /// @param _node 
    /// @param _object 
    /// @return 
    std::shared_ptr<Node> m_insert(std::shared_ptr<Node>& _node, const _T& _object) {
        if (_node == nullptr) {
            return std::make_shared<Node>(_object);
        }

        if (_object < _node->key) {
            _node->LNode = m_insert(_node->LNode, _object);
        }
#ifndef NO_REPEAT_INSERTION
        else if (_object >= _node->key)
#else
        else if (_object > _node->key)
#endif
        {
            _node->RNode = m_insert(_node->RNode, _object);
        }
        else {
            m_nodeNum--;
            return _node;
        }

        _node->height = std::max(getHeight(_node->LNode), getHeight(_node->RNode)) + 1;

        int32_t balance = getBalance(_node);

        if (balance > 1 && _object < _node->LNode->key) {
            return rightRotate(_node);
        }

        if (balance < -1 && _object > _node->RNode->key) {
            return leftRotate(_node);
        }

        if (balance > 1 && _object > _node->LNode->key) {
            _node->LNode = leftRotate(_node->LNode);
            return rightRotate(_node);
        }

        if (balance < -1 && _object < _node->RNode->key) {
            _node->RNode = rightRotate(_node->RNode);
            return leftRotate(_node);
        }

        return _node;
    }

    /// @brief 遍历
    /// @param _node 
    /// @param _traversalType 有三种模式：前序，中序，后序
    void m_traverse(const std::shared_ptr<Node>& _node, const TraversalType& _traversalType) const {
        if (_node == nullptr) return;

        if (_traversalType == TraversalType::PREORDER) {
            std::cout << _node->key << " ";
        }

        m_traverse(_node->LNode, _traversalType);

        if (_traversalType == TraversalType::INORDER) {
            std::cout << _node->key << " ";
        }

        m_traverse(_node->RNode, _traversalType);

        if (_traversalType == TraversalType::POSTORDER) {
            std::cout << _node->key << " ";
        }
    }

    /// @brief 层级遍历
    /// @param _node 
    void m_levelOrderTraversal(const std::shared_ptr<Node>& _node) const {
        if (_node == nullptr) return;
        std::queue<std::shared_ptr<Node>> queue;
        queue.push(_node);
        while (!queue.empty()) {
            auto current = queue.front();
            queue.pop();
            std::cout << current->key << " ";
            if (current->LNode != nullptr) queue.push(current->LNode);
            if (current->RNode != nullptr) queue.push(current->RNode);
        }
    }

    /// @brief 查找子节点
    /// @param _node 
    /// @param _target 目标节点
    /// @return 如果找到了该子节点，返回true，否则返回false
    bool m_find(const std::shared_ptr<Node>& _node, const _T& _target) const {
        if (_node == nullptr) return false;

        if (_node->key == _target) {
            return true;
        }

        if (_target < _node->key && _node->LNode != nullptr) {
            if (m_find(_node->LNode, _target)) {
                return true;
            }
        }

        if (_target > _node->key && _node->RNode != nullptr) {
            if (m_find(_node->RNode, _target)) {
                return true;
            }
        }

        return false;
    }

    /// @brief 查找子节点的路径
    /// @param _node 
    /// @param _target 目标子节点
    /// @param _currentPath 
    /// @return 返回从根节点到目标子节点的路径
    std::string m_findPosition(const std::shared_ptr<Node>& _node, const _T& _target, std::string _currentPath) const {
        if (_node == nullptr) return "";

        if (_node->key == _target) {
            return _currentPath + std::to_string(_node->key);
        }

        if (_target < _node->key && _node->LNode != nullptr) {
            std::string leftPath = m_findPosition(_node->LNode, _target, _currentPath + std::to_string(_node->key) + "->");
            if (!leftPath.empty()) {
                return leftPath;
            }
        }

        if (_target > _node->key && _node->RNode != nullptr) {
            std::string rightPath = m_findPosition(_node->RNode, _target, _currentPath + std::to_string(_node->key) + "->");
            if (!rightPath.empty()) {
                return rightPath;
            }
        }

        return "";
    }

    /// @brief 删除子节点
    /// @param _node 
    /// @param _key 节点值
    /// @return 
    std::shared_ptr<Node> m_delete(std::shared_ptr<Node>& _node, const _T& _key) {
        if (_node == nullptr) {
            return _node;
        }

        if (_key < _node->key) {
            _node->LNode = m_delete(_node->LNode, _key);
        }
        else if (_key > _node->key) {
            _node->RNode = m_delete(_node->RNode, _key);
        }
        else {
            if (_node->LNode == nullptr || _node->RNode == nullptr) {
                std::shared_ptr<Node> temp = _node->LNode ? _node->LNode : _node->RNode;

                if (temp == nullptr) {
                    _node.reset();
                }
                else {
                    _node = temp;
                }
            }
            else {
                std::shared_ptr<Node> temp = maxValueNode(_node->LNode);
                _node->key = temp->key;
                _node->LNode = m_delete(_node->LNode, temp->key);
            }
        }

        if (_node == nullptr) {
            return _node;
        }

        _node->height = 1 + std::max(getHeight(_node->LNode), getHeight(_node->RNode));

        int balance = getBalance(_node);

        if (balance > 1 && getBalance(_node->LNode) >= 0) {
            return rightRotate(_node);
        }

        if (balance > 1 && getBalance(_node->LNode) < 0) {
            _node->LNode = leftRotate(_node->LNode);
            return rightRotate(_node);
        }

        if (balance < -1 && getBalance(_node->RNode) <= 0) {
            return leftRotate(_node);
        }

        if (balance < -1 && getBalance(_node->RNode) > 0) {
            _node->RNode = rightRotate(_node->RNode);
            return leftRotate(_node);
        }

        return _node;
    }

    /// @brief 最小节点值
    /// @param _node 
    /// @return 
    std::shared_ptr<Node> minValueNode(const std::shared_ptr<Node>& _node) {
        std::shared_ptr<Node> current = _node;

        while (current->LNode != nullptr) {
            current = current->LNode;
        }

        return current;
    }

    /// @brief 最大节点值
    /// @param _node 
    /// @return 
    std::shared_ptr<Node> maxValueNode(const std::shared_ptr<Node>& _node) {
        std::shared_ptr<Node> current = _node;

        while (current->RNode != nullptr) {
            current = current->RNode;
        }

        return current;
    }

    /// @brief 打印树
    /// @param _node 
    /// @param _prefix 
    /// @param _isLeft 
    void m_printTree(const std::shared_ptr<Node>& _node, const std::string& _prefix, bool _isLeft) const {
        if (_node != nullptr) {
            std::cout << _prefix;

            std::cout << (_isLeft ? "├──" : "└──");

            std::cout << _node->key << std::endl;

            m_printTree(_node->LNode, _prefix + (_isLeft ? "│   " : "    "), true); // │
            m_printTree(_node->RNode, _prefix + (_isLeft ? "│   " : "    "), false);
        }
    }

    /// @brief 获取深度
    /// @param _node 
    /// @return 该树的深度
    int32_t m_getDepth(const std::shared_ptr<Node>& _node) const {
        if (_node == nullptr) {
            return 0;
        }
        return _node->height;
    }
};

TREE_NAMESPACE_END
OWE_NAMESPACE_END

#endif // AVL_HPP