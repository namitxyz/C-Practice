// Multiple producers and single consumer. Used for logging.
#include <iostream>
#include <thread>
#include <queue>
#include <sstream>
#include <mutex>

using namespace std;
mutex mtx;

class PrinterQueue{
	queue<string> m_PrintQueue;
public:
	void AddToQueue(string data)
	{
		mtx.lock();

		m_PrintQueue.push(data);	

		mtx.unlock();
	}

	string GetDataFromQueue(int iConsumerNumber)
	{		
		if(!m_PrintQueue.empty())
		{
			mtx.lock();
			
			string data;
			data = m_PrintQueue.front();
			m_PrintQueue.pop();
			cout<<"Consumer Number :"<<iConsumerNumber<<"Data :"<<data<<endl;
			
			mtx.unlock();
		}

		return "";
	}
};

PrinterQueue DataQueue;

void AddData(int n) 
{
	for(int i = 0; i< n; i++)
	{
		stringstream ss;
		ss<<i;
		DataQueue.AddToQueue(ss.str());

	}
		
}

void ConsumeData(int iConsumerNumber)
{
	while(1)
	{
		DataQueue.GetDataFromQueue(iConsumerNumber);
	}
}

int main() 
{
  std::thread Producer_1 (AddData, 100);     
  std::thread Producer_2 (AddData, 50);     
  std::thread Consumer_1 (ConsumeData, 1);  


  // synchronize threads:
  Producer_1.join();                // pauses until first finishes
  Producer_2.join(); 
  Consumer_1.join();            

  return 0;
}