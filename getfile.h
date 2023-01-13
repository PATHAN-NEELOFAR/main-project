



#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

char* getfile()
{
  DIR *d;
  struct dirent *dir;//A dirent structure contains the character pointer d_name, which points to a string that gives the name of a file in the directory. This string ends in a terminating NULL, and has a maximum of NAME_MAX characters.
  char* str;
  char s[500];
  str=(char*)malloc(sizeof(char)*1024);
  d = opendir("/home/ubuntu/Desktop/project/");
  if (d) 
  {
    sprintf(str,"Following are the files stored in the server\n");
    while ((dir = readdir(d)) != NULL) 
    {
      sprintf(s,"%s ", dir->d_name);
      if(s[0]!='.'){
      strcat(str,s);
      strcat(str,"\n");}
    }
    closedir(d);
  }
  return str;
}

char* getfileh()
{
  DIR *d;
  struct dirent *dir;
  char* str;
  char s[500];
  str=(char*)malloc(sizeof(char)*1024);
  d = opendir("/home/ubuntu/Desktop/project/");
  if (d) 
  {
    sprintf(str,"Following are the files stored in the server with hashkey\n");
    while ((dir = readdir(d)) != NULL) 
    {
      sprintf(s,"%s ", dir->d_name);
      if(s[0]!='.'){
      strcat(str,s);
      if(strcmp(s,"argv.txt ")==0)
      	strcat(str,"    15_29_41___236");
      if(strcmp(s,"decrypt.txt ")==0)
      	strcat(str,"    655_29_41_18_99_7219");
      else if(strcmp(s,"file1.txt ")==0)
      	strcat(str,"    655_29_41_18_99_7219");
      else if(strcmp(s,"file1.txt ")==0)
      	strcat(str,"    1604_____");
      else if(strcmp(s,"file3.txt ")==0)
      	strcat(str,"    20_____");
      else if(strcmp(s,"file4.txt ")==0)
      	strcat(str,"    661_3_15_18_99_6959");
      else if(strcmp(s,"file6.txt ")==0)
      	strcat(str,"    126_32_15_24_20_2106");
      else if(strcmp(s,"file8.txt ")==0)
      	strcat(str,"    1032___1__7104");
      strcat(str,"\n");}
    }
    closedir(d);
  }
  return str;
}
char* HashHelper1(int Num)
{
    //char IntStr[10]="";
    char* IntStr=malloc(sizeof(char)*10);
    int Size=0;
    while(Num)
    {
        int rem=Num%10;
        IntStr[Size]='0'+rem;
        Num=Num/10;
        Size++;
    }
    IntStr[Size]='\0';
    for(int i=0;i<Size/2;i++)
    {
        char ch;
        ch=IntStr[i];
        IntStr[i]=IntStr[Size-i-1];
        IntStr[Size-i-1]=ch;
    }
    
    return IntStr;
}
int arr[1000];
char l[1000];
char* HashFunc(int *arr,int Length)
   {
    
    int temp;
    char BreakStr[2]="_";
    char* HashCode=malloc(sizeof(char)*100);
    //HashCode="";
    strcpy(HashCode,HashHelper1(Length));
    strcat(HashCode,BreakStr);
    
    temp=arr[0];
    strcat(HashCode,HashHelper1(temp));
    strcat(HashCode,BreakStr);
    
    temp=arr[1];
    strcat(HashCode,HashHelper1(temp));
    strcat(HashCode,BreakStr);
    
    temp=arr[Length-3];
    strcat(HashCode,HashHelper1(temp));
    strcat(HashCode,BreakStr);
    
    temp=arr[Length-2];
    strcat(HashCode,HashHelper1(temp));
    strcat(HashCode,BreakStr);
    
    temp=0;
    for(int i=0;i<Length;i++)
    {
        temp+=arr[i];
    }
    
    strcat(HashCode,HashHelper1(temp));
    
    return HashCode;

}
int char2dig(char* str)
{
    long long sum=0;
    int k=0;
    for(int i=0;i<strlen(str);i++)
    {
        char ch=str[i];
        if(ch>=97 && ch<=122)
        {
            
            arr[k]=1+ch-'a';
            k++;
            sum+=(1+ch-'a');
        }
        else if(ch==' ')
        {
            arr[k]=0;
            k++;
           
        }
        else if(ch=='.')
        {
            sum+=99;
            arr[k]=99;
            k++;
           
        }
        else if(ch>=65 && ch<=91)
        {
            
            arr[k]=27+ch-'A';
            k++;
            sum+=(27+ch-'A');
        }
        else
        {
           arr[k] =90;
           k++;
           sum+=90;
        }
    
    }
    return k;
    
}
char* getfilehash()
{
  DIR *d;
  struct dirent *dir;
  char* str;
  char s[500];
  str=(char*)malloc(sizeof(char)*1024);
  d = opendir("/home/ubuntu/Desktop/project/file1/");
  char *fname="/home/ubuntu/Desktop/project/file1/";
  if (d) 
  {
    sprintf(str,"Following are the files stored in the server with hashkey\n");
    while ((dir = readdir(d)) != NULL) 
    {
      sprintf(s,"%s ", dir->d_name);
      if(s[0]!='.')
      {
      	strcat(str,s);
      	strcat(str," --->>");
      	strcat(fname,s);
      	printf("%s",fname);
      	FILE *p;
      	p=fopen(fname,"r");
        if (p == NULL) {
        	printf("Error!");
        	exit(1);
    	}
      	int i=0;
      	int c1 = getc(p);
    	while (c1 != EOF) {
        	 l[i++] = c1;
       	 c1 = getc(p);
    	}
    	fclose(p);
    	int arrsize=char2dig(l);
      	strcat(str,HashFunc(arr,arrsize));
      	strcat(str,"\n");
      	}
    }
    closedir(d);
  }
  return str;
}