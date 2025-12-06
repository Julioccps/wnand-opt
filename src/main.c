#include "circuit.h"
#include <stdio.h>

int main(){
	struct Node* A = make_var('A');
	struct Node* B = make_var('B');

	struct Node* mid = make_nand(A, B);
	
	struct Node* left_part = make_nand(A, mid);

	struct Node* right_part = make_nand(B, mid);

	struct Node* circuit_xor = make_nand(left_part, right_part);
	struct CircuitMatch* result = optimize_circuit(circuit_xor);

    if (result->gate == GATE_XOR) {
        printf("Test Passed: Circuit detected as XOR\n");
        return 0;
    } else {
        printf("Test Failed: Circuit detected as %d\n", result->gate);
        return 1;
    }
}