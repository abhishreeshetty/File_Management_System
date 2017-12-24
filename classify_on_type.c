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
                    // the rename succeeded
                    }
                }   
        }
    if(count>0)
    printf("%d file(s) moved to %s successfully\n",count,str);
    closedir(d);
}


void checkTextFiles()
{
	int no_textfiles=11;
	char *textFiles[11]={".doc",".docs",".log",".msg",".odt",".pages",".rtf",".tex",".txt",".wpd",".wps"};
    int ch,i;
    printf("Do you want to check for text files?\n");
    scanf("%d",&ch);
    if(ch==1)
    {
       	int choice,count,tot=0;
        for(i=0;i<no_textfiles;i++)
        	{
        		count = 0;
        		getMatch(textFiles[i],&count);
        		tot+=count;
        	}
        	printf("%d entries found!\n",tot);
        	printf("Do you want to \n1.move them all \n 2.check for the next file type\n 3.quit\n");
        	scanf("%d",&choice);
        	if(choice==1)
        	{
        	for(i=0;i<no_textfiles;i++)
            	moveMatch("Text-Files",textFiles[i]);
        	}
    else if(choice==3)
        exit(0);
   }
}


void checkImageFiles()
{
	int no_imageFiles=10;
    char *imageFiles[10]={".jpg",".png",".psd",".ai",".ps",".gif",".bmp",".pspimage",".tif",".yuv"};
    int ch,i;
    printf("Do you want to check for image files?\n");
    scanf("%d",&ch);
    if(ch==1)
    {
       	int choice,count,tot=0;
        for(i=0;i<no_imageFiles;i++)
        	{
        		count = 0;
        		getMatch(imageFiles[i],&count);
        		tot+=count;
        	}
        	printf("%d entries found!\n",tot);
        	printf("Do you want to \n1.move them all \n 2.check for the next file type\n 3.quit\n");
        	scanf("%d",&choice);
        	if(choice==1)
        	{
        	for(i=0;i<no_imageFiles;i++)
            	moveMatch("Image-Files",imageFiles[i]);
        	}
    else if(choice==3)
        exit(0);
   }
}


void checkDataFiles()
{
	int no_dataFiles=13;
	char *dataFiles[13]={".csv",".dat",".ged",".key",".keychain",".pps",".ppt",".pptx",".sdf",".tar",".tax2016",".vcf",".xml"};int ch,i;
    printf("Do you want to check for data files?\n");
    scanf("%d",&ch);
    if(ch==1)
    {
       	int choice,count,tot=0;
        for(i=0;i<no_dataFiles;i++)
        	{
        		count = 0;
        		getMatch(dataFiles[i],&count);
        		tot+=count;
        	}
        	printf("%d entries found!\n",tot);
        	printf("Do you want to \n1.move them all \n 2.check for the next file type\n 3.quit\n");
        	scanf("%d",&choice);
        	if(choice==1)
        	{
        	for(i=0;i<no_dataFiles;i++)
            	moveMatch("Data-Files",dataFiles[i]);
        	}
    else if(choice==3)
        exit(0);
   }
}

void checkAudioFiles()
{
	int no_audioFiles=9;
	char *audioFiles[9]={".aif",".iff",".m3u",".m4a",".mid",".mp3",".mpa",".wav",".wma"};
	int ch,i;
    printf("Do you want to check for audio files?\n");
    scanf("%d",&ch);
    if(ch==1)
    {
       	int choice,count,tot=0;
        for(i=0;i<no_audioFiles;i++)
        	{
        		count = 0;
        		getMatch(audioFiles[i],&count);
        		tot+=count;
        	}
        	printf("%d entries found!\n",tot);
        	printf("Do you want to \n1.move them all \n 2.check for the next file type\n 3.quit\n");
        	scanf("%d",&choice);
        	if(choice==1)
        	{
        	for(i=0;i<no_audioFiles;i++)
            	moveMatch("Audio-Files",audioFiles[i]);
        	}
    else if(choice==3)
        exit(0);
   }
}

void checkVideoFiles()
{
	int no_videoFiles=14;
	char *videoFiles[14]={".3g2",".3gp",".asp",".avi",".flv",".m4u",".mov",".mp4",".mpg",".rm",".srt",".swf",".vob",".wmv"};
	int ch,i;
    printf("Do you want to check for video files?\n");
    scanf("%d",&ch);
    if(ch==1)
    {
       	int choice,count,tot=0;
        for(i=0;i<no_videoFiles;i++)
        	{
        		count = 0;
        		getMatch(videoFiles[i],&count);
        		tot+=count;
        	}
        	printf("%d entries found!\n",tot);
        	printf("Do you want to \n1.move them all \n 2.check for the next file type\n 3.quit\n");
        	scanf("%d",&choice);
        	if(choice==1)
        	{
        	for(i=0;i<no_videoFiles;i++)
            	moveMatch("Video-Files",videoFiles[i]);
        	}
    else if(choice==3)
        exit(0);
   }
}


int main()
{
	checkTextFiles();
	checkDataFiles();
    checkImageFiles();
    checkAudioFiles();
    checkVideoFiles();
	return(0);
}
