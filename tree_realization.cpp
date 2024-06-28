#include <iostream>
#include <queue>
//
// Created by Lenya on 26.06.2024.
//
template<typename T>
class Tree{
private:
    struct Node{
        Node* left;
        Node* right;
        Node* parent;
        T value;
        explicit Node(T value_) : value(value_), left(nullptr), right(nullptr), parent(nullptr){}
        Node* Get_left() const{
            if(left != nullptr)
                return left;
            else throw std::invalid_argument("Node haven't left node");
        }
        Node* Get_parent() const{
            if(parent != nullptr)
                return parent;
            else throw std::invalid_argument("Node haven't parent node");
        }
        Node* Get_right() const{
            if(right != nullptr)
                return right;
            else throw std::invalid_argument("Node haven't right node");
        }
        T Get_value() const{
            return value;
        }
    };
    void Destruct_Order(Node* node){
        if(node != nullptr){
            Destruct_Order(node->left);
            Destruct_Order(node->right);
            delete node;
        }
    }
    void Count_Order(Node* node, size_t& size_){
        if(node != nullptr){
            Count_Order(node->left, size_);
            Count_Order(node->right, size_);
            size_++;
        }
    }
    void Custom_Order_Stream_Output(Node* node, std::ostream& out, char* instructions) const{
        if (node != nullptr) {
            for(size_t i = 0; i < 3; i++){
                if(instructions[i] == 'K'){
                    out << node->value << " ";
                }
                else if(instructions[i] == 'L'){
                    Custom_Order_Stream_Output(node->left, out, instructions);
                }
                else if(instructions[i] == 'P'){
                    Custom_Order_Stream_Output(node->right, out, instructions);
                }
            }
        }
    }

    bool Check_Instruction(char* instructions){
        bool first = true, second = true, third = true;
        for(size_t i = 0; i < 3; i++){
            if(instructions[i] == 'K'){
                if(first)
                    return false;
                first = true;
            }
            else if(instructions[i] == 'L'){
                if(second)
                    return false;
                second = true;
            }
            else if(instructions[i] == 'P'){
                if(third)
                    return false;
                third = true;
            }
            return false;
        }
        return true;
    }
    void Order_Array(Node* node, T* array, size_t& i) const{
        if(node != nullptr){
            Order_Array(node->left, array, i);
            array[i] = node->value;
            i++;
            Order_Array(node->right, array, i);
        }
    }
    Node* root;
    size_t size;

public:
    Tree() : root(nullptr), size(0){}
    Tree(T* array, size_t size_) {
        size = 0;
        for(size_t i = 0; i < size_; i++){
            Append(array[i]);
        }
        if(size == 0){
            root = nullptr;
        }
    }
    Tree(const Tree& tree){
        size = 0;
        T* array = tree.Get_Array();
        for(size_t i = 0; i < tree.size; i++){
            Append(array[i]);
        }
        if(size == 0){
            root = nullptr;
        }
    }
    ~Tree(){
        Destruct_Order(root);
    }
    Node* Get_Root() const{
        return root;
    }
    size_t Get_Size() const{
        return size;
    }
    size_t Get_Count_Sub_Tree(Node* node){
        size_t size_ = 0;
        Count_Order(node, size_);
        return size_;
    }
    T* Get_Array() const{
        T* array = new T[size];
        size_t i = 0;
        Order_Array(root, array, i);
        return array;
    }
    T Get_Max() const{
        Node* now = root;
        while (true){
            if(now->right == nullptr){
                break;
            }
            now = now->right;
        }
        return now->value;
    }
    T Get_Min() const{
        Node* now = root;
        while (true){
            if(now->left == nullptr){
                break;
            }
            now = now->left;
        }
        return now->value;
    }
    Node* Find(T value){
        Node* now = root;
        while(true){
            if(now == nullptr){
                break;
            }
            else if(now->value == value){
                return now;
            }
            else if(now->value > value){
                now = now->left;
            }
            else if(now->value < value){
                now = now->right;
            }
        }
        return nullptr;
    }
    void Append(T value){
        if(size == 0){
            root = new Node(value);
        }
        else{
            Node* now = root;
            Node* parent = root;
            while(now != nullptr) {
                parent = now;
                if (value > now->value) {
                    now = now->right;
                } else {
                    now = now->left;
                }
            }
            now = new Node(value);
            if (value > parent->value) {
                parent->right = now;
                now->parent = parent;
            } else {
                parent->left = now;
                now->parent = parent;
            }
        }
        size++;
    }
    void Merge(Tree<T> tree){
        T* array = tree.Get_Array();
        for(size_t i = 0; i < tree.size; i++){
            Append(array[i]);
        }
    }

    Tree<T>* Sub_Tree(Node* node){
        T* array = new T[Get_Count_Sub_Tree(node)];
        size_t size_ = 0;
        Order_Array(node, array, size_);
        Tree<T>* new_tree = new Tree(array, size_);
        return new_tree;
    }

    void Print_Tree_By_Level() const {
        if (root == nullptr) return;
        std::queue<Node*> nodesQueue;
        nodesQueue.push(root);

        while (!nodesQueue.empty()) {
            int levelSize = nodesQueue.size();
            while (levelSize > 0) {
                Node* node = nodesQueue.front();
                nodesQueue.pop();

                std::cout << node->value << " ";

                if (node->left != nullptr) nodesQueue.push(node->left);
                if (node->right != nullptr) nodesQueue.push(node->right);

                levelSize--;
            }
            std::cout << std::endl;
        }
    }
    void Delete(T value){
        Node* node = Find(value);
        if(node->left == nullptr && node->right == nullptr){
            if(node->parent != nullptr){
                if(node->parent->right == node){
                    node->parent->right = nullptr;
                }
                else if(node->parent->left == node){
                    node->parent->left = nullptr;
                }
            }
            else {
                root = nullptr;
            }
            delete node;
        }
        else if(node->left == nullptr && node->right != nullptr){
            if(node->parent != nullptr){
                if(node->parent->right == node){
                    node->right->parent = node->parent;
                    node->parent->right = node->right;
                }
                else{
                    node->right->parent = node->parent;
                    node->parent->left = node->right;
                }
            }
            else {
                root->right->parent = nullptr;
                root = root->right;
            }
            delete node;
        }
        else if(node->left != nullptr && node->right == nullptr){
            if(node->parent != nullptr){
                if(node->parent->right == node){
                    node->left->parent = node->parent;
                    node->parent->right = node->left;
                }
                else{
                    node->left->parent = node->parent;
                    node->parent->left = node->left;
                }
            }
            else {
                root->left->parent = nullptr;
                root = root->left;
            }
            delete node;
        }
        else{
            Node *now = node->right;
            while (now->left != nullptr) {
                now = now->left;
            }
            if(now->parent == node){
                if(now->right == nullptr){
                    node->right = nullptr;
                    node->value = now->value;
                    delete now;
                }
                else{
                    node->right = now->right;
                    now->right->parent = now->parent;
                    node->value = now->value;
                    delete now;
                }
            }
            else{
                if(now->right == nullptr){
                    now->parent->left = nullptr;
                    node->value = now->value;
                    delete now;
                }
                else{
                    now->parent->left = now->right;
                    now->right->parent = now->parent;
                    node->value = now->value;
                    delete now;
                }
            }
        }
        size--;
    }

    void Custom_Print(std::ostream& out, char* instructions){
        if(Check_Instruction(instructions)){
            Custom_Order_Stream_Output(root, out, instructions);
        }
        else{
            throw std::invalid_argument("Invalid instructions");
        }
    }

    template<typename U>
    friend std::ostream& operator << (std::ostream& out, Tree<U>& tree);
    template<typename U>
    friend std::istream& operator >> (std::istream& in, Tree<T>& tree);
};

template<typename T>
std::ostream& operator << (std::ostream& out, Tree<T>& tree)
{
    tree.Custom_Print(out, "LKP");
    return out;
}

template<typename T>
std::istream& operator >> (std::istream& in, Tree<T>& tree)
{
    size_t n;
    T value;
    in >> n;
    for(size_t i = 0; i < n; i++){
        in >> value;
        tree.Append(value);
    }
    return in;
}
