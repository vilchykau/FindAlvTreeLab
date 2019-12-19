#include <iostream>
#include <string>
#include <list>
#include <cmath>

struct TreeNode{
	TreeNode* left;
	TreeNode* right;
	int value;
};

struct AvlInfo{
	AvlInfo(const TreeNode* node, int node_count, int height):node(node), node_count(node_count), height(height){

	}
	const TreeNode* node;
	int node_count;
	int height;
};


class BinTree{
public:
	BinTree(){
		root = nullptr;
	}

	BinTree(const BinTree& other){
		root = Copy(other.root);
	}

	BinTree(BinTree&& other){
		root = nullptr;
		Swap(other);
	}

	~BinTree(){
		RecurRemove(root);
	}

	BinTree& operator=(BinTree&& other){
		if(this != &other){
			RecurRemove(root);
			Swap(other);
		}
		return *this;
	}

	BinTree& operator=(const BinTree& other){
		if(this != &other){
			BinTree t(other);
			Swap(t);
		}
		return *this;
	}

	void Swap(BinTree &other){
		std::swap(other.root, root);
	}

	void Insert(int insert_value){
		Insert(insert_value, &root);
	}

	std::string ToString() const{
		std::list<int> l;
		GetElements(root, l);

		std::string out = "";
		for(const auto& item: l){
			out += std::to_string(item);
			out += " ";
		}

		return out;
	}

	BinTree FindMaxAvl(){
		auto o = BinTree(FindMaxAvl(root).node);
		return BinTree(FindMaxAvl(root).node);
	}


private:
	BinTree(const TreeNode* node){
		root = Copy(node);
	}

	AvlInfo FindMaxAvl(const TreeNode* node){
		if(!node){return {nullptr, 0, 0};}
		auto left = FindMaxAvl(node->left);
		auto right = FindMaxAvl(node->right);

		if(std::abs(left.height - right.height) <= 1 &&
		   left.node == node->left && right.node == node->right){
		    return AvlInfo(node,
				left.node_count + right.node_count+1,
				std::max(left.height, right.height)+1);
		}else{
			if(left.node_count < right.node_count){
				return right;
			}else{
				return left;
			}
		}
	}

	TreeNode* Copy(const TreeNode* node) const{
		if(!node){
			return nullptr;
		}
		TreeNode* out = new TreeNode{Copy(node->left),Copy(node->right),node->value};
		return out;
	}

	void RecurRemove(TreeNode* node){
		if(!node){return;}
		RecurRemove(node->left);
		RecurRemove(node->right);
		delete node;
	}

	void GetElements(TreeNode* node, std::list<int>& l) const{
		if(!node){
			return;
		}

		GetElements(node->left, l);
		l.push_back(node->value);
		GetElements(node->right, l);
	}

    void Insert(int insert_value, TreeNode** p_element){
    	if(*p_element){
	    if((*p_element)->value < insert_value){
	        Insert(insert_value, &(*p_element)->right);
	    }else if(insert_value < (*p_element)->value){
	        Insert(insert_value, &(*p_element)->left);
	    }
	}else{
            *p_element = new TreeNode{nullptr, nullptr, insert_value};
	}
    }


    TreeNode* root;
};

std::ostream& operator<<(std::ostream& stream, const BinTree& tree){
    std::cout << tree.ToString();
    return stream;
}

int main(){
    BinTree tree;
    tree.Insert(86);
    tree.Insert(50);
    tree.Insert(30);
    tree.Insert(60);
    tree.Insert(100);
    tree.Insert(90);
    tree.Insert(95);
    tree.Insert(93);
    tree.Insert(120);
    tree.Insert(115);
    tree.Insert(130);

    std::cout << tree.FindMaxAvl();
    return 0;
}
