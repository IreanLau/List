#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#define __DEBUG__



//以升序为基准


/**************************************************************************************/

/*单链表排序*/
struct Node
{
	int key;
	Node* next;
	Node(int nKey, Node* pNext)
		: key(nKey)
		, next(pNext)
	{}
};

void show(Node* pBeign)
{
	Node* cur = pBeign;
	while (cur)
	{
		cout << cur->key << " ";
		cur = cur->next;
	}
}



/*****************************************************/
/*
	从尾到头打印
*/
void ResPrint(Node* pBegin)
{
	if (pBegin == NULL)
		return;

	else
	{
		ResPrint(pBegin->next);
		cout << pBegin->key << " ";
	}
}



/*
	删除一个无头链表的非尾节点（偷梁换柱）
\*/
#include <assert.h>
void DelNode(Node* Pos)
{
	assert(Pos&&Pos->next);

	Node* _Pnext = Pos->next;
	Pos->key = _Pnext->key;
	Pos->next = _Pnext->next;

	delete(_Pnext);
	_Pnext = NULL;
}


/***************************************/
/*
	在一个无头链表的非头节点前插入一个节点
*/

void InsPrev(Node*_Pos, int _Key)
{
	assert(_Pos);

	Node* pNext = _Pos->next;
	Node* Ins = new Node(_Pos->key,pNext);
	_Pos->key = _Key;

	_Pos->next = Ins;
}


/************************************/
/*
	逆置链表
*/
Node* _Reverse(Node *pBegin)
{
	if (pBegin == NULL || pBegin->next == NULL)//size=1或0时  返回
		return pBegin;

	Node* SubHead = pBegin->next;
	pBegin->next = NULL;

	while (SubHead)
	{
		Node* Ins = SubHead;

		SubHead = SubHead->next;
		Ins->next = pBegin;
		pBegin = Ins;
	}
	return pBegin;
}

/*******************************************************/
//枢轴 ，把数组分成两部分  左比他小 右比他大
Node* GetPartion(Node* pBegin, Node* pEnd)
{
	Node* _key = pBegin;
	Node* prev = pBegin;
	Node* cur = prev->next;
	while (cur != pEnd)
	{
		if (cur->key < _key->key)
		{
			prev = prev->next;
			std::swap(prev->key, cur->key);
		}
		cur = cur->next;
	}
	std::swap(prev->key, _key->key);
	return prev;
}
//
void QuickSort(Node* pBeign, Node* pEnd)
{
	if (pBeign == NULL || pBeign->next == pEnd)
		return;
	if (pBeign != pEnd)
	{
		Node* partion = GetPartion(pBeign, pEnd);
		QuickSort(pBeign, partion);
		QuickSort(partion->next, pEnd);
	}
}



/*冒泡*/
void BubbleSort(Node* pBeign)
{
	if (pBeign == NULL)
		return;
	Node* tail = NULL;/*控制趟数*/
	while (tail != pBeign)
	{
		Node* prev = pBeign;
		Node* cur = prev->next;
		bool flag = true;/*标记 减少无效的比较*/

		while (cur != tail)/*一趟排序*/
		{
			if (cur->key < prev->key)
			{
				swap(cur->key, prev->key);
				flag = false;
			}
			prev = cur;
			cur = cur->next;
		}
		if (flag)
			return;

		tail = prev;
	}
}


void test1()
{
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);

	show(a);

	cout << endl;
	Node* pBeign = a;

	cout << "Rev:> \t" << endl;
	//Node* Rbegin = _Reverse(pBeign);
	Node* Rbegin = NULL;
	show(Rbegin);
	cout << endl;

	/*cout << "QuickSort:> \t" << endl;
	QuickSort(pBeign, NULL);
	show(a);
	cout << endl;*/


	//cout << "BubbleSort for list:> \t" << endl;
	//BubbleSort(pBeign);
	//show(a);
	//cout << endl;
}
/*************************************************/
/*	
	合并两个有序链表，之后仍然有序
*/
//node* merge(node*begin1,node*begin2)
//{
//	if(begin1==begin2 || begin1 == null || begin2 == null)
//		return null;
//	node* newhead=new node(-1,null);
//	node* tail = newhead;
//	while (begin1 && begin2)
//	{
//		if (begin1->key < begin2->key)
//		{
//			node* s = begin1;
//			begin1 = begin1->next;
//			s->next = null;
//			
//			tail->next = s;
//			tail = tail->next;
//			s = null;
//		}
//		else
//		{
//			node* s = begin2;
//			begin2 = begin2->next;
//			s->next = null;
//			
//			tail->next = s;
//			tail = tail->next;
//			s = null;
//		}
//	}
//
//	node* pa = null;
//	if (begin1)
//		pa = begin1;
//	else
//		pa = begin2;
//
//	tail->next = pa;
//	return newhead;
//}

Node* _Merge(Node*Begin1, Node*Begin2)
{
	if (Begin1 == NULL || Begin2 == NULL)
		return Begin1 == NULL ? Begin2 : Begin1;

	Node*cur = Begin1;
	if (Begin1->key > Begin2->key)
	{
		cur = Begin2;
		Begin2 = Begin2->next;
	}
	else
	{
		Begin1 = Begin1->next;
	}

	Node* NewHead = cur;
	while (Begin1 != NULL && Begin2 != NULL)
	{
		if (Begin1->key < Begin2->key)
		{
			cur->next = Begin1;
			Begin1 = Begin1->next;
		}
		else
		{
			cur->next = Begin2;
			Begin2 = Begin2->next;
		}
		cur = cur->next;
	}
	if (Begin1 != NULL)
		cur->next = Begin1;
	else
		cur->next = Begin2;

	return NewHead;
}


//Res
Node* __Merge(Node*Begin1, Node*Begin2)
{
	if (Begin1 == NULL || Begin2 == NULL)
		return Begin1 == NULL ? Begin2 : Begin1;

	Node* Head = NULL;
	if (Begin1->key < Begin2->key)
	{
		Head = Begin1;
		Head->next = __Merge(Begin1->next,Begin2);
	}
	else
	{
		Head = Begin2;
		Head->next = __Merge(Begin1, Begin2->next);
	}
	return Head;
}

void test3()
{
	Node *i = new Node(9, NULL);
	Node *h = new Node(7, i);
	Node *g = new Node(5, h);
	Node *f = new Node(3, g);
	Node *e = new Node(1, f);

	Node *d = new Node(6, NULL);
	Node *c = new Node(4, d);
	Node *b = new Node(2, c);
	Node *a = new Node(0, b);

	show(a);
	cout << endl;

	show(e);
	cout << endl;

	Node*NewHead = __Merge(a, e);
	show(NewHead);
	cout << endl;
}
/*************************************************/
/*
	只遍历一边，找中间节点(快慢指针)

	有头结点  快慢指针指向头结点
	
*/
Node* FindMid(Node* pBegin)
{
	if (pBegin == NULL || pBegin->next == NULL)
		return pBegin;

	Node* left = new Node(-1, pBegin);//
	Node* right = new Node(-1, pBegin);

	while (right && right->next)
	{
		left = left->next;

		right = right->next;
		right = right->next;
	}
	return left;
}


void test2()
{
	/*4 2 3 5 7 9 0 1*/
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);

	show(a);
	cout << endl;

	ResPrint(a);
	cout << endl;

	//DelNode(a);


	//InsPrev(h,8);

	/*Node*NewHead = _Reverse(a);
	show(NewHead);
	cout << endl;*/

	//Node*mid = FindMid(a);
	//cout << mid->key << endl;


	cout << endl;
}

/*************************************************/
/*
	查找单链表的倒数第K个节点，只能遍历一次
*/
Node* _FindTailKpos(Node* pBegin, size_t K)
{
	if (K == 0 || pBegin == NULL)
	{
		cout << "error argc! proc will exit" << endl;
		exit(1);
	}

	Node* fast = pBegin;
	Node* slow = fast;

	size_t num = K;
	while (--num)
	{
		if (fast->next)
			fast = fast->next;
		else
		{
			cout << "K too big" << endl;
			exit(2);
		}
	}

	while (fast->next)
	{
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

void test4()
{
	/*4 2 3 5 7 9 0 1*/
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);

	show(a);
	cout << endl;


	Node*cur = _FindTailKpos(a,4);
	cout <<"倒数第4个：》 "<< cur->key << endl;


	cout << endl;
}

/*************************************************/
/*
	判断链表是否带环，若带环求长度，求环的入口，  并求每个方法的时/空复杂度
*/

/*
	判断带环（快慢指针），时：O(n)	空：O(1)
*/


bool JudgeRing(Node* pBegin)
{
	assert(pBegin);
	Node *slow = pBegin, *fast = pBegin;

	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) break;
	}

	return !(fast == NULL || fast->next == NULL);
}

/*
找入口		时：O(n)	空：O(1)
*/
Node* FindPort(Node* pBegin)
{
	assert(pBegin);
	Node *slow = pBegin, *fast = pBegin;

	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) break;
	}

	if (fast == NULL || fast->next == NULL)
	{
		cout << "No Loop! the proc will exit!" << endl;
		exit(1);
	}
		
	slow = pBegin;
	while (slow != fast)
	{
		fast = fast->next;
		slow = slow->next;
	}

	/*确定 环长*/
	Node* Gurd = slow;
	size_t count = 1;
	slow = slow->next;
	while (slow != Gurd && ++count)
		slow = slow->next;
		
	cout << "The lenth of ring is:> " << count << endl;
	return slow;
}



void test5()
{
	/*4 2 3 5 7 9 0 1*/

	/*带环*/
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);
	h->next = g;

	/*show(a);
	cout << endl;*/

	
	cout << JudgeRing(a) << endl;

	Node* Find = FindPort(a);
	cout << "The port is :>"<<Find->key << endl;

	cout << endl;
}

/*************************************************/

/*
	判断两个链表是否相交（链表不带环）

	将链表1 首尾相接， 转化成判断 链表2 是否带环问题
*/

bool JudgeMeet(Node* pBegin1, Node*pBegin2)
{
	if (pBegin1 == NULL && pBegin2 == NULL)
		return false;
	
	Node* tail = pBegin1;
	while (tail->next)
		tail = tail->next;

	tail->next = pBegin1;

	return JudgeRing(pBegin2);
}
void test6()
{
	/*4 2 3 5 7 9 0 1*/

	/*带环*/
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, NULL);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);
	d->next = g;

	cout << "The JudgeMeet is :>" << JudgeMeet(a,e) << endl;

	cout << endl;
}

//思路2：压栈， 两个栈弹出的元素一样则返回该节点.
#include<stack>
Node* Meet(Node* pBegin1, Node*pBegin2)
{
	if (pBegin1 == NULL || pBegin2 == NULL)
		exit(1);

	stack<Node*> st1;
	stack<Node*> st2;

	while (pBegin1)
	{
		st1.push(pBegin1);
		pBegin1 = pBegin1->next;
	}
	while (pBegin2)
	{
		st2.push(pBegin2);
		pBegin2 = pBegin2->next;
	}
	

	Node* common1 = NULL;
	Node* common2 = NULL;

	while (!st1.empty() && !st2.empty())
	{
		common1 = st1.top();
		st1.pop();

		common2 = st2.top();
		st1.pop();

		if (common1->key != common2->key)
			return common1->next;
	}
	exit(2);
}


void test9()
{
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, NULL);
	Node *c = new Node(3, g);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);


	cout << Meet(a, e)->key << endl;
}
/*************************************************/
/*
	Josephus：n个人围成圈，依次编号为1,2,..,n，现在从1号开始依次报数，
	当报到m时，报m的人退出，下一个人重新从1报起，
	循环下去，问最后剩下那个人的编号是多少？（环链表 模拟法）

*/


Node *_Josephus(Node* pBegin, size_t m)
{
	Node* cur = pBegin;
	if (cur == NULL)
		return cur;

	while (1)
	{
		if (cur->next == cur)
			return cur;

		size_t num = m;
		while (--num)  //到第三个 走两步 
			cur = cur->next;

		Node* del = cur->next;
		cur->key = del->key;
		cur->next = del->next;
		delete del;
	}
}


Node *_Josephus(Node* pBegin, size_t m)
{
	Node* cur = pBegin;
	if (cur == NULL)
		return cur;

	while(1)
	{
		if (cur->next == cur)
			return cur;

		size_t num = m;
		while (--num)
			cur = cur->next;

		Node* del = cur->next;
		cur->key = del->key;
		cur->next = del->next;
		delete del;
	}
}


/*数学法*/
void Josephus()
{
	int n, m, i, s=0;
	printf ("N M = ");   //n:总人数  m调度个数
	scanf("%d%d", &n, &m);
	for (i=2; i<=n; i++)
		s=(s+m)%i;
	printf ("The winner is %d\n", s);
}




//Josephus
void test7()
{

	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);
	h->next = a;

	Node* _key = _Josephus(a, 2);
	cout << "The Josephus owner is :>" << _key->key << endl;

	cout << endl;
}


//单链表部分逆置
//Node* RolloverList(Node* list,int k)
//list 无头结点
//1->2->3->4->5  k=2   翻转后： 2-1->4->3->5
// 思路： 小部分翻转，各个部分拼接
Node* RolloverList(Node* list, int k)
{
	if (list == NULL || list->next == NULL || k <= 1)
		return list;

	Node* newHead=NULL;
	Node* prevSectionTail = NULL;
	Node* sectionHead = NULL, *sectionTail = NULL;
	int sectionNum = 0;

	Node* cur = list;
	while (cur)
	{
		int count = k;
		prevSectionTail = sectionTail;
		sectionTail = cur;

		while (count-- && cur)
		{
			Node* tmp = cur;
			cur = cur->next;
			tmp->next = sectionHead;
			sectionHead = tmp;
		}

		++sectionNum;
		if (1 == sectionNum)
			newHead = sectionHead;
		else
			prevSectionTail->next = sectionHead;
	}
	sectionTail->next = NULL;
	return newHead;

}

void test8()
{
	Node *e = new Node(5, NULL);

	Node *d = new Node(4, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(1, b);

	Node* list = RolloverList(a, 2);
	show(list);
}

/*************************************************/
void main()
{
	//test1();
	//test2();
	//test3();//归并
	//test6();
	//test7(); //约瑟夫
	//Josephus();
	//test4();  //查找单链表的倒数第K个节点，只能遍历一次
	//test5(); //判读 有环  找出口
	//test8();   //部分逆置链表
	test9();//链表公共节点
}