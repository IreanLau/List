#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#define __DEBUG__



//������Ϊ��׼


/**************************************************************************************/

/*����������*/
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
	��β��ͷ��ӡ
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
	ɾ��һ����ͷ����ķ�β�ڵ㣨͵��������
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
	��һ����ͷ����ķ�ͷ�ڵ�ǰ����һ���ڵ�
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
	��������
*/
Node* _Reverse(Node *pBegin)
{
	if (pBegin == NULL || pBegin->next == NULL)//size=1��0ʱ  ����
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
//���� ��������ֳ�������  �����С �ұ�����
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



/*ð��*/
void BubbleSort(Node* pBeign)
{
	if (pBeign == NULL)
		return;
	Node* tail = NULL;/*��������*/
	while (tail != pBeign)
	{
		Node* prev = pBeign;
		Node* cur = prev->next;
		bool flag = true;/*��� ������Ч�ıȽ�*/

		while (cur != tail)/*һ������*/
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
	�ϲ�������������֮����Ȼ����
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
	ֻ����һ�ߣ����м�ڵ�(����ָ��)

	��ͷ���  ����ָ��ָ��ͷ���
	
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
	���ҵ�����ĵ�����K���ڵ㣬ֻ�ܱ���һ��
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
	cout <<"������4������ "<< cur->key << endl;


	cout << endl;
}

/*************************************************/
/*
	�ж������Ƿ�������������󳤶ȣ��󻷵���ڣ�  ����ÿ��������ʱ/�ո��Ӷ�
*/

/*
	�жϴ���������ָ�룩��ʱ��O(n)	�գ�O(1)
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
�����		ʱ��O(n)	�գ�O(1)
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

	/*ȷ�� ����*/
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

	/*����*/
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
	�ж����������Ƿ��ཻ������������

	������1 ��β��ӣ� ת�����ж� ����2 �Ƿ��������
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

	/*����*/
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

//˼·2��ѹջ�� ����ջ������Ԫ��һ���򷵻ظýڵ�.
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
	Josephus��n����Χ��Ȧ�����α��Ϊ1,2,..,n�����ڴ�1�ſ�ʼ���α�����
	������mʱ����m�����˳�����һ�������´�1����
	ѭ����ȥ�������ʣ���Ǹ��˵ı���Ƕ��٣��������� ģ�ⷨ��

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
		while (--num)  //�������� ������ 
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


/*��ѧ��*/
void Josephus()
{
	int n, m, i, s=0;
	printf ("N M = ");   //n:������  m���ȸ���
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


//������������
//Node* RolloverList(Node* list,int k)
//list ��ͷ���
//1->2->3->4->5  k=2   ��ת�� 2-1->4->3->5
// ˼·�� С���ַ�ת����������ƴ��
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
	//test3();//�鲢
	//test6();
	//test7(); //Լɪ��
	//Josephus();
	//test4();  //���ҵ�����ĵ�����K���ڵ㣬ֻ�ܱ���һ��
	//test5(); //�ж� �л�  �ҳ���
	//test8();   //������������
	test9();//�������ڵ�
}