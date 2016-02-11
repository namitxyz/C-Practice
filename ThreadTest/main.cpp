// Multiple producers and Multiple consumers. Used for logging.
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

	void AddToQueue(T data)
	{
		m_mtx.lock();

		m_PrintQueue.push(data);	

		m_mtx.unlock();
	}

	T GetDataFromQueue(int iConsumerNumber)
	{	
 	    m_mtx.lock();
 	    T data;	
		if(!m_PrintQueue.empty())
		{		
			data = m_PrintQueue.front();
			m_PrintQueue.pop();
			PerformNonThreadSafeOperations(iConsumerNumber, data);			
		}
		m_mtx.unlock();

		return data;
	}

	void PerformNonThreadSafeOperations(int iConsumerNumber, T data)
	{
		cout<<"Consumer Number :"<<iConsumerNumber<<", Data :"<<data<<endl; //cout is not thread safe.
	}

	void PerformThreadSafeOperations(T data)
	{

	}
};

template <typename T> void AddData(int n) 
{
	for(int i = 0; i< n; i++)
	{
		stringstream ss;
		ss<<i;
		T data = ss.str();
		PrinterQueue<string>::getInstance().AddToQueue(data);
	}
		
}

template <typename T> void ConsumeData(int iConsumerNumber)
{
	while(1)
	{
		T data = PrinterQueue<string>::getInstance().GetDataFromQueue(iConsumerNumber);
		
		PrinterQueue<string>::getInstance().PerformThreadSafeOperations(data);
	}
}

int main() 
{
  std::thread Producer_1 (AddData<string>, 100);   
  std::thread Producer_2 (AddData<string>, 120);       
  std::thread Consumer_1 (ConsumeData<string>, 1);  
  std::thread Consumer_2 (ConsumeData<string>, 2);  

  // synchronize threads:
  Producer_1.join();                // pauses until first finishes 
  Producer_2.join();
  Consumer_1.join();            
  Consumer_2.join();

  return 0;
}
