#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
// structure used to make different kind of variables
struct students {
    char full_name[20];
    int rollno;
    char class[20];
    char contact[20];
    char date[20];
} st;
// Global File pointer to a file
FILE* fptr;
// Fuctions 
void display();
void input();
void search();
void searchbyname();
void searchbyroll();
void guide();
void deleteRecord();
void modify();
// Function to check if roll already exists in data
int rollexist(int rollNUM) {
    FILE *fp = fopen("Data.csv", "r");
    if (fp == NULL) {
        return 0; // file empty or not created
    }
    char name[100], clas[20], conta[20], dat[20];
    int rol;
    while (fscanf(fp, "%99[^,],%d,%19[^,],%19[^,],%19[^\n]\n",
                  name, &rol, clas, conta, dat) == 5) {
        if (rol == rollNUM) {
            fclose(fp);
            return 1; // Roll no found
        }
    }
    fclose(fp);
    return 0; // not found
}
//Function to modify student data
void modify() {
    system("cls");
    char name[100], clas[20], conta[20], dat[20];
    int rol;
    char r[20];
    int rl, f = 0;
    printf("\t\t\tModify Student\n");
    printf("Enter Roll no to modify:\n");
    scanf("%d", &rl);
    while (getchar() != '\n'); // clear buffer
    FILE* fp = fopen("Data.csv", "r");
    FILE* temp = fopen("Temp.csv", "w");
    if (!fp || !temp) {
        perror("Error Opening File!\n");
        return;
    }
    while (fscanf(fp, "%99[^,],%d,%19[^,],%19[^,],%19[^\n]\n",
                  name, &rol, clas, conta, dat) == 5) {
        if (rol == rl) {
            f = 1;

            printf("Enter New Name:\n");
            fgets(name, sizeof(name), stdin);
            char *p = strchr(name, '\n');// to replace  '\n' with '\0'
            if (p) *p = '\0';

            printf("Enter New Rollno:\n");
            fgets(r, sizeof(r), stdin);
            char *k = strchr(r, '\n');
            if (k) *k = '\0';
            rol = atoi(r);

            printf("Enter New Class:\n");
            fgets(clas, sizeof(clas), stdin);
            char *j = strchr(clas, '\n');
            if (j) *j = '\0';

            printf("Enter New Contact Number:\n");
            fgets(conta, sizeof(conta), stdin);
            char *c = strchr(conta, '\n');
            if (c) *c = '\0';

            printf("Enter New Date of Admission (dd/mm/yy):\n");
            fgets(dat, sizeof(dat), stdin);
            char *d = strchr(dat, '\n');
            if (d) *d = '\0';
        }
        fprintf(temp, "%s,%d,%s,%s,%s\n", name, rol, clas, conta, dat);
    }

    fclose(fp);
    fclose(temp);

    remove("Data.csv");
    rename("Temp.csv", "Data.csv");

    if (f) {
        printf("Record Modified Successfully\n");
    } else {
        printf("No record found!\n");
    }

    printf("Press any key to continue---\n");
    getch();
}

// Function to guide users
void guide() {
    system("cls");
    printf("I am Muhammad Hamza Shaukat, developed project Student Management System in C\n");
    printf("Press any key to continue---\n");
    getch();
}
// Function to Delete record
void deleteRecord() {
    system("cls");
    char name[100], clas[20], conta[20], dat[20];
    int rol, rl, f = 0;

    printf("\t\t\tDelete Student\n");
    printf("Enter Roll no:\n");
    scanf("%d", &rl);

    fptr = fopen("Data.csv", "r");
    FILE* temp = fopen("Temp.csv", "w");

    if (!fptr || !temp) {
        perror("Error Opening File!\n");
        return;
    }

    while (fscanf(fptr, "%99[^,],%d,%19[^,],%19[^,],%19[^\n]\n",
                  name, &rol, clas, conta, dat) == 5) {
        if (rol == rl) {
            f = 1;
            continue; // skip record
        }
        fprintf(temp, "%s,%d,%s,%s,%s\n",
                name, rol, clas, conta, dat);
    }

    fclose(fptr);
    fclose(temp);

    remove("Data.csv");
    rename("Temp.csv", "Data.csv");

    if (f) {
        printf("Record Deleted Successfully\n");
    } else {
        printf("No record found!\n");
    }

    printf("Press any key to continue---\n");
    getch();
}
//Function to Search Student
void search() {
    system("cls");
    int ch;
    printf("Enter your choice\n");
    printf("1.Search by rollno\n");
    printf("2.Search by name\n");
    scanf("%d", &ch);
    while (getchar()!='\n');
    switch (ch) {
    case 1:
        searchbyroll();
        break;
    case 2:
        searchbyname();
        break;
    default:
        printf("Invalid Choice!\n");
        break;
    }

    printf("Press any key to continue---\n");
    getch();
}
// Funtion to Search student by name
void searchbyname() {
    system("cls");
    char search_name[100];
    char name[100], clas[20], conta[20], dat[20];
    int rol, f = 0;

    printf("\t\t\tSearch by Name\n");
    printf("Enter Name:\n");
    fgets(search_name, sizeof(search_name), stdin);
    char *p = strchr(search_name, '\n');
    if (p) *p = '\0';

    fptr = fopen("Data.csv", "r");
    if (!fptr) {
        perror("Error Opening File!\n");
        return;
    }

    while (fscanf(fptr, "%99[^,],%d,%19[^,],%19[^,],%19[^\n]\n",
                  name, &rol, clas, conta, dat) == 5) {
        if (strcmp(name, search_name) == 0) {
            printf("\nRecord Found:\n");
            printf("Name: %s\nRoll No: %d\nClass: %s\nContact: %s\nDate: %s\n",
                   name, rol, clas, conta, dat);
            f = 1;
            break;
        }
    }
    fclose(fptr);

    if (!f) {
        printf("No Record Found!\n");
    }

    printf("Press any key to continue---\n");
    getch();
}
//Function to search student by roll no
void searchbyroll() {
    system("cls");
    int rl, rol, f = 0;
    char name[100], clas[20], conta[20], dat[20];

    printf("\t\t\tSearch by Roll No\n");
    printf("Enter Roll No: ");
    scanf("%d", &rl);
    while (getchar() != '\n'); // clear buffer

    fptr = fopen("Data.csv", "r");
    if (!fptr) {
        perror("Error Opening File!\n");
        return;
    }

    while (fscanf(fptr, "%99[^,],%d,%19[^,],%19[^,],%19[^\n]\n",
                  name, &rol, clas, conta, dat) == 5) {
        if (rol == rl) {
            printf("\nRecord Found:\n");
            printf("Name: %s\nRoll No: %d\nClass: %s\nContact: %s\nDate: %s\n",
                   name, rol, clas, conta, dat);
            f = 1;
            break;
        }
    }
    fclose(fptr);

    if (!f) {
        printf("No Record Found!\n");
    }

    printf("Press any key to continue---\n");
    getch();
}
//Function to Display entire record of Students stored in .csv file
void display() {
    system("cls");
    char name[100], clas[20], conta[20], dat[20];
    int rol;

    printf("\t\t\t\tAll Students Data\n");

    fptr = fopen("Data.csv", "r");
    if (!fptr) {
        perror("No Records Found!\n");
        getch();
        return;
    }

    // Print table heading
    printf("%-20s %-10s %-20s %-20s %-20s\n",
           "Name", "Roll No", "Class", "Contact", "Date");

    // Read and display records
    while (fscanf(fptr, "%99[^,],%d,%19[^,],%19[^,],%19[^\n]\n",
                  name, &rol, clas, conta, dat) == 5) {
        printf("%-20s %-10d %-20s %-20s %-20s\n",
               name, rol, clas, conta, dat);
    }

    fclose(fptr);

    printf("\nPress any key to continue---\n");
    getch();
}
//Function to Input Student Data
void input() {
    char stri_roll[20];
    system("cls");
    printf("\t\t\tAdd Student\n");
    printf("--------------DISCLAIMER-----------------------\n");
    printf("Dont Leave Any Field Blank!\n");
    printf("Press any key to continue----");
    while (getchar() != '\n'); // clear input buffer
    printf("Enter Name:\n");
    fgets(st.full_name, sizeof(st.full_name), stdin);
    char *p = strchr(st.full_name, '\n');
    if (p) *p = '\0';

    printf("Enter Rollno:\n");
    fgets(stri_roll, sizeof(stri_roll), stdin);
    char *k = strchr(stri_roll, '\n');
    if (k) *k = '\0';
    st.rollno = atoi(stri_roll);

    // check roll no if already exists
    if (rollexist(st.rollno)) {
        printf("Roll no Already Exists!\n");
        getch();
        return;
    }

    fptr = fopen("Data.csv", "a");
    if (fptr == NULL) {
        printf("Error Opening file!\n");
        return;
    }

    printf("Enter Class:\n");
    fgets(st.class, sizeof(st.class), stdin);
    char *j = strchr(st.class, '\n');
    if (j) *j = '\0';

    printf("Enter Contact Number:\n");
    fgets(st.contact, sizeof(st.contact), stdin);
    char *c = strchr(st.contact, '\n');
    if (c) *c = '\0';

    printf("Enter Date of Admission (dd/mm/yy):\n");
    fgets(st.date, sizeof(st.date), stdin);
    char *d = strchr(st.date, '\n');
    if (d) *d = '\0';

    fprintf(fptr, "%s,%d,%s,%s,%s\n",
            st.full_name, st.rollno, st.class, st.contact, st.date);

    printf("Record Saved Successfully!\n");

    fclose(fptr);
    getch();
}
// Function for main menu and to get user choice 
int main() {
    int choice;
    while (1) {
        system("cls");
        printf("\t\t\t--Student Management System---\n");
        printf("Enter your choice:\n");
        printf("1.Add Admission\n");
        printf("2.Student Info\n");
        printf("3.Search\n");
        printf("4.Modify\n");
        printf("5.Delete\n");
        printf("6.Guide Us\n");
        printf("0.Exit\n");
         scanf("%d", &choice);
        while (getchar() != '\n'); // clear buffer

        switch (choice) {
        case 0:
            exit(0);
        case 1:
            input();
            break;
        case 2:
            display();
            break;
        case 3:
            search();
            break;
        case 4:
            modify();
            break;
        case 5:
            deleteRecord();
            break;
        case 6:
            guide();
            break;
        default:
            printf("Invalid choice!\n");
            getch();
        }
    }
    return 0;
}
