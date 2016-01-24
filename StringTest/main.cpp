#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
void SplitString(string &input, char delim, vector<string> &tokens);
void GenerateString(vector<string> &tokens, char delim, string &output);
int main()
{
	string test = "    namit  ,,,,,,,    is   a  ,,,, good     boy       ";

	const char * cTest = test.c_str();

	cout<<"Input string :";
	for (int i = 0; i < test.size(); i++)
		cout<<test[i];
	
	int found = test.find("is");
	cout<<endl<<"Found 'is' at :"<<found<<endl;

	// Replace all commas with a pipe delimiter and get rid of the unnecessary spaces through trimming. Could be extended to clean up extra spaces without a pipe as well.

	vector<string> tokens;
	vector<string> Newtokens;
	string NewOutput;
	string FinalString;

	SplitString(test, ' ', tokens); // split the input string and trim unnecessary spaces

	GenerateString(tokens, ' ', NewOutput); // create a new string with only one space

	SplitString(NewOutput, ',', Newtokens); // split the new string and remove all commas

	GenerateString(Newtokens, '|', FinalString);  // replace the comma with a single pipe

	cout<<FinalString<<endl;

	return 0;
}

void GenerateString(vector<string> &tokens, char delim, string &output)
{
	for (int i =0; i < tokens.size(); i++)
		
		if(i == tokens.size() - 1)
			output = output + tokens[i];
		else
			output = output + tokens[i] + delim;

}
void SplitString(string &input, char delim, vector<string> &tokens)
{
	stringstream ss;
	ss<<input;
	string SingleElement;
	string NewOutput;

	while(getline(ss, SingleElement, delim))
	{
		if(!SingleElement.empty())
			tokens.push_back(SingleElement);
	}
}