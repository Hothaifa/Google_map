#include <string>
#include <algorithm>
#include <tr1/unordered_map>
#include <iterator>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <vector>
#include <iterator>
#include <time.h>
#include <iostream>
#include <iostream>
#include <sparsehash/dense_hash_map>
#include <stdio.h>
#include <string.h>
using google::dense_hash_map;  
using std::tr1::hash; 
using namespace std;
using std::string;

bool ProcessInput(const string& inChar, vector<string> *invector);
void Processmax( dense_hash_map < string, int>* ins, vector<int> *inc, vector<string>      *outs, vector<int> *outc);

int main()
{
time_t start, stop;
time(&start);
ofstream finall;
vector<int> usrsc,artc,tmusrc,tmart2c,atrsc,tmartc;
vector<string> tmart,tmusr,tmart2;
vector< vector<string> > usrlist,artlist;
string x1,x2;
ifstream ifTraceFile;
bool f,f2;
dense_hash_map < string, int > a;
dense_hash_map < string, int > u;
a.set_empty_key(string());
u.set_empty_key(string());

int kl=0;
ifTraceFile.open ("data2.tr", std::ifstream::in);
while (ifTraceFile.good ())
{
    ifTraceFile>>x1>> x2;


    if (kl==0)
    {
        a.insert(make_pair(x1,0));
        u.insert(make_pair(x2,0));
        usrlist.push_back((vector<string>()));
        usrlist[0].push_back(x1);
        artlist.push_back((vector<string>()));
        artlist[0].push_back(x2);
        usrsc.push_back(1);
        artc.push_back(1);
        atrsc.push_back(1);

    }
    else
    {

        dense_hash_map < string, int>::iterator itn;
        itn=a.find(x1);
        if (itn == a.end())
        {
            a.insert(make_pair(x1,(artlist.size())));
            artlist.push_back((vector<string>()));
            artlist[(artlist.size()-1)].push_back(x2);
            artc.push_back(1);
            atrsc.push_back(1);
        }
        else
        {
            f=ProcessInput(x2, &artlist[itn->second]);
            if(f)
            {
                artlist[itn->second].push_back(x2);
                atrsc[itn->second]+=1;
                artc[itn->second]+=1;
            }
            else
                atrsc[itn->second]+=1;

        }


         dense_hash_map < string, int>::iterator its;
        its=u.find(x2);
        if (its == u.end())
        {
            u.insert(make_pair(x2,(usrlist.size())));
            usrlist.push_back((vector<string>()));
            usrlist[(usrlist.size()-1)].push_back(x1);
            usrsc.push_back(1);

        }
        else
        {
            f2=ProcessInput(x1, &usrlist[its->second]);

            if(f2)
            {
                usrlist[its->second].push_back(x1);
                usrsc[its->second]+=1;

            }

        }

    }

    kl++;
}
ifTraceFile.close();
Processmax(&a, &artc, &tmart, &tmartc);
Processmax(&a, &atrsc, &tmart2 ,&tmart2c);
Processmax(&u, &usrsc ,&tmusr, &tmusrc);
int width=15;
cout <<"article has Max. review by users Top 1: "<<tmart.at(0)<<'\t'<<tmartc.at(0)<<endl;
cout <<"article has Max. review by users Top 2: "<<tmart.at(1)<<'\t'<<tmartc.at(1)<<endl;
cout <<"article has Max. review by users Top 3: "<<tmart.at(2)<<'\t'<<tmartc.at(2)<<endl;
cout <<endl;
cout <<"article has Max. review Top 1: "<<tmart2.at(0)<<'\t'<<tmart2c.at(0)<<endl;
cout <<"article has Max. review Top 2: "<<tmart2.at(1)<<'\t'<<tmart2c.at(1)<<endl;
cout <<"article has Max. review Top 3: "<<tmart2.at(2)<<'\t'<<tmart2c.at(2)<<endl;
cout <<endl;
cout <<"user who edited most articles Top 1: "<<tmusr.at(0)<<'\t'<<tmusrc.at(0)<<endl;
cout <<"user who edited most articles Top 2: "<<tmusr.at(1)<<'\t'<<tmusrc.at(1)<<endl;
cout <<"user who edited most articles Top 3: "<<tmusr.at(2)<<'\t'<<tmusrc.at(2)<<endl;

finall.open ("results");
finall << "Q1 results:"<<endl;;
finall <<"article has Max. review Top 1: "<<setw(width)<<tmart2.at(0)<<setw(width)<<tmart2c.at(0)<<endl;
finall <<"article has Max. review Top 2: "<<setw(width)<<tmart2.at(1)<<setw(width)<<tmart2c.at(1)<<endl;
finall <<"article has Max. review Top 3: "<<setw(width)<<tmart2.at(2)<<setw(width)<<tmart2c.at(2)<<endl;
finall<<endl;

finall<<"article has Max. review by users Top 1: "<<setw(width)<<tmart.at(0)<<setw(width)<<tmartc.at(0)<<endl;
finall <<"article has Max. review by users Top 2: "<<setw(width)<<tmart.at(1)<<setw(width)<<tmartc.at(1)<<endl;
finall <<"article has Max. review by users Top 3: "<<setw(width)<<tmart.at(2)<<setw(width)<<tmartc.at(2)<<endl;
finall<<endl;
finall <<"user edited most articles Top 1: "<<setw(width)<<tmusr.at(0)<<setw(width-5)<<tmusrc.at(0)<<endl;
finall <<"user edited most articles Top 2: "<<setw(width)<<tmusr.at(1)<<setw(width-5)<<tmusrc.at(1)<<endl;
finall <<"user edited most articles Top 3: "<<setw(width)<<tmusr.at(2)<<setw(width-5)<<tmusrc.at(2)<<endl;
finall.close ();
time(&stop);
cout<<"Finished in about "<< difftime(stop, start)<< " seconds"<<endl;

return 0;
}

void Processmax(  dense_hash_map< string,int >* ins, vector<int> *inc, vector<string> *outs, vector<int> *outc)
{
int index=0;
int l=0;
 dense_hash_map < string, int>:: iterator iti;
string value;
while(l!=4)
{
    vector<int>::iterator it=max_element(inc->begin(), inc->end());
    index = distance(inc->begin(), it);

    for (iti = ins->begin(); iti != ins->end(); ++iti)
    {
        if (iti->second == index)
        {
            value = iti->first;
            break;
        }
    }
    outs->push_back(value);
    outc->push_back(inc->at(index));
    inc->at(index)=0;
    l++;
  }
}

bool ProcessInput(const string& inChar, vector<string> *invector)
{
 bool index=true;
 vector<string>::iterator it=find(invector->begin(), invector->end(), inChar);
 if (it!=invector->end())
    index=false;

 return index;
}