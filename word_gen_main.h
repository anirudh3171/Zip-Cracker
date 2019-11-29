#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <math.h>
#include <iostream>
class Word_Gen_main{
    public:
    std::vector<int> wrd;
    std::vector<bool> chng;

    int min, countr;

    std::string list, op;

    void initial_setup(int);
    void inc_count();
    void initial_build();
    int current;
    Word_Gen_main(int, int, std::string);
    int resume(std::string);

    std::string next();
    void run();
};

Word_Gen_main::Word_Gen_main(int new_max, int new_min, std::string new_list){
  if(new_max > 0 && new_min > 0 && new_min <= new_max && new_list.size() != 0){
    min = new_min;
    countr = new_max;
    list = new_list;

    initial_setup(countr);
  }
}

int Word_Gen_main::resume(std::string str){
  int total = 0;

  wrd.clear();
  chng.clear();

  for(int i = 0; i < str.size(); i++){
    for(int j = 0; j < list.size(); j++){
      if(str[i] == list[j])
        {
        total+=(list.size()-j-1)*pow(10,(str.size()-i-1));

        wrd.push_back(j);
        chng.push_back(false);
        break;
      }
    }
  }
  total += 1;
  return total;
}

void Word_Gen_main::run(){
  while(min <= countr){
    initial_build();
    inc_count();
  }
}

std::string Word_Gen_main::next()
{
  if(min <= countr)
  {
    initial_build();
    inc_count();

    return op;
  }

  return "";
}


void Word_Gen_main::initial_setup(int num)
{
  current = num;

  for(int i = 0; i < num; i++)
  {
    wrd.push_back(0);
    chng.push_back(false);
  }
}

void Word_Gen_main::inc_count()
{
  for(int i = countr - 1; i>=0 ; i--)
    {
    if(chng[i])
    {
      if(wrd[i] == list.size() - 1)
      {
        if(i == 0)
        {
          wrd.clear();
          chng.clear();

          if(countr != min)
            {
            countr--;
            initial_setup(countr);
          }
          else
          {
            countr--;
          }
        }
        else
        {
          chng[i - 1] = true;
          wrd[i] = 0;
          chng[i] = false;
        }
      }
      else
      {
        wrd[i]++;
        chng[i] = false;
      }
    }
  }
}

void Word_Gen_main::initial_build()
{
  op.clear();
  for(int i = 0; i < wrd.size(); i++)
  {
    op += list[wrd[i]];
  }

  chng[countr - 1] = true;
}


