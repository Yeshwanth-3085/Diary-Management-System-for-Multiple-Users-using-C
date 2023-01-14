#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <synchapi.h>
#include <sys/stat.h>
#include <time.h>
int signup(int flag, char EUN[]);
void signin();
void menu(char UN[]);
int view(char UN[]);
int remove_directory(const char *path);
int signup(int flag, char EUN[])
{
 char C, UN[100]={0}, PW[100]={0}, CPW[100]={0}, Filepath[125]={0}, Digits[]={"0123456789"}, Punctu[]={"`~!@#$^&*()%- _+={}[]|;:',.<>/?"}, Alpha[]={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}, alpha[]={"abcdefghijklmnopqrstuvwxyz"};
 FILE *fp;
 int i, j, D=1, P=1, A=1, a=1, Choice;
 if(flag)
   goto RetryPW;
 system("cls");
 printf("            ~~~~~~~~~~~~\n            ~ WELCOME! ~\n            ~~~~~~~~~~~~\n\n");
 RetryUN:
 printf("Enter your Username which should not contain spaces (Steve-46290): ");
 memset(UN, 0, 100);
 fflush(stdin);
 gets(UN);
 for(i=0;UN[i]!='\0';i++)
    if(UN[i]==' ')
      {
       printf("Username Should not contain Spaces!\n");
       while(1)
            {
             printf("\nEnter 1 to Try again\nEnter 2 to Exit\nEnter your Choice: ");
             scanf("%d", &Choice);
             switch(Choice)
                   {
                    case 1: {
                             goto RetryUN;
                            }
                    case 2: {
                             return 0;
                            }
                    default:{
                             printf("Invalid Choice!\n");
                             break;
                            }
                   }
            }
      }
 if(mkdir(UN))
   {
    printf("\nIt looks like you already have an existing account or an Error might have occured while setting up your account\n");
    while(1)
         {
          printf("\nEnter 1 to sign back in to your account(Sign In)\nEnter 2 to retry & if the issue continues, use a different username\nEnter 3 to Exit\nEnter your Choice: ");
          scanf("%d", &Choice);
          switch(Choice)
                {
                 case 1 : {
                           signin();
                           return 0;
                          }
                 case 2 : {
                           goto RetryUN;
                          }
                 case 3 : {
                           return 0;
                          }
                 default: {
                           printf("Invalid Choice!\n");
                           break;
                          }
                }
         }
   }
 RetryPW:
 memset(PW, 0, 100);
 printf("Enter a Password which contains atleast a Number, a Special Character, an Upper & Lower case letters, should not contain Spaces & should not be same as the Username (1@StEvE): ");
 i=0;
 D=P=A=a=1;
 while(1)
	    {
       fflush(stdin);
	     C=getch();
	     if(C==13)
         {
          printf("\n"); 
          break;
         }
	     else if(C=='\b')
              {
               if(i!=0)
                 {
                  printf("\b \b");
                  i--;
                  PW[i]='\0';
                 }
              }
            else
              {
               PW[i]=C;
               printf("*");
               PW[i+1]='\0';
               i++;
              }
        }
 for(i=0;PW[i]!='\0';i++)
    {
     if(PW[i]!=' ')
       {
        if(D)
          for(j=0;j<sizeof(Digits);j++)
             if(PW[i]==Digits[j])
               {
                D=0;
                break;
               }
             else 
               D=1;
        if(P)
          for(j=0;j<sizeof(Punctu);j++)
             if(PW[i]==Punctu[j])
               {
                P=0;
                break;
               }
             else  
               P=1;
        if(A)
          for(j=0;j<sizeof(Alpha);j++)
             if(PW[i]==Alpha[j])
               {
                A=0;
                break;
               }
             else 
               A=1;
        if(a)
          for(j=0;j<sizeof(alpha);j++)
             if(PW[i]==alpha[j])
               {
                a=0;
                break;
               }
             else 
               a=1;
       }
     else
       {
        ErrorPW:
        printf("\nPassword should contain Special Character like '!@$#', Numbers like '469', Uppercase and Lowercase letters, should not contain Spaces & should not be same as the Username!\n");
        while(1)
             {
              printf("\nEnter 1 to Re-enter Password\nEnter 2 to Exit\nEnter your Choice: ");
              scanf("%d", &Choice);
              switch(Choice)
                    {
                     case 1: {
                              goto RetryPW;
                             }
                     case 2: {
                              if(flag)
                                return 1;
                              rmdir(UN);
                              return 0;
                             }
                     default:{
                              printf("Invalid Choice!\n");
                              break;
                             }
                    }
             }
       }
    }
 if(D||P||A||a||!strcmp(UN, PW)||!strcmp(EUN, PW))
   goto ErrorPW;
 ConfirmPW:
 printf("Confirm your Password: ");
 i=0;
 memset(CPW, 0, 100);
 while(1)
	    {
       fflush(stdin);
	     C=getch();
	     if(C==13) 
         {
          printf("\n"); 
          break;
         }
	     else if(C=='\b')
              {
               if(i!=0)
                 {
                  printf("\b \b");
                  i--;
                  CPW[i]='\0';
                 }
              }
            else
              {
               CPW[i]=C;
               printf("*");
               CPW[i+1]='\0';
               i++;
              }
        }
 if((strcmp(PW, CPW)))
   {
    printf("\nPassword doesn't match!\n");
    while(1)
         {
          printf("\nEnter 1 to Re-enter password\nEnter 2 to Retry confirmation\nEnter 3 to Exit\nEnter your Choice: ");
          scanf("%d", &Choice);
          switch(Choice)
                {
                 case 1: {
                          goto RetryPW;
                         }
                 case 2: {
                          goto ConfirmPW;
                         }
                 case 3: {
                          if(flag)
                            return 1;
                          rmdir(UN);
                          return 0;
                         }
                 default:{
                          printf("Invalid Choice!\n");
                          break;
                         }
                }
         }
   }
 if(flag)
   sprintf(Filepath, "%s\\Password.txt", EUN);
 else
   sprintf(Filepath, "%s\\Password.txt", UN);
 fp=fopen(Filepath, "w");
 if(fp==NULL)
   {
    printf("\nAn error occured while setting up your account\nPress any key to continue");
    fclose(fp);
    rmdir(UN);
    getch();
    return 0;
   }
 fputs(PW ,fp);
 fclose(fp);
 if(flag)
   return 0;
 printf("\nCREATING ACCOUNT, PLEASE WAIT");
 for(i=0;i<5;i++)
    {
     printf(".");
     Sleep(420);
    }
 printf("\nACCOUNT CREATED SUCCESSFULLY.\n\nPress any key to continue");
 getch();
 menu(UN);
 return 0;
}
void signin()
{
 char C, UN[100]={0}, PW[100]={0}, Filepath[125]={0}, TPW[100]={0};
 DIR *folder;
 FILE *fp;
 int Choice, i;
 system("cls");
 printf("                 ~~~~~~~~~~~~~~~~~\n                 ~ WELCOME BACK! ~\n                 ~~~~~~~~~~~~~~~~~\n\n");
 RetryLUN:
 memset(UN, 0, 100);
 printf("Enter your Username: ");
 fflush(stdin);
 gets(UN);
 folder=opendir(UN);
 if(folder==NULL)
   {
    printf("\nIt looks like you don't have an account or an Error might have occured while logging you in\n");
    closedir(folder);
    while(1)
         {
          printf("\nEnter 1 to create a new account (Sign Up)\nEnter 2 to Sign in with a different account or to retry\nEnter 3 to Exit\nEnter your Choice: ");
          scanf("%d", &Choice);
          switch(Choice)
                {
                 case 1: {
                          signup(0, "DMS");
                          return;
                         }
                 case 2: {
                          goto RetryLUN;
                         }
                 case 3: {
                          return;
                         }
                 default:{
                          printf("Invalid Choice!\n");
                          break;
                         }
                }
         }
   }
 closedir(folder);
 RetryLPW:
 printf("Enter your Password: ");
 i=0;
 memset(PW, 0, 100);
 while(1)
	    {
       fflush(stdin);  
	     C=getch();
	     if(C==13) 
         {
          printf("\n"); 
          break;
         }
	     else if(C=='\b')
              {
               if(i!=0)
                 {
                  printf("\b \b");
                  i--;
                  PW[i]='\0';
                 }
              }
            else
              {
               PW[i]=C;
               printf("*");
               PW[i+1]='\0';
               i++;
              }
	    }
 sprintf(Filepath, "%s\\Password.txt", UN);
 fp=fopen(Filepath, "r");
 if(fp==NULL)
   {
    printf("\nAn error occured while logging in to your account\nPress any key to continue");
    fclose(fp);
    getch();
    return;
   }
 fgets(TPW, 100, fp);
 fclose(fp);
 if(strcmp(PW, TPW))
   {
    printf("\nIncorrect Password!\n");
    while(1)
         {
          printf("\nEnter 1 to try again\nEnter 2 to sign in with different account\nEnter 3 to Exit\nEnter your Choice: ");
          scanf("%d", &Choice);
          switch(Choice)
                {
                 case 1: {
                          goto RetryLPW;
                         }
                 case 2: {
                          goto RetryLUN;
                         }
                 case 3: {
                          return;
                         }
                 default:{
                          printf("Invalid Choice!\n");
                          break;
                         }
                }
         }
   }
 printf("\nLOGGING YOU IN, PLEASE WAIT");
 for(i=0;i<5;i++)
    {
     printf(".");
     Sleep(420);
    }
 printf("\nLOGGED IN SUCCESSFULLY.\n\nPress any key to continue");
 getch();
 menu(UN);
}
void menu(char UN[])
{
 char Name[15]={0}, TName[15]={0}, Date[5]={0}, Month[5]={0}, Year[7]={0}, C, Note[1000000]={0}, FolderPath[111]={0}, FilePath[200]={0}, PW[100]={0}, CPW[100]={0};
 DIR *dr;
 FILE *fp;
 int Choice, flag=0, i, Count;
 struct dirent *en;
 struct tm dt;
 time_t t;
 while(1)
      {
       memset(FilePath, 0, 200);
       memset(FolderPath, 0, 111);
       memset(Name, 0, 15);
       memset(TName, 0, 15);
       memset(Note, 0, 1000000);
       memset(PW, 0, 100);
       memset(CPW, 0, 100);
       system("cls");
       printf("         ~~~~~~~~~\n         ~ MENU: ~\n         ~~~~~~~~~\n[1] Create a Note\n[2] View a Note\n[3] Edit a Note\n[4] Delete a Note or Multiple Notes\n[5] Edit your Password\n[6] Permanently Delete your Account\n[7] Log Out\nEnter your Choice: ");
       scanf("%d", &Choice);
       switch(Choice)
             {
              case 1: {
                       CreateNote:
                       t=time(NULL);
                       dt=*localtime(&t);
                       sprintf(Year, "\\%d", dt.tm_year+1900);
                       sprintf(Month, "\\%02d", dt.tm_mon+1);
                       sprintf(Date, "\\%02d", dt.tm_mday);
                       for(i=0;i<3;i++)
                          {
                           if(i==0)
                             {
                              sprintf(FolderPath, "%s%s", UN, Year);
                              mkdir(FolderPath);
                             }
                           if(i==1)
                             {
                              strcat(FolderPath, Month);
                              mkdir(FolderPath);
                             }
                           if(i==2)
                             {
                              strcat(FolderPath, Date);
                              mkdir(FolderPath);
                             }
                          }
                       Count=0;
                       dr=opendir(FolderPath);
                       if(dr)
                         {
                          while((en=readdir(dr))!=NULL)
                               {
                                if(!strcmp(en->d_name, ".")||!strcmp(en->d_name, ".."))
                                  continue;
                                Count++;
                               }
                          closedir(dr);
                         }
                       else
                         {
                          printf("\nAn error occured\n");
                          closedir(dr);
                          goto NoteEnd;
                         }
                       if(Count==9999)
                         {
                          printf("\nThe Maximum Notes creation limit for a day is reached (%d)\n", Count);
                          goto NoteEnd;
                         }
                       printf("\nPlease note the date of creation of Note: %02d-%02d-%d\n\nEnter the Name of your Note: ", dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900);
                       fflush(stdin);
                       gets(Name);
                       sprintf(FilePath, "%s\\%s.txt", FolderPath, Name);
                       sprintf(TName, "%s.txt", Name);
                       dr=opendir(FolderPath);
                       while((en=readdir(dr))!=NULL)
                            {
                             if(!strcmp(en->d_name, ".")||!strcmp(en->d_name, ".."))
                               continue;
                             if(!strcmp(TName, en->d_name))
                               {
                                closedir(dr);
                                printf("\nThis Note already exists.\n");
                                while(1)
                                     {
                                      printf("\nEnter 1 to View the note\nEnter 2 to Overwrite (Re-write) the note\nEnter 3 to Continue writing (Append) the note\nEnter 4 to Try another name\nEnter 5 to Exit\nEnter your Choice: ");
                                      scanf("%d", &Choice);
                                      switch(Choice)
                                            {
                                             case 1: {
                                                      goto ViewNote;
                                                     }
                                             case 2: {
                                                      goto Note;
                                                     }
                                             case 3: {
                                                      flag=1;
                                                      goto AppendNote1;
                                                     }
                                             case 4: {
                                                      goto CreateNote;
                                                     }
                                             case 5: {
                                                      goto NoteEnd;
                                                     }
                                             default:{
                                                      printf("Invalid Choice!\n");
                                                      break;
                                                     }
                                            }
                                     }
                               }
                            }
                       closedir(dr);
                       Note:
                       printf("\nEnter your note, Enter 'CTRL+Z' at end of your note to stop & save your note: \n\n");
                       i=0;
                       memset(Note, 0, 1000000);
                       while(1)
                            {
                             fflush(stdin);
                             C=getch();
                             if(C!=26)
                               {
                                if(C=='\b')
                                  {
                                   if(i!=0&&Note[i]!=13)
                                     {
                                      printf("\b \b");
                                      i--;
                                      Note[i]='\0';
                                     }
                                  }
                                else if(C==13)
                                       {
                                        printf("\n");
                                        Note[i]='\n';
                                        Note[i+1]='\0';
                                        i++;
                                       }
                                     else
                                       {
                                        printf("%c", C);
                                        Note[i]=C;
                                        Note[i+1]='\0';
                                        i++;
                                       }
                               }
                             else
                               break;
                            }
                       if(flag)
                         goto AppendNote;
                       fp=fopen(FilePath, "w");
                       if(fp==NULL)
                         {
                          printf("\nAn error occured\n");
                          fclose(fp);
                          goto NoteEnd;
                         }
                       fputs(Note ,fp);
                       fclose(fp);
                       printf("\nYour Note has been saved Successfully.\n");
                       NoteEnd:
                       printf("Press any key to continue");
                       getch();
                       break;
                      }
              case 2: {
                       if(view(UN))                        
                         {
                          printf("\nAn error occured\n");
                          goto NoteEnd;
                         }
                       printf("\nEnter the date of your note you are about to view [ in this format 'DD MM YYYY' ]: ");
                       scanf("%s%s%s", Date, Month, Year);
                       sprintf(FolderPath, "%s\\%s\\%s\\%s", UN, Year, Month, Date);
                       dr=opendir(FolderPath);
                       i=0;
                       if(dr)
                         {
                          printf("\n");
                          while((en=readdir(dr))!=NULL)
                               {
                                if(!strcmp(en->d_name, ".")||!strcmp(en->d_name, ".."))
                                  continue;
                                printf("%s\n", en->d_name);
                                i++;
                               }
                          closedir(dr);
                          if(!i)
                            {
                             printf("NO NOTES WERE FOUND!\n\n");
                             goto NoteEnd;
                            }
                         }
                       else
                         {
                          printf("\nNO NOTES WERE FOUND! or an error might have occured\n\n");
                          closedir(dr);
                          goto NoteEnd;
                         }
                       printf("\nEnter the Name of your note you are about to view: ");
                       fflush(stdin);
                       gets(Name);
                       sprintf(FilePath, "%s\\%s.txt", FolderPath, Name);
                       ViewNote:
                       fp=fopen(FilePath, "r");
                       if(fp==NULL)
                         {
                          printf("\nAn error occured\n");
                          fclose(fp);
                          goto NoteEnd;
                         }
                       i=0;
                       memset(Note, 0, 1000000);
                       while(1)
                            {
                             Note[i]=fgetc(fp);
                             i++;
                             if(feof(fp))
                              {
                               Note[i]='\0';  
                               break;
                              }
                            }
                       fclose(fp);
                       printf("\nNOTE:\n\n%s\n\nPress any key to stop viewing", Note);
                       getch();
                       break;
                      }
              case 3: {
                       if(view(UN))
                         {
                          printf("\nAn error occured\n");
                          goto NoteEnd;
                         }
                       while(1)
                            {
                             printf("\nEnter 1 to Overwrite (Re-write) on an existing note\nEnter 2 to Continue writing (Append) on an existing note\nEnter 3 to Exit\nEnter your Choice: ");
                             scanf("%d", &Choice);
                             switch(Choice)
                                   {
                                    case 1: {
                                             NoteOverWrite:
                                             printf("\nEnter the date of your note you are about to edit [ in this format 'DD MM YYYY' ]: ");
                                             scanf("%s%s%s", Date, Month, Year);
                                             sprintf(FolderPath, "%s\\%s\\%s\\%s", UN, Year, Month, Date);
                                             i=0;
                                             dr=opendir(FolderPath);
                                             if(dr)
                                               {
                                                printf("\n");
                                                while((en=readdir(dr))!=NULL)
                                                     {
                                                      if(!strcmp(en->d_name, ".")||!strcmp(en->d_name, ".."))
                                                        continue;
                                                      printf("%s\n", en->d_name);
                                                      i++;
                                                     }
                                                closedir(dr);
                                                if(!i)
                                                  {
                                                   printf("NO NOTES WERE FOUND!\n\n");
                                                   goto NoteEnd;
                                                  }
                                               }
                                             else
                                               {
                                                printf("\nNO NOTES WERE FOUND! or an error might have occured\n\n");
                                                closedir(dr);
                                                goto NoteEnd;
                                               }
                                             printf("\nEnter the Name of your note you are about to edit: ");
                                             fflush(stdin);
                                             gets(Name);
                                             sprintf(FilePath, "%s\\%s.txt", FolderPath, Name);
                                             if(flag)
                                               goto AppendNote1; 
                                             goto Note;
                                            }
                                    case 2: {
                                             flag=1;
                                             goto NoteOverWrite;
                                             AppendNote1:
                                             fp=fopen(FilePath, "r");
                                             if(fp==NULL)
                                               {
                                                printf("\nAn error occured\n");
                                                fclose(fp);
                                                goto NoteEnd;
                                               }
                                             i=0;
                                             memset(Note, 0, 1000000);
                                             while(1)
                                                  {
                                                   Note[i]=fgetc(fp);
                                                   i++;
                                                   if(feof(fp))
                                                     {
                                                      Note[i]='\0';
                                                      break;
                                                     }
                                                  }
                                             fclose(fp);
                                             printf("\nNOTE:\n\n%s\n\n", Note);
                                             goto Note;
                                             AppendNote:
                                             fp=fopen(FilePath, "a");
                                             if(fp==NULL)
                                               {
                                                printf("\nAn error occured\n");
                                                fclose(fp);
                                                flag=0;
                                                goto NoteEnd;
                                               }
                                             fputs(Note ,fp);
                                             fclose(fp);
                                             printf("\nYour Note has been Appended Successfully.\n");
                                             flag=0;
                                             goto NoteEnd;
                                            }
                                    case 3: {
                                             goto NoteEnd;
                                            }
                                    default:{
                                             printf("Invalid Choice!\n");
                                             break;
                                            }
                                   }
                            }
                      }
              case 4: {
                       if(view(UN))                        
                         {
                          printf("\nAn error occured\n");
                          goto NoteEnd;
                         }
                       while(1)
                            {
                             printf("\nEnter 1 to Delete a single note\nEnter 2 to Delete multiples notes\nEnter 3 to Exit\nEnter your Choice: ");
                             scanf("%d", &Choice);
                             switch(Choice)
                                   {
                                    case 1: {
                                             printf("\nEnter the date of your note you are about to Delete [ in this format 'DD MM YYYY' ]: ");
                                             scanf("%s%s%s", Date, Month, Year);
                                             sprintf(FolderPath, "%s\\%s\\%s\\%s", UN, Year, Month, Date);
                                             i=0;
                                             dr=opendir(FolderPath);
                                             if(dr)
                                               {
                                                printf("\n");
                                                while((en=readdir(dr))!=NULL)
                                                     {
                                                      if(!strcmp(en->d_name, ".")||!strcmp(en->d_name, ".."))
                                                        continue;
                                                      printf("%s\n", en->d_name);
                                                      i++;
                                                     }
                                                closedir(dr);
                                                if(!i)
                                                  {
                                                   printf("NO NOTES WERE FOUND!\n\n");
                                                   goto NoteEnd;
                                                  }
                                               }
                                             else
                                               {
                                                printf("\nNO NOTES WERE FOUND! or an error might have occured\n\n");
                                                closedir(dr);
                                                goto NoteEnd;
                                               }
                                             printf("\nEnter the Name of your note you are about to Delete: ");
                                             fflush(stdin);
                                             gets(Name);
                                             sprintf(FilePath, "%s\\%s.txt", FolderPath, Name);
                                             if(remove(FilePath))
                                               printf("\nUnable to delete the Note\n");
                                             else
                                               printf("\nNote Deleted successfully\n");
                                             goto NoteEnd; 
                                            }
                                    case 2: {
                                             while(1)
                                                  {
                                                   printf("\nEnter 1 to Delete Multiple Notes of a particular date\nEnter 2 to Delete Multiple Notes of a particular month\nEnter 3 to Delete Multiple Notes of a particular year\nEnter 4 to Exit\nEnter your Choice: ");
                                                   scanf("%d", &Choice);
                                                   switch(Choice)
                                                         {
                                                          case 1: {
                                                                   printf("\nEnter the date, month & year of your notes you are about to Delete [ in this format 'DD MM YYYY' ]: ");
                                                                   scanf("%s%s%s", Date, Month, Year);
                                                                   sprintf(FolderPath, "%s\\%s\\%s\\%s", UN, Year, Month, Date);
                                                                   goto DMNRD;
                                                                  }
                                                          case 2: {
                                                                   printf("\nEnter the month & year of your notes you are about to Delete [ in this format 'MM YYYY' ]: ");
                                                                   scanf("%s%s",Month, Year);
                                                                   sprintf(FolderPath, "%s\\%s\\%s", UN, Year, Month);
                                                                   goto DMNRD;
                                                                  }
                                                          case 3: {
                                                                   printf("\nEnter the year of your notes you are about to Delete [ in this format 'YYYY' ]: ");
                                                                   scanf("%s", Year);
                                                                   sprintf(FolderPath, "%s\\%s", UN, Year);
                                                                   goto DMNRD;
                                                                  }
                                                          case 4: {
                                                                   goto NoteEnd;
                                                                  }
                                                          default:{
                                                                   printf("Invalid Choice!\n");
                                                                   break;
                                                                  }
                                                         }
                                                  }
                                             DMNRD:
                                             if(remove_directory(FolderPath))
	                                             printf("\nUnable to delete Notes!\n");
                                             else
                                               printf("\nNotes Deleted successfully\n");
                                             goto NoteEnd; 
                                            }
                                    case 3: {
                                             goto NoteEnd; 
                                            }
                                    default:{
                                             printf("Invalid Choice!\n");
                                             break;
                                            }
                                   }
                            }
                      }
              case 5: {
                       printf("Enter your existing password: ");
                       i=0;
                       while(1)
	                          {
                             fflush(stdin);
	                           C=getch();
	                           if(C==13)
                               {
                                printf("\n"); 
                                break;
                               }
	                           else if(C=='\b')
                                    {
                                     if(i!=0)
                                       {
                                        printf("\b \b");
                                        i--;
                                        PW[i]='\0';
                                       }
                                    }
                                  else
                                    {
                                     PW[i]=C;
                                     printf("*");
                                     PW[i+1]='\0';
                                     i++;
                                    }
	                          }
                       sprintf(FilePath, "%s\\Password.txt", UN);
                       fp=fopen(FilePath, "r");
                       if(fp==NULL)
                         {
                          printf("\nAn error occured\n");
                          fclose(fp);
                          goto NoteEnd;
                         }
                       fgets(CPW, 100, fp);
                       fclose(fp);
                       if(strcmp(PW, CPW))
                         {
                          printf("\nIncorrect Password!\n");
                          goto NoteEnd;
                         }
                       if(signup(1, UN))
                         goto NoteEnd;
                       printf("\nCHANGING YOUR ACCOUNT PASSWORD, PLEASE WAIT");
                       for(i=0;i<5;i++)
                          {
                           printf(".");
                           Sleep(420);
                          }
                       printf("\nPASSWORD CHANGED SUCCESSFULLY.\n\n");
                       goto NoteEnd;
                      }
              case 6: {
                       printf("Enter your existing password: ");
                       i=0;
                       while(1)
	                          {
                             fflush(stdin);
	                           C=getch();
	                           if(C==13) 
                               {
                                printf("\n");
                                break;
                               }
	                           else if(C=='\b')
                                    {
                                     if(i!=0)
                                       {
                                        printf("\b \b");
                                        i--;
                                        PW[i]='\0';
                                       }
                                    }
                                  else
                                    {
                                     PW[i]=C;
                                     printf("*");
                                     PW[i+1]='\0';
                                     i++;
                                    }
	                          }
                       sprintf(FilePath, "%s\\Password.txt", UN);
                       fp=fopen(FilePath, "r");
                       if(fp==NULL)
                         {
                          printf("\nAn error occured\n");
                          fclose(fp);
                          goto NoteEnd;
                         }
                       fgets(CPW, 100, fp);
                       fclose(fp);
                       if(strcmp(PW, CPW))
                         {
                          printf("\nIncorrect Password!\n");
                          goto NoteEnd;
                         }
                       if(remove_directory(UN))
	                       {
                          printf("\nUnable to delete Account!\n");
                          goto NoteEnd;
                         }
                       printf("\nGOODBYE!\nDELETING ACCOUNT, PLEASE WAIT");
                       for(i=0;i<5;i++)
                          {
                           printf(".");
                           Sleep(420);
                          }
                       printf("\nACCOUNT DELETED SUCCESSFULLY.\n\nPress any key to continue");
                       getch();
                       return;
                      }
              case 7: {
                       printf("\nGOODBYE!\nLOGGING YOU OUT, PLEASE WAIT");
                       for(i=0;i<5;i++)
                          {
                           printf(".");
                           Sleep(420);
                          }
                       printf("\nLOGGED OUT SUCCESSFULLY.\n\nPress any key to continue");
                       getch();
                       return;
                      }
              default:{
                       printf("\nInvalid Choice!\n");
                       goto NoteEnd;
                      }
             }
      }
}
int view(char UN[])
{
 char FPY[150], FPM[150], FPD[150];
 DIR *dr, *dry, *drm, *drd;
 struct dirent *en, *eny, *enm, *end;
 int Count=0, i, j, k, l, jc=0, kc=0;
 printf("\n  |--------|---------|--------|-----------------------|\n  |  Year  |  Month  |  Date  |  Number of the Notes  |\n  |--------|---------|--------|-----------------------|\n");
 Count=0;
 dr=opendir(UN);
 if(dr)
   {
    while((en=readdir(dr))!=NULL)
         Count++;
    closedir(dr);
   }
 dr=opendir(UN);
 if(dr)
   {
    for(i=1;i<Count;i++)
       {
        en=readdir(dr);
        if(!strcmp(en->d_name, ".")||!strcmp(en->d_name, ".."))
          continue;
        printf("  |  %s", en->d_name);
        sprintf(FPY, "%s\\%s", UN, en->d_name);
        jc=0;
        dry=opendir(FPY);
        while((eny=readdir(dry))!=NULL)
             {
              if(!strcmp(eny->d_name, ".")||!strcmp(eny->d_name, ".."))
                continue;
              jc++;
             }
        closedir(dry);
        dry=opendir(FPY);
        if(dry)
          {
           j=0;
           while((eny=readdir(dry))!=NULL)
                {
                 if(!strcmp(eny->d_name, ".")||!strcmp(eny->d_name, ".."))
                   continue;
                 if(j==0)
                   printf("  |   %02s", eny->d_name);
                 else
                   printf("  |        |   %02s", eny->d_name);
                 sprintf(FPM, "%s\\%s", FPY, eny->d_name);
                 kc=0;
                 drm=opendir(FPM);
                 while((enm=readdir(drm))!=NULL)
                      {
                       if(!strcmp(enm->d_name, ".")||!strcmp(enm->d_name, ".."))
                         continue;
                       kc++;
                      }
                 closedir(drm);
                 drm=opendir(FPM);
                 if(drm)
                   {
                    k=0;
                    while((enm=readdir(drm))!=NULL)
                         {
                          if(!strcmp(enm->d_name, ".")||!strcmp(enm->d_name, ".."))
                            continue;
                          if(k==0)
                            printf("    |   %02s", enm->d_name);
                          else
                            printf("  |        |         |   %02s", enm->d_name);
                          sprintf(FPD, "%s\\%s", FPM, enm->d_name);
                          drd=opendir(FPD);
                          if(drd)
                            {
                             l=0;
                             while((end=readdir(drd))!=NULL)
                                  {
                                   if(!strcmp(end->d_name, ".")||!strcmp(end->d_name, ".."))
                                     continue;
                                   l++;
                                  }
                             if(l)
                               {
                                printf("   |  Contains %04d Notes  |\n", l);
                                if(!((jc-1==j)&&(kc-1==k)))
                                  printf("  |        |         |        |                       |\n");
                               }
                             else
                               {
                                printf("   |  No Notes were found  |\n");
                                if(!((jc-1==j)&&(kc-1==k)))
                                  printf("  |        |         |        |                       |\n");
                               }
                             closedir(drd);
                            }
                          else
                            {
                             closedir(drd);
                             closedir(drm);
                             closedir(dry);
                             goto ErrorView;
                            }
                          k++;
                         }
                    if(k==0)
                      {
                       printf("    |        |  No Notes were found  |\n");
                       if(!(jc-1==j))
                         printf("  |        |         |        |                       |\n");
                      }
                    closedir(drm);
                   }
                 else
                   {
                    closedir(drm);
                    closedir(dry);
                    goto ErrorView;
                   }
                 j++;
                }
           if(j==0)
             printf("  |         |        |  No Notes were found  |\n");
           closedir(dry);
          }
        else
          {
           closedir(dry);
           goto ErrorView;
          }
        printf("  |--------|---------|--------|-----------------------|\n");
       }
    closedir(dr);
    if(Count<4)
      printf("  |        |         |        |  No Notes were found  |\n  |--------|---------|--------|-----------------------|\n");
    return 0;
   }
 else
   {
    ErrorView:
    closedir(dr);
    return 1;
   }
}
int remove_directory(const char *path)
{
 int r=-1;
 DIR *d=opendir(path);
 size_t path_len=strlen(path);
 if(d)
   {
    struct dirent *p;
    r=0;
    while(!r&&(p=readdir(d))) 
         {
          int r2=-1;
          char *buf;
          size_t len;
          if(!strcmp(p->d_name, ".")||!strcmp(p->d_name, ".."))
            continue;
          len=path_len+strlen(p->d_name)+2; 
          buf=malloc(len);
          if(buf) 
            {
             struct stat statbuf;
             snprintf(buf, len, "%s/%s", path, p->d_name);
             if(!stat(buf, &statbuf))
               {
                if(S_ISDIR(statbuf.st_mode))
                  r2=remove_directory(buf);
                else
                  r2=unlink(buf);
               }
             free(buf);
            }
           r=r2;
          }
    closedir(d);
   }
 if(!r)
   r=rmdir(path);
 return r;
}
void main()
{
 int Choice, i=0;
 system("color 03");
 while(1)
      {
       system("cls");
       printf("\n                                                  ~~~~~~~~~~~~~~~~~~~~~~~~~~~\n                                                  ~ DIARY MANAGEMENT SYSTEM ~\n                                                  ~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
       if(!i)
         {
          printf("\nLOADING, PLEASE WAIT");
          for(i=0;i<5;i++)
             {
              printf(".");
              Sleep(420);
             }
         }
       printf("\n\n              ~~~~~~~~~~~~~~\n              ~ LOGIN PAGE ~\n              ~~~~~~~~~~~~~~\n\nEnter 1 if you are a New User (To Sign Up)\nEnter 2 if you are an Exisiting user (To Sign In)\nEnter 3 to Close Application\nEnter your Choice: ");
       scanf("%d", &Choice);
       switch(Choice)
             {
              case 1: {
                       signup(0, "DMS");
                       break;
                      }
              case 2: {
                       signin();
                       break;
                      }
              case 3: {
                       printf("\nGOODBYE!\nCLOSING APPLICATION");
                       for(i=0;i<5;i++)
                          {
                           printf(".");
                           Sleep(420);
                          }
                       exit(0);
                      }
              default:{ 
                       printf("Invalid Choice!\nPress any key to continue");
                       getch();
                       break;
                      }
             }
      }
}