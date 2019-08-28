// TypedStack.h: interface for the CTypedStack class.

//模板堆栈

#ifndef _CTSTACK_H
#define _CTSTACK_H

//扩容量
#define STACK_EXTEND_SIZE			10 

template <class T> 
class CTypedStack  
{
public:
	CTypedStack(int nCapacity = 10);
	virtual ~CTypedStack();

public:

	//入栈
	void Push(const T& item);

	//出栈
	T Pop();

	//访问栈顶元素
	T Peek();

	//检查堆栈是否为空
	BOOL IsEmpty() const;

	//清除栈中的元素,但并不释放内存
	void ClearItem();

	//返回堆栈中的元素的个数
	int GetSize();

	//在堆栈中搜索
	int Search(const T& item);


private:

	//堆栈栈顶点位置
	int m_nTop;

	//事实上,有三种方法:
	//第一,通用数组,并指定数组长度
	//第二,动态数组,在构造函数中分配
	//第三,动态收集数组,这种方法时间开销大一点,但方便,
	
	//存储元素的动态数组
	T* m_ptStack;

	//堆栈容量(动态安全数组)
	int m_nCapacity;


};


#ifndef _CTSTACK_CPP
#define _CTSTACK_CPP
#include "TypedStack.cpp"
#endif

#endif 

