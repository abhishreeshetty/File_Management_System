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


void getMatch(char *substr,int *count)
{

    DIR *d;
    d = opendir(".");  
    struct dirent *dir;
    while ((dir = readdir(d)) != NULL)
        {
            if(strstr(dir->d_name,substr)!=NULL)
                {(*count)++;}   
        }
    closedir(d);
}



void moveMatch(char *str,char *substr)
{
    DIR *d;
    d = opendir(".");
    struct dirent *dir;
    mkdir(str,777);
    char* s1 = concat(str,"/");
    int count = 0;
    while ((dir = readdir(d)) != NULL)
        {
            if(strstr(dir->d_name,substr)!=NULL)
                {
                    char* srcpath = dir -> d_name;
                    char destpath[1024];
                    snprintf (destpath, sizeof(destpath), concat(s1,"%s"), srcpath); // "algoLab" is into which folder you want to take that file
                    if (!rename (srcpath, destpath)) {
                    count++;
                    }
                }   
        }
    if(count>0)
    	printf("%d folders moved to %s successfully\n",count,str);
    closedir(d);
}

int main(int argv,char *argc[])
{
    
        while(1)
        {
        char substr[500];
        int choice,count=0;//counts the number of occurences of that substring in the folder names
        printf("Enter the word you're looking for in the folder names:\n");
        scanf("%s",substr);
        printf("The entered substring is %s\n",substr);
        getMatch(substr,&count);
        printf("%d entries found!\n",count);
        if(count!=0)
        {printf("Do you want to \n1.move them all \n 2.check for the next entry \n 3.quit\n");
        scanf("%d",&choice);}
        else
        	choice =4;
        switch(choice)
        {
        case 1:
        	{
            printf("What do you want the main folder name to be:");
            char str[100];
            scanf("%s",str);
            printf("The input main folder name is %s\n",str);
            moveMatch(str,substr);
            break;
        	}
       	case 2:
            continue;
        case 3:
            exit(0);
        case 4:
        	break;
        default :
            {printf("Invalid choice!\n");}
        }
        printf("Do you want to try for a new entry?1/0\n");
        scanf("%d",&choice);
        if(choice==1)
        	continue;
        else
        	break;
    }   
    return(0);
}