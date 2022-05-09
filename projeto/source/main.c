//
// Mini - Projeto
// Princípios de Programação Procedimental 2021-2022
//
// Pedro M. Oliveira - 2016255658
//

#include "main.h"

int bar_init(bar **bar, student **students, product **products){
    char buf[MAX_SIZE_LINE];

    // Carregar info-geral do bar
    *bar = (struct bar*)calloc(1, sizeof(struct bar));

    FILE *init_fp;
    init_fp = fopen(INIT_FILENAME, "r");
    if (init_fp == NULL){
        printf("Não foi possível carregar o ficheiro de INICIALIZAÇÃO.");
        exit(1);
    }

    fgets(buf, MAX_SIZE_LINE, init_fp);
    char *bar_name = strtok(buf, "\n");
    (*bar)->name = malloc(sizeof(char) * strlen(bar_name));
    strcpy((*bar)->name, bar_name);

    fgets(buf, MAX_SIZE_LINE, init_fp);
    char *bar_address = malloc(sizeof(char)* strlen(buf));
    strcpy(bar_address,strtok(buf, "\n"));

    fgets(buf, MAX_SIZE_LINE, init_fp);
    char *bar_postal = malloc(sizeof(char)* strlen(buf));
    strcpy(bar_postal, strtok(buf, "\n"));

    (*bar)->address = malloc(sizeof(char)*(strlen(bar_name)+strlen(bar_name)+1));
    strcpy((*bar)->address,bar_address);
    strcat((*bar)->address,"\n");
    strcat((*bar)->address,bar_postal);

    free(bar_address); free(bar_postal);

    fgets(buf, MAX_SIZE_LINE, init_fp);

    char * d = strtok(buf, "-");
    (*bar)->today.day = atoi(d);

    d = strtok(NULL, "-");
    (*bar)->today.month = atoi(d);

    d = strtok(NULL, "-");
    (*bar)->today.year = atoi(d);

    fclose(init_fp);

    FILE *students_fp;
    students_fp = fopen(STUDENTS_FILENAME, "r");
    if (students_fp == NULL){
        printf("Não foi possível carregar o ficheiro de ESTUDANTES.");
        exit(1);
    }
    while(fgets(buf, MAX_SIZE_LINE, students_fp)!=NULL){
        student *s = calloc(1,sizeof(student));

        char *part = strtok(buf, ";");
        s->number = atoi(part);

        part = strtok(NULL, ";");
        s->name = malloc(sizeof(char)* strlen(part));
        strcpy(s->name, part);

        part = strtok(NULL, ";");
        char *date = malloc(sizeof(char)*strlen(part));
        strcpy(date, part);

        part = strtok(NULL, ";");
        s->class_year = atoi(part);

        part = strtok(NULL, ";");
        s->class_letter = malloc(sizeof(char)* strlen(part));
        strcpy(s->class_letter, part);

        part = strtok(NULL, ";");
        s->balance = atol(part);

        char *date_ptr = strtok(date, "-");
        s->birthday.day = atoi(date_ptr);
        date_ptr = strtok(NULL, "-");
        s->birthday.month = atoi(date_ptr);
        date_ptr = strtok(NULL, "-");
        s->birthday.year = atoi(date_ptr);
        free(date);

        s->prev = (*students);
        s->next = NULL;
        if((*students)!=NULL) (*students)->next = s;
        (*students) = s;

    }
    fclose(students_fp);

    FILE *products_fp;
    products_fp = fopen(PRODUCTS_FILENAME, "r");
    if (products_fp == NULL){
        printf("Não foi possível carregar o ficheiro de PRODUTOS.");
        exit(1);
    }
    while(fgets(buf, MAX_SIZE_LINE, products_fp)!=NULL){
        product *p = calloc(1,sizeof(product));

        char *part = strtok(buf, ";");
        p->barcode = malloc(sizeof(char)* strlen(part));
        strcpy(p->barcode, part);

        part = strtok(NULL, ";");
        p->name = malloc(sizeof(char)* strlen(part));
        strcpy(p->name, part);

        part = strtok(NULL,";");
        p->price = atof(part);

        p->next = (*products);
        (*products) = p;

    }
    fclose(products_fp);

    return 0;

}
int main(int argc, char *argv[]){
    bar *bar_set = NULL;
    student *students = NULL;
    product *products = NULL;
    bill *bills = NULL;
    bar_init(&bar_set, &students, &products);
    printf("\n*************************** ");
    printf("\n***      %s     ***", bar_set->name);
    printf("\n***************************");

    printf("\nHOJE: \t %d/%d/%d\n", bar_set->today.day, bar_set->today.month, bar_set->today.year);






}
