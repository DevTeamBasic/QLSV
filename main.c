#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>

struct Student{
    char name[200];
    int YearOfBirth;
    char mssv[200];
    float dlt;
    float dth;
    float dtb;
};

typedef struct Student student;
typedef student* sinhvien;
char tmpOfChar[500];
int tmpOfInteger;

student getInformation(){
    student tmp;
    printf("Nhap ten sinh vien: "); fgets(tmpOfChar, sizeof(tmpOfChar), stdin); fflush(stdin);
    tmpOfChar[strlen(tmpOfChar)-1] = '\0';
    strcpy(tmp.name, tmpOfChar);
    printf("Nhap nam sinh: "); scanf("%d", &tmp.YearOfBirth); fflush(stdin); 
    printf("Nhap ma so sinh vien: "); fgets(tmpOfChar, sizeof(tmpOfChar), stdin); fflush(stdin);
    tmpOfChar[strlen(tmpOfChar)-1] = '\0';
    strcpy(tmp.mssv, tmpOfChar);
    printf("Nhap diem li thuyet: "); scanf("%f", &tmp.dlt); fflush(stdin);
    printf("Nhap diem thuc hanh: "); scanf("%f", &tmp.dth); fflush(stdin);
    tmp.dtb = (tmp.dlt+tmp.dth)/2;
    return tmp;
}

void showInformation(student sv){
    printf("Name: "); puts(sv.name);
    printf("Birth: %d\n", sv.YearOfBirth);
    printf("Student ID: "); puts(sv.mssv);
    printf("Diem li thuyet: %.2f\n", sv.dlt);
    printf("Diem thuc hanh: %.2f\n", sv.dth);
    printf("Diem trung binh: %.2f\n", sv.dtb);
}

int i,j;
int sizeofList = 0;
int Run = 1;
int chose = -1;
int size = 500;
FILE *f;

void addnewStudent(sinhvien sv, int *size){
    fflush(stdin);
    student tmp;
    tmp = getInformation();

    sv = (sinhvien) realloc(sv, sizeof(student)*(*size+1));
    sv[*size] = tmp;
    *size = *size + 1;
    fflush(stdin);
}
void showAll(sinhvien sv, int size){
    if(size == 0){
        printf("Danh sach trong."); printf("\n");
    }
    else{
        printf("%-4s|%-20s|%-10s|%-10s|%-5s|%-5s|%-5s\n","STT","Name","Birth","ID","Score_1","Score_2","AVG");
        printf("=====================================================================\n");
        for(i = 0; i <= size-1; i++){
            printf("%-4d|%-20s|%-10d|%-10s|%-7.2f|%-7.2f|%-7.2f\n",i+1,sv[i].name,sv[i].YearOfBirth,sv[i].mssv,sv[i].dlt,sv[i].dth, sv[i].dtb);
            printf("---------------------------------------------------------------------\n");
        }
    }
}

void function_3(sinhvien sv, int *size){
    fflush(stdin);
    char s[200];
    printf("Nhap ma so sinh vien can xoa: "); fgets(s, sizeof(s), stdin); fflush(stdin);
    s[strlen(s)-1] = '\0';
    int index = 0;
    for(i = 0; i <= *size-1; i++){
        if(strcmp(sv[i].mssv, s) == 0) index = i;
    }
    for(i = index; i <= *size-1; i++){
        sv[i] = sv[i+1];
    }
    sv = (sinhvien) realloc(sv, *size-1);
    *size = *size - 1;
    fflush(stdin);
}
void function_4(sinhvien sv, int size){
    printf("---------------------MENU------------------\n");
    printf("+   1. Tim theo nam sinh.                 +\n");
    printf("+   2. Tim theo ma so sinh vien.          +\n");
    printf("-------------------------------------------\n");
    int index;
    printf("Nhap lua chon cua ban: "); scanf("%d", &index);
    printf("-------------------------------------------\n");
    if(index == 1){
        int year;
        printf("Nhap nam sinh can tim: "); scanf("%d", &year); 
        system("cls");
        int count = 0;
        printf("%-4s|%-20s|%-10s|%-10s|%-5s|%-5s|%-5s\n","STT","Name","Birth","ID","Score_1","Score_2","AVG");
        printf("=====================================================================\n");
        for(i = 0; i <= size-1; i++){
            if(sv[i].YearOfBirth == year){
                printf("%-4d|%-20s|%-10d|%-10s|%-7.2f|%-7.2f|%-7.2f\n",i+1,sv[i].name,sv[i].YearOfBirth,sv[i].mssv,sv[i].dlt,sv[i].dth, sv[i].dtb);
                printf("---------------------------------------------------------------------\n");
                count++;
            }
        }
        printf("Co %d sinh vien sinh nam %d.", count, year);
    }
    else if(index == 2){
        char MSSV[200]; fflush(stdin);
        printf("Nhap ma so sinh vien can tim: "); fgets(MSSV, sizeof(MSSV), stdin); fflush(stdin);
        MSSV[strlen(MSSV)-1] = '\0';
        system("cls"); int t = 0; int index;
        for(i = 0; i <= size-1; i++){
            if(strcmp(sv[i].mssv, MSSV) == 0){
                t = 1;
                index = i;
                break;
            }
        }
        if(t == 0){
            printf("Khong co sinh vien nao co ma so sinh vien %d.", MSSV);
        }
        else{
            showInformation(sv[i]);
        }
    }
    else{
        printf("ERROR 404");
    }
    fflush(stdin);
}
void function_5(sinhvien sv, int size){
    student tmp_sv;
    for(i = 0; i <= size-1; i++){
        for(j = 0; j <= size-1; j++){
            if(sv[i].dtb > sv[j].dtb){
                tmp_sv = sv[i];
                sv[i] = sv[j];
                sv[j] = tmp_sv;
            }
        }
    }
    showAll(sv,size);
}
void MENU(){
    printf("---------------------MENU------------------\n");
    printf("+   1. Them sinh vien.                    +\n");
    printf("+   2. Xem toan bo sinh vien.             +\n");
    printf("+   3. Xoa sinh vien.                     +\n");
    printf("+   4. Tim sinh vien.                     +\n");
    printf("+   5. Danh sach sinh vien theo diem.     +\n");
    printf("+   0. Thoat chuong trinh.                +\n");
    printf("-------------------------------------------\n");
}
int main(){
    f = fopen("QLSV.bin","rb");
    fread(&sizeofList, sizeof(sizeofList), 1, f);
    student *ListStudent = (sinhvien) malloc(sizeofList*sizeof(student));
    for(i = 0; i <= sizeofList-1; i++){
        fread(&ListStudent[i], sizeof(student), 1, f);
    }
    fclose(f);
    while(Run == 1){
        MENU();
        printf("Moi ban nhap lua chon: "); scanf("%d", &chose);
        if(chose<0 && chose>5){
            printf("ERROR 404");
        }
        else{
            if(chose == 1){
                fflush(stdin);
                system("cls");
                printf("-------------------------------------------\n");
                printf("+              THEM SINH VIEN             +\n");
                printf("-------------------------------------------\n");
                addnewStudent(ListStudent, &sizeofList);
                printf("+        Them sinh vien thanh cong!       +\n");
            }
            else if(chose == 2){
                fflush(stdin);
                system("cls");
                printf("-------------------------------------------\n");
                printf("+           DANH SACH SINH VIEN           +\n");
                printf("-------------------------------------------\n");
                showAll(ListStudent, sizeofList);
            }
            else if(chose == 3){
                fflush(stdin);
                system("cls");
                printf("-------------------------------------------\n");
                printf("+               XOA SINH VIEN             +\n");
                printf("-------------------------------------------\n");
                function_3(ListStudent, &sizeofList);
                printf("+         Xoa sinh vien thanh cong!       +\n");

            }
            else if(chose == 4){
                fflush(stdin);
                system("cls");
                printf("-------------------------------------------\n");
                printf("+               TIM SINH VIEN             +\n");
                printf("-------------------------------------------\n");
                function_4(ListStudent, sizeofList);
            }
            else if(chose == 5){
                fflush(stdin);
                system("cls");
                printf("-------------------------------------------\n");
                printf("+      DANH SACH THEO DIEM TRUNG BINH     +\n");
                printf("-------------------------------------------\n");
                function_5(ListStudent, sizeofList);
            }
            else if(chose == 0){
                fflush(stdin);
                system("cls");
                printf("-------------------------------------------\n");
                printf("+            THOAT CHUONG TRINH           +\n");
                printf("-------------------------------------------\n");
                Run = 0;
                
                char A[11] = {'_','_','_','_','_','_','_','_','_','_'};
                int count = 0;
                for(i = 0; i <= 10000 ;i++){
                    if(i%1000 == 0) {system("cls");printf("Auto save!\n");
                        A[count] = '#'; 
                        count++;
                        printf("["); for(j = 0; j <= 9; j++) printf("%c", A[j]);
                        printf("]");
                    }
                }
                printf("\n");
                printf("SUCCESSFUL");
            }
        }
    }
    f = fopen("QLSV.bin","wb");
    fwrite(&sizeofList, sizeof(sizeofList), 1, f);
    for(i = 0; i <= sizeofList-1; i++){
        fwrite(&ListStudent[i], sizeof(student), 1, f);
    }
    fclose(f);
    return 0;
}
