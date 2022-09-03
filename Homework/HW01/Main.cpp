#include <iostream>

#include "Queue.h"
#include "Alberto.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

using namespace std;

int main()
{
	//check for leak
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//create queues
	Queue<int> intQueue = Queue<int>();
	Queue<char> charQueue = Queue<char>();
	Queue<double> doubleQueue = Queue<double>();
	Queue<AlbertoClass> albertoQueue = Queue<AlbertoClass>();

	//int
	cout << "------Ints------" << endl << endl;

	//check if empty
	cout << "Is the int queue empty? " << intQueue.isEmpty() << endl << endl;

	//push data
	cout << "Adding Data..." << endl << endl;
	intQueue.push(5);
	intQueue.push(2);
	intQueue.push(10);
	intQueue.push(1);

	//check if empty
	cout << "Is the int queue empty? " << intQueue.isEmpty() << endl << endl;
	//get size of queue
	cout << "The size of the int queue is " << intQueue.getSize() << endl << endl;

	//copy constructor
	cout << "------Used Copy Constructor------" << endl << endl;
	Queue<int> newIntQueue(intQueue);

	//print queue and copied queue
	cout << "------Printing Original Queue------" << endl;
	intQueue.print();
	cout << endl;

	cout << "------Printing Copied Queue------" << endl;
	newIntQueue.print();
	cout << endl;

	//pop data off both queues
	cout << "Removing Data From Both Queues..." << endl  << endl;
	intQueue.pop();

	newIntQueue.pop();
	newIntQueue.pop();

	//show updated size of queue
	cout << "The size of the original int queue is now " << intQueue.getSize() << endl << endl;

	//print queue and copied queue
	cout << "------Printing Original Queue------" << endl;
	intQueue.print();
	cout << endl;

	cout << "------Printing Copied Queue------" << endl;
	newIntQueue.print();
	cout << endl;

	cout << "------Used Copy Assignment------" << endl << endl;
	newIntQueue = intQueue;

	cout << "------Printing Copied Queue------" << endl;
	newIntQueue.print();
	cout << endl;

	//char
	cout << "------Chars------" << endl << endl;

	//push data
	cout << "Adding Data..." << endl << endl;
	charQueue.push('a');
	charQueue.push('q');
	charQueue.push('g');

	//print queue
	cout << "------Printing queue------" << endl;
	charQueue.print();
	cout << endl;

	//pop data off queue
	cout << "Removing Data from Queue..." << endl << endl;
	charQueue.pop();

	//print queue
	cout << "------Printing Queue------" << endl;
	charQueue.print();
	cout << endl;

	//double
	cout << "------Doubles------" << endl << endl;

	//push data
	cout << "Adding Data..." << endl << endl;
	doubleQueue.push(2.34);
	doubleQueue.push(11.37);
	doubleQueue.push(3.145);

	//print queue
	cout << "------Printing Queue------" << endl;
	doubleQueue.print();
	cout << endl;

	//pop data off queue
	cout << "Removing Data from Queue..." << endl << endl;
	doubleQueue.pop();
	doubleQueue.pop();

	//print queue
	cout << "------Printing Queue------" << endl;
	doubleQueue.print();
	cout << endl;

	//alberto
	cout << "------Albertos------" << endl << endl;

	//push data
	albertoQueue.push(AlbertoClass(84));
	albertoQueue.push(AlbertoClass());
	albertoQueue.push(AlbertoClass(23));
	
	//print queue
	cout << "------Printing Queue------" << endl;
	albertoQueue.print();
	cout << endl;
	//pop data off queue
	cout << "Removing Data from Queue..." << endl << endl;
	albertoQueue.pop();

	//print queue
	cout << "------Printing Queue------" << endl;
	albertoQueue.print();
	cout << endl;
}