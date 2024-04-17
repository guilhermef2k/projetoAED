#ifndef H_BIBLIOTECA
#define H_BIBLIOTECA

typedef struct livro;
typedef struct login;
typedef struct conta;

void menuinicial();

void criarconta();

int verificaEmail(char *email);

void logar();

void cadastrar();

void listar();

int tamanho();

int tamanho2();

void editar(int codigo);

void excluir(int codigo);

void buscar (int cod);

void catalogos();

void emprestimo(int cod);

void meusEmprestimos();

void ordenar();
#endif
