#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <stdint.h>
#include <stdio.h>

typedef enum{
	NODE_NAND,
	NODE_VAR
} node_t;

typedef enum{
	GATE_NOT,
	GATE_NAND,
	GATE_AND,
	GATE_NOR,
	GATE_OR,
	GATE_XNOR,
	GATE_XOR,
	NONE
} gate_t;

struct CircuitMatch{
    gate_t gate;
    char op1;
    char op2;
};

struct Node{
	node_t type;
	char var_name;
	struct Node *left;
	struct Node *right;	
};

struct Node* make_var(char name);
struct Node* make_nand(struct Node* l, struct Node* r);
void print_binary(uint64_t n);
uint64_t get_var_signature(char var_name);
uint64_t get_truth_signature(struct Node* n);
struct CircuitMatch* optimize_circuit(struct Node* root);

#endif
