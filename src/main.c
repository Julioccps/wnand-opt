#include "circuit.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For free

int main(int argc, char *argv[]){
	// XOR circuit construction: (A NAND (A NAND B)) NAND (B NAND (A NAND B))
	// To avoid shared nodes for simple recursive freeing, all intermediate nodes are unique instances.
	struct Node* a_node_for_nand_ab_left = make_var('A');
	struct Node* b_node_for_nand_ab_left = make_var('B');
	struct Node* nand_ab_left = make_nand(a_node_for_nand_ab_left, b_node_for_nand_ab_left);

	struct Node* a_node_for_nand_ab_right = make_var('A');
	struct Node* b_node_for_nand_ab_right = make_var('B');
	struct Node* nand_ab_right = make_nand(a_node_for_nand_ab_right, b_node_for_nand_ab_right);

	struct Node* a_node_for_left_part = make_var('A');
	struct Node* left_part = make_nand(a_node_for_left_part, nand_ab_left);

	struct Node* b_node_for_right_part = make_var('B');
	struct Node* right_part = make_nand(b_node_for_right_part, nand_ab_right);

	struct Node* circuit_xor = make_nand(left_part, right_part);
	struct Node* main_circuit_to_free = circuit_xor; 

	int return_code = 0; // Default success

	if (argc > 1) {
		if (strcmp(argv[1], "display") == 0) {
			printf("Displaying current XOR circuit:\n");
			display_circuit(main_circuit_to_free, 0);
		} else if (strcmp(argv[1], "save") == 0) {
			if (argc < 3) {
				fprintf(stderr, "Usage: %s save <filename>\n", argv[0]);
				return_code = 1;
			} else {
				if (save_circuit(argv[2], main_circuit_to_free) == 0) {
					printf("Circuit saved to %s\n", argv[2]);
				} else {
					fprintf(stderr, "Failed to save circuit to %s\n", argv[2]);
					return_code = 1;
				}
			}
		} else if (strcmp(argv[1], "load") == 0) {
			if (argc < 3) {
				fprintf(stderr, "Usage: %s load <filename>\n", argv[0]);
				return_code = 1;
			} else {
				struct Node* loaded_circuit = load_circuit(argv[2]);
				if (loaded_circuit != NULL) {
					printf("Circuit loaded from %s:\n", argv[2]);
					display_circuit(loaded_circuit, 0);

					struct CircuitMatch* result = optimize_circuit(loaded_circuit);
					printf("Optimization result for loaded circuit: Gate = %d\n", result->gate);
					free(result);
					free_circuit(loaded_circuit); // Free the loaded circuit as it's done being used
					main_circuit_to_free = NULL; // Indicate that the original circuit_xor should not be freed
				} else {
					fprintf(stderr, "Failed to load circuit from %s\n", argv[2]);
					return_code = 1;
				}
			}
		} else { // Unknown command
			fprintf(stderr, "Unknown command: %s\n", argv[1]);
			fprintf(stderr, "Usage: %s [display | save <filename> | load <filename>]\n", argv[0]);
			return_code = 1;
		}
	} else { // Default behavior if no specific command is given (original optimization)
		printf("Running default circuit optimization...\n");
		struct CircuitMatch* result = optimize_circuit(main_circuit_to_free);

		if (result->gate == GATE_XOR) {
			printf("Test Passed: Circuit detected as XOR\n");
			free(result);
		} else {
			printf("Test Failed: Circuit detected as %d\n", result->gate);
			free(result);
			return_code = 1;
		}
	}

	// Free the circuit that was initially created or if not overwritten by a loaded circuit
	if (main_circuit_to_free != NULL) {
		free_circuit(main_circuit_to_free);
	}
	return return_code;
}
