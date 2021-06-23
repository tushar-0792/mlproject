#include<bits/stdc++.h>
using namespace std;

struct first{
    float arr[4];
    int type;
};

bool cmp(pair<int,int> p1, pair<int,int> p2)
{
    return (p1.first < p2.first);
}

int power(int n, int m)
{
    if(m != 0)
        return(n*power(n,m-1));
    else
        return 1;
}

float stringTofloat(string s)
{
    int n = s.length();
    if(n == 1)
    {
        float r = int(s[0])-48;
        return r;
    }

    int d;
    for(int i=0; i<n; i++)
    {
        if(s[i] == '.')
            d = i;
    }
    float r1=0;
    float r2=0;
    int x = n-d-1;
    for(int i=0; i<d; i++)
        r1 = r1*10 + (int(s[i])-48);
    for(int i=d+1; i<n; i++)
        r2 = r2*10 + (int(s[i])-48);

    r2 = r2/power(10,x);
    return (r1+r2);
}

int KNN(int K, vector<first>&test, vector<first>&train)
{
    int len = test.size();
    int correct = 0;
    int wrong = 0;
    
    for(int i=0; i<len; i++)
    {
        vector< pair<float, int> >g;

        for(int j=0; j<train.size(); j++)
        {
            float d = 0;
            for(int k=0; k<K; k++)
                d += pow(train[j].arr[k]-test[i].arr[k],2);

            g.push_back(make_pair(sqrt(d),train[j].type));
        }

        sort(g.begin(), g.end(), cmp);

        int s=0,ver=0,vir=0;
        for(int j=0; j<K; j++)
        {
            if(g[j].second == 1)
                s++;
            else if(g[j].second == 2)
                ver++;
            else 
                vir++;
        }

        int max;
        if(s >= ver && s >= vir)
            max = 1;
        else if(ver >= s && ver >= vir)
            max = 2;
        else 
            max = 3;
        
        switch(max)
        {
            case 1:
                if(test[i].type == 1)
                    correct ++;
                else 
                    wrong++;
                break;
            
            case 2:
                if(test[i].type == 2)
                    correct ++;
                else 
                    wrong++;
                break;

            case 3:
                if(test[i].type == 3)
                    correct ++;
                else 
                    wrong++;
                break;
        }
    }
    return correct;
}


int main()
{
    fstream f;
    f.open("/home/cryptoduh/Downloads/Iris.csv",ios::in);
    vector<first>t1,t2,t3,t4,train,test;
    string line;
    getline(f,line);
    int d=1;
    first tr,te;

    int n = 35;
    while(d != 51 && getline(f,line))
    {
        stringstream s(line);
        string temp;
        if(d < n)
        {
            int i = 0;
            while(getline(s, temp, ','))
            {
                if(i != 4)
                {
                    float result = stringTofloat(temp);
                    tr.arr[i] = result;
                    i++;
                }
            }
            tr.type = 1;
            train.push_back(tr);
            d++;
        }
        else
        {
            int i = 0;
            while(getline(s, temp, ','))
            {
                if(i != 4)
                {
                    float result = stringTofloat(temp);
                    te.arr[i] = result;
                    i++;
                }
            }
            te.type = 1;
            test.push_back(te);
            d++;
        }
    }

    while(d != 101 && getline(f,line))
    {
        stringstream s(line);
        string temp;
        if(d < 50+n)
        {
            int i = 0;
            while(getline(s, temp, ','))
            {
                if(i != 4)
                {
                    float result = stringTofloat(temp);
                    tr.arr[i] = result;
                    i++;
                }
            }
            tr.type = 2;
            train.push_back(tr);
            d++;
        }
        else
        {
            int i = 0;
            while(getline(s, temp, ','))
            {
                if(i != 4)
                {
                    float result = stringTofloat(temp);
                    te.arr[i] = result;
                    i++;
                }
            }
            te.type = 2;
            test.push_back(te);
            d++;
        }
    }

    while(d != 151 && getline(f,line))
    {
        stringstream s(line);
        string temp;
        if(d < 100+n)
        {
            int i = 0;
            while(getline(s, temp, ','))
            {
                if(i != 4)
                {
                    float result = stringTofloat(temp);
                    tr.arr[i] = result;
                    i++;
                }
            }
            tr.type = 3;
            train.push_back(tr);
            d++;
        }
        else
        {
            int i = 0;
            while(getline(s, temp, ','))
            {
                if(i != 4)
                {
                    float result = stringTofloat(temp);
                    te.arr[i] = result;
                    i++;
                }
            }
            te.type = 3;
            test.push_back(te);
            d++;
        }
    }

    int max = 0;
    int K;
    for(int k=1; k<100; k = k+2)
    {
        int correct = KNN(k,test,train);
        float per = (correct*100)/test.size();

        if(per > max)
        {
            max = per;
            K = k;
        }

        cout <<"Accuracy of k = " <<k <<" is " <<per <<"%" <<endl;
    }

    cout <<"Maximum accuracy is at k = " <<K <<" and the accuracy is = " <<max <<"%" <<endl;
}
