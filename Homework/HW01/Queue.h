#pragma once
#ifndef _QUEUE_H
#define _QUEUE_H

template <class T>
class Queue
{
public:
	//queue constructor
	Queue()
	{
		//set inital size, array, and current num elements
		size = 1;
		queueArr = new T[size];
		current = -1;
	}

	//queue deconstructor
	~Queue()
	{
		delete[] queueArr;
		queueArr = nullptr;
	}

	//queue copy constructor
	Queue(const Queue& other)
	{
		//copy array size, data, and current
		size = other.size * 2;
		current = other.current;
		queueArr = new T[size];
		for (int i = 0; i < current + 1; i++)
		{
			queueArr[i] = other.queueArr[i];
		}
	}

	//queue copy assignment
	Queue& operator=(const Queue& other)
	{
		//check if copying itself
		if (this == &other)
		{
			return *this;
		}

		//check if not deleted
		if (queueArr != nullptr)
		{
			delete[] queueArr;
		}

		//copy array size, data, and current
		size = other.size * 2;
		current = other.current;
		queueArr = new T[size];
		for (int i = 0; i < current + 1; i++)
		{
			queueArr[i] = other.queueArr[i];
		}

		return *this;
	}

	//add element to queue
	void push(T data)
	{
		//check if queue is full
		if (isFull())
		{
			//copy to new array with twice size
			doubleSize();
		}

		//increase current
		current++;
		//add data to queue
		queueArr[current] = data;
		//sort current data in queue if more than 1 item
		sort();
	}

	//find first added element and remove from queue
	void pop()
	{
		//shift data down by 1
		for (int i = 0; i < size; i++)
		{
			queueArr[i] = queueArr[i + 1];
		}
		//decrease element count by 1
		current--;
	}

	//print all elements to console
	void print()
	{
		for (int i = 0; i < current + 1; i++)
		{
			std::cout << queueArr[i] << " ";
		}
		std::cout << std::endl;
	}

	//return amount of elements in array
	int getSize()
	{
		//current + 1 for size of queue
		return current + 1;
	}

	//return t/f to check if data is on queue
	bool isEmpty()
	{
		//check current size to see if empty
		return current == -1;
	}

	//return t/f to check if queue is full
	bool isFull()
	{
		//check current size to see if empty
		return size == current + 1;
	}

	//increase queue array size if full
	void doubleSize()
	{
		//create temp pointer array
		T* temp = new T[size];

		//copy data over
		for (int i = 0; i < current + 1; i++)
		{
			temp[i] = queueArr[i];
		}

		//double size and reset array to new size
		size *= 2;
		delete[] queueArr;
		queueArr = new T[size];

		//recopy data into updated array
		for (int i = 0; i < current + 1; i++)
		{
			queueArr[i] = temp[i];
		}

		//delete temp array
		delete[] temp;
		temp = nullptr;
	}

	//sort queue array in ascending order
	void sort()
	{
		//store temp variable if needed
		T temp;

		//move through queue and reorder to ascending
		for (int i = 0; i < current; i++)
		{
			for (int j = i + 1; j <= current; j++)
			{
				if (queueArr[i] > queueArr[j])
				{
					temp = queueArr[i];
					queueArr[i] = queueArr[j];
					queueArr[j] = temp;
				}
			}
		}
	}

private:
	T* queueArr;
	int size;
	int current;
};

#endif