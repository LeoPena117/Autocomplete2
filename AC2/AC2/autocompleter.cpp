#include "autocompleter.h"
#include <iostream>
using namespace std;

Autocompleter::Autocompleter()
{

}
void Autocompleter::insert(string x, int freq)
{
	Entry cpy;
	cpy.s = x; cpy.freq = freq;
	
	insert_recurse(cpy, root);
}
int Autocompleter::size()
{
	return size_recurse(root);
}
void Autocompleter::completions(string x, vector<string> &T)
{
	T.clear();
	vector<Entry> R;
	completions_recurse(x, root, R);
	int max1 = 0, max2 = 0, max3 = 0;
	string word1, word2, word3;
	for (int i = 0; i < R.size(); i++)
	{
		if (R[i].freq >= max1)
		{
			max3 = max2; max2 = max1; max1 = R[i].freq;
			word3 = word2; word2 = word1; word1 = R[i].s;
		}
		else if (R[i].freq >= max2)
		{
			max3 = max2; max2 = R[i].freq;
			word3 = word2; word2 = R[i].s;
		}
		else if (R[i].freq >= max3)
		{
			max3 = R[i].freq;
			word3 = R[i].s;
		}
	}
	if (max1 == 0) { return; }
	if (max2 == 0) { T.push_back(word1); return; }
	if (max3 == 0) { T.push_back(word1); T.push_back(word2); return; }
	T.push_back(word1); T.push_back(word2); T.push_back(word3); return;
}
int Autocompleter::size_recurse(Node* root)
{
	if (root == NULL)
		return 0;
	else
		return(size_recurse(root->left) + 1 + size_recurse(root->right));
}
void Autocompleter::completions_recurse(string x, Node* root, vector<Entry> &T)
{
	if (root == nullptr)
	{
		return;
	}
	if (!strncmp(root->e.s.c_str(), x.c_str(), x.size()))
	{
		completions_recurse(x, root->left, T);
		T.push_back(root->e);
		completions_recurse(x, root->right, T);
	}
	else if (root->e.s < x)
	{
		completions_recurse(x, root->right, T);
	}
	else if (root->e.s > x)
	{
		completions_recurse(x, root->left, T);
	}
}
void Autocompleter::insert_recurse(Entry e, Node* cur)
{
	//Inserting if not found
	if (root == nullptr)
	{
		root = new Node(e);
		root->height = height(root) + 1;
		return;
	}


	if (cur->e.s == e.s)
		return;
	else if (cur->e.s < e.s)
	{
		if (cur->right != nullptr)
			insert_recurse(e, cur->right);
		else
			cur->right = new Node(e);
	}
	else
	{
		if (cur->left != nullptr)
			insert_recurse(e, cur->left);
		else
			cur->left = new Node(e);
	}
}
void Autocompleter::rebalance(Node* root)
{

}
void Autocompleter::right_rotate(Node* root)
{
	Node* lc = root->left;
	root->left = lc->left;
	lc->left = lc->right;
	lc->right = root->left;
	root->right = lc;
	swap(root->e, lc->e);
	
}
void Autocompleter::left_rotate(Node* root)
{
	Node* rc = root->right;
	root->right = rc->right;
	rc->right = rc->left;
	rc->left = root->right;
	root->left =rc;
	swap(root->e, rc->e);
	
}

