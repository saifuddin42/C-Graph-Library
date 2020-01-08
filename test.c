#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

int main(int argc, char *argv[]) {

	Graph *graph = graph_initialize();
	
	if(graph == NULL) {
		printf("Error in initializing graph. Exiting...\n");
		return 0;
	}
	printf("Graph Initialized.\n");

	/* Set up the filename with the default sample */
  	char filename[100] = "sample1.txt";

  	/* One argument is allowed, a filename of the file to open */
  	if(argc == 2) {
  	  strncpy(filename, argv[1], 100);
  	}

	int opt = -1, x = -1, y = -1, w = -1;
	int flag = -1;
	char buffer[10];
	int *arr = NULL;

	do {

		printf(".-----------------------------------------.\n");
		printf("| Operations                              |\n");
		printf("+---------+-------------------------------+\n");
		printf("| 1 X     | Add Vertex X                  |\n");
		printf("| 2 X Y W | Add Edge X->Y with Weight W   |\n");
		printf("| 3 X Y   | Remove Edge X->Y              |\n");
		printf("| 4 X     | Remove Vertex (and Edges)     |\n");
		printf("| 5 X     | Contains Vertex (Does Exist?) |\n");
		printf("| 6       | Num of Vertices in Graph      |\n");
		printf("| 7       | Num of Edges in Graph         |\n");
		printf("| 8 X     | Degree of Vertex X            |\n");
		printf("| 9       | Total Weight of Graph         |\n");
		printf("|10 X     | Successors of X               |\n");
		printf("|11 X     | Predecessors of X             |\n");
		printf("|12 X Y   | Is X a neighbour of Y?        |\n");
		printf("|13 X Y   | Edge Weight of (X->Y)         |\n");
		printf("|14       | Output Adj List to dot file   |\n");
		printf("|15 X Y   | Is there a path from X to Y?  |\n");
		printf("|16       | Load Graph from file          |\n");
		printf("|17       | Print current Graph           |\n");
		printf("|18       | Save current Graph            |\n");
		printf("|19 X Y   | Contains Edge (Does Exist?)   |\n");
		printf("+---------+-------------------------------+\n");
		printf("|-1       | Quit                          |\n");
		printf(".-----------------------------------------.\n");
		printf("> ");

		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d" "%d" "%d" "%d", &opt, &x, &y, &w);

		switch(opt) {

			case -1:
				printf("Exiting... Thank you.\n");
			break;

			case 1:
				flag = graph_add_vertex(graph, x);
				if(flag == 0) {
					printf("\nVertex added.");
					graph_print(graph);
				}
				else {
					printf("\nError while adding Vertex.");
				}
				printf("\n\n");
			break;

			case 2:
				flag = graph_add_edge(graph, x, y ,w);
				if(flag == 0) {
					printf("\nEdge added.");
					graph_print(graph);
				}
				else {
					printf("\nError while adding Edge.");
				}
				printf("\n\n");
			break;

			case 3:
				flag = graph_remove_edge(graph, x, y);
				if(flag == 0) {
					printf("\nEdge removed.");
					graph_print(graph);
				}
				else {
					printf("\nError while removing Edge.");
				}
				printf("\n\n");
			break;

			case 4:
				flag = graph_remove_vertex(graph, x);
				if(flag == 0) {
					printf("\nVertex removed.");
					graph_print(graph);
				}
				else {
					printf("\nError while removing Vertex.");
				}
				printf("\n\n");
			break;

			case 5:
				flag = graph_contains_vertex(graph, x);
				if(flag) {
					printf("\nVertex exists.");
					graph_print(graph);
				}
				else {
					printf("\nVertex does not exist.");
				}
				printf("\n\n");
			break;

			case 6:
				flag = graph_num_vertices(graph);
				if(flag == -1) {
					printf("\nError while counting Vertices.");
				}
				else {
					printf("\nNum of Vertices = %d.", flag);
					graph_print(graph);
				}
				printf("\n\n");
			break;

			case 7:
				flag = graph_num_edges(graph);
				if(flag == -1) {
					printf("\nError while counting Edges.");
				}
				else {
					printf("\nNum of Edges = %d.", flag);
					graph_print(graph);
				}
				printf("\n\n");
			break;

			case 8:
				flag = graph_get_degree(graph, x);
				if(flag == -1) {
					printf("\nError while calculating total degree.");
				}
				else {
					printf("\nTotal degree = %d.", flag);
					graph_print(graph);
				}
				printf("\n\n");
			break;

			case 9:
				flag = graph_total_weight(graph);
				if(flag == -1) {
					printf("\nError while calculating total weight.");
				}
				else {
					printf("\nTotal weight = %d.", flag);
					graph_print(graph);
				}
				printf("\n\n");
			break;

			case 10:
				arr = graph_get_successors(graph, x);
				if(arr != NULL) {
					printf("\nSuccessors are: ");

					int i = 0;
					while(arr[i] != -1) {
						printf("%d ", arr[i]);
						i++;
					}

					printf("%d ", arr[i]);

					graph_print(graph);
					free(arr);
				}
				else {
					printf("\nError while getting Successors.");
				}
				printf("\n\n");
			break;

			case 11:
				arr = graph_get_predecessors(graph, x);
				if(arr != NULL) {
					printf("\nPredeccessors are: ");

					int i = 0;
					while(arr[i] != -1) {
						printf("%d ", arr[i]);
						i++;
					}

					printf("%d ", arr[i]);

					graph_print(graph);
					free(arr);
				}
				else {
					printf("\nError while getting Predecessors.");
				}
				printf("\n\n");
			break;

			case 12:
				if(graph_is_neighbor(graph, x, y)) {
					printf("\nYes. %d is a neighbour of %d", x, y);
					graph_print(graph);
				}
				else {
					printf("\nNo. %d is not a neighbour of %d", x, y);
					graph_print(graph);
				}
				printf("\n\n");
			break;

			case 13:
				flag = graph_get_edge_weight(graph, x, y);
				if(flag == -1) {
					printf("\nError while calculating edge weight.");
				}
				else {
					printf("\nEdge weight = %d.", flag);
					graph_print(graph);
				}
				printf("\n\n");
			break;

			case 14:
				graph_output_dot(graph, "dotGraph.txt");
				printf("\nDot Graph saved.\n\n");
			break;

			case 15:
				if(graph_has_path(graph, x, y)) {
					printf("\nYes. Graph has a path from %d -> %d", x, y);
					graph_print(graph);
				}
				else {
					printf("\nNo. Graph doesn't have a path from %d -> %d", x, y);
					graph_print(graph);
				}
				printf("\n\n");
			break;

			case 16:
				printf("\nEnter filename to load: ");
				char buffer1[100];
				fgets(buffer1, sizeof(buffer1), stdin);
				sscanf(buffer1, "%s", filename);
				
				flag = graph_load_file(graph, filename);

				if(flag == 0) {
					printf("\nFile loaded.");
					graph_print(graph);
				}
				else {
					printf("\nFile not loaded.");
				}

				printf("\n\n");
			break;

			case 17:
				graph_print(graph);
				printf("\n\n");
			break;

			case 18:
				flag = graph_save_file(graph, "savedGraph.txt");

				if(flag == 0) {
					printf("\nFile saved.");
				}
				else {
					printf("\nFile not saved.");
				}

				printf("\n\n");
			break;

			case 19:
				flag = graph_contains_edge(graph, x, y);
				if(flag) {
					printf("\nEdge exists.");
				}
				else {
					printf("\nEdge does not exist.");
				}
				printf("\n\n");
			break;

			default:
				printf("\nInvalid Input. Please try again.\n");
			break;

		}

	} while (opt != -1);

	free(graph);
	return 0;
}