/* ls -l --time-style=+%F */
/* Thu Oct 26 13:32:58 2017 */
/* PS: Year is present after the 4th space */
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*extract one year. Check for the presence of it in every other string! Move them all. Repeat! */

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int getYear(char *main_str)
{
    struct stat status;
    FILE *fp;
    fp=fopen(main_str,"r");
    fstat(fileno(fp),&status);
    char *s = ctime(&status.st_ctime);
    int t=4,i=0,j;
    while(t)
    {
        if(s[i++]==' ')t--;
    }
    char sub[4];
    for(j=0;j<4;j++)
        sub[j]=s[i++];
    sub[j]='\0';
    int num = atoi(sub);
    if(num/10==1)
        num=2000+num;//if the year is saved as 16,15,14
    return num;
}

void getMatch(char *substr,int *count,char *dontMove)
{
    DIR *d;
    d = opendir(".");  
    struct dirent *dir;
    while ((dir = readdir(d)) != NULL)
        {
            if(atoi(dir->d_name)/100==20)   //to eliminate all the year files
                continue;

            if(strcmp(dir->d_name,"..")==0 || strcmp(dir->d_name,".")==0)
                continue;

        	if(strcmp(dir->d_name,dontMove)!=0)
        	{
            	int year = getYear(dir->d_name);
            	if(year==atoi(substr))
            	{
                	(*count)++;
            	}   
        	}
        }
    closedir(d);
}

void moveMatch(char *str,char *substr,char *dontMove)
{
    DIR *d;
    d = opendir(".");
    struct dirent *dir;
    mkdir(str,777);
    char* s1 = concat(str,"/");
    int count = 0;
    while ((dir = readdir(d)) != NULL)
        {
        if(strcmp(dir->d_name,dontMove)!=0)
        {
        	//to eliminate all the year directories which have been just modified because of this program
            if(atoi(dir->d_name)/100==20)   
                continue;
            int year = getYear(dir->d_name);
            if(year==atoi(substr))
                {
                    char* srcpath = dir -> d_name;
                    char destpath[1024];
                    snprintf (destpath, sizeof(destpath), concat(s1,"%s"), srcpath);
                    if (!rename (srcpath, destpath)) {
                    count++;
                    }   
                }
        }   
        }
    printf("%d folders moved to %s successfully\n",count,str);
    closedir(d);
}



int main()
    {
        int year;
        char *dontMove="q3.c";
        for(year=2000;year<=2017;year++)
        {
        char substr[500];
        int choice,count=0;//counts the number of occurences of that substring in the folder names
        sprintf(substr,"%d",year);
        getMatch(substr,&count,dontMove);
        if(count>0)
        {
            printf("%d entries found for year %d!\n",count,year);
            printf("Do you want to \n1.move them all \n 2.check for the next entry \n 3.quit\n");
            scanf("%d",&choice);
            if(choice==1)
            {
                moveMatch(substr,substr,dontMove);
            }
            else if(choice==2)
                continue;
            else if(choice==3)
                break;
            else
                {printf("Invalid choice!Try again next time\n");break;}
        }

        }
    return 0;
}