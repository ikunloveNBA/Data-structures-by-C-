#include<iostream>
#include<sstream>
#include<stack>
#include<queue>
#include<vector>
#include<map>
#include<stdexcept>
using namespace std;

#define maxNums 20

template<class T>
struct BinTreeNode//二叉树节点类
{
	T data;//数据域
	BinTreeNode<T>* leftChild, * rightChild;//左孩子指针，右孩子指针
	BinTreeNode() :leftChild(nullptr), rightChild(nullptr) {}//构造函数
	BinTreeNode(T item, BinTreeNode* left = nullptr, BinTreeNode* right = nullptr) : data(item), leftChild(left), rightChild(right) {}

};


template<class T>
class BinaryTree
{
public:
	BinaryTree() :root(nullptr) {}//默认构造
	BinaryTree(const BinaryTree& bt) { root = copy(bt.root); }//拷贝构造
	~BinaryTree() { destory(root); }//析构函数

	bool isEmpty() { return (root == nullptr) ? true : false; }//判断根节点是否为空
	void creatBinTree(T stopValue, istream& is) { cout << "请输入根节点："; creatBinTree(stopValue, is, root); }//前序建立二叉树（键盘输入）
	void creatBinTree(T stopValue, const string& s);//前序建立二叉树（字符串输入）
	template<int LEN>void creatBinTree(const T(&pre)[LEN], const T(&in)[LEN]) { creatBinTree(pre, in, root, LEN); }//根据前序和中序建立二叉树
	void printBinTree01() { printBinTree01(cout, root); }//前序输出二叉树
	void printBinTree02() { printBinTree02(cout, root); }//输出括号表达式
	void preOrder01(void(*visit)(BinTreeNode<T>*) = [](BinTreeNode<T>*) {}) { preOrder01(root, visit); }//前序遍历（递归）
	void preOrder02(void(*visit)(BinTreeNode<T>*) = [](BinTreeNode<T>*) {}) { preOrder02(root, visit); }//前序遍历（非递归）
	void inOrder01(void(*visit)(BinTreeNode<T>*) = [](BinTreeNode<T>*) {}) { inOrder01(root, visit); }//中序遍历（递归）
	void inOrder02(void(*visit)(BinTreeNode<T>*) = [](BinTreeNode<T>*) {}) { inOrder02(root, visit); }//中序遍历（非递归）
	void postOrder01(void(*visit)(BinTreeNode<T>*) = [](BinTreeNode<T>*) {}) { postOrder01(root, visit); }//后序遍历（递归）
	void postOrder02(void(*visit)(BinTreeNode<T>*) = [](BinTreeNode<T>*) {}) { postOrder02(root, visit); }//后序遍历（非递归）
	void levelOrder(void (*visit)(BinTreeNode<T>*) = [](BinTreeNode<T>*) {}) { levelOrder(root, visit); }//层次遍历
	void verticalOrder(void(*visit)(BinTreeNode<T>*) = [](BinTreeNode<T>*) {}) { verticalOrder(root, visit); }//垂直遍历（BFS）
	int leavesCount() { return leavesCount(root); }//求叶子节点个数(递归)
	int hight() { return hight(root); }//返回树的高度（递归）

private:
	BinTreeNode<T>* root;//二叉树根


	void destory(BinTreeNode<T>*&);//递归删除节点
	void creatBinTree(T, istream&, BinTreeNode<T>*&);//前序建立二叉树（键盘输入）
	void creatBinTree(T, istringstream&, BinTreeNode<char>*&);//前序建立二叉树（字符串输入）
	void creatBinTree(const T(&)[], const  T(&)[], BinTreeNode<T>*&, int len);//根据前序和中序建立二叉树
	void printBinTree01(ostream&, BinTreeNode<T>*);//前序输出二叉树
	void printBinTree02(ostream&, BinTreeNode<T>*);//输出括号表达式
	void preOrder01(BinTreeNode<T>*, void(*visit)(BinTreeNode<T>*));//前序遍历（递归）
	void preOrder02(BinTreeNode<T>*, void(*visit)(BinTreeNode<T>*));//前序遍历（非递归）
	void inOrder01(BinTreeNode<T>*, void(*visit)(BinTreeNode<T>*));//中序遍历（递归）
	void inOrder02(BinTreeNode<T>*, void(*visit)(BinTreeNode<T>*));//中序遍历（非递归）
	void postOrder01(BinTreeNode<T>*, void(*visit)(BinTreeNode<T>*));//后序遍历（递归）
	void postOrder02(BinTreeNode<T>*, void(*visit)(BinTreeNode<T>*));//后序遍历（非递归）
	void levelOrder(BinTreeNode<T>*, void (*visit)(BinTreeNode<T>*));//层次遍历
	void verticalOrder(BinTreeNode<T>*, void(*visit)(BinTreeNode<T>*));//垂直遍历(BFS)
	int leavesCount(BinTreeNode<T>*);//求叶子节点个数(递归)
	int hight(BinTreeNode<T>*);//返回树的高度（递归）
	BinTreeNode<T>* copy(BinTreeNode<T>*);//复制二叉树（递归）

};


//递归删除节点
template<class T>
void BinaryTree<T>::destory(BinTreeNode<T>*& subTree)
{
	if (subTree != nullptr)
	{
		destory(subTree->leftChild);
		destory(subTree->rightChild);
		delete subTree;
	}
}


//前序建立二叉树（字符串输入）
template<class T>
void BinaryTree<T>::creatBinTree(T stopValue, const string& s)
{
	throw runtime_error("对不起，无法用字符串建立其他类型的二叉树");
}


//前序建立二叉树（字符串输入）
template<>
void BinaryTree<char>::creatBinTree(char stopValue, const string& s)
{
	istringstream ist(s);
	creatBinTree(stopValue, ist, root);
}


//前序建立二叉树（键盘输入）
template<class T>
void BinaryTree<T>::creatBinTree(T stopValue, istream& in, BinTreeNode<T>*& subTree)
{
	T item;
	in >> item;//将输入流到item中
	if (item != stopValue)//如果item不等于停止数
	{
		subTree = new BinTreeNode<T>(item);//创建新节点
		cout << "请输入" << item << "的左子树：";
		this->creatBinTree(stopValue, in, subTree->leftChild);//创建左子树
		cout << "请输入" << item << "的右子树：";
		this->creatBinTree(stopValue, in, subTree->rightChild);//创建右子树
	}
	else subTree = nullptr;
}


//前序建立二叉树（字符串输入）
template<>
void BinaryTree<char>::creatBinTree(char stopValue, istringstream& ist, BinTreeNode<char>*& subTree)
{

	char item;
	ist >> item;//将字符输入到item中
	if (item != stopValue)//如果item不等于停止数
	{
		subTree = new BinTreeNode<char>(item);//创建新节点
		this->creatBinTree(stopValue, ist, subTree->leftChild);//创建左子树
		this->creatBinTree(stopValue, ist, subTree->rightChild);//创建右子树
	}
	else subTree = nullptr;

}


//根据前序和中序建立二叉树
template<class T>
void BinaryTree<T>::creatBinTree(const T(&pre)[], const T(&in)[], BinTreeNode<T>*& subtree, int len)
{
	if (len == 0)
	{
		subtree = nullptr;
		return;
	}

	int lp_n = 0, li_n = 0, rp_n = 0, ri_n = 0;//左右孩子的序列长度
	T lpre[maxNums], lin[maxNums], rpre[maxNums], rin[maxNums];//分别建立左右孩子的先序和中序序列
	
	subtree = new BinTreeNode<T>(pre[0]);//先序序列第一个为根

	for (int i = 0; i < len; i++)//建立左右孩子的中序序列
	{
		if (in[i] != pre[0] && i <= li_n)
		{
			lin[li_n++] = in[i];
		}
		else if (in[i] != pre[0])
		{
			rin[ri_n++] = in[i];
		}
	}

	for (int i = 1; i < len; i++)//建立左右孩子的先序序列
	{
		lp_n < li_n ? lpre[lp_n++] = pre[i] : rpre[rp_n++] = pre[i];
	}

	//递归建立左右孩子
	creatBinTree(lpre, lin, subtree->leftChild, lp_n);
	creatBinTree(rpre, rin, subtree->rightChild, rp_n);

}


//前序输出二叉树
template<class T>
void BinaryTree<T>::printBinTree01(ostream& os, BinTreeNode<T>* subTree)
{
	if (subTree != nullptr)
	{
		os << subTree->data << ' ';//输出节点数据
		printBinTree01(os, subTree->leftChild);//访问左子树
		printBinTree01(os, subTree->rightChild);//访问右子树
	}

}


//输出括号表达式
template<class T>
void BinaryTree<T>::printBinTree02(ostream& os, BinTreeNode<T>* subTree)
{
	if (subTree != nullptr)
	{
		os << subTree->data;//输出节点数据
		if (subTree->leftChild != nullptr || subTree->rightChild != nullptr) os << '(';
		printBinTree02(os, subTree->leftChild);//访问左子树
		if (subTree->leftChild != nullptr && subTree->rightChild != nullptr) os << ',';
		printBinTree02(os, subTree->rightChild);//访问右子树
		if (subTree->leftChild != nullptr || subTree->rightChild != nullptr) os << ')';
	}

}


//前序遍历（递归）
template<class T>
void BinaryTree<T>::preOrder01(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>*))
{
	if (subTree != nullptr)
	{
		visit(subTree);//访问根
		preOrder01(subTree->leftChild, visit);//访问左子树
		preOrder01(subTree->rightChild, visit);//访问右子树
	}
}


//前序遍历（非递归）
template<class T>
void BinaryTree<T>::preOrder02(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>*))
{
	if (subTree == nullptr)return;
	BinTreeNode<T>* p = subTree;
	stack<BinTreeNode<T>*> s;
	while (p != nullptr || !s.empty())
	{
		while (p != nullptr)//先循环到最后的左子树
		{
			visit(p);//依次访问根节点
			s.push(p);//将访问过的节点都压入栈中
			p = p->leftChild;//直到最后一个左子树的左子树为空
		}
		if (!s.empty())//栈不为空就代表还有根节点可以回溯
		{
			p = s.top();//回溯到没有访问过的上一个节点
			s.pop();//将访问过的节点都弹出栈
			p = p->rightChild;//访问一个右子树，将此右子树为根节点再循环访问它的左子树
		}
	}
}


//中序遍历（递归）
template<class T>
void BinaryTree<T>::inOrder01(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>*))
{
	if (subTree != nullptr)
	{
		inOrder01(subTree->leftChild, visit);//访问左子树
		visit(subTree);//访问根
		inOrder01(subTree->rightChild, visit);//访问右子树
	}
}


//中序遍历（非递归）
template<class T>
void BinaryTree<T>::inOrder02(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>*))
{

	if (subTree == nullptr)return;
	BinTreeNode<T>* p = subTree;
	stack<BinTreeNode<T>*>s;
	while (p != nullptr || !s.empty())
	{
		while (p != nullptr)//遍历到最底端的左子树
		{
			s.push(p);
			p = p->leftChild;
		}
		if (!s.empty())//如果栈不为空则回溯上一个节点，并将根节点重新设置为右子树，以此循环
		{
			p = s.top();
			s.pop();
			visit(p);
			p = p->rightChild;
		}
	}

}


//后序遍历（递归）
template<class T>
void BinaryTree<T>::postOrder01(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>*))
{
	if (subTree != nullptr)
	{
		postOrder01(subTree->leftChild, visit);//访问左子树
		postOrder01(subTree->rightChild, visit);//访问右子树
		visit(subTree);//访问根
	}
}


//后序遍历（非递归）
//如果上次访问的是左子树则访问该节点的右子树，如果上次访问的是右子树则访问该节点
template<class T>
void BinaryTree<T>::postOrder02(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>*))
{

	if (subTree == nullptr)return;
	BinTreeNode<T>* pCur = subTree, * pLast = nullptr;//pCur指向当前访问的节点，pLast指向上一次访问的节点
	stack<BinTreeNode<T>*> s;
	while (pCur != nullptr)//先将pCur移动到左子树的最下边
	{
		s.push(pCur);
		pCur = pCur->leftChild;
	}
	while (!s.empty())//此时pCur为空
	{
		pCur = s.top();//返回它的上一个节点，也就是最后一个左子树
		s.pop();//将回溯过的节点弹出栈
		if (pCur->rightChild == nullptr || pCur->rightChild == pLast)//如果该节点的右子树为空或者已经访问过则访问此节点
		{
			visit(pCur);//访问此节点
			pLast = pCur;//将此节点更新为上一此访问过的节点
		}
		else//如果这个节点的右子树没有被访问过并且不为空
		{
			s.push(pCur);//则这个节点还不能删除，所以要重新入栈
			pCur = pCur->rightChild;//并访问该节点的右子树
			while (pCur != nullptr)//访问这个右子树的最后一个左子树，并循环以上过程
			{
				s.push(pCur);
				pCur = pCur->leftChild;
			}
		}
	}
}


//层次遍历
template<class T>
void BinaryTree<T>::levelOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>*))
{
	//把同一层的节点入队，依次访问每一层的节点，访问一个出队一个
	if (subTree == nullptr)return;
	BinTreeNode<T>* p = subTree;
	queue<BinTreeNode<T>*>s;
	s.push(p);//先将根节点入队，使得循环成立
	while (!s.empty())
	{
		p = s.front();
		visit(s.front());//访问此节点
		s.pop();//将此节点出队
		if (p->leftChild != nullptr)s.push(p->leftChild);//将左子树入队
		if (p->rightChild != nullptr)s.push(p->rightChild);//将右子树入队
	}

}


//垂直遍历（BFS）
template<class T>
void BinaryTree<T>::verticalOrder(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>*))
{

	map<int, vector<BinTreeNode<T>*>> nmap;//用列号作为key值，同一列的节点放到一个vector中
	queue<pair<int, BinTreeNode<T>*>> q;//将节点和列号作为一对一起入队
	int cur = 0;//当前根节点的列号
	if (subTree != nullptr) q.push(make_pair(cur, subTree));//先将根节点和它的列号入队
	//层次遍历
	while (!q.empty())//根节点为0，左子树依次减小，右子树依次增大，进行层次遍历保证同一列的根节点从上到下的顺序
	{
		pair<int, BinTreeNode<T>*> p(q.front());
		q.pop();
		if (p.second->leftChild != nullptr)q.push(make_pair((p.first) - 1, p.second->leftChild));
		if (p.second->rightChild != nullptr)q.push(make_pair((p.first) + 1, p.second->rightChild));

		nmap[p.first].push_back(p.second);
	}

	vector<vector<BinTreeNode<T>*>> v(nmap.size());//创建一个保存节点集合的集合

	for (auto& c : nmap)//因为map会自动按照key值从小到大排序，所以直接尾插
	{
		v.push_back(c.second);
	}

	for (typename vector<vector<BinTreeNode<T>*>>::iterator vit = v.begin(); vit != v.end(); vit++)//依次访问
	{
		for (typename vector<BinTreeNode<T>*>::iterator it = (*vit).begin(); it != (*vit).end(); it++)
			visit(*it);
	}

}


//求叶子节点个数(递归)
template<class T>
int BinaryTree<T>::leavesCount(BinTreeNode<T>* subtree)
{
	if (subtree == nullptr)return 0;
	if (subtree->leftChild == nullptr && subtree->rightChild == nullptr)return 1;
	return (leavesCount(subtree->leftChild) + leavesCount(subtree->rightChild));
}



//返回树的高度（递归）
template<class T>
int BinaryTree<T>::hight(BinTreeNode<T>* subTree)
{
	if (subTree == nullptr) return 0;//最底层的树的左右子树肯定都为空，所以最后一次递进返回一个0
	else
	{
		int m = hight(subTree->leftChild);//m为左子树的个数
		int n = hight(subTree->rightChild);//n为右子树的个数
		return m > n ? m + 1 : n + 1;//返回数量更多的子树个数，并加上此节点的个数，返回给上一个节点
	}
}

//复制二叉树（递归）
template<class T>
BinTreeNode<T>* BinaryTree<T>::copy(BinTreeNode<T>* subTree)
{
	if (subTree == nullptr)return nullptr;
	BinTreeNode<T>* temp = new BinTreeNode<T>;//前序遍历递归复制
	temp->data = subTree->data;
	temp->leftChild = copy(subTree->leftChild);
	temp->rightChild = copy(subTree->rightChild);
	return temp;
}


//访问节点函数
template<class T>
void printData(BinTreeNode<T>* subTree)
{
	cout << subTree->data << ' ';
}



//二叉树功能函数集合输出
template<class T>
void printBinaryTree(BinaryTree<T>&bt)
{
	cout << "前序序列（递归）：";
	bt.preOrder01(printData);
	cout << endl;
	cout << "前序序列（非递归）：";
	bt.preOrder02(printData);
	cout << endl;
	cout << "中序序列（递归）：";
	bt.inOrder02(printData);
	cout << endl;
	cout << "中序序列（非递归）：";
	bt.inOrder01(printData);
	cout << endl;
	cout << "后序序列（递归）：";
	bt.postOrder01(printData);
	cout << endl;
	cout << "后序序列（非递归）：";
	bt.postOrder02(printData);
	cout << endl;
	cout << "括号表达式：";
	bt.printBinTree02();
	cout << endl;
	cout << "层次遍历：";
	bt.levelOrder(printData);
	cout << endl;
	cout << "垂直遍历：";
	bt.verticalOrder(printData);
	cout << endl;
	cout << "二叉树的高度为：";
	cout << bt.hight() << endl;
	cout << "二叉树的叶子结点个数为：" << bt.leavesCount() << endl;
}



int main()
{
		cout << "整型二叉树" << endl;
	BinaryTree<int>bt1;
	bt1.creatBinTree(99, cin);
	printBinaryTree(bt1);
	cout << endl << endl;

	cout << "字符型二叉树" << endl;
	string s("ABC#DE###FG###H##");
	BinaryTree<char>bt2;
	bt2.creatBinTree('#', s);
	printBinaryTree(bt2);
	cout << endl << endl;
	
	cout << "字符串型二叉树" << endl;
	string pre[6] = { "blue","red","yellow","pink","black","orange" };
	string in[6] = { "red","orange","black","blue","pink","yellow" };
	BinaryTree<string> bt3;
	bt3.creatBinTree(pre, in);
	printBinaryTree(bt3);
	cout << endl << endl;

	return 0;
}



