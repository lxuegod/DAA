#include <bits/stdc++.h>
using namespace std;

#define FILE_NAME "huffman.txt"

//  Node类
class Node{
public:
	char c;
	int w;
	Node * lChild;
	Node * rChild;

    //  结点构造函数
	Node(char ch, int weight);
    //  中间结点构造函数
	Node(int weight, Node * leftChild = NULL, Node * rightChild = NULL);
    //  获得中间结点
	Node * operator+(Node & another);
};

Node::Node(int weight, Node * leftChild, Node * rightChild){
	c = 0;
	w = weight;
	lChild = leftChild;
	rChild = rightChild;
}

Node::Node(char ch, int weight){
	c = ch;
	w = weight;
	lChild = rChild = NULL;
}

Node * Node::operator+(Node & another){
	return new Node(w + another.w, this, &another);
}

//  Code结构体
struct Code{
	char c;
	string code;
};

class Solution {
public:
    Node * popMinNode(vector<Node *> & nodes);
    void Work();
};

void Solution::Work(){
    //  存储26个字母的大小写，单词间用 # 隔开
	int num[53];
	for (int i = 0; i < 53; ++i){
		num[i] = 0;
	}

	/*
	format:
	num[0] ~ num[25] = a ~ z
	num[26] ~ num[51] = A ~ Z
	num[52] = #
	*/

	//  输入
	ifstream fin;
	fin.open(FILE_NAME);
	string str[5];
	for (int i = 0; i < 5; ++i){
		fin >> str[i];
		for (int j = 0; j < str[i].length(); ++j){
			if (str[i][j] >= 'a' && str[i][j] <= 'z'){
				++num[str[i][j] - 'a'];
			} else if (str[i][j] >= 'A' && str[i][j] <= 'Z'){
				++num[str[i][j] - 'A' + 26];
			} else if (str[i][j] == '#'){
				++num[52];
			}
		}
	}
	fin.close();

	vector<Node *> tree;
	ofstream fout;
	fout.open("output.txt");

	//  输出字符计数和构造树
	{
		cout << "char count:\n";
		fout << "char count:\n";
		for (int i = 0; i < 26; ++i){
			cout << (char)(i + 'a') << ": " << num[i] << endl;
			fout << (char)(i + 'a') << ": " << num[i] << endl;
			if (num[i]){
				tree.push_back(new Node(i + 'a', num[i]));
			}
		}
		for (int i = 26; i < 52; ++i){
			cout << (char)(i + 'A' - 26) << ": " << num[i] << endl;
			fout << (char)(i + 'A' - 26) << ": " << num[i] << endl;
			if (num[i]){
				tree.push_back(new Node(i + 'A' - 26, num[i]));
			}
		}
		cout << "#: " << num[52] << endl;
		fout << "#: " << num[52] << endl;
		if (num[52]){
			tree.push_back(new Node('#', num[52]));
		}
	}

	//  合并节点
	while (tree.size() != 1){
		//  获得两个具有最小权重的节点
		Node * node1 = popMinNode(tree);
		Node * node2 = popMinNode(tree);
		Node * result = *node1 + *node2;
		tree.push_back(result);
	}

	//  已经构造了一棵树，tree[0] 是指向根的指针

	//  使用堆栈构造Huffman代码
    //  保存下一个要处理的节点
	stack<Node *> nodeStack;
	stack<string> codeStack;
	vector<Code> codes;
	nodeStack.push(tree[0]);
	codeStack.push(string());
	while (nodeStack.size()){
		Node * currentNode = nodeStack.top();
		nodeStack.pop();
		string code = codeStack.top();
		codeStack.pop();
		if (currentNode->lChild){
			nodeStack.push(currentNode->lChild);
			codeStack.push(code + '0');
		}
		if (currentNode->rChild){
			nodeStack.push(currentNode->rChild);
			codeStack.push(code + '1');
		}
		if (!currentNode->lChild && !currentNode->rChild){
			codes.push_back({currentNode->c, code});
		}
	}

	//  输出Huffman代码
	cout << "\nHuffman Code:\n";
	fout << "\nHuffman Code:\n";
	for (int i = 0; i < codes.size(); ++i){
		cout << codes[i].c << ": " << codes[i].code << endl;
		fout << codes[i].c << ": " << codes[i].code << endl;
	}

	//  计算位数
	cout << "\nbit length:\n";
	fout << "\nbit length:\n";
	cout << "Using Fixed Length Coding: ";
	fout << "Using Fixed Length Coding: ";
	int charNum = 0;
	for (int i = 0; i < 5; ++i){
		charNum += str[i].length();
	}
    //  每个字符8位
	cout << charNum * 8 << endl;
	fout << charNum * 8 << endl;
	int bitNum = 0;
	for (int i = 0; i < codes.size(); ++i){
		if (codes[i].c >= 'a' && codes[i].c <= 'z'){
			bitNum += num[codes[i].c - 'a'] * codes[i].code.length();
		} else if (codes[i].c >= 'A' && codes[i].c <= 'Z'){
			bitNum += num[codes[i].c - 'A' + 26] * codes[i].code.length();
		} else {
			bitNum += num[52] * codes[i].code.length();//'#'
		}
	}
	cout << "Using Huffman Coding: " << bitNum << endl;
	fout << "Using Huffman Coding: " << bitNum << endl;

	//  使用堆栈释放内存
	stack<Node *> freeStack;
	freeStack.push(tree[0]);
	while (freeStack.size()){
		Node * t = freeStack.top();
		freeStack.pop();
		if (t->lChild){
			freeStack.push(t->lChild);
		}
		if (t->rChild){
			freeStack.push(t->rChild);
		}
		delete t;
	}

	fout.close();
}

Node * Solution::popMinNode(vector<Node *> & nodes){
	int min = nodes[0]->w;
	int index = 0;

	//  找到最小权重结点
	for (int i = 1; i < nodes.size(); ++i){
		if (nodes[i]->w < min){
			min = nodes[i]->w;
			index = i;
		}
	}

	//  删除对象并返回结果
	Node * result = nodes[index];
	nodes.erase(nodes.begin() + index);
	return result;
}

int main() {
    Solution s;
    s.Work();
    system("pause");
    return 0;
}