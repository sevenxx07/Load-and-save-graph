#include <stdlib.h>
#include <stdio.h>
 
#include "graph.h"
 
#define CAPACITY 1000
 
/* This is a testing file just to be able to compile the 
 * examples of binary files to convert graph from txt->bin
 * and bin -> txt
 */
 
// - function -----------------------------------------------------------------
graph_t* allocate_graph(void) 
{
   graph_t *g = (graph_t*)malloc(sizeof(graph_t));
   if (g == NULL){
        exit(100);
   }
   g->size = 0;
   g->capacity = CAPACITY;
   g->edges = (edges_t**)malloc(g->capacity*sizeof(edges_t*));
    if (g->edges == NULL){
        free(g);
        exit(100);
    }
   /*
    for (int i = 0; i < CAPACITY; i++){
        g->edges[i] = NULL;
    }
    */
 
   return g;
}
 
// - function -----------------------------------------------------------------
void free_graph(graph_t **graph)
{
   for(int i = 0; i < (*graph)->size; i++){
        free((*graph)->edges[i]);
   }
   free((*graph)->edges);
   free(*graph);
}
 
// - function -----------------------------------------------------------------
void load_txt(const char *fname, graph_t *graph)
{
   FILE *f = fopen(fname, "r");
   int i = 0;
   int tmp = 0;
   while(tmp == 0){ //!feof(f)
      int from, to, cost;
      if (fscanf(f, "%d %d %d", &from, &to, &cost) != EOF){
         edges_t *e = malloc(3*sizeof(int));
         e->from = from;
         e->to = to;
         e->cost = cost;
         graph->size += 1;
         graph->edges[i++] = e;
         if (i >= graph->capacity){
            graph->capacity *= 2;
            graph->edges = (edges_t**)realloc(graph->edges,graph->capacity*(sizeof(edges_t*)));
         }
      }else{
         fclose(f);
         tmp = 1;
      }
   }
}
 
// - function -----------------------------------------------------------------
void load_bin(const char *fname, graph_t *graph)
{
   FILE *f = fopen(fname, "rb");
   int i = 0;
   int tmp = 0;
   while(tmp == 0){ //!feof(f)
      int from, to, cost;
      if (fread(&from, sizeof(int), 1, f)){
         if (fread(&to, sizeof(int), 1, f)){
            if (fread(&cost, sizeof(int), 1, f)){
               edges_t *e = malloc(3*sizeof(int));
               e->from = from;
               e->to = to;
               e->cost = cost;
               graph->size += 1;
               graph->edges[i++] = e;
            }else{
               fclose(f);
               tmp = 1;
            }
         }else{
            fclose(f);
            tmp = 1;
         }
      }else{
         fclose(f);
         tmp = 1;
      }
      if (i >= graph->capacity){
         graph->capacity *= 2;
         graph->edges = (edges_t**)realloc(graph->edges,graph->capacity*(sizeof(edges_t*)));
      }
 
   }
    
}
 
// - function -----------------------------------------------------------------
void save_txt(const graph_t * const graph, const char *fname)
{
   FILE *f = fopen(fname, "w");
   for (int i = 0; i < graph->size; i++){
      //fwrite(&graph->edges[i], sizeof(edges_t), 1 /*or 3*/, f);
      int from = graph->edges[i]->from;
      int to = graph->edges[i]->to;
      int cost = graph->edges[i]->cost;
 
      fprintf(f,"%d %d %d", from, to, cost);
      fprintf(f, "\n");
   }
   fclose(f);
}
 
// - function -----------------------------------------------------------------
void save_bin(const graph_t * const graph, const char *fname)
{
   FILE *f = fopen(fname, "wb");
   for (int i = 0; i < graph->size; i++){
      int from = graph->edges[i]->from;
      int to = graph->edges[i]->to;
      int cost = graph->edges[i]->cost;
      fwrite(&from, sizeof(int), 1, f);
      fwrite(&to, sizeof(int), 1, f);
      fwrite(&cost, sizeof(int), 1, f);
 
   }
   fclose(f);
}
