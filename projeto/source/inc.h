//
// Mini - Projeto
// Princípios de Programação Procedimental 2021-2022
//
// Pedro M. Oliveira - 2016255658
//

#ifndef PPP_MAIN_H
#define PPP_MAIN_H

#define MAX_SIZE_LINE 100
#define MAX_SIZE_INPUT 64
#define INIT_FILENAME "init.txt"
#define STUDENTS_FILENAME "students.txt"
#define PRODUCTS_FILENAME "products.txt"
#define BILLS_FILENAME "bills.txt"

#define MIN_YEAR 1990
#define MAX_YEAR 2010

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct date{
    int day;
    int month;
    int year;
}date;

typedef struct bar{
    char *name;
    char *address;
    date today;
}bar;

typedef struct student{
    int number;
    char *name;
    date birthday;
    int class_year;
    char *class_letter;
    double balance;
    struct student *next;
} student;

typedef struct product{
    char *barcode;
    char *name;
    double price;
    struct product *next;
} product;

typedef struct bill_descriptive{
    int quantity;
    product *product;
    struct bill_descriptive *next;
} bill_descriptive;

typedef struct bill{
    int type; // 0 = despesa, 1 = carregamento. Se = 1, description is NULL.
    date date;
    student *student;
    bill_descriptive *description;
    float total;
} bill;



int is_valid_int(char str[]);
void bar_init(bar **bar, student **students, product **products);
int is_valid_int(char str[]);
int is_leap(int y);
int verify_date(char str[]);
char *date_to_str(date d);
date str_to_date(char str[]);
int student_number_exists(int new_number, student **students);
void print_student_profile(student *s);
int cli_add_student(student **students);
int main(int argc, char *argv[]);


#endif //PPP_MAIN_H
