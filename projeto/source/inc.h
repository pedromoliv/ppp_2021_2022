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
#define MAX_YEAR 2022

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

typedef struct student_list{
    student *node;
    struct student_list *next;
}student_list;

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
    struct bill *next;
} bill;

typedef struct bill_list{
    int id;
    bill *node;
    struct bill_list *next;
} bill_list;

typedef struct bill_descriptive_list{
    int id;
    bill_descriptive *node;
    struct bill_descriptive_list *next;
} bill_descriptive_list;

void bar_init(bar **bar, student **students, product **products, bill **bills);
void bar_save_bar_set(bar **bar_set);
void bar_save_students(student **students);
void bar_save_bills(bill **bills);
void bar_save(bar **bar, student **students, product **products, bill **bills);
int is_valid_int(char str[]);
void enter_to_continue();
/** for dates */
int is_leap(int y);
int verify_date(char str[]);
char *date_to_str(date d);
date str_to_date(char str[]);
/** for students */
int student_number_exists(int new_number, student **students);
int cli_asks_for_student_number(student **students);
student *get_student_profile(student **students, int number);
void print_student_profile(student *s);
int cli_add_student(student **students);
int compare_student(const void *p, const void *q);
student_list *sorted_student_list(student **students);
void cli_list_students(student **students);
void cli_show_user_bills(student *s, bill **bills);
int delete_student(student *student_to_delete, student **students);
void cli_student(student *s, bill **bills, student **students);
student_list *get_students_below(float value, student **students);
/** for bills */
float is_valid_float(char str[]);
int cli_top_up(bar **bar_set, student **students, bill **bills);
void show_bill(bill *b);
product *product_search(char *barcode, product **products);
float cart_total(bill_descriptive *shopping_cart);
int cart_total_articles(bill_descriptive *shopping_cart);
bill_descriptive *cli_asks_for_bill_descriptive(bill_descriptive **shopping_cart, product **products);
int cli_print_cart(bill_descriptive *shopping_cart);
int cli_bill(bar **bar_set, student **students, bill **bills, product **products);

int main(int argc, char *argv[]);


#endif //PPP_MAIN_H
