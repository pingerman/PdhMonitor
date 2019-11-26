#define _CRT_SECURE_NO_WARNINGS

#ifndef RING_CONTAINER_H
#define RING_CONTAINER_H

#include <mutex>

namespace Containers
{
	template<typename T>
	class RingContainer
	{
	private:

		int count;

		std::mutex mutex;
		std::shared_ptr<T> buffer;
		const int capacity;
		int head = 0;
		int tail = 0;
		bool full = false;

	public:

		RingContainer(int count) :
			buffer(std::shared_ptr<T>(new T[count], std::default_delete<T[]>())),
			capacity(count)
		{
		}

		/*RingContainer(int count) :
			capacity(count)
		{
			buffer = std::make_shared<float>(new float[count], std::default_delete<T[]>());
		}*/

		void Put(T item)
		{
			std::lock_guard<std::mutex> lock(mutex);

			buffer.get()[head] = item;

			if(full)
			{
				tail = (tail + 1) % capacity;
			}

			head = (head + 1) % capacity;

			full = head == tail;
		}

		T Get() 
		{
			std::lock_guard<std::mutex> lock(mutex);

			if(Empty())
			{
				return T();
			}

			auto value = buffer[tail];
			full = false;
			tail = (tail + 1) % capacity;

			return value;
		}

		std::shared_ptr<T> GetAll() 
		{
			return buffer;
		}

		void Reset() 
		{
			std::lock_guard<std::mutex> lock(mutex);
			head = tail;
			full = false;
		}

		bool Empty() const 
		{
			return (!full && head == tail);
		}

		bool Full() const 
		{
			return full;
		}

		int Capacity() const 
		{
			return capacity;
		}

		int Count() const 
		{
			int length = capacity;

			if(!full)
			{
				if(head >= tail)
				{
					length = head - tail;
				}
				else
				{
					length = capacity + head - tail;
				}
			}

			return length;
		}
	};

}

#endif
