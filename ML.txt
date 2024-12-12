#include<stdio.h>
#include<string.h>
void receiver();
char frames[1024];
int main()
{
int n,len,i;
char buffer[256],length[10];
printf("How many frames you want to send:");
bzero(buffer,256);
scanf("%d",&n);
for(i=0;i<n;i++)
{
printf("Enter frames:\n");
scanf("%s",buffer);
printf("String length pf buffer is %d\n",strlen(buffer));
len=strlen(buffer);
len=len+1;
printf(length,"%d",len);
strcat(frames,length);
strcat(frames,buffer);
}
for(i=0;frames[i]!='\0';i++)
printf("%c",frames[i]);
receiver();
return 0;
}
void receiver()
{
int i=0,framelen,lpvar;
char leninchar;
printf("\n\nThis is the receiver\n");
printf("\nData received id %s",frames);
while(frames[i]!='\0')
{
leninchar=frames[i];
framelen=(int)leninchar-(int)'0';
printf("\n Length of this frame is %d\n",framelen);
printf("\nFrame---->");
lpvar=i+framelen;
i=i+1;
while(i<lpvar)
{
printf("%c",frames[i++]);
}
printf("\n");
}
}
