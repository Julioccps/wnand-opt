#include "circuit.h"
#include <stdlib.h>
#include <stdio.h>

struct Node* make_var(char name){
	struct Node* n = malloc(sizeof(struct Node));
	n->type = NODE_VAR;
	n->var_name = name;
	n->left = n->right = NULL;
	return n;
}

struct Node* make_nand(struct Node* l, struct Node* r){
	struct Node* n = malloc(sizeof(struct Node));
	n->type = NODE_NAND;
	n->left = l;
	n->right = r;
	return n;
}

void print_binary(uint64_t n){
	printf("(Binary) ");
	for (int i = 63; i >= 0; i--){
		printf("%d", (int)(n >> i) & 1);

		if (i % 4 == 0 && i !=0){
			printf(" ");
		}
	}
	printf("\n");
}

uint64_t get_var_signature(char var_name){
	switch(var_name){
		case 'A': return 0xAAAAAAAAAAAAAAAA;
		case 'B': return 0xCCCCCCCCCCCCCCCC;
		case 'C': return 0xF0F0F0F0F0F0F0F0;
		case 'D': return 0xFF00FF00FF00FF00;
		case 'E': return 0xFFFF0000FFFF0000;
		case 'F': return 0xFFFFFFFF00000000;
	}
	return 0;
}

uint64_t get_truth_signature(struct Node* n){
	if (n->type == NODE_VAR){
		return get_var_signature(n->var_name);
	}
	if (n->type == NODE_NAND){
		uint64_t sig_left = get_truth_signature(n->left);
		uint64_t sig_right = get_truth_signature(n->right);

		return (~(sig_left & sig_right));
	}
	return 0;	
}

struct CircuitMatch* optimize_circuit(struct Node* root){
	uint64_t signature = get_truth_signature(root);
	struct CircuitMatch*  cm = malloc(sizeof(struct CircuitMatch));
	cm->gate = NONE;
	printf("Circuit Signature: 0x%llX ", (unsigned long long)signature);
	print_binary(signature);
	char vars[] = {'A','B','C','D','E','F'};
	int num_vars = 6;
	
	for (int i = 0; i < num_vars; i++){
		uint64_t sig = get_var_signature(vars[i]);
		if (signature == ~sig){
			cm->gate = GATE_NOT;
			cm->op1 = vars[i];
			cm->op2 = 0;
		}
	}
	if (cm->gate != GATE_NOT){
		for (int i = 0; i < num_vars; i++){
			for (int j = i + 1; j < num_vars; j++){
				uint64_t s1 = get_var_signature(vars[i]);
				uint64_t s2 = get_var_signature(vars[j]);

				if (signature == ~(s1 & s2)) {
					cm->gate = GATE_NAND;
				};
				if (signature == (s1 & s2)) {
					cm->gate = GATE_AND;
				};
				if (signature == ~(s1 | s2)) {
					cm->gate = GATE_NOR;
				};
				if (signature == (s1 | s2)) {
					cm->gate = GATE_OR;
				};
				if (signature == ~(s1 ^ s2)) {
					cm->gate = GATE_XNOR;
				};
				if (signature == (s1 ^ s2)) {
					cm->gate = GATE_XOR;
				};
			}
			if (cm->gate != NONE){
				cm->op1 = vars[i];
				cm->op2 = vars[i];
				break;
			}
		}
	}
	return cm;
}
