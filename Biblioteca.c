#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[40];
    char autor[30];
    char categoria[20];
    int paginas;
    int codigo;
    float preco;
}livro;

typedef struct{
    char usuario[20];
    int senha;
}login;

typedef struct{
    char email[80];
    char usuario[15];
    int senha;
}conta;

void menuinicial(){
    printf("\nBem vindo a nossa biblioteca!\n");
    printf("=============================\n");
    printf("Porfavor, escolha uma opção: \n");
    printf("1 - Fazer login\n");
    printf("2 - Criar conta\n");
    printf("0 - Sair\n");
}
void menu(){
    printf("\nMenu Principal:\n");
    printf("1 - Cadastar um novo livro\n");
    printf("2 - Consultar acervo\n");
    printf("3 - Editar livro\n");
    printf("4 - Excluir um livro do acervo\n");
    printf("5 - Ordenar por codigo\n");
    printf("6 - Buscar livro\n");
    printf("7 - Catalogos de interesse\n");
    printf("8 - Emprestimo de livros\n");
    printf("9 - Meus emprestimos\n");
    printf("0 - Sair\n");
    printf("================================\n");
}

void criarconta(){
    FILE* file2 = fopen("conta.b", "ab");
    conta a;
    printf("\nInforme um email valido:\n");
    scanf("%s", a.email);
    while (!verificaEmail(a.email)) {
        printf("\nInforme um email valido:\n");
        scanf("%s", a.email);
    }
    printf("Agora digite um nome de usuario valido: \n");
    scanf("%s", &a.usuario);
    printf("Para finalizar, crie uma senha com apenas numeros: \n");
    scanf("%d", &a.senha);
    fwrite(&a, sizeof(conta), 1, file2);
    printf("Conta criada com sucesso");
    fclose(file2);
}
int verificaEmail(char *email){
    FILE* file2 = fopen("conta.b", "ab");
    conta a;
    char *arroba = strchr(email, '@');
    if (arroba == NULL) {
        return 0;
    }
    if (strlen(email) >= 80) {
        return 0;
    }
    file2 = fopen("conta.b", "rb");
    while (fread(&a, sizeof(conta), 1, file2)) {
        if (strcmp(a.email, email) == 0) {
            fclose(file2);
            printf("Este email ja esta cadastrado no sistema.\n");
            return 0;
        }
    }
    fclose(file2);
    return 1;
}

void logar(){
    FILE* file2 = fopen("conta.b", "rb");
    conta a; 
    char usuario1[15];
    int senha1;
    int logado = 0;
    while(logado != 1){
    printf("Nome de usuario: ");
    scanf("%s", usuario1);
    printf("Senha: ");
    scanf("%d", &senha1);
        while (fread(&a, sizeof(conta), 1, file2)) {
            if (strcmp(a.usuario, usuario1) == 0 && a.senha == senha1) {
                printf("Login efetuado com sucesso!\n");
                logado = 1;
            } 
        } 
        if(logado == 0){
            printf("Nome de usuario ou senha incorreto, tente novamente! \n");
        }  
    }   
}
void cadastrar() {
    int op;
    FILE* file = fopen("livro.b", "ab");
    livro a;
    printf("Informe o nome do livro separado por '_':\n");
    scanf("%s", a.nome);
    printf("Informe o autor do livro separado por '_':\n");
    scanf("%s", a.autor);
    printf("Informe o numero de paginas:\n");
    scanf("%d", &a.paginas);
    printf("Informe o codigo de 3 digitos do livro:\n");
    scanf("%d", &a.codigo);
    printf("Informe o preço:\n");
    scanf("%f", &a.preco);
    printf("Selecione a categoria do livro: \n");
    printf("1 - Ciencias Exatas\n");
    printf("2 - Ciencias Sociais\n");
    printf("3 - Literatura\n");
    printf("4 - Autoajuda\n");
    printf("5 - Outros\n");
    scanf("%d", &op);
        if (op == 1)
        {
            strcpy(a.categoria, "Ciencias Exatas");
        }else if (op == 2){
            strcpy(a.categoria, "Ciencias Sociais");
        }else if(op == 3){
            strcpy(a.categoria, "Literatura");
        }else if(op == 4){
            strcpy(a.categoria, "Autoajuda");
        }else if(op >= 5){  
            strcpy(a.categoria, "Outros");    
        } 
    fwrite(&a, sizeof(livro), 1, file);
    fclose(file);
}
void listar() {
    FILE* file = fopen("livro.b", "rb");
    livro a;
    if(tamanho() == 0){
    	printf("\nAinda nao ha nenhum livro cadastrado.\n");
    }else{
        while (fread(&a, sizeof(livro), 1, file)) {
            printf("\n%s - %s. %d pag\nCategoria: %s\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.categoria, a.codigo, a.preco);
        }
        fclose(file);
    }
}
int tamanho() {
    FILE* file = fopen("livro.b", "rb");
    livro a;
    int cont = 0;
    while (fread(&a, sizeof(livro), 1, file)) {
        cont++;
    }
    fclose(file);
    return cont;
}
int tamanho2() {
    FILE* file3 = fopen("emprestimo.b", "rb");
    livro a;
    int cont = 0;
    while (fread(&a, sizeof(livro), 1, file3)) {
        cont++;
    }
    fclose(file3);
    return cont;
}
void editar(int codigo){
    FILE *file = fopen("livro.b", "rb+");
    livro a;
    int op;
    int encontrado = 0;
    while (fread(&a, sizeof(livro), 1, file)) {
        if (a.codigo == codigo) {
            encontrado = 1;
            printf("Livro encontrado:\n");
            printf("Informe o que deseja editar: \n");
            printf("1 - Nome\n");
            printf("2 - Autor\n");
            printf("3 - Preco\n");
            scanf("%d", &op);
            if(op == 1)
            {
                printf("Informe o novo nome: ");
                scanf("%s", a.nome);
            }else if (op == 2){
                printf("Informe o autor: ");
                scanf("%s", a.autor);
            }else if (op == 3){
                printf("Informe o novo preco: ");
                scanf("%f", &a.preco);
            }
            
            fseek(file, -sizeof(livro), SEEK_CUR);
            fwrite(&a, sizeof(livro), 1, file);
            break;
        }
    }

    fclose(file);

    if (!encontrado) {
        printf("Livro nao encontrado.\n");
    } else {
        printf("Livro editado com sucesso!\n");
    }
}
void excluir(int codigo) {
    int n = tamanho();
    livro v[n];
    FILE *file = fopen("livro.b", "rb");
    int i = 0;
    while (fread(&v[i], sizeof(livro), 1, file)) {
        i++;
    }
    fclose(file);
    file = fopen("livro.b", "wb");
    for (i = 0; i < n; i++) {
        if (v[i].codigo != codigo) {
            fwrite(&v[i], sizeof(livro), 1, file);
        }
    }
    fclose(file);
}
void buscar (int cod) {
    FILE* file = fopen("livro.b", "rb");
    livro a;
    int entrou = 0;
    while (fread(&a, sizeof(livro), 1, file)) {
        if (a.codigo == cod) {
            printf("\n%s - %s. %d pag\nCategoria: %s\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.categoria, a.codigo, a.preco);
            entrou = 1;
        }
    }
    if (entrou == 0) {
        printf("Livro nao encontrado\n");
    }
    fclose(file);
}
void catalogos(){
    FILE* file = fopen("livro.b", "rb");
    livro a;
    int enc = 0;
    int op;
    printf("\nSelecione uma opcao:\n");
    printf("1 - Ciencias Exatas\n");
    printf("2 - Ciencias Sociais\n");
    printf("3 - Literatura\n");
    printf("4 - Autoajuda\n");
    printf("5 - Outros\n");
    scanf("%d", &op);
    if (op == 1){
        while (fread(&a, sizeof(livro), 1, file)) {
            if(strcmp(a.categoria, "Ciencias Exatas") == 0){
                printf("\n%s - %s. %d pag\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.codigo, a.preco);
                enc = 1;
            }
        }
    }else if (op == 2){
        while (fread(&a, sizeof(livro), 1, file)) {
            if(strcmp(a.categoria, "Ciencias Sociais") == 0){
                printf("%s - %s. %d pag\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.codigo, a.preco);
                enc = 1;
            }
        }
    }else if(op == 3){
        while (fread(&a, sizeof(livro), 1, file)) {
            if(strcmp(a.categoria, "Literatura") == 0){
                printf("%s - %s. %d pag\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.codigo, a.preco);
                enc = 1;
            }
        }
    }else if(op == 4){
        while (fread(&a, sizeof(livro), 1, file)) {
            if(strcmp(a.categoria, "Autoajuda") == 0){
                printf("%s - %s. %d pag\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.codigo, a.preco);
                enc = 1;
            }
        }
    }else if(op >= 5){
        while (fread(&a, sizeof(livro), 1, file)) { 
            if(strcmp(a.categoria, "Outros") == 0){
                printf("%s - %s. %d pag\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.codigo, a.preco);
                enc = 1;
            }
        }   
    }
    fclose(file);
    if (!enc) {
        printf("Catalogo vazio\n");
    }
}
void emprestimo(int cod){
    int n = tamanho();
    livro a[n];
    int enc = 0;
    int i = 0;
    FILE* file = fopen("livro.b", "rb");
    while (fread(&a[i], sizeof(livro), 1, file)){
    	i++;
	}
    fclose(file);
    FILE* file3 = fopen("emprestimo.b", "wb");
    for(i = 0; i < n; i++){ 
        if(a[i].codigo == cod){
            printf("\n%s - %s. %d pag\nCategoria: %s\nCodigo: %d \n%.2f R$\n", a[i].nome, a[i].autor, a[i].paginas, a[i].categoria, a[i].codigo, a[i].preco);
            enc = 1;
            fwrite(&a[i], sizeof(livro), 1, file3);
        }
    }
    fclose(file3);
    if (enc == 1)
    {
        printf("Operacao realizada com sucesso, visite a aba 'meus emprestimos' para ver seus emprestimos\n");
    }else{
        printf("Livro nao encontrado\n");
    }  
}
void meusEmprestimos(){
    FILE* file3 = fopen("emprestimo.b", "rb");
    livro a;
    if(tamanho2() == 0){
    	printf("\nNenhum emprestimo efetuado.\n");
    }else{
        while (fread(&a, sizeof(livro), 1, file3)) {
            printf("\n%s - %s. %d pag\nCategoria: %s\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.categoria, a.codigo, a.preco);
        }
    }
    fclose(file3);
}
void ordenar(){
	int n = tamanho();
    livro a[n];
    FILE *file = fopen("livro.b", "rb");

    for (int i = 0; i < n; i++) {
        fread(&a[i], sizeof(livro), 1, file);
    }
    fclose(file);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j].codigo > a[j + 1].codigo) {
                livro temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    file = fopen("livro.b", "wb");

    for (int i = 0; i < n; i++) {
        fwrite(&a[i], sizeof(livro), 1, file);
    }
    fclose(file);

    printf("Os livros foram ordenados por codigo\n");
}

int main(){
    int op;
    menuinicial();
    scanf("%d", &op);
    while (op != 0) {
        if (op == 1) {
            logar();
            break;
        } else if (op == 2) {
            criarconta();
            menuinicial();
            scanf("%d", &op);
        }
    }
    menu();
    scanf("%d", &op);           
    while (op != 0){
        if (op == 1) {
            cadastrar();
        } else if (op == 2) {
            listar();
        } else if (op == 3) {
            int codigo;
            printf("Informe o codigo do livro que deseja editar: ");
            scanf("%d", &codigo);
            editar(codigo);
        } else if (op == 4) {
            int codigo;
            printf("Informe o codigo do livro que deseja excluir: ");
            scanf("%d", &codigo);
            excluir(codigo);
        }else if(op == 5){
            ordenar();
        }else if (op == 6) {
            int codigo;
            printf("Informe o codigo do livro que deseja buscar: ");
            scanf("%d", &codigo);
            buscar(codigo);
        }else if (op == 7) {
            catalogos();
        }else if (op == 8) {
            int codigo;
            printf("Informe o codigo do livro que deseja pedir emprestimo: ");
            scanf("%d", &codigo);
            emprestimo(codigo);
        }else if (op == 9) {
            meusEmprestimos();
        }
        menu();
        scanf("%d", &op);
    }
    return 0;
}