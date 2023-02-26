#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>
#include "tests.h"

using namespace std;

int Tests(){
  int option = 0;

  cout<< "This is the test menu:\n";
  cout<< "Not much here right now.\n\n";
  cout<< "Most tests are for service_provided\n\n";
  while(option != 99){
    cout<<"Please select from the following menu: \n";
    cout << " 1. copy test, bad data\n";
    cout << " 2. copy test, good data\n";
    cout << " 3. save/load test\n";
    cout << " 4. vector testing\n";
    cout << "99. Quit\n\n";

    cout << "option: ";
    
    cout << "\n";
    cin>>option;
		cin.clear();
		cin.ignore(100, '\n');
    cout<<"\n\n";

    switch(option){
    case 1: 
      //copy test with bad data
      {
        int error = 0;
        vector<int> date;
        vector<int> date_entered;
        vector<int> time_entered;
        float cost = 3.1;
        string provider_num;
        string member_number;
        string service_code;
        string comments;
        service_provided test;
        service_provided test2 (date, cost, provider_num,member_number,
                               service_code, comments);
        error = test.copy(test2);
        test2.display();
        if(error == 0)
          cout << "ERROR, as expected\n\n";
        else
          cout << "no error\n\n";
        

      }  
      break;

    case 2: 
    {
      //copy test with good data
      int error = 0;
      vector<int> date{2,28,2011};
      float cost = 3.1;
      string provider_num = "123456789";
      string member_number = "987654321";
      string service_code = "134256";
      string comments = "This is a fine how-do-you-do.";
      service_provided test;
      service_provided test2(date, cost, provider_num, member_number, 
                             service_code, comments);
      error = test.copy(test2);
      cout <<  "\ntest2\n";
      test2.display();
      cout <<  "\ntest\n";
      test.display();
      if(error == 0)
          cout << "\nERROR\n\n";
        else
          cout << "\nno error\n\n";

                            
    }
      break;

    case 3: 
    {
      //copy 
      int error = 0;
      vector<int> date{2,28,2011};
      float cost = 3.1;
      string provider_num = "123456789";
      string member_number = "987654321";
      string service_code = "134256";
      string comments = "This is a fine how-do-you-do.";
      service_provided test;
      service_provided test2(date, cost, provider_num, member_number, 
                             service_code, comments);
      ofstream testsave;
      testsave.open ("test_service.txt");
      error = test2.save(testsave);
      testsave.close();
      if(error == 0)
          cout << "\nERROR saving\n";
        else
          cout << "\nno error saving\n";

      ifstream testload;
      testload.open ("test_service.txt");
      error = test.load(testload);
      testload.close();
      if(error == 0)
          cout << "\nERROR loading\n";
        else
          cout << "\nno error loading\n";

//      error = test.copy(test2);
      cout <<  "\n\ntest2\n";
      test2.display();
      cout <<  "\n\ntest\n";
      test.display();
      if(error == 0)
          cout << "\n\nERROR\n\n";
        else
          cout << "\n\nno error\n\n";
    }
        break;

    case 4: 
    {
      vector<service_provided> list;
      cout << list.size() << "\n\n";
      service_provided service;
//      list.push_back(service);
    }
        break;
    case 99:
        cout<<"Have a good day!\n";
        break;
    default:
        cout<<"Invalid entry, please try again\n";
  }
}


    return 0;


  return 0;
}

