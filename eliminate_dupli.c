/* using strtok: system call */
/* system("rm -rf "+str);  */
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *getToken(char *str,int no)
{
    int count=0;
    char *tokens;
    tokens = strtok(str,"(). ");
    while(tokens!=NULL)
    {
        count++;
        if(count==no)
            {
                return tokens;
            }
        tokens = strtok(NULL,"(). ");  //space coz in linux,the names of the copies have a space after the name
    }
    return NULL;
}
int countToken(char *str)
{
    int count=0;
    char *tokens;
    tokens = strtok(str,"(). ");
    while(tokens!=NULL)
    {
        count++;
        tokens = strtok(NULL,"(). ");
    }
    return count;
}
int getMatch(char *substr)
{
	int count=0;
    DIR *d;
    d = opendir(".");  
    struct dirent *dir;
    while ((dir = readdir(d)) != NULL)
        {
            if(countToken(dir->d_name)<=1)
                continue;
            char *s1 = getToken(dir->d_name,1);
            if(strcmp(s1,substr)==0)
                {count++;}   
        }
    closedir(d);
    return count;
}

void removeMatch(char *substr)
{
	int count=0;
    DIR *d;
    d = opendir(".");  
    struct dirent *dir;
    int flag=0;
    while ((dir = readdir(d)) != NULL)
        {
            if(strstr(dir->d_name,substr)!=NULL)
                {
                if(flag==0) // to retain one copy
                {
                	flag=1;
                	continue;
                }
                char *s1="rm -rf \"";  //To account for file names with spaces in them
                char* s2=concat(s1,dir->d_name);
                char *s3=concat(s2,"\"");
                system(s3);
                count++;
            	}  
        }
    printf("%d files deleted successfully\n",count); 
    closedir(d);
}
int main()
{
	DIR *d;
    d = opendir(".");  
    struct dirent *dir;
    while ((dir = readdir(d)) != NULL)
        {
        	int count1 = countToken(dir->d_name);
            if(count1==0)
                continue;
        	char *toCheck = getToken(dir->d_name,1);
        	int count2 = getMatch(toCheck);
            if(count2>2)
        		removeMatch(toCheck);  
        }
    closedir(d);
	return 0;
}

