# include <iostream>
# include <vector>
# include <utility>

enum COLOR {RED, BLACK};

class Node
{
	public:

		std::pair<int, int>		val;
		COLOR	color;
		Node	*left, *right, *parent;

		Node(const std::pair<int, int> &val)
		{
			this->val = val;
			this->parent = NULL;
			this->left = NULL;
			this->right = NULL;
		}

		Node	*uncle()
		{
			if (parent == NULL || parent->parent == NULL)
				return NULL;
			if (parent->is_on_left())
				return (parent->parent->right);
			else
				return (parent->parent->left);
		}

		bool	is_on_left()
			{ return (this == parent->left); }

		Node	*sibling()
		{
			if (parent == NULL)
				return (NULL);
			if (is_on_left())
				return (parent->right);
			return (parent->left);
		}

		void	move_down(Node *nParent)
		{
			if (parent != NULL)
			{
				if (is_on_left())
					parent->left = nParent;
				else
					parent->right = nParent;
			}
			nParent->parent = parent;
			parent = nParent;
		}

		bool	has_red_child()
			{ return ( (left != NULL && left->color == RED)
							|| (right != NULL && right->color == RED)); }

	private:

}; // class Node

class BtsTree
{
	public :

	private :
		void	left_rotate(Node *x)
		{
			Node	*nParent = x->right;

			if (x == root)
				root == nParent;
			
			x->move_down();
			x->right = nParent->left;

			if (nParent->left != NULL)
				nParent->left->parent = x;
			nParent->left = x;
		}

		void	right_rotate(Node *x)
		{
			Node	*nParent = x->left;

			if (x == root)
				root = nParent;

			x->move_down(nParent);
			x->left = nParent->right;

			if (nParent->right != NULL)
				nParent->right->parent = x;
			
			nParent->right = x;
		}

		void	swap_colors(Node *x1, Node *x2)
		{
			COLOR temp;

			temp = x1->color;
			x1->color = x2->color;
			x2->color = temp;
		}

		void	swap_values(Node *u, Node *v)
		{
			std::pair<int, int>	temp;

			temp = u->val;
			u->val = v->val;
			v->val = temp;
		}

		void	fix_red_red(Node *x)
		{
			if (x == root)
			{
				x->color = BLACK;
				return ;
			}

			Node	*parent = x->parent;
			Node	*grandParent = parent->parent;
			Node	*uncle = x->uncle();

			if (parent->color != BLACK)
			{
				if (uncle != NULL && uncle->color == RED)
				{
					parent->color = BLACK;
					uncle->color = BLACK;
					grandParent->color = RED;
					fix_red_red(grandParent);
				}
				else
				{
					if (parent->is_on_left())
					{
						if (x->is_on_left())
							swap_colors(parent, grandParent);
						else
						{
							left_rotate(parent);
							swap_colors(x, grandParent);
						}
						right_rotate(grandParent);
					}
					else
					{
						if (x->is_on_left())
						{
							right_rotate(parent);
							swap_colors(x, grandParent);
						}
						else
							swap_colors(parent, grandParent);
						left_rotate(grandParent);
					}
				}
			}
		}

		Node	*successor(Node *x)
		{
			Node *temp = x;

			while (temp->left != NULL)
				temp = temp->left;
			return (temp);
		}

		Node	*BSTreplace(Node *x)
		{
			if (x->left != NULL && X->right != NULL)
				return (successor(x->right));
			if (x->left == NULL && x->right == NULL)
				return (NULL);
			if (x->left != NULL)
				return (x->left);
			else
				return (x->right);
		}

		void	deleteNode(Node *V)

}; // class BtsTree


int	main()
{
	Node	test(std::pair<int, int>(1, 2));

	return (0);
}
