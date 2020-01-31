#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

/* Notes:
* 1. Vertices are denoted by adj_matrix[i][i]
* 2. Edges (weights) are denoted by adj_matrix[i][j], where i != j
* 3. For all vertices and edges that do not exist, values are set to -1
* 4. If a vertex exists, value is set as 0
* 5. Weights from vertex v1 to v2 or v1 to v1 (self loop) are set as values > 0
* 6. All return values are according to Project3_GL(5).pdf
*/


//Helper function for DFS:
void depth_first_search(Graph *graph, int v1) {

	int i;

	//Set visited for v1 = 1
    graph->visited[v1] = 1;
	
	//For every valid path and a node that's not visited yet, call depth_first_search()
	for(i = 0; i <= graph->max_vertex; i++) {

       if((graph->adj_matrix[v1][i] > 0) && (graph->visited[i] == 0)) {
            depth_first_search(graph, i);
       }
	}
}

// Initialization Functions
Graph *graph_initialize() {

	int i, j;
	
	//Initialize from heap
	Graph *graph_ptr = malloc(sizeof(Graph));

	//Handler for malloc errors
	if(graph_ptr == NULL) {
    	return NULL;
  	}
  	//Set the default values for Graph struct and return it
  	else {

    	graph_ptr -> max_vertex = -1; //Default max_vertex
    	
    	//Default visited[]
    	for(i = 0; i < MAX_VERTICES; i++) { 
    		graph_ptr->visited[i] = 0;
    	}
    	
    	//Default adj_matrix[]
    	for(i = 0; i < MAX_VERTICES; i++) { 
    		for(j = 0; j < MAX_VERTICES; j++) {
    			graph_ptr->adj_matrix[i][j] = -1;
    		}
    	}

    	return graph_ptr;
  	}
}


// Vertex Operations
int graph_add_vertex(Graph *graph, int v1) {

	//Handler for malloc errors or invalid v1
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES) {
    	return -1;
  	}
  	//If v1 already exists return success
  	if(graph->adj_matrix[v1][v1] != -1) {
  		return 0;
  	}
  	else {
  		//Else adjust max_vertex to maximum index and initialize the vertex
  		if(v1 > graph->max_vertex) {
  			graph->max_vertex = v1;
  		}

  		graph->adj_matrix[v1][v1] = 0;

  		return 0;
  	}
}

int graph_contains_vertex(Graph *graph, int v1) {

	//Handler for malloc errors or invalid v1
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES) {
    	return 0;
  	}
  	//If vertex is found return success
  	if(graph->adj_matrix[v1][v1] >= 0) {
  		return 1;
  	}

  	return 0; //Final return for any other failures
}

int graph_remove_vertex(Graph *graph, int v1) {

	int i;

	//Handler for malloc errors or invalid v1
	if(!graph_contains_vertex(graph, v1)) {
    	return -1;
  	}

  	//if v1 doesn't exist, consider it a success
  	if(graph->adj_matrix[v1][v1] == -1) {
  		return 0;
  	}
  	else {
  		//Set all adj_matrix[v1][i] = -1
  		for(i = 0; i <= graph->max_vertex; i++) {
  			graph->adj_matrix[v1][i] = -1;
  		}
  		//Set all adj_matrix[i][v1] = -1
  		for(i = 0; i <= graph->max_vertex; i++) {
  			graph->adj_matrix[i][v1] = -1;
  		}
  		//Update max_vertex in case the recently deleted vertex was the max_vertex
  		int temp = graph->max_vertex;
  		graph->max_vertex = -1;

  		for(i = 0; i <= temp; i++) {
  			
  			if(graph->adj_matrix[i][i] != -1) {

  				if(i > graph->max_vertex) {
  					graph->max_vertex = i;
  				}
  			}
  		}
  		//Return success
  		return 0;
  	}
}


// Edge Operations
int graph_add_edge(Graph *graph, int v1, int v2, int wt) {

	//Handler for malloc errors or invalid v1 or v2
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES) {
    	return -1;
  	}

  	//Handler for when v1 or v2 does not exist
  	if(graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1) {
  		return -1;
  	}

  	//Handler for when wt <= 0 (Since wt is always > 0)
  	if(wt <= 0) {
  		return -1;
  	}

  	//set the corresponding edge with the weight and return success
  	graph->adj_matrix[v1][v2] = wt;
  	return 0;
}

int graph_contains_edge(Graph *graph, int v1, int v2) {

	//Handler for malloc errors or invalid v1 or v2
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES) {
    	return 0;
  	}

  	//Handler for when v1 or v2 does not exist
  	if(graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1) {
  		return 0;
  	}

  	//Return 1 on success else 0
  	if(graph->adj_matrix[v1][v2] > 0) {
  		return 1;
  	}
  	else {
  		return 0;
  	}
}

int graph_remove_edge(Graph *graph, int v1, int v2) {

	//Check if edge exists before removing
	if(graph_contains_edge(graph, v1, v2)) {
		
		//Reset edge and return success
  		graph->adj_matrix[v1][v2] = -1;
  		return 0;
	}

  	else {
  		return -1;
  	}
}


// Graph Metrics Operations
int graph_num_vertices(Graph *graph) {

	//Handler for malloc errors
	if(graph == NULL) {
    	return -1;
  	}
	
	//Traverse the matrix and count the valid vertices
	int count = 0;
	int i;

	for(i = 0; i <= graph->max_vertex; i++) {

		if(graph->adj_matrix[i][i] >= 0) {
			count++;
		}
	}
	//Return count on success
	return count;
}

int graph_num_edges(Graph *graph) {

	//Handler for malloc errors
	if(graph == NULL) {
    	return -1;
  	}
	
	//Traverse the matrix and count the valid edges
	int count = 0;
	int i, j;

	for(i = 0; i <= graph->max_vertex; i++) {

		for(j = 0; j <= graph->max_vertex; j++) {

			if(graph->adj_matrix[i][j] > 0) {
				count++;
			}
		}
	}
	//Return count on success
	return count;
}

int graph_total_weight(Graph *graph) {
	
	//Handler for malloc errors
	if(graph == NULL) {
    	return -1;
  	}
	
	//Traverse the matrix and calculate sum of the valid edges
	int sum = 0;
	int i, j;

	for(i = 0; i <= graph->max_vertex; i++) {

		for(j = 0; j <= graph->max_vertex; j++) {

			if(graph->adj_matrix[i][j] > 0) {
				sum = sum + graph->adj_matrix[i][j];
			}
		}
	}
	//Return sum on success
	return sum;
}


// Vertex Metrics Operations
int graph_get_degree(Graph *graph, int v1) {
	
	//Handler for malloc errors or invalid v1
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES) {
    	return -1;
  	}

  	//if v1 doesn't exist, consider it a success
  	if(graph->adj_matrix[v1][v1] == -1) {
  		return -1;
  	}

  	int count = 0;
  	int i;

  	//Count all out degrees (adj_matrix[v1][i])
  	for(i = 0; i <= graph->max_vertex; i++) {

  		if(graph->adj_matrix[v1][i] > 0) {
  			count++;
  		}
  	}
  	//Count all in degrees (adj_matrix[i][v1])
  	for(i = 0; i <= graph->max_vertex; i++) {

  		if(graph->adj_matrix[i][v1] > 0) {
  			count++;
  		}
  	}
  	//Return total count on success
  	return count;
}

int graph_get_edge_weight(Graph *graph, int v1, int v2) {
	
	//If graph contains edge, return its weight
	if(graph_contains_edge(graph, v1, v2)) {
		return graph->adj_matrix[v1][v2];
	}
	else {
		return -1;
	}
}

int graph_is_neighbor(Graph *graph, int v1, int v2) {
	
	//Check if there is a edge from v1 to v2 or v2 to v1. Returns 1 on success and 0 on failures.
	return (graph_contains_edge(graph, v1, v2) || graph_contains_edge(graph, v2, v1));
}

int *graph_get_predecessors(Graph *graph, int v1) {
	
	//For an invalid vertex, return error
	if(!graph_contains_vertex(graph, v1)) {
		return NULL;
	}
	else {

		//Count the number of predecessors of v1
		int count = 0;
		int i;

		for(i = 0; i <= graph->max_vertex; i++) {

			if(graph_contains_edge(graph, i, v1)) {
				count++; 
			}
		}

		//Malloc a dynamic array with that count +1 (for the extra -1 at the end)
		int *arr = malloc(sizeof(int) * (count+1));
		int j = 0;

		//Move all predecessors in the malloc'd array and return it
		for(i = 0; i <= graph->max_vertex; i++) {

			if(graph_contains_edge(graph, i, v1)) {
				arr[j] = i;
				j++; 
			}
		}

		arr[j] = -1;

		return arr;
	}
}

int *graph_get_successors(Graph *graph, int v1) {
	
	//For an invalid vertex, return error
	if(!graph_contains_vertex(graph, v1)) {
		return NULL;
	}
	else {

		//Count the number of successors of v1
		int count = 0;
		int i;

		for(i = 0; i <= graph->max_vertex; i++) {

			if(graph_contains_edge(graph, v1, i)) {
				count++; 
			}
		}

		//Malloc a dynamic array with that count +1 (for the extra -1 at the end)
		int *arr = malloc(sizeof(int) * (count+1));
		int j = 0;

		//Move all successors in the malloc'd array and return it
		for(i = 0; i <= graph->max_vertex; i++) {

			if(graph_contains_edge(graph, v1, i)) {
				arr[j] = i;
				j++; 
			}
		}

		arr[j] = -1;

		return arr;
	}
}

//Graph Path Operations
int graph_has_path(Graph *graph, int v1, int v2) {
	
	//For any invalid vertex, return Error
	if(!graph_contains_vertex(graph, v1) || !graph_contains_vertex(graph, v2)) {
		return 0;
	}

	else {

		int i;

		//Every time this function is called, reset the visited array to avoid discrepencies
		for(i = 0; i < MAX_VERTICES; i++) { 
    		graph->visited[i] = 0;
    	}

    	//Handler for a case when the function wants to check if a path exists from v1 to itself.
    	if(v1 == v2) {

    		//If there is a self loop (path exists), return success.
    		if(graph->adj_matrix[v1][v2] > 0) {
    			return 1;
    		}
    		//In case there is no self loop, check if an indirect path exists.
    		else {

    			//Get all successors of of the vertex v1 and check if a path from them comes back to v1
    			int *arr = graph_get_successors(graph, v1);

    			if(arr == NULL) {
					return 0;
				}
				else {

					int j = 0;
					//Call DFS on each of the successor and set all visitable vertices to 1.
					while(arr[j] != -1) {
						
						depth_first_search(graph, arr[j]);
						j++;
					}

					free(arr);

					//If a path to v2 (which in this case is = v1) is found, return Success.
					if(graph->visited[v2]) {
						return 1;
					}
					//Else return failure.
					return 0;
				}
    		}
    	}
    	//Else case 
    	else {

    		//Call depth_first_search and set the visitable nodes to 1.
			depth_first_search(graph, v1);

			//If a path is found, return Success.
			if(graph->visited[v2]) {
				return 1;
			}
			//Else return failure.
			return 0;
    	}
	}
}


// Input/Output Operations
void graph_print(Graph *graph) {
	
	//Handler for malloc errors
	if(graph == NULL) {
    	return;
  	}
  	//Handler for the case when the graph is just initialized
  	if(graph->max_vertex == -1) {
  		printf("\nNo elements in the Graph currently.");
  		return;
  	}

  	char dot[] = ".";
  	char dash[] = "----";
  	int i, j;

  	printf("\nGraph (Adj Matrix):\n");
  	//Printing the indexes
  	printf("     ");
  	for(i = 0; i <= graph->max_vertex; i++) {
    	printf("%3d ", i);
    }
    
    //Printing the dotted line
    printf("\n   ");
    for(i = -1; i <= graph->max_vertex; i++) {
    	printf("%s", dash);
    }
    printf("\n");
    
    //Printing the matrix
  	for(i = 0; i <= graph->max_vertex; i++) {

  		printf("%3d| ", i);

    	for(j = 0; j <= graph->max_vertex; j++) {
    		
    		if(graph -> adj_matrix[i][j] == -1) {
    			printf("%3s ", dot);
    		}
    		else {
    			printf("%3d ", graph->adj_matrix[i][j]);
    		}
    	}

    	printf(" |\n");
    }
    
    //Printing the dotted line again
    printf("   ");
    for(i = -1; i <= graph->max_vertex; i++) {
    	printf("%s", dash);
    }
    printf("\n");
}

void graph_output_dot(Graph *graph, char *filename) {
	
	//Handler for malloc or filename errors
	if(graph == NULL || filename == NULL) {
    	return;
  	}
	
	//Open filename for writing (overwrites everytime it's opened)
	FILE *fp = fopen(filename, "w");
	if(fp == NULL) {
		return;
	}

	//Read the matrix and write the data according to dot graph format
	fprintf(fp, "digraph {\n");

	int i, j;

	for(i = 0; i <= graph->max_vertex; i++) {
    	for(j = 0; j <= graph->max_vertex; j++) {

    		//If the vertex exists then check if it is a vertex or an edge
    		if(graph->adj_matrix[i][j] != -1) {

    			if(graph->adj_matrix[i][j] == 0) {
    				fprintf(fp, "%d;\n", i);
    			}
    			else {
    				fprintf(fp, "%d -> %d [label = %d];\n", i, j, graph->adj_matrix[i][j]);
    			}
    		}
    	}
    }

    fprintf(fp, "}\n");

    //Close file
	fclose(fp);
}

int graph_load_file(Graph *graph, char *filename) {

	//Handler for malloc or filename errors
	if(graph == NULL || filename == NULL) {
    	return -1;
  	}

  	int i, j;

  	//Reinitializing a new graph in case an old graph exists
  	graph -> max_vertex = -1;  	
    //Default visited[]
    for(i = 0; i < MAX_VERTICES; i++) { 
    	graph->visited[i] = 0;
    }    	
    //Default adj_matrix[]
    for(i = 0; i < MAX_VERTICES; i++) { 
    	for(j = 0; j < MAX_VERTICES; j++) {
    		graph->adj_matrix[i][j] = -1;
    	}
    }	
	//Open filename for reading
	FILE *fp = fopen(filename, "r");
	if(fp == NULL) {
		return -1;
	}

	//Initializing variables to use
	char buffer[FILE_ENTRY_MAX_LEN];
	char *p_tok = NULL;
	int x = -1, y = -1, w = -1;

	while(feof(fp) == 0) { // Run until EOF is reached

		fgets(buffer, sizeof(buffer), fp); // Get one line from file
		
		//Get first token (x) if exists and add vertex to the graph
		p_tok = strtok(buffer, ",");
		if(p_tok != NULL) {
			sscanf(p_tok, "%d", &x);
			graph_add_vertex(graph, x);
		}

		//Get second token (y) if exists and add vertex to the graph
		p_tok = strtok(NULL, ",");
		if(p_tok != NULL) {
			sscanf(p_tok, "%d", &y);
			graph_add_vertex(graph, y);
		}

		//Get weight (w) if exists and add edge to the graph
		p_tok = strtok(NULL, ",");
		if(p_tok != NULL) {
			sscanf(p_tok, "%d", &w);
			graph_add_edge(graph, x, y, w);
		}
	}
	//Close file and return success
	fclose(fp);
	return 0;
}

int graph_save_file(Graph *graph, char *filename) {

	//Handler for malloc or filename errors
	if(graph == NULL || filename == NULL) {
    	return -1;
  	}
	
	//Open filename for writing (overwrites everytime it's opened)
	FILE *fp = fopen(filename, "w");
	if(fp == NULL) {
		return -1;
	}

	int i, j;

	//Read the matrix and write the data according to csv format
	for(i = 0; i <= graph->max_vertex; i++) {
    	for(j = 0; j <= graph->max_vertex; j++) {

    		//If the vertex exists then check if it is a vertex or an edge
    		if(graph->adj_matrix[i][j] != -1) {

    			if(graph->adj_matrix[i][j] == 0) {
    				fprintf(fp, "%d\n", i);
    			}
    			else {
    				fprintf(fp, "%d,%d,%d\n", i, j, graph->adj_matrix[i][j]);
    			}
    		}
    	}
    }

    //Close file and return success
	fclose(fp);
	return 0;
}