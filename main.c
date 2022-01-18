#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct library{
    char name[50];
    int copies;
    float cost;
}book;
int search(FILE *p,char *name){
    int flag =0;
    rewind(p);
    while(fread(&book, sizeof(book),1,p) == 1){
        if(strcmp(name,book.name)==0){
            flag = 1;
            break;
        }
    }
    if(flag == 0 ){
        printf("\t Name Not Found......\n\n");
        return flag;
    }else{
        return flag;
    }
}

void insert(FILE *p){
    fseek(p,0,2);
    printf("Enter Name: \n");
    scanf("%s",book.name);
    printf("Enter Copies: \n");
    scanf("%d",&book.copies);
    printf("Enter Cost: \n");
    scanf("%f",&book.cost);
    fwrite(&book, sizeof(book),1,p);
}
void del(FILE *p){
    FILE *ptemp;char name[50];int flag = 0;
    ptemp = fopen("temp","wb");
    p = fopen("Books","rb");
    printf("Enter name of book to delete: \n");
    scanf("%s",name);
    while(fread(&book, sizeof(book),1,p) == 1){
        if(strcmp(book.name,name)!=0){
            fwrite(&book, sizeof(book),1,ptemp);
        }else{flag =1;}
    }
    if(flag ==1){printf("Book Removed.......\n\n");}
    else{ printf("Book Not Found");}
    fclose(p);
    fclose(ptemp);
    remove("Books");
    rename("temp","Books");
    p = fopen("Books","rb+");
}
void modify(FILE *p){
    char name[50];
    printf("Enter Name of book to be modified: \n");
    scanf("%s",name);
    if(search(p,name) == 1){
        printf("Enter New Data:\n");
        printf("Enter Name:\n");
        scanf("%s",book.name);
        printf("Enter Book Copies:\n");
        scanf("%d",&book.copies);
        printf("Enter Book Cost:\n");
        scanf("%f",book.cost);
        fseek(p,-sizeof(book),1);
        fwrite(&book, sizeof(book),1,p);
        printf("Book record Modified.....\n\n");

    }
}
void booksold(FILE *p){
    char name[50];
    printf("Enter name of book to be sold:\n");
    scanf("%s",name);
    if(search(p,name)==1){
        if(book.copies > 0){
            book.copies--;
            fseek(p,-sizeof(book),1);
            fwrite(&book, sizeof(book),1,p);
            printf("Book Sold......\n\n");
        }else
            printf("Book Out of Stock ...\t Sorry!!\n\n");
    }
}
void display(FILE *p){
    char name[50];
    printf("Enter Name to Display that record: \n");
    scanf("%s",name);
    if(search(p,name)==1){
        printf("\nName\t%s\n",book.name);
        printf("Copies\t%d\n",book.copies);
        printf("Cost\t%f\n\n",book.cost);

    }
}
void list(FILE *p){
    rewind(p);
    printf("\nNAME\tCOPIES\t\tCOST\n");
    while(fread(&book, sizeof(book),1,p)==1){
        printf("%s\t",book.name);
        printf("%d\t\t",book.copies);
        printf("%f\n",book.cost);
    }printf("\n");
}

int main(void ) {
    int choices;
    FILE *p;
    p= fopen("Books","wb+");
    if(p == NULL){
        printf("ERROR");
        exit(1);
    }
    while(1){
        printf("1.INSERT A NEW RECORD\n2.DELETE A RECORD\n3.DISPLAY RECORD\n4.MODIFY A RECORD\n5.LIST ALL RECORDS\n6.BOOK SOLD\n7.EXIT\n\n");
        printf("Enter choices:\n");
        scanf("%d",&choices);

        switch(choices){
            case 1:
                insert(p);
                break;
            case 2:
                del(p);
                break;
            case 3:
                display(p);
                break;
            case 4:
                modify(p);
                break;
            case 5:
                list(p);
                break;
            case 6:
                booksold(p);
                break;
            case 7:
                fclose(p);
                exit(1);
            default:
                printf("YOU ENTERED WRONG CHOICE\n");
        }
    }
return 0;
}
