#ifndef MEMORY_H
#define MEMORY_H

///////////////////
//  ANSNA Memory //
///////////////////
//The conce-based memory of ANSNA
//See voting mechanism to make it fast:
//https://github.com/patham9/ANSNA/wiki/Voting-Schema

//References//
//////////////
#include "Concept.h"
#include "PriorityQueue.h"

//Parameters//
//----------//
#define CONCEPTS_MAX 1024 //always adjust both
#define CONCEPT_LAYERS 10 //with 2^10=1024 
#define USE_HASHING true
#define PROPAGATE_GOAL_SPIKES true
//only propagate promising spikes:
#define PROPAGATION_TRUTH_EXPECTATION_THRESHOLD DECISION_THRESHOLD

//Data structure//
//--------------//
//Data structures
PriorityQueue concepts[CONCEPT_LAYERS];
FIFO belief_events;
FIFO goal_events;
typedef void (*Action)(void);
typedef void (*EventInspector)(Event *);
typedef struct
{
    SDR sdr;
    Action action;
}Operation;
Operation operations[OPERATIONS_MAX];
EventInspector event_inspector;

//Methods//
//-------//
//Init memory
void Memory_INIT();
//Find a concept
bool Memory_FindConceptBySDR(int layer, SDR *sdr, SDR_HASH_TYPE sdr_hash, int *returnIndex);
//Create a new concept
void Memory_Conceptualize(SDR *sdr);
//Return closest concept
bool Memory_getClosestConcept(int layer, SDR *sdr, SDR_HASH_TYPE sdr_hash, int *returnIndex);
//Add an already existing concept to memory that was taken out from the concept priority queue
void Memory_addConcept(int layer, Concept *concept, long currentTime);
//Add event to memory
bool Memory_addEvent(Event *event);
//Add operation to memory
void Memory_addOperation(Operation op);
//Propagate spikes
void Memory_SpikePropagation(long currentTime);
//Match event to concept
Event Memory_MatchEventToConcept(Concept *c, Event *e);

#endif
