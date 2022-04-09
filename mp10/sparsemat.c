/* partners: bmn4, sgohil3
 * Sparse Matrix - MP10 UIUC ECE220 SP22 bmn4, sgohil3
 * 
 * Wrote two helper functions:
 * sp_tuples_node * generateNode(int row, int col, double value, sp_tuples_node* nextNode);
 * // returns a node with those details filled out
 * 
 * void deleteNextNode(sp_tuples_node* node);
 * // Takes a node in a linked lists and deletes the next node from the list
 */

#define buffLen 100

#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

// Input: int row, int col, double val, sp_tuples_node* nextNode, deatils for new node
// Output: Noting
// Returns: pointer to node with parameters from input
// This is basically a constructor
sp_tuples_node* generateNode(int row, int col, double val, sp_tuples_node* nextNode) {
    // Makes a new node in memory
    sp_tuples_node* newNode = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));

    // Sets it's properties, basically a constructor
    newNode->row = row;
    newNode->col = col;
    newNode->value = val;
    newNode->next = nextNode;

    // Return it
    return newNode;
}

// Input: Pointer to a node who's next node should be deleted
// Output: just deletes the next node
// Return: nothing
void deleteNextNode(sp_tuples_node* node) {
    // Saves the deleted node's next link
    sp_tuples_node* newNext = node->next->next;

    // Delete the node
    free(node->next);

    // Change the next link (now pointing to freed memory) to the deleted node's next link
    node->next = newNext;
}

sp_tuples * load_tuples(char* input_file)
{
    char buff[buffLen];

    // Open file and check for sucessful open
    FILE* fp = fopen(input_file, "r");

    if(fp == NULL) {
        printf("Illegal input file name: \"%s\"\n", input_file);
        return NULL;
    }

    // Allocates space for new list header
    sp_tuples* header = (sp_tuples*) malloc(sizeof(sp_tuples));

    // Reads first line
    if(fgets(buff, buffLen, fp) == NULL){
        printf("Could not read first line \n");

        fclose(fp);
        return NULL;
    }

    // Parse first line for matrix dimensions
    if(sscanf(buff, "%d %d", &(header->m), &(header->n)) != 2) {
        printf("Could not get dimensions from the first row: \"%s\"", buff);

        fclose(fp);
        return NULL;
    }

    // Set header->nz to show empty list
    header->nz = 0;

    // Set first item to NULL
    header->tuples_head = NULL;

    // Loop through each line of the file and parse as an item in matrix
    while( !(feof(fp)) ) {
        int row, col;
        double val;

        fgets(buff, buffLen, fp); // Should be safe since EOF has not been hit

        // Scans in the row, col, and value in the line
        if((sscanf(buff, "%d %d %lf", &row, &col, &val) != 3) && (buff[0] != '\n')) { // Not sure if %f works for double
            printf("Could not parse line: \"%s\"", buff);

            fclose(fp);
            return NULL;
        }

        set_tuples(header, row, col, val);
    }
    
    fclose(fp);
    return header;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    // Find spot for new node (prevNode will be node right before where new node should go)
    sp_tuples_node *prevNode = mat_t->tuples_head;

    // Edge case where mat_t is empty linked list
    if(prevNode == NULL) {
        // If new val is 0, don't add anything (spare matrix doesn't store 0)
        if(value == 0) {
            return;
        } else {
            // If new val is non-0, make a new node and set it as head of linked list
            sp_tuples_node *newNode = generateNode(row, col, value, NULL);

            mat_t->tuples_head = newNode;
            mat_t->nz++;
        }
    } else {
        // Edge case where node should overwrite first item
        if((prevNode->row == row) && (prevNode->col == col)) {
            if(value == 0) {
                // Move head pointer to second item (could be NULL)
                mat_t->tuples_head = prevNode->next;

                // Delete node
                free(prevNode);
                mat_t->nz--;
                return;
            } else {
                // Overwrite value if non-zero
                prevNode->value = value;
                return;
            }
        }

        // Edge case where node should be inserted as first item
        if( (prevNode->row > row) || (prevNode->row == row && (prevNode->col > col)) ) {
            if(value == 0) {
                // If value is 0, don't add it to linked list since it doesn't store 0 values
                return;
            } else {
                // Generate new node and insert in front of linked list
                mat_t->tuples_head = generateNode(row, col, value, prevNode);
                mat_t->nz++;
                return;
            }
        }

        // Keep on incrementing node in linked list until next item is null
        // or is past/equal to our desired location (next->row is > to target row or next is same as target row but col is greater than target col )
        while(!( (prevNode->next == NULL) || ((prevNode->next->row > row) || ((prevNode->next->row >= row) && (prevNode->next->col >= col))) ))  {
            prevNode = prevNode->next;
        }

        // If prevNode->next is not NULL and matches our location, overwrite it
        if( (prevNode->next != NULL) && (prevNode->next->row == row) && (prevNode->next->col == col) ) {
            if(value == 0) {
                deleteNextNode(prevNode);
                mat_t->nz--;
            } else {
                prevNode->next->value = value;
            }
        } else {
            // There is no node with our dimensions yet, we have to insert
            if(value == 0) {
                // If value is 0, don't add it to linked list since it doesn't store 0 values
                return;
            } else {
                // Save next node pointer
                sp_tuples_node *nextNode = prevNode->next;

                // Generate new node and instert it
                prevNode->next = generateNode(row, col, value, nextNode);

                // Increment non-zero counter
                mat_t->nz++;
                return;
            }
        }
    }


    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    // Open file for writing + check for sucessful file open
    FILE* wfp = fopen(file_name, "w");
    if(wfp == NULL) {
        printf("Couldn't open file %s to write to.\n", file_name);
    }

    // Write first line (matrix dimensions)
    fprintf(wfp, "%d %d\n", mat_t->m, mat_t->n);

    // Loop through linked list and write each file
    sp_tuples_node * currentNode = mat_t->tuples_head;

    while(currentNode != NULL) {
        fprintf(wfp, "%d %d %f\n", currentNode->row, currentNode->col, currentNode->value);
        currentNode = currentNode->next;
    }

    fclose(wfp);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

    return NULL;
	// return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    
    return NULL;
    // return retmat;
}


	
void destroy_tuples(sp_tuples * mat_t){

    // Free the linked list by stepping through and freeing nodes
	sp_tuples_node *currentNode = mat_t->tuples_head;
    sp_tuples_node *nextNode;

    while(currentNode->next != NULL) {
        nextNode = currentNode->next;

        free(currentNode);

        currentNode = nextNode;
    }

    free(currentNode);

    free(mat_t);

    return;
}  





