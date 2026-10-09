#ifndef AST_H
#define AST_H

typedef enum { TIPO_DESCONOCIDO, TIPO_ERROR, TIPO_INT, TIPO_DOUBLE } Tipo;
typedef enum { N_INT, N_DOUBLE, N_ID, N_BINOP, N_LET, N_PRINT } NodeKind;

typedef struct Node {
    NodeKind kind;
    int line, col;
    Tipo tipo;
    long ival;
    double dval;
    char *name;
    char op;
    struct Node *left;
    struct Node *right;
    struct Node *next;
} Node;

Node *ast_int(long v, int line, int col);
Node *ast_double(double v, int line, int col);
Node *ast_id(char *name, int line, int col);
Node *ast_binop(char op, Node *l, Node *r, int line, int col);
Node *ast_let(char *name, Node *expr, int line, int col);
Node *ast_print(Node *expr, int line, int col);
Node *ast_append(Node *list, Node *stmt);
void  ast_dump(Node *prog);
const char *tipo_str(Tipo t);

#endif
