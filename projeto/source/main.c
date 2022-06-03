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
 * Verifica se string é um número
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
 * Aguarda leitura do utilizador
 */
void enter_to_continue(){
    printf("<ENTER> PARA CONTINUAR ");
    char wait[MAX_SIZE_INPUT];
    fflush(stdin);
    while(fgets(wait,MAX_SIZE_INPUT,stdin) != NULL){
        fflush(stdin);
        return;
    }
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
        if (mm == 4 || mm == 6 || mm == 9 || mm == 11){
            if(dd <= 30){
                return 1;
            }else{
                return 0;
            }
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
 * Pede numero de estudante ao utilizador
 * @param students
 * @return
 */
int cli_asks_for_student_number(student **students){
    int number = -999;
    char input[MAX_SIZE_INPUT];
    while(number==-999){
        printf("NÚMERO # ");
        scanf("%s", input);
        if(strcmp(input, "c!")==0) return -999;
        number = is_valid_int(input);
        if(number==-999) {
            printf("NÃO FOI INTRODUZIDO UM NÚMERO VÁLIDO. ");
            enter_to_continue();
            number = -999;
        }else{
            if(student_number_exists(number, students)==0){
                printf("NÚMERO DE ESTUDANTE INEXISTENTE. ");
                enter_to_continue();
                number = -999;
            }
        }
    }
    return number;
}



student *get_student_profile(student **students, int number){
    for(student * st = (*students); st->next != NULL ; st = st->next){
        if(number == st->number) return st;
    }
    return NULL;
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

    int number = cli_asks_for_student_number(students);
    if(number <= -999){
        return -1;
    }

    char name[MAX_SIZE_INPUT];
    char birthday[MAX_SIZE_INPUT];
    char class_year[MAX_SIZE_INPUT];
    char class_letter[MAX_SIZE_INPUT];

    printf("NOME DO ALUNO: ");
    scanf(" %[^\n]s",name);
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
        scanf("%s", verify_check);
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
        printf("%d\t(%d, %s) %s\t\t[%.2f€]\n", st->number, st->class_year, st->class_letter, st->name, st->balance);
    }
}


void cli_show_user_bills(student *s, bill **bills){
    printf("***************************\n");
    printf("TRANSAÇÕES DO ALUNO \n");
    printf("***************************\n");

    bill_list *user_bills = malloc(sizeof(struct bill_list));
    user_bills = NULL;
    int bill_id = 1;
    for(bill *a_bill = (*bills); a_bill != NULL ; a_bill = a_bill->next){
        if(a_bill->student == s){
            bill_list *new_bill = malloc(sizeof(struct bill_list));
            new_bill->id = bill_id;
            new_bill->node = a_bill;
            new_bill->next = user_bills;
            user_bills = new_bill;
            bill_id++;
        }
    }

    if(!user_bills){
        printf("SEM TRANSAÇÕES PARA MOSTRAR. ");
        enter_to_continue();
    }else{
        bill_list *user_bills_list = user_bills;
        for(; user_bills_list != NULL ;){
            printf("%d\t", user_bills_list->id);
            if(user_bills_list->node->type==0) printf("COMPRA        ");
            if(user_bills_list->node->type==1) printf("CARREGAMENTO  ");
            printf("%s | %.2f€\n", date_to_str(user_bills_list->node->date), user_bills_list->node->total);
            user_bills_list = user_bills_list->next;
        }
        printf("***************************\n");
        char input[MAX_SIZE_INPUT];
        int menu = -1;
        printf("1 - MOSTRAR TRANSAÇÃO\n");
        printf("2 - VOLTAR AO MENU ANTERIOR\n");
        while(menu<0){
            printf("OPÇÃO \t# ");
            scanf("%s", input);
            menu = is_valid_int(input);
            switch (menu) {
                case 1:
                {
                    int id = -1;
                    char input_id[MAX_SIZE_INPUT];
                    while(id<0){
                        printf("ID \t# ");
                        scanf("%s", input_id);
                        if(strcmp(input_id, "c!")==0) return;
                        id = is_valid_int(input_id);
                        if(id>bill_id-1) id=-1;
                    }
                    user_bills_list = user_bills;
                    for(; user_bills_list != NULL ;){
                        if(user_bills_list->id == id){
                            show_bill(user_bills_list->node);
                            enter_to_continue();
                            break;
                        }
                    }
                    break;
                }
                case 2:
                    return;
                default:
                    printf("OPÇÃO INVÁLIDA. ");
                    enter_to_continue();
            }
        }
    }



}

void cli_student(student *s, bill **bills){

    char input[MAX_SIZE_INPUT];
    int menu = -1;
    while(menu<0){
        printf("***************************\n");
        printf("%s (%d)\nANO: %dº | TURMA: %s\nANIVERSÁRIO: %s\n", s->name, s->number, s->class_year, s->class_letter,
               date_to_str(s->birthday));
        printf("***************************\n");
        printf("1 - TRANSAÇÕES DO ALUNO\n");
        printf("2 - APAGAR ALUNO\n");
        printf("3 - VOLTAR AO MENU ANTERIOR\n");
        printf("OPÇÃO \t# ");
        scanf("%s", input);
        menu = is_valid_int(input);
        switch (menu) {
            case 1:
                cli_show_user_bills(s, bills);
                break;
            case 2:
                // TODO: APAGAR ALUNO
                break;
            case 3:
                return;
            default:
                printf("OPÇÃO INVÁLIDA. ");
                enter_to_continue();
        }
    }

}
/**
 * Verifica se string é um float
 * @param str
 * @return -999 se não for um número, ou o número introduzido
 */
float is_valid_float(char str[]){
    char *p;
    float d = strtof(str, &p);
    if (*p != 0) {
        return -999;
    }
    float x = atof(str);
    return x;
}

/**
 * CLI de carregamentos
 * @param bar_set
 * @param students
 * @param bills
 * @return
 */
int cli_top_up(bar **bar_set, student **students, bill **bills){
    printf("\e[1;1H\e[2J");
    printf("***************************\n");
    printf("CARREGAR CONTA ALUNO\n");
    printf("***************************\n");

    int number = cli_asks_for_student_number(students);
    if(number <= -999){
        return -1;
    }

    student *s = get_student_profile(students,number);
    printf("%s\nSALDO: %.2f€\n", s->name, s->balance);

    float amount = -1;
    char amount_input[MAX_SIZE_INPUT];
    while(amount<0){
        printf("\tMONTANTE A CARREGAR # ");
        scanf("%s", amount_input);
        if(strcmp(amount_input, "c!")==0) return -1;
        amount = is_valid_float(amount_input);
        if(amount==-999) {
            printf("NÃO FOI INTRODUZIDO UM MONTANTE VÁLIDO. ");
            enter_to_continue();
        }
    }

    int verify = -1;
    char verify_check[MAX_SIZE_INPUT];
    while(verify<0){
        printf("CONFIRMA CARREGAMENTO? s/n \t#");
        scanf("%s", verify_check);
        if(strcmp(verify_check, "s")==0) verify=1;
        if(strcmp(verify_check, "n")==0) verify=0;
    }
    if(verify==1){
        bill *new_top_up = malloc(sizeof(bill));
        if(!new_top_up){
            printf("---->  ERRO A REGISTAR TRANSAÇÃO, A MESMA SERÁ CANCELADA. (malloc error)\n");
            enter_to_continue();
            return -999;
        }
        new_top_up->type = 1;
        new_top_up->date = (*bar_set)->today;
        new_top_up->student = s;
        new_top_up->description = NULL;
        new_top_up->total = amount;
        new_top_up->next = (*bills);
        (*bills) = new_top_up;

        s->balance += amount;
        printf("***************************\n");
        printf("   CARREGAMENTO EFECTUADO\n");
        printf("%s (%d)\n", s->name, s->number);
        printf("***************************\n");
        printf("MONTANTE: %.2f€\n", amount);
        printf("SALDO DO ALUNO: %.2f€\n", s->balance);
        printf("***************************\n");
        return 1;
    }else{
        return 0;
    }
}

/**
 * Mostra talão
 * @param b
 */
void show_bill(bill *b){
    printf("\e[1;1H\e[2J");
    printf("*************************** ");
    printf("\n***       TALÃO      ***");
    printf("\n***************************\n");
    printf("%s\t\t (%d, %s)\n", b->student->name, b->student->class_year, b->student->class_letter);
    char *date = date_to_str(b->date);
    printf("%s\n", date);
    free(date);
    printf("***************************\n");
    if(b->type == 1){
        printf("CARREGAMENTO\n");
        printf("MONTANTE: %.2f€\n", b->total);
    }else{

    }
    return;
}

/**
 * Procura o produto
 * @param barcode
 * @param products
 * @return
 */
product *product_search(char *barcode, product **products){
    for(product * p = (*products); p != NULL ; p = p->next){
        if(strcmp(barcode, p->barcode)==0) return p;
    }
    return NULL;
}

/**
 * Calcula o total do cesto, em preço
 * @param shopping_cart
 * @return
 */
float cart_total(bill_descriptive *shopping_cart){
    float total = 0;
    for(bill_descriptive * b = shopping_cart; b != NULL ; b = b->next){
        total += b->quantity*b->product->price;
    }
    return total;
}

/**
 * Calcula o total do cesto, em artigos
 * @param shopping_cart
 * @return
 */
int cart_total_articles(bill_descriptive *shopping_cart){
    int total = 0;
    for(bill_descriptive * b = shopping_cart; b != NULL ; b = b->next){
        total += b->quantity;
    }
    return total;
}



bill_descriptive *cli_asks_for_bill_descriptive(bill_descriptive **shopping_cart, product **products) {
    printf("***************************\n");
    printf("*** ADICIONAR AO CESTO ***\n*                          *");
    printf("\n* QUANTIDADExCODIGO_BARRAS *");
    printf("\n***************************\n");
    char input[MAX_SIZE_INPUT];
    char input1[MAX_SIZE_INPUT];
    bill_descriptive *new_entry = *shopping_cart;
    while (new_entry == *shopping_cart) {
        printf("#\t ");
        scanf("%s", input);
        if (strcmp(input, "c!") == 0) return NULL;
        strcpy(input1, input);
        char *part = strtok(input, "x");
        int parts = 0;
        while (part != NULL) {
            parts++;
            part = strtok(NULL, "x");
        }

        if (parts != 2) {
            printf("NÃO SEGUE FORMATAÇÃO. QUANTIDADExCODIGO_BARRAS - ");
            enter_to_continue();
        } else {
            part = strtok(input1, "x");
            int amount;
            if (is_valid_int(part) > 0) {
                amount = atoi(part);
                part = strtok(NULL, "x");
                char *barcode = malloc(sizeof(char) * strlen(part));
                strcpy(barcode, part);
                product *productsearch = product_search(barcode, products);
                if (productsearch != NULL) {
                    int added = 0;
                    for (bill_descriptive *entry = *shopping_cart; entry != NULL; entry = entry->next) {
                        if (entry->product == productsearch) {
                            entry->quantity += amount;
                            added = 1;
                            printf("> ATUALIZADO %d x %s.\n", entry->quantity, entry->product->name);
                            return *shopping_cart;
                        }
                    }
                    if (added==0) {
                        bill_descriptive *shopping_cart_new_entry = malloc(sizeof(struct bill_descriptive));
                        shopping_cart_new_entry->product = productsearch;
                        shopping_cart_new_entry->quantity = amount;
                        shopping_cart_new_entry->next = *shopping_cart;
                        shopping_cart = &shopping_cart_new_entry;
                        printf("> ADICIONADO %d x %s.\n", (*shopping_cart)->quantity, (*shopping_cart)->product->name);
                        return *shopping_cart;
                    }
                } else {
                    printf("CÓDIGO BARRAS NÃO EXISTE. ");
                    enter_to_continue();
                }
            } else {
                printf("QUANTIDADE NÃO É NÚMERO VÁLIDO. ");
                enter_to_continue();
            }
        }
    }
}


/**
 * Mostra cesto, devolve quantidade número de produtos diferentes
 * @param shopping_cart
 * @return
 */
int cli_print_cart(bill_descriptive *shopping_cart){
    int qtd = 0;
    printf("***************************\nCESTO\n***************************\n");
    for(bill_descriptive * b = shopping_cart; b != NULL ; b = b->next){
        printf("%d\t %s\t %.2f€\n", b->quantity, b->product->name, (b->quantity*b->product->price));
        qtd++;
    }
    printf("\t > TOTAL: %.2f€ [%d produtos]\n***************************\n", cart_total(shopping_cart),
           cart_total_articles(shopping_cart));
    return qtd;
}

/**
 * CLI venda
 * @param bar_set
 * @param students
 * @param bills
 * @param products
 * @return
 */
int cli_bill(bar **bar_set, student **students, bill **bills, product **products){
    bill_descriptive *shopping_cart = malloc(sizeof(struct bill_descriptive));
    student *s = NULL;
    shopping_cart = NULL;
    int finished = -1;
    while(finished<0){
        char input[MAX_SIZE_INPUT];
        int menu = -1;
        printf("\e[1;1H\e[2J");
        printf("***************************");
        printf("\n***        VENDA       ***");
        printf("\n***************************\n");
        if(!s){
            int number = cli_asks_for_student_number(students);
            if(number <= -999){
                return -1;
            }
            s = get_student_profile(students, number);
        }
        printf("%s (%d)\n", s->name, s->number);
        if(!shopping_cart){
            printf("CESTO VAZIO.\n");
        }else{
            printf("%d produtos, total: %.2f€\n", cart_total_articles(shopping_cart), cart_total(shopping_cart));
        }
        printf("***************************\n");
        printf("1 - VER PRODUTOS\n");
        if(shopping_cart) printf("2 - VER CESTO\n");
        printf("3 - ADICIONAR AO CESTO\n");
        printf("4 - REMOVER DO CESTO\n");
        printf("5 - FINALIZAR VENDA\n");
        printf("6 - VOLTAR AO MENU ANTERIOR\n");

        printf("OPÇÃO \t# ");
        scanf("%s", input);
        menu = is_valid_int(input);
        switch (menu) {
            case 1:
                printf("***************************\nLISTA DE PRODUTOS\n***************************\n");
                for(product * p = *products; p != NULL ; p = p->next){
                    printf("%s\t %s\t %.2f€\n", p->barcode, p->name, p->price);

                }
                printf("***************************\n");
                enter_to_continue();
                break;
            case 2:
                if(!shopping_cart) {
                    printf("O CESTO ESTÁ VAZIO. ");
                    enter_to_continue();
                }else{
                    cli_print_cart(shopping_cart);
                    enter_to_continue();
                }
                break;
            case 3:
            {
                bill_descriptive *new_shopping_cart_entry = cli_asks_for_bill_descriptive(&shopping_cart, products);
                enter_to_continue();
                if(new_shopping_cart_entry == NULL){
                    break;
                }else{
                    shopping_cart = new_shopping_cart_entry;
                    break;
                }
            }
            case 4:
                if(!shopping_cart){
                    printf("CESTO VAZIO. ");
                    enter_to_continue();
                }else{
                    int n_lines = cli_print_cart(shopping_cart);
                    int line_to_delete = -1;
                    char input_id[MAX_SIZE_INPUT];
                    while(line_to_delete<0){
                        printf("LINHA A APAGAR \t#");
                        scanf("%s", input_id);
                        if(strcmp(input_id, "c!")==0) break;
                        line_to_delete = is_valid_int(input_id);
                        if(line_to_delete>n_lines) line_to_delete=-1;
                    }
                    int n = 1;
                    bill_descriptive * shopping_cart_prev = NULL;
                    bill_descriptive * b = shopping_cart;
                    for(; b != NULL ; b = b->next){
                        if(line_to_delete==1){
                            bill_descriptive *sc = shopping_cart->next;
                            free(shopping_cart);
                            shopping_cart = sc;
                            break;
                        }else{
                            shopping_cart_prev = shopping_cart;
                            shopping_cart = shopping_cart_prev->next;
                            if(line_to_delete==n){
                                shopping_cart_prev->next = shopping_cart->next;
                                free(shopping_cart);
                                shopping_cart = shopping_cart_prev->next;
                                break;
                            }
                        }
                        n++;
                    }
                }
                break;
            case 5:
                if(!shopping_cart){
                    printf("CESTO VAZIO. ");
                    enter_to_continue();
                }else{
                    cli_print_cart(shopping_cart);
                    int verify = -1;
                    char verify_check[MAX_SIZE_INPUT];
                    while(verify<0){
                        printf("COMFIRMAR VENDA? s/n \t#");
                        scanf("%s", verify_check);
                        if(strcmp(verify_check, "s")==0) verify=1;
                        if(strcmp(verify_check, "n")==0) verify=0;
                    }
                    if(verify==1){
                        bill * new_bill = malloc(sizeof(struct bill));
                        new_bill->type = 0;
                        new_bill->date = (*bar_set)->today;
                        new_bill->student = s;
                        new_bill->description = shopping_cart;
                        new_bill->total = cart_total(shopping_cart);
                        new_bill->next = (*bills);
                        (*bills) = new_bill;
                        return 1;
                    }else{
                        break;
                    }
                }
                break;
            case 6:
            {
                if(shopping_cart){
                    printf("CESTO COM PRODUTOS. ");
                    int verify = -1;
                    char verify_check[MAX_SIZE_INPUT];
                    while(verify<0){
                        printf("PRETENDE APAGAR? s/n \t#");
                        scanf("%s", verify_check);
                        if(strcmp(verify_check, "s")==0) verify=1;
                        if(strcmp(verify_check, "n")==0) verify=0;
                    }
                    if(verify==1){
                        for(bill_descriptive * b = shopping_cart; b != NULL ; b = b->next){
                            free(b);
                        }
                        return finished;
                    }else{
                        break;
                    }
                }else{
                    break;
                }
                finished = 1;
                return finished;
            }
            default:
                printf("OPÇÃO INVÁLIDA. ");
                enter_to_continue();
        }
    }
    return 1;
}





int main(int argc, char *argv[]) {
    bar *bar_set = NULL;
    student *students = malloc(sizeof(student));
    students = NULL;
    product *products = NULL;
    bill *bills = NULL;

    bar_init(&bar_set, &students, &products);

    int menu = 0;
    while (menu != 4) {
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
                if (cli_add_student(&students) == 1) {
                    printf("---->  ALUNO ADICIONADO. ");
                    enter_to_continue();
                } else {
                    printf("---> ALUNO *NÃO* ADICIONADO. ");
                    enter_to_continue();
                }
                break;
            case 2:
            {
                int number = cli_asks_for_student_number(&students);
                if(number <= -999){
                    break;
                }
                student *s = get_student_profile(&students, number);
                cli_student(s, &bills);
                break;
            }
            case 3:
                cli_list_students(&students);
                enter_to_continue();
                break;
            case 4:
                break;
            case 5:
                if (cli_top_up(&bar_set, &students, &bills) == 1) {
                    printf("---->  CONTA ALUNO CARREGADA. ");
                    enter_to_continue();
                } else {
                    printf("---> CONTA ALUNO *NÃO* CARREGADA. ");
                    enter_to_continue();
                }
                break;
            case 6:
                if (cli_bill(&bar_set, &students, &bills, &products) == 1) {
                    printf("---->  VENDA EFECTUADA. ");
                    enter_to_continue();
                } else {
                    printf("---> VENDA *NÃO* EFECTUADA. ");
                    enter_to_continue();
                }
                break;
            case 7:
                break;
            case 8:
                break;
            default:
                printf("OPÇÃO INVÁLIDA. ");
                enter_to_continue();
                break;
        }

    }
}

