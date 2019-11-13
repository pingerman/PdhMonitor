#define _CRT_SECURE_NO_WARNINGS

#ifndef CONTAINER_H
#define CONTAINER_H

namespace Containers
{
	template<typename T>
	class Node
	{
	private:

	public:
		T* value = nullptr;
		Node<T>* Next = nullptr;

		T* GetValue() 
		{
			return value;
		}

		void SetValue(T value) 
		{
			this->value = value;
		}

		void Attach(Node<T>* node) 
		{
			if (Next != nullptr)
				return;

			Next = node;
		}

		Node() 
		{
			Node(nullptr);
		}

		Node(T* value) 
		{
			this->value = value;
			Next = nullptr;
		}

		~Node() 
		{
		}
	};

	template<typename T>
	class Container
	{
	private:
		Node<T>* head = nullptr;

		int count;
		int countLimit = 100;

	public:

		void AddToEnd(T* value) 
		{
			Node<T>* node = new Node<T>(value);

			if (head == nullptr)
			{
				head = node;
				count++;
				return;
			}
			else
			{
				Node<T>* current = head;

				while (current->Next != nullptr)
				{
					current = current->Next;
				}

				current->Attach(node);
				count++;
			}
		}
		
		void AddToTop(T* value) 
		{
			Node<T>* node = new Node<T>(value);

			node->Attach(head);

			head = node;

			count++;
		}

		bool RemoveFromEnd() 
		{
			if (head == nullptr)
			{
				return false;
			}
			else
			{
				Node<T>* current = head;
				Node<T>* last = head;

				while (current->Next != nullptr)
				{
					last = current;
					current = current->Next;
				}

				T* value = current->value;

				if(value != nullptr)
					delete value;

				if(current != nullptr)
					delete current;

				if (last != nullptr)
				{
					last->Next = nullptr;
				}
			}

			count--;
			return true;
		}

		void Push(T* value) 
		{
			if (countLimit >= 0 && count >= countLimit)
			{
				RemoveFromEnd();
			}

			AddToTop(value);
		}

		T** Read(int& count) 
		{
			if (head == nullptr)
			{
				return nullptr;
			}
			else
			{
				int iterator = 1;

				Node<T>* current = head;

				while(current->Next != nullptr)
				{
					iterator++;
					current = current->Next;
				}

				T** arr = new T*[iterator];
				current = head;
				arr[0] = current->GetValue();

				if (current->Next == nullptr)
				{
					count = iterator;
					return &arr[0];
				}

				for (int i = 1; current->Next != nullptr; i++)
				{
					arr[i] = current->GetValue();
					current = current->Next;
				}

				count = iterator;
				return arr;
			}

			return nullptr;
		}

		Container() 
		{
			Container(100);
		}

		Container(int countLimit) 
		{
			head = nullptr;
			this->countLimit = countLimit;
		}

		~Container() 
		{
			while (RemoveFromEnd());
		}
	};

}

#endif