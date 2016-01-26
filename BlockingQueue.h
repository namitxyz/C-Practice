#include <queue>

template <class T> class BlockingQueue{
private:
    std::queue<T> m_InternalQueue;
    std::atomic<int> m_Readers;
    std::mutex m_Mutex;
    std::shared_mutex m_SharedMutex;

public:
	template <typename T> BlockingQueue()
	{
		m_Readers = 0;
	}

	template <typename T> void Push(T &element)
	{
		m_Mutex.lock();

		while(m_Readers > 0)
		{
			// wait for read to finish
		}

		m_InternalQueue.push(element);
		m_Mutex.unlock();


		//Another solution
		unique_lock<shared_mutex> lck(m_SharedMutex);
		m_InternalQueue.push(element);
	}

	template <typename T> void Pop()
	{
		m_Mutex.lock();

		while(m_Readers > 0)
		{
			// wait for read to finish
		}

		m_InternalQueue.pop(element);
		m_Mutex.unlock();

		// Another solution
		unique_lock<shared_mutex> lck(m_SharedMutex);
		m_InternalQueue.push(element);
	}

	template <typename T> T Front()
	{
		m_Mutex.lock();
		m_Readers++;
		m_Mutex.unlock();

		

		T element = m_InternalQueue.front();

		// Another solution
		shared_lock<shared_mutex> lck(m_SharedMutex);
		T element_2 = m_InternalQueue.front();

		readers --;

		return element; //or element_2
	}
};
