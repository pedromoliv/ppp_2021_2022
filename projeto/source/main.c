//
// Mini - Projeto
// Princípios de Programação Procedimental 2021-2022
//
// Pedro M. Oliveira - 2016255658
//

#include "inc.h"

/**
 * Inicializa através dos ficheiros de texto a aplicação
 * @param bar
 * @param students
 * @param products
 * @return
 */
void bar_init(bar **bar, student_list **students, product **products){
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

        student *last_student_added = (*students)->last;

        last_student_added->next = s;
        (*students)->last = s;

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
    return;

}

/**
 * Verifica se array de carateres é um número
 * @param str numero (sem '\0')
 * @return  -999 se não for um número, ou o número introduzido
 */
int is_valid_int(char str[]){
    for(unsigned long i=0; i<strlen(str); i++){
        if(!isdigit(str[i])) {
            if(str[i] != '\0') {
                return -999;
            }
        }
    }
    int num = atoi(str);
    return num;
}

/**
 * Verifica se existe algum estudante com new_number
 * @param new_number
 * @param students
 * @return
 */
int student_number_exists(int new_number, student_list **students){
    student * st = (*students)->first;
    for(; st->next != (*students)->last ; st = st->next){
        if(new_number == st->number) return 1;
    }
    return 0;
}

int cli_add_student(student_list **students){
    printf("\e[1;1H\e[2J");
    printf("*************************** ");
    printf("\n***  ADICIONAR ALUNO   ***");
    printf("\n***************************\n");

    int number = -999;
    char input[MAX_SIZE_INPUT];
    while(number==-999){
        printf("NÚMERO # ");
        scanf("%s", input);
        if(strcmp(input, "c!")==0) break;
        number = is_valid_int(input);
        if(number==-999) printf("NÃO FOI INTRODUZIDO UM NÚMERO VÁLIDO\n");
        if(student_number_exists(number, &(*students))==1){
            printf("JÁ EXISTE UM ESTUDANTE COM ESSE NÚMERO\n");
            number = -999;
        }
    }

    char name[MAX_SIZE_INPUT];
    char birthday[MAX_SIZE_INPUT];
    char class_year[MAX_SIZE_INPUT];
    char class_letter[MAX_SIZE_INPUT];

    printf("NOME DO ALUNO: ");
    scanf("%s", name);

    printf("DATA DE NASCIMENTO: ");
    scanf("%s", birthday);

    printf("ANO: ");
    scanf("%s", class_year);
    
    printf("TURMA: ");
    scanf("%s", class_letter);
    return 0;

}

int main(int argc, char *argv[]){
    bar *bar_set = NULL;
    student_list *students = NULL;
    product *products = NULL;
    bill *bills = NULL;

    bar_init(&bar_set, &students, &products);

    int menu = 0;
    while(menu != 4){
        printf("\e[1;1H\e[2J");
        printf("*************************** ");
        printf("\n***      %s     ***", bar_set->name);
        printf("\n***************************");
        printf("\n*** HOJE: \t %.2d/%.2d/%d ", bar_set->today.day, bar_set->today.month, bar_set->today.year);
        printf("\n***************************\n");
        printf("1 - ADICIONAR ALUNO\n");
        printf("2 - VER INFORMAÇÕES DE UM ALUNO\n");
        printf("3 - LISTAR TODOS OS ALUNOS\n");
        printf("4 - LISTAR ALUNOS [SALDO ABAIXO DE X]\n");
        printf("5 - CARREGAR CONTA ALUNO\n");
        printf("6 - EFECTUAR VENDA\n");
        printf("7 - ALTERAR DATA\n");
        printf("8 - SAIR\n");


        char input[MAX_SIZE_INPUT];
        printf("OPÇÃO \t# ");
        scanf("%s", input);
        menu = is_valid_int(input);

        switch (menu) {
            case 1:
                cli_add_student(&students);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            default:
                // Not workin
                printf("OPÇÃO INVÁLIDA, <ENTER PARA CONTINUAR>\n");
                char i = 0;
                while (i != '\r' && i != '\n') { fflush(stdout); i = getchar(); }
                break;
        }

    }

}
