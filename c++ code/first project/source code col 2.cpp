#include<iostream>// made by Manas Makde
#include<cstdlib>
#include<math.h>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;
int exist(char s[100])//to check if file exists
{
	fstream f;
	f.open(s,ios::in);
	if(!f)
		return 0;
	return 1;
}
int no_digits(double f)//to tell the no. of digits left to the decimal point
{
    int n,i=0;
    n=int(f);
 while(n!=0)
 {
     i++;
  n/=10;
 }
return i;
}
int telldigit(char c)//to return the digit if in char
{
 return int(c)-48;
}
void assign(double a[10],char s[100],double &sample,double &value)// assigns parameters to a[][] for further calculations
{
int m=0,neg=0,i,n=-1,stat=1,t=1;
 t=strlen(s);
 s[t-1]=' ';
 s[t]='\0';
for(i=0;i<strlen(s);i++)
{
if(isdigit(s[i])&&stat==1)
{
 a[n]=a[n]*10+telldigit(s[i]);
}
else if(isdigit(s[i])&&stat==0)
{
a[n]+=telldigit(s[i])*pow(10.0,-1*t);
t++;
}
else if(s[i]=='.')
stat=0;

else if(s[i]=='-')
neg=1;

else
{
 if(s[i+1]!=' ')
 {
 if(neg==1)
 a[n]*=-1;
 n++;
 a[n]=0;
 t=1;
 stat=1;
 neg=0;
 }
 }
}
value=a[0];
sample=(a[0]-a[1])/(a[5]-1);
}
int hasalpha(char s[100])//checks if the given string has an a single alphabet or not
{
    int i;
 for(i=0;i<strlen(s);i++)
 if(isalpha(s[i]))
 return 1;
 return 0;
}
int toassign(char s[100]) //to check if the given string is the one through which values are to be assigned
{
    int i;
 for(i=0;i<strlen(s);i++)
 if(isalpha(s[i]))
 return 0;
 if(s[0]==' '&&s[1]==' ')
return 1;
return 0;
}
int main()
{
int i,j=0,spacing;
double a[10],sample,value,tmp,corr,m=0.00214,c=-1.29847;
char s[100],temp[100],file_name[100];
fstream f,f1,f2,f3;
cout<<"enter file name (with extension)=>";
gets(file_name);
if(exist(file_name)==0)
{
	cout<<"no such file exists!"<<endl<<"(try putting the file in the same folder or check if you have typed file extension as well)"<<endl;
	system("pause");
	goto end;
}

cout<<"enter charging correction (eV):";
cin>>corr;
cout<<"files produced:"<<endl;
f.open(file_name,ios::in);
f.getline(s,100,'\n');
while(!f.eof())
{
f.getline(s,100,'\n');
if(strcmpi(s,"")==0)
	goto skip;
if(toassign(s)==1)
{
	spacing=0;
assign(a,s,sample,value);
if((value-(value*m+c))-corr<0)
    {
		spacing++;
        f3<<"-";
        tmp=((value-(value*m+c))-corr)*-1;
    }
    else
        tmp=(value-(value*m+c))-corr;
spacing+=no_digits(tmp)+4;
}

else
if(hasalpha(s)==1)
{
 f3.close();


strcpy(temp,s);
strcat(temp,".txt");
f3.open(temp,ios::out);
cout<<temp<<endl;
}
else//this is longer than expected because of '.' not changing is column wrt largest number (first number)
{
 if(no_digits((value-(value*m+c))-corr)==0)// 0 and -0. gives error hence i made a temp solution i can do better
 {
	 if((value-(value*m+c))-corr<0)
    {
		for(i=0;i<spacing-(no_digits((value-(value*m+c))-corr))-2;i++)
			f3<<" ";
        f3<<"-";
        tmp=((value-(value*m+c))-corr)*-1;
    }
    else
	{
        tmp=(value-(value*m+c))-corr;
 for(i=0;i<spacing-no_digits((value-(value*m+c))-corr)-1;i++)
			f3<<" ";    
   } 

 }
 else if((value-(value*m+c))-corr<0)
    {
		for(i=0;i<spacing-(no_digits((value-(value*m+c))-corr)+1);i++)
			f3<<" ";
        f3<<"-";
        tmp=((value-(value*m+c))-corr)*-1;
    }
    else
	{
        tmp=(value-(value*m+c))-corr;
 for(i=0;i<spacing-no_digits((value-(value*m+c))-corr);i++)
			f3<<" ";    
 } 
 f3<<setprecision(no_digits((value-(value*m+c))-corr)+5)<<left<<setfill('0')<<setw(no_digits(tmp)+6)<<tmp<<char(9)<<char(9)<<s;//y'
 value-=sample;
 j++;
 if(j!=a[5])//so that there is no extra blank line at the end of the file
 {
   f1<<endl;
   f2<<endl;
   f3<<endl;
 }

}
skip:;
}
end:;
}