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
void bar_init(bar **bar, student **students, product **products){
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
    (*students) = calloc(1,sizeof(struct student));

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

        s->next = (*students);
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

}

/**
 * Verifica se array de carateres é um número
 * @param str
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
 * Verifica se ano é bissexto
 * @param y
 * @return
 */
int is_leap(int y) {
    if((y%4==0) && (y%100!=0) && (y%400==0))
        return 1;
    else
        return 0;
}


/**
 * Verifica se data é válida
 * @param str
 * @return
 */
int verify_date(char str[]){
    int dd, mm, yyyy;
    if (sscanf(str, "%d-%d-%d", &dd, &mm, &yyyy) == 3) {
        if(yyyy < MIN_YEAR || yyyy > MAX_YEAR)
            return 0;
        if(mm < 1 || mm > 12)
            return 0;
        if(dd < 1 || dd > 31)
            return 0;
        if(mm == 2 ) {
            if(is_leap(yyyy)) {
                if(dd <= 29)
                    return 1;
                else
                    return 0;
            }else{
                if(dd <= 28)
                    return 1;
                else
                    return 0;
            }
        }
        if (mm == 4 || mm == 6 || mm == 9 || mm == 11)
            if(dd <= 30){
                return 1;
            }
            else{
                return 0;
            }
        return 1;
    }
    return 0;
}

/**
 * Converte elemento do tipo data para string
 * @param d
 * @return
 */
char *date_to_str(date d){
    char *date = malloc(10*sizeof(char));
    sprintf(date, "%d-%d-%d", d.day, d.month, d.year);
    return date;
}

/**
 * Converte string no formato dd-mm-yyyy para elemento do tipo data
 * @param str
 * @return
 */
date str_to_date(char str[]){
    date d;
    char *date_ptr = strtok(str, "-");
    d.day = atoi(date_ptr);
    date_ptr = strtok(NULL, "-");
    d.month = atoi(date_ptr);
    date_ptr = strtok(NULL, "-");
    d.year = atoi(date_ptr);
    return d;
}

/**
 * Verifica se existe algum estudante com new_number
 * @param new_number
 * @param students
 * @return
 */
int student_number_exists(int new_number, student **students){
    for(student * st = (*students); st->next != NULL ; st = st->next){
        if(new_number == st->number) return 1;
    }
    return 0;
}

/**
 * Imprime no ecrã elemento do tipo estudante
 * @param s
 */
void print_student_profile(student *s){
    printf("\e[1;1H\e[2J");
    printf("*************************** ");
    printf("\n***   PERFIL DO ALUNO   ***");
    printf("\n***     %d", s->number);
    printf("\n***************************\n");
    printf("%s\t\t (%d, %s)\n", s->name, s->class_year, s->class_letter);
    char *date = date_to_str(s->birthday);
    printf("DATA DE NASCIMENTO: %s\n", date);
    free(date);
}


/**
 * CLI para adicionar elemento do tipo estudante
 * @param students
 * @return
 */
int cli_add_student(student **students){
    printf("\e[1;1H\e[2J");
    printf("*************************** ");
    printf("\n***  ADICIONAR ALUNO   ***");
    printf("\n***************************\n");

    int number = -999;
    char input[MAX_SIZE_INPUT];
    while(number==-999){
        printf("NÚMERO # ");
        scanf("%s", input);
        if(strcmp(input, "c!")==0) return -1;
        number = is_valid_int(input);
        if(number==-999) printf("NÃO FOI INTRODUZIDO UM NÚMERO VÁLIDO\n");
        if(student_number_exists(number, students)==1){
            printf("JÁ EXISTE UM ESTUDANTE COM ESSE NÚMERO\n");
            number = -999;
        }
    }

    char name[MAX_SIZE_INPUT];
    char birthday[MAX_SIZE_INPUT];
    char class_year[MAX_SIZE_INPUT];
    char class_letter[MAX_SIZE_INPUT];

    printf("NOME DO ALUNO: ");
    scanf(" %[^\n]s",&name);
    if(strcmp(name, "c!")==0) return -1;
    for (int i = 0; name[i]!='\0'; i++) {
        if(name[i] >= 'a' && name[i] <= 'z') {
            name[i] = name[i] -32;
        }
    }

    int valid_date = -1;
    while(valid_date<=0){
        printf("DATA DE NASCIMENTO: ");
        scanf("%s", birthday);
        if(strcmp(birthday, "c!")==0) return -1;
        valid_date = verify_date(birthday);
    }

    int classyear = -999;
    while(classyear==-999){
        printf("ANO: ");
        scanf("%s", class_year);
        if(strcmp(class_year, "c!")==0) return -1;
        classyear = is_valid_int(class_year);
    }

    printf("TURMA: ");
    scanf("%s", class_letter);
    if(strcmp(class_letter, "c!")==0) return -1;
    for (int i = 0; class_letter[i]!='\0'; i++) {
        if(class_letter[i] >= 'a' && class_letter[i] <= 'z') {
            class_letter[i] = class_letter[i] -32;
        }
    }

    student *s = calloc(1, sizeof(struct student));
    s->number = number;
    s->name = malloc(strlen(name)*sizeof(char));
    strcpy(s->name, name);
    s->birthday = str_to_date(birthday);
    s->class_year = classyear;
    s->class_letter = malloc(strlen(class_letter)*sizeof(char));
    strcpy(s->class_letter, class_letter);

    print_student_profile(s);

    int verify = -1;
    char verify_check[MAX_SIZE_INPUT];
    while(verify<0){
        printf("CONFIRMA? s/n \t#");
        scanf("%s", &verify_check);
        if(strcmp(verify_check, "s")==0) verify=1;
        if(strcmp(verify_check, "n")==0) verify=0;
    }
    if(verify==1){
        s->next = *students;
        *students = s;
        return 1;
    }else{
        free(s);
        return 0;
    }

}

/**
 * CLI para listar todos os elementos do tipo estudante
 * @param students
 */
void cli_list_students(student **students){
    printf("\e[1;1H\e[2J");
    printf("***************************\n");
    printf("LISTAR TODOS OS ALUNOS\n");
    printf("***************************\n");
    for(student * st = (*students); st->next != NULL ; st = st->next){
        printf("%d\t%s\t(%d, %s)\n", st->number, st->name, st->class_year, st->class_letter);
    }
}

int main(int argc, char *argv[]){
    bar *bar_set = NULL;
    student *students = malloc(sizeof(student));
    students = NULL;
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
                if(cli_add_student(&students)==1){
                    printf("---->  ALUNO ADICIONADO.\n");
                }else{
                    printf("---> ALUNO NÃO ADICIONADO.\n");
                }
                break;
            case 2:
                break;
            case 3:
                cli_list_students(&students);
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
