#include <iostream>
#include <ctime>

struct Node
 {
	int data; 
	Node *parent; 
	Node *sol;
	Node *sag; 
};

typedef Node *NodePtr;


class SplayTree 
{
private:
	NodePtr root;

	void preOrderHelper(NodePtr node) 
    {
		if (node != nullptr)
        {
			std::cout<<node->data<<" ";
			preOrderHelper(node->sol);
			preOrderHelper(node->sag);
		} 
	}

	void inOrderHelper(NodePtr node) 
    {
		if (node != nullptr) 
        {
			inOrderHelper(node->sol);
			std::cout<<node->data<<" ";
			inOrderHelper(node->sag);
		} 
	}

	void postOrderHelper(NodePtr node) 
    {
		if (node != nullptr)
        {
			postOrderHelper(node->sol);
			postOrderHelper(node->sag);
			std::cout<<node->data<<" ";
		} 
	}

	void silmeNodeHelper(NodePtr node, int key) 
    {
		NodePtr x = nullptr;
		NodePtr t, s;
		while (node != nullptr)
        {
			if (node->data == key) 
            {
				x = node;
			}

			if (node->data <= key) 
            {
				node = node->sag;
			} 
            else 
            {
				node = node->sol;
			}
		}

		if (x == nullptr) {
			std::cout<<"Deger bulunamadi"<< std::endl;
			return;
		}
		split(x, s, t); 
		if (s->sol)
        { 
			s->sol->parent = nullptr;
		}
		root = join(s->sol, t);
		delete(s);
		s = nullptr;
	}
	void printHelper(NodePtr root, std::string indent, bool last)
    {
	
	   	if (root != nullptr) 
           {
		   std::cout<<indent;
		   if (last) {
		      std::cout<<"-----";
		      indent += "     ";
		   } else {
		      std::cout<<"-----";
		      indent += "|    ";
		   }

		   std::cout << root->data << std::endl;

		   printHelper(root->sol, indent, false);
		   printHelper(root->sag, indent, true);
		}
	}
	void solRotate(NodePtr x) 
    {
		NodePtr y = x->sag;
		x->sag = y->sol;
		if (y->sol != nullptr) 
        {
			y->sol->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) 
        {
			this->root = y;
		} 
        else if (x == x->parent->sol) 
        {
			x->parent->sol = y;
		} else 
        {
			x->parent->sag = y;
		}
		y->sol = x;
		x->parent = y;
	}
	void sagRotate(NodePtr x) 
    {
		NodePtr y = x->sol;
		x->sol = y->sag;
		if (y->sag != nullptr) 
        {
			y->sag->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) 
        {
			this->root = y;
		} else if (x == x->parent->sag) 
        {
			x->parent->sag = y;
		} else 
        {
			x->parent->sol = y;
		}
		y->sag = x;
		x->parent = y;
	}

	void splay(NodePtr x) 
    {
		while (x->parent) 
        {
			if (!x->parent->parent) 
            {
				if (x == x->parent->sol) 
                {
					
					sagRotate(x->parent);
				} 
                else 
                {
					
					solRotate(x->parent);
				}
			} 
            else if (x == x->parent->sol && x->parent == x->parent->parent->sol) 
            {
				sagRotate(x->parent->parent);
				sagRotate(x->parent);
			} else if (x == x->parent->sag && x->parent == x->parent->parent->sag) 
            {
				solRotate(x->parent->parent);
				solRotate(x->parent);
			} 
            else if (x == x->parent->sag && x->parent == x->parent->parent->sol) 
            {
				solRotate(x->parent);
				sagRotate(x->parent);
			} 
            else 
            {
				sagRotate(x->parent);
				solRotate(x->parent);
			}
		}
	}
	NodePtr join(NodePtr s, NodePtr t)
    {
		if (!s)
        {
			return t;
		}

		if (!t) 
        {
			return s;
		}
		NodePtr x = maximum(s);
		splay(x);
		x->sag = t;
		t->parent = x;
		return x;
	}
	void split(NodePtr &x, NodePtr &s, NodePtr &t) 
    {
		splay(x);
		if (x->sag) 
        {
			t = x->sag;
			t->parent = nullptr;
		} else 
        {
			t = nullptr;
		}
		s = x;
		s->sag = nullptr;
		x = nullptr;
	} 

public:
	SplayTree() 
    {
		root = nullptr;
	}
	void preorder() 
    {
		preOrderHelper(this->root);
	}
	void inorder() 
    {
		inOrderHelper(this->root);
	}
	void postorder() 
    {
		postOrderHelper(this->root);
	}
	NodePtr minimum(NodePtr node) 
    {
		while (node->sol != nullptr) 
        {
			node = node->sol;
		}
		return node;
	}
	NodePtr maximum(NodePtr node) 
    {
		while (node->sag != nullptr) 
        {
			node = node->sag;
		}
		return node;
	}
	NodePtr successor(NodePtr x) 
    {
		if (x->sag != nullptr) 
        {
			return minimum(x->sag);
		}
		NodePtr y = x->parent;
		while (y != nullptr && x == y->sag) 
        {
			x = y;
			y = y->parent;
		}
		return y;
	}
	NodePtr predecessor(NodePtr x) 
    {
		if (x->sol != nullptr) 
        {
			return maximum(x->sol);
		}

		NodePtr y = x->parent;
		while (y != nullptr && x == y->sol) 
        {
			x = y;
			y = y->parent;
		}

		return y;
	}

	
	void ekleme(int key)
    {
		NodePtr node = new Node;
		node->parent = nullptr;
		node->sol = nullptr;
		node->sag = nullptr;
		node->data = key;
		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != nullptr) 
        {
			y = x;
			if (node->data < x->data) 
            {
				x = x->sol;
			} 
            else 
            {
				x = x->sag;
			}
		}
		node->parent = y;
		if (y == nullptr) 
        {
			root = node;
		} 
        else if (node->data < y->data) 
        {
			y->sol = node;
		} 
        else 
        {
			y->sag = node;
		}
		splay(node);
	}

	NodePtr getRoot()
    {
		return this->root;
	}

	void silmeNode(int data) 
    {
		silmeNodeHelper(this->root, data);
	}

	void prettyPrint() 
    {
		printHelper(this->root, "", true);
	}

    void arama(int deger)
    {
        Node *temp = root;
        bool found = false;
        while(temp != NULL)
        {
            if(deger == temp->data)
            {
                found = true;
                break;
            }
            else
            {
                if(deger < temp->data)
                    temp = temp->sol;
                else
                    temp = temp->sag;

            }
        }
            if(found)
            {
                std::cout << deger <<  " bulundu" << std::endl;
            }
            else
            {
                std::cout << deger << " bulunamadi" << std::endl;
            }
    }

};
void printArray(int array[30])
{
    for(int i = 0; i < 30; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

int main() 
{
	SplayTree bst;

    srand(time(NULL));
    int array[30];

    for(auto& iter:array)
    {
        iter = rand() + 1;
    }
    printArray(array);

    for(int i = 0; i < 30; i++)
    {
        bst.ekleme(array[i]);
    }
	bst.silmeNode(array[3]);
    bst.arama(array[2]);
    bst.arama(array[3]);
    bst.prettyPrint();

	return 0;
}