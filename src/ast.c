#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static Node *nuevo(NodeKind k, int line, int col) {
    Node *n = calloc(1, sizeof(Node));
    if (!n) { fprintf(stderr, "sin memoria\n"); exit(1); }
    n->kind = k;
    n->line = line;
    n->col = col;
    n->tipo = TIPO_DESCONOCIDO;
    return n;
}

Node *ast_int(long v, int l, int c) {
    Node *n = nuevo(N_INT, l, c);
    n->ival = v;
    return n;
}

Node *ast_double(double v, int l, int c) {
    Node *n = nuevo(N_DOUBLE, l, c);
    n->dval = v;
    return n;
}

Node *ast_id(char *s, int l, int c) {
    Node *n = nuevo(N_ID, l, c);
    n->name = s;
    return n;
}

Node *ast_binop(char op, Node *a, Node *b, int l, int c) {
    Node *n = nuevo(N_BINOP, l, c);
    n->op = op;
    n->left = a;
    n->right = b;
    return n;
}

Node *ast_let(char *s, Node *e, int l, int c) {
    Node *n = nuevo(N_LET, l, c);
    n->name = s;
    n->left 

cat > src/ast.c << 'EOF'
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static Node *nuevo(NodeKind k, int line, int col) {
    Node *n = calloc(1, sizeof(Node));
    if (!n) { fprintf(stderr, "sin memoria\n"); exit(1); }
    n->kind = k;
    n->line = line;
    n->col = col;
    n->tipo = TIPO_DESCONOCIDO;
    return n;
}

Node *ast_int(long v, int l, int c) {
    Node *n = nuevo(N_INT, l, c);
    n->ival = v;
    return n;
}

Node *ast_double(double v, int l, int c) {
    Node *n = nuevo(N_DOUBLE, l, c);
    n->dval = v;
    return n;
}

Node *ast_id(char *s, int l, int c) {
    Node *n = nuevo(N_ID, l, c);
    n->name = s;
    return n;
}

Node *ast_binop(char op, Node *a, Node *b, int l, int c) {
    Node *n = nuevo(N_BINOP, l, c);
    n->op = op;
    n->left = a;
    n->right = b;
    return n;
}

Node *ast_let(char *s, Node *e, int l, int c) {
    Node *n = nuevo(N_LET, l, c);
    n->name = s;
    n->left = e;
    return n;
}

Node *ast_print(Node *e, int l, int c) {
    Node *n = nuevo(N_PRINT, l, c);
    n->left = e;
    return n;
}

Node *ast_append(Node *list, Node *stmt) {
    if (!list) return stmt;
    Node *p = list;
    while (p->next) p = p->next;
    p->next = stmt;
    return list;
}

const char *tipo_str(Tipo t) {
    return t == TIPO_INT ? "i32" :
           t == TIPO_DOUBLE ? "double" :
           t == TIPO_ERROR ? "error" : "?";
}

static void dump_nodo(Node *n, int d) {
    printf("%*s", d * 2, "");
    switch (n->kind) {
        case N_INT:    printf("INT %ld\n", n->ival); break;
        case N_DOUBLE: printf("DOUBLE %g\n", n->dval); break;
        case N_ID:     printf("ID %s [%s]\n", n->name, tipo_str(n->tipo)); break;
        case N_BINOP:  printf("BINOP '%c' [%s]\n", n->op, tipo_str(n->tipo));
                       dump_nodo(n->left, d + 1);
                       dump_nodo(n->right, d + 1);
                       break;
        case N_LET:    printf("LET %s\n", n->name);
                       dump_nodo(n->left, d + 1);
                       break;
        case N_PRINT:  printf("PRINT\n");
                       dump_nodo(n->left, d + 1);
                       break;
    }
}

void ast_dump(Node *prog) {
    for (Node *s = prog; s; s = s->next)
        dump_nodo(s, 0);
}
