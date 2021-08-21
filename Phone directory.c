#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<stdbool.h>
FILE *fp;
struct clients
{
    struct clients* link;
    char name[100];
    char number[100];
};
typedef struct clients* client;

client head=NULL;

bool checknm(char na[100])
{
    int i,c=strlen(na);
    for(i=0;i<c;i++)
    {
        if(na[i]>='0'&&na[i]<='9'||na[i]==' ')
        {
            printf("\tINVALID NAME!!!\n");
            printf("\tENTER AGAIN!!!\n");
            return 0;
        }
    }
    return 1;
}
bool checkno(char nos[100])
{
    int i,c=strlen(nos);
    for(i=0;i<c;i++)
    {
        if(nos[i]>='a'&&nos[i]<='z'||nos[i]>='A'&&nos[i]<='Z'||nos[i]==' ')
        {
            printf("\tINVALID NUMBER!!!\n");
            printf("\tENTER AGAIN!!!\n");
            return 0;
        }
    }
    fp=fopen("phonedirec.txt","r+");
    char str1[100],str2[100];
    while(fscanf(fp,"%s",str1)==1)
    {
        fscanf(fp,"%s",str2);
        if(strcmp(nos,str2)==0)
        {
            printf("\tNUMBER ALREADY PRESENT!!!\n");
            printf("\tENTER AGAIN!!!\n");
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

void creat_file(char n[100],char num[100])
{
    client temp=(client)malloc(sizeof(struct clients));
    strcpy(temp->name,n);
    strcpy(temp->number,num);
    temp->link=NULL;
    fp=fopen("phonedirec.txt","a+");
    fprintf(fp,"%s %s\n",temp->name,temp->number);
    fclose(fp);
    printf("\tThe name is %s and the corresponding number is %s\n",temp->name,temp->number);

    if(head==NULL)
    {
        head = temp;
        return;
    }

    client cur=head;
    while(cur->link!=NULL)
    {
        cur=cur->link;
    }
    cur->link=temp;
}
void delfile(char name[100])
{
    fp=fopen("phonedirec.txt","r+");
    FILE *fp1;
    fp1=fopen("temp.txt","w+");
    fseek(fp,0,0);
    char name1[100],no1[100];
    while(fscanf(fp,"%s",name1)==1)
    {
        fscanf(fp,"%s",no1);
        if(strcmp(name,name1)!=0)
        {
            fprintf(fp1,"%s %s\n",name1,no1);
        }
    }
    fseek(fp,0,2);
    fclose(fp1);
    fclose(fp);
    remove("phonedirec.txt");
    rename("temp.txt", "phonedirec.txt");
}
void searchdelfile(char name2[100])
{
    int mod,x=0;
    char str[100];
    fp=fopen("phonedirec.txt","r+");
    char name1[100],no1[100];
    while(!feof(fp))
    {
        fscanf(fp,"%s %s",name1,no1);
        if(!strcmp(name2,name1))
        {
            x=1;
            printf("\n\t____DATA FOUND IN FILE___\n\n");
            fclose(fp);
            delfile(name1);
            printf("%s is deleted successfully\n",name1);
            printf("\n\t____Data deleted in file___\n");
            break;
        }
    }
    if(x==0)
    {
        printf("\n\t____DATA NOT FOUND___\n\n");
    }
}

void terminating_file(char n[100])
{
    client cur,temp;
    cur=head;
    if(strcmp(cur->name,n)==0)
    {
        temp=head;
        head=head->link;
        free(temp);
        delfile(n);
        printf("%s is deleted successfully\n",n);
    }
    else
    {
        while(strcmp(cur->name,n)!=0)
        {
            if(cur->link==NULL)
            {
                printf("Any case of %s does not exist in linked list\n",n);
                searchdelfile(n);
                return;
            }
            temp=cur;
            cur=cur->link;
        }
        temp->link=cur->link;
        free(cur);
        delfile(n);
        printf("%s is deleted successfully\n",n);
    }
}

void print_now()
{
    if(head==NULL)
    {
        printf("Directory empty\n");
        return;
    }
    client cur=head;
    int c=1;
    printf("Person # ---> Name \t Number\n");
    while(cur!=NULL)
    {
        printf("Person %d ---> %s \t %s\n",c,cur->name,cur->number);
        cur=cur->link;
        c++;
    }
}
void modifyfile(char name[100],char no[100])
{
    fp=fopen("phonedirec.txt","r+");
    char name1[100],no1[100];
    printf("\n");
    while(!feof(fp))
    {
        fscanf(fp,"%s %s",name1,no1);
        if(!strcmp(name,name1))
        {
            int pos=strlen(no1)+strlen(name1)+1;
            fseek(fp,-1*pos,SEEK_CUR);
            fprintf(fp,"%s %s\n",name,no);
            break;
        }
    }
    fclose(fp);
}
void searchfile(char n[100])
{
    int mod,x=0;
    char str[100];
    fp=fopen("phonedirec.txt","r+");
    char name1[100],no1[100];
    while(!feof(fp))
    {
        fscanf(fp,"%s %s",name1,no1);
        if(!strcmp(n,name1))
        {
            x=1;
            printf("\n\t____DATA FOUND IN FILE___\n\n");
            printf("Name :%s \n",name1);
            printf("Phone no# :%s\n",no1);
            printf("\nDo You want to modify Phone Number (0/1)(1 for yes ,0 for no) : ");
            scanf("%d",&mod);
            if(mod==1)
            {
                poi:
                printf("\nEnter New Phone Number ");
                scanf ("%s",str);
                if(!checkno(str))
                goto poi;
                modifyfile(n,str);
                printf("\n\t____Data Updated in file___\n");
                break;
            }
        }
    }
    if(x==0)
    {
        printf("\n\t____DATA NOT FOUND___\n\n");
    }
}

void search(char n[100])
{
    int mod;
    char str[100];

    client cur=head;
    while(cur!=NULL)
    {
        if(strcmp(cur->name,n)==0)
        {

            printf("\n\t____DATA FOUND___\n\n");
            printf("Name :%s \n",cur->name);
            printf("Phone no# :%s\n",cur->number);
            printf("\nDo You want to modify Phone Number (0/1)(1 for yes ,0 for no) : ");
            scanf("%d",&mod);
            if(mod==1)
            {
                po:
                printf("\nEnter New Phone Number(without space) ");
                scanf ("%s",str);
                if(!checkno(str))
                goto po;
                strcpy(cur->number,str);
                modifyfile(n,str);
                printf("\n\t____Data Updated in file and linked list___\n");

            }
            return;
        }
        cur=cur->link;
    }

    printf("\n\t____DATA NOT FOUND IN LINKED LIST__\n\n");
    searchfile(n);
}

void print()
{
    char s[100],s1[100];
    fp=fopen("phonedirec.txt","r");
    printf("\nNAME\t PHONE NUMBER\n");
    while(fscanf(fp,"%s",s)==1)
    {
        fscanf(fp,"%s",s1);
        printf("%s\t %s\n",s,s1);
    }
    fclose(fp);
}

int main()
{
    printf("\t\t\t\tRV COLLEGE OF ENGINEERING\n\n");
    printf("NAME-OS SUMUKH    1RV19IS035\n\n");
    int nooffiles,i,p,z;
    char n[100],nm[100];
    printf("\t\t\t PHONE DIRECTORY SYSTEM\n");
    printf("\n\t===================================================================\n\n");
    printf("\n\t===================================================================\n\n");
    printf("\n\t1- SAVE NUMBERS\n");
    printf("\n\t2- CAN SEARCH AND UPDATE THE NUMBER\n");
    printf("\n\t3- WHEN A NUMBER IS OFF,,, YOU CAN DELETE IT FROM YOUR DIRECTORY\n");
    printf("\n\t4-CAN SEE ALL THE LIST ANY TIME\n");
    printf("\n\t===================================================================\n\n");
    printf("\n\t========================SAVE NUMBERs===============================\n\n");
    printf("\tEnter the number of numbers you want to store: ");
    scanf("%d",&nooffiles);
    fflush(stdin);

    for(i=0;i<nooffiles;i++)
    {
        xy:
        printf("\n\tEnter Name(without space): ");
        gets(n);
        if(!checknm(n))
            goto xy;
        z:
        printf("\n\tEnter Phone number(without space) : ");
        gets(nm);
        if(!checkno(nm))
            goto z;
        creat_file(n,nm);
    }
    system("cls");

    while(1)
    {
        printf("\n\nWhats the next operation you want to perform?\n");
        printf("1-Save new phone number\n");
        printf("2-Delete any number\n");
        printf("3-Search and Modify\n");
        printf("4-See All list\n");
        printf("5-List of numbers added now\n");
        printf("6-Exit\n\n\n");
        scanf("%d",&z);
        if(z==6) break;
        switch(z)
        {
            case 1:
            printf("\n\t================SAVE NEW NUMBER============================\n\n");
            printf("Enter Data to insert new person's data\n");
            zx:
            printf("\n\tEnter Name(without space): ");
            scanf("%s",n);
            if(!checknm(n))
            goto zx;
            zy:
            printf("\n\tEnter Phone number(without space): ");
            scanf("%s",nm);
            if(!checkno(nm))
            goto zy;
            creat_file(n,nm);
            printf("\tNumber of %s has been Saved in your phone directory \n",n);
            break;
            case 2:
            printf("\n\t====================DELETE NUMBER============================\n\n");
            printf("\nEnter name of person whose number you want to delete\n");
            scanf("%s",n);
            terminating_file(n);
            break;
            case 3:
            printf("\n\t===============SEARCH AND UPDATE NUMBER===================\n\n");
            printf("Enter NAME of Person to search it from list\t");
            scanf("%s",n);
            search(n);
            break;
            case 4:
            printf("\n\t=================PRINTING ALL LIST=========================\n\n");
            print();
            break;
            case 5:
            printf("\n\t=================LIST OF Numbers added now==================\n\n");
            print_now();
            break;
            default:
            printf("\t----------Invalid----------\n");
        }
        getch();
        system("cls");
    }
    printf("\nTHANK YOU\n");
    return 0;
}
