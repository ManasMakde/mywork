#include<iostream>// by Manas makde
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
void assign(double a[10],char h[100],double &value,double &sample)// assigns parameters to a[][] for further calculations
{
int m=0,neg=0,i,n=-1,stat=1,t=1;
char s[100];
strcpy(s,h);
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
void spac(char s[100],int sp[10])
{
	int j=0;
	sp[0]=0;
	sp[1]=0;
	sp[2]=0;
	for(int i=0;i<strlen(s);i++)
	{
		if(s[i]==' ')
		{
			while(s[i]==' ')
			{i++;sp[j]++;     }
			i--;
			j++;
		}
		if(j==3)
			break;
	}

}
int main()
{
int i,j=0,neg=0,spacing=0,sp[5];
double a[10],value,tmp,m=0.00214,c=-1.29847,sample,a11,a12,corr;
char s[100],file_name[100];
fstream f,f1;
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
for(i=0;i<strlen(file_name);i++)
	if(file_name[i]=='.')
	{
		file_name[i]='\0';
	break;
	}
strcat(file_name,"_CC.1");
f1.open(file_name,ios::out);

cout<<file_name<<endl;

f.getline(s,100,'\n');
f1<<endl;
while(!f.eof())
{
	f.getline(s,100,'\n');
		if(toassign(s)==1)
{
assign(a,s,value,sample);
spac(s,sp);//spacing btw assigning numbers
if(a[0]<0)
	spacing++;
if(a[1]<0)
	spacing++;
if(a[2]<0)
	spacing++;
spacing+=28+no_digits(a[0])+no_digits(a[1])+no_digits(a[2]);
 
for(i=0;i<sp[0];i++)
	f1<<" ";

	
	if(value-(value*m+c)<0)//a11
    {
		neg++;
        f1<<"-";
        tmp=((value-(value*m+c))-corr)*-1;//first value
    }
    else
	{
        tmp=(value-(value*m+c))-corr;
    }
 if(neg==1)
 a11=tmp*-1;
 else
	 a11=tmp;
f1<<setprecision(no_digits(value-(value*m+c))+5)<<left<<setfill('0')<<setw(no_digits(tmp)+6)<<tmp;
for(i=0;i<sp[1];i++)//space 2
	f1<<" ";
neg=0;

value=value-sample*(a[5]-1);
 if(value-(value*m+c)<0)//a12
    {
		neg++;
        f1<<"-";
        tmp=((value-(value*m+c))-corr)*-1;
    }
    else
        tmp=(value-(value*m+c))-corr;
 if(neg==1)
 a12=tmp*-1;
 else
	a12=tmp;
 neg=0;
f1<<setprecision(no_digits(value-(value*m+c))+5)<<left<<setfill('0')<<setw(no_digits(tmp)+6)<<tmp;
for(i=0;i<sp[2];i++)
	f1<<" ";

tmp=(a11-a12)/(a[5]-1)*-1;
 if(tmp<0)//samply
    {
        f1<<"-";
        tmp=tmp*-1;
    }

f1<<setprecision(no_digits(tmp)+5)<<left<<setfill('0')<<setw(no_digits(tmp)+6)<<tmp;

for(i=spacing+1;i<strlen(s);i++)
	f1<<s[i];
f1<<endl;
spacing=0;
}
 	else if(strcmpi(s,"")!=0)
	f1<<s<<endl;

}
end:;
}