#include <iostream>
#include <fstream>
using namespace std;

int lcs(string a, string b)
{
    int lena,lenb,i,j,**mat;
    string lcs="";
    
    lena=a.length();
    lenb=b.length();
    mat=new int*[lena];
    for(i=0;i<lena;i++)
        mat[i]=new int[lenb];
    
    for(i=0;i<lena;i++)
        for(j=0;j<lenb;j++)
            mat[i][j]=0;
    
    for(i=1;i<lena;i++)
        for(j=1;j<lenb;j++)
        {
            if(a[i-1]==b[j-1])
                mat[i][j]=mat[i-1][j-1]+1;
            else 
                mat[i][j]=max(mat[i-1][j],mat[i][j-1]);
        }

    i=lena-1;
    j=lenb-1;
    while(i>=1&&j>=1)
    {
        if(mat[i][j]==mat[i-1][j])
            i--;
        else if(mat[i][j]==mat[i][j-1])
            j--;
        else 
        {
            lcs=a[i-1]+lcs;
            i--;
            j--;
        }
    }
    cout<<lcs<<" "<<mat[lena-1][lenb-1];
    return mat[lena-1][lenb-1];
}

int main()
{
    string a,b,c;
    char chr;
    ifstream fin;

    fin.open("8. LCS\\6400.txt",ios::in);
    fin>>a>>b>>c;
    cout<<"String 1: "<<a;
    cout<<"\nString 2: "<<b;
    cout<<"\nString 3: "<<c;
    cout<<"\n\nLCS 1&2:\n";
    lcs(a,b);
    cout<<"\n\nLCS 2&3:\n";
    lcs(b,c);
    cout<<"\n\nLCS 1&3:\n";
    lcs(c,a);
    
    fin.close();
    return 0;
}