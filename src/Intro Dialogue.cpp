#include <iostream>
#include <string>
using namespace std;

int main()
{
	string playerName;
	string gender;
	string rivalName;

	cout<<"Hello there!"<<endl;
	cout<<""<<endl;
	cout<<"Welcome to the world of pokepets! My name is Haney!"<<endl;
	cout<<"I study pokepets and so people call me the pokepet Professor!"<<endl;
	cout<<"This world is filled with creatures called pokepets!"<<endl;
	cout<<"For some people, pokepets are just pets, but others use them for fights!"<<endl;
	cout<<""<<endl;
	cout<<"Oh sorry, I got so carried away that I didn't catch your name?"<<endl;

	cout<<""<<endl;
	//enter name
	cin>>playerName;
	cout<<""<<endl;

	cout<<"Are you a boy or girl?"<<endl;
	cout<<""<<endl;
	
	//enter gender
	cin>>gender;
	cout<<""<<endl;

	cout<<"Hi "<<playerName<<'!'<<endl;
	cout<<""<<endl;
	cout<<"You are about to embark on an incredible journey!"<<endl;
	cout<<"But you also had a rival ever since you were young."<<endl;
	cout<<"Err..what was his/her name again??"<<endl; //rival gender will be the same as you

	cout<<""<<endl;
	cin>>rivalName;
	cout<<""<<endl;

	cout<<"Thats right! "<<rivalName<<" was his/her name!"<<endl;
	cout<<"Are you ready?? Because your journey starts now!"<<endl;

	return (0);

}