
// TypedStack.cpp: implementation of the CTypedStack class.
#include "stdafx.h"

#ifndef _CTSTACK_CPP
#define _CTSTACK_CPP
#include "TypedStack.h"
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//构造函数
template <class T>
CTypedStack<T>::CTypedStack(int nCapacity) : m_nTop(-1)
{
	m_nCapacity = nCapacity;
	if(m_nCapacity < 1) m_nCapacity = 1;
	//初始化数组
	m_ptStack = new T[m_nCapacity];
	if(m_ptStack == NULL)
	{
		AfxMessageBox("内存分配失败!");
		exit(1);
	}
}

template <class T>
CTypedStack<T>::~CTypedStack()
{
	if(m_ptStack)
	{
		delete[] m_ptStack;
		m_ptStack = NULL;
	}
}

//Push  (入栈)
template <class T>
void CTypedStack<T>::Push(const T& item)
{
	if(m_nTop == (m_nCapacity - 1))
	{
		//需要扩容
		T* ptNewStack = new T[m_nCapacity + STACK_EXTEND_SIZE];
		if(ptNewStack == NULL)
		{
			AfxMessageBox("内存分配失败!");
			exit(1);		
		}
		
		//拷贝元素
		T* ptSrc = m_ptStack;
		T* ptDst = ptNewStack;
		
		//此时, 
		for(int i = 0; i <= m_nTop; i++)
			*ptDst++ = *ptSrc++;
		
		//删除旧堆栈
		delete[] m_ptStack;

		//让它指向新的地址
		m_ptStack = ptNewStack;
		
		//容量大小记录器对应改变
		m_nCapacity += STACK_EXTEND_SIZE;
	}

	//将数据压入堆栈
	m_nTop++;
	m_ptStack[m_nTop] = item;
}

//Push (出栈)
template <class T>
T CTypedStack<T>::Pop()
{
	if(m_nTop == -1)
	{
		AfxMessageBox("堆栈已空!");
		exit(1);		
	}

	//如果T是一个类对象, " = " 运算符可能要重载
	T tTop = m_ptStack[m_nTop];
	m_nTop--;
	return tTop;
}

//Peek  (拾取, 访问栈顶元素)
template <class T>
T CTypedStack<T>::Peek()
{
	if(m_nTop == -1)
	{
		AfxMessageBox("堆栈已空!");
		exit(1);		
	}

	T tTop = m_ptStack[m_nTop];
	return tTop;
}

//在堆栈中搜索
//返回被搜索条目位于堆栈中距离栈顶的整数偏移量.
//如果条目没有在堆栈中, 则返回 -1 .
template <class T>
int CTypedStack<T>::Search(const T& item)
{
	//如果堆栈为空, 返回
	if(m_nTop == -1) return -1;
	
	int i = m_nTop;
	while(i > -1)
	{
		//比较位于栈中的条目
			if(m_ptStack[i] == item)
			return (m_nTop - i);
		i--;
	}
	return -1;
}


//检查堆栈是否为空
template <class T>
BOOL CTypedStack<T>::IsEmpty() const
{
	return (m_nTop == -1);
}

//从栈中清除元素, 但并不释放内存
template <class T>
void CTypedStack<T>::ClearItem()
{
	m_nTop = -1;
}

//返回堆栈中的元素的个数(栈顶下标加1)
template <class T>
int CTypedStack<T>::GetSize()
{
	return (m_nTop + 1);
}

