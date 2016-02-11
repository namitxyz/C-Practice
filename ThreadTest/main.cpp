// Multiple producers and Multiple consumers. Used for logging. 
//Execution command: "clang++ -std=c++11 -stdlib=libc++  *.cpp"

#include <iostream>
#include <thread>
#include <queue>
#include <sstream>
#include <mutex>

using namespace std;

template <class T> class PrinterQueue{
	queue<T> m_PrintQueue;
	mutex         m_mtx;

	PrinterQueue() {};
	PrinterQueue(PrinterQueue const &);
	void operator=(PrinterQueue const &);

public:

	static PrinterQueue & getInstance()
	{
		static PrinterQueue instance;
		return instance;
	}

	void ProduceData(T data)
	{
		m_mtx.lock();

		m_PrintQueue.push(data);	

		m_mtx.unlock();
	}

	void ConsumeData(const int iConsumerNumber)
	{
		while(true)
		{
			T data;

			m_mtx.lock();

			if(!m_PrintQueue.empty())
			{		
				data = m_PrintQueue.front();
				m_PrintQueue.pop();
				PerformNonThreadSafeOperations(data, iConsumerNumber);			
			}

			m_mtx.unlock();
			PerformThreadSafeOperations(data, iConsumerNumber);
		}
	}

	void PerformNonThreadSafeOperations(T &data, const int iConsumerNumber)
	{
		cout<<"Consumer Number :"<<iConsumerNumber<<", Data :"<<data<<endl; //cout is not thread safe.
	}

	void PerformThreadSafeOperations(T &data, const int iConsumerNumber)
	{

	}
};

class ProducersConsumers{
	vector<thread> Consumers;
	vector<thread> Producers;
	const int MAX_NO_CONSUMERS = 10;
	const int MAX_NO_PRODUCERS = 100;

public:
	vector<thread> & GetConsumers()
	{
		return Consumers;
	}

	vector<thread> & GetProducers()
	{
		return Producers;
	}

	int GetMaxNumberOfComsumers()
	{
		return MAX_NO_CONSUMERS;
	}

	int GetMaxNumberOfProducers()
	{
		return MAX_NO_PRODUCERS;
	}

	~ProducersConsumers()
	{
		for(int i = 0; i < Consumers.size(); i++)
			if(Consumers[i].joinable())
				Consumers[i].join();

		for(int i = 0; i < Producers.size(); i++)
			if(Producers[i].joinable())
				Producers[i].join();
	}
};

string GetSeedData()
{
	stringstream ss;
	ss<<(rand()% 100);
	string data = ss.str();
	return data;
}

int main() 
{
	ProducersConsumers PC;

	for(int i = 0; i< PC.GetMaxNumberOfComsumers(); i++)
		PC.GetConsumers().push_back(thread(&PrinterQueue<string>::ConsumeData, &PrinterQueue<string>::getInstance(), i));

	for (int i =0; i < PC.GetMaxNumberOfProducers(); i++)
		PC.GetProducers().push_back(thread(&PrinterQueue<string>::ProduceData, &PrinterQueue<string>::getInstance(), GetSeedData()));
	
	return 0;
}
