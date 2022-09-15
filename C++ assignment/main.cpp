#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <random>
#include<algorithm> 
using namespace std;


vector<int> getNumbers(){
	random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(25, 63); // define the range
	vector<int> randomNumbers;
    for(int n=0; n<5; ++n)
        randomNumbers.push_back(distr(gen)); //add each number generated to the randonNuber vector
    
 

    sort(randomNumbers.begin(),randomNumbers.end())	; //sorts the random values in ascending order
    return randomNumbers;
	
	
}
void setPowerBall(vector<int> & randomNumbers ){
	random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(48, 92); // define the range
    randomNumbers.push_back(distr(gen));
    
    
	
}
void showNumbers(const vector<int>&v){
	for (auto i = v.begin(); i != v.end(); ++i)
		if (*i == v[5]){
		 cout << "PB " << v[5];	//appeds the PB tag on the last element in the vector
		}else{
		 cout << *i << " ";	// prints all the other values in the vector
		}
       
}
int main(int argc, char** argv) {
  int lotteryNumber; // number of lotter numbers the user wants to generate
  cout << "How many lotto numbers do you want to generate?";//string to guide the user on what to do
  cin >> lotteryNumber; // allows the user to enter a value
	for (int i;i<lotteryNumber;i++){
	vector<int> randomValues=getNumbers(); //the getNumber func returns a vector which is saved to the random number variable
	setPowerBall(randomValues); //pass the vector above to the setPowerball func
	showNumbers(randomValues); //utility func to show the output of the code
	
	cout << "\n"; //separates all the different numbers
	
	}
	string seeMoreNumbers;
	cout <<"Would you like to see more numbers? ('Y' or 'N')";
	cin >> seeMoreNumbers;
	
	if(seeMoreNumbers=="Y"){
	int lotteryNumber;
	cout << "How many lotto numbers do you want to generate?";
    cin >> lotteryNumber;
	for (int i;i<5;i++){
	vector<int> randomValues=getNumbers();
	setPowerBall(randomValues);
	showNumbers(randomValues);
	
	cout << "\n";
	
	}
	

}
	return 0;
}