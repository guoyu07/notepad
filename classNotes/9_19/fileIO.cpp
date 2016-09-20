// Example program
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
  string input, output;
  ofstream ofile("output.dat");
  cout << "Input: " << endl;
  while(true){
      cin >> input;
      if(input == "end") break;
      ofile << input << endl;
      }
    ofile.close();
    
    cout << "Output: " << endl;
    ifstream displayFile("output.dat");
    
    while(!displayFile.eof()){
        displayFile >> output;
        cout << output << endl;
        }
    return 0;
}
