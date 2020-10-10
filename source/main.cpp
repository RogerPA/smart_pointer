// Copyright 2020 Roger Peralta Aranibar
#include "smart_pointer/smart_pointer.hpp"
#include<iostream>
#include<string>
#include<string.h>

using namespace std;

struct Person
{
    int age;
    string pName;

    public:
        Person(): pName(0),age(0)
        {
        }
        Person(string pName, int age): pName(pName), age(age)
        {
        }
        ~Person()
        {
        }

        void Display()
        {
            cout<<"Name = " << pName<<endl;
            cout<<"Age = " << age<<endl;
        }
        void Shout()
        {
            cout<<"Ooooooooooooooooo"<<endl;
        } 
};

int main() {

  SmartPointer<Person> p(new Person("Luis",20));

  //cout<<p->GetReferenceCount();
  //cout<<p.GetReferenceCount();

  SmartPointer<int> p2(new int (5));
  if (p2.GetPointer()==nullptr)
    cout<<"Null"<<endl;

  // p2.GetPointer()=5;
  // cout<<*p2<<endl;
  // *(p2.GetPointer())=10;
  // cout<<*p2<<endl;

  SmartPointer<int> p3(new int (5));
  SmartPointer<int> copy_pointer = p3;

  // cout<<copy_pointer.referencia<<endl;
  // cout<<p3.referencia<<endl;
  cout<<p3.GetReferenceCount()<<endl;

  
  return 0;
}
