/*-------------------------------------------------------------------------
 *
 * nodeHash.h
 *	  prototypes for nodeHash.c
 *
 *
 * Portions Copyright (c) 1996-2003, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $Id: nodeHash.h,v 1.32 2003/08/04 02:40:13 momjian Exp $
 *
 *-------------------------------------------------------------------------
 */
#ifndef NODEHASH_H
#define NODEHASH_H
#define NUMHASHFUNCTIONS 5

#include "nodes/execnodes.h"
#include <limits.h>

extern int	ExecCountSlotsHash(Hash *node);
extern HashState *ExecInitHash(Hash *node, EState *estate);
extern TupleTableSlot *ExecHash(HashState *node);
extern void ExecEndHash(HashState *node);
extern void ExecReScanHash(HashState *node, ExprContext *exprCtxt);

extern HashJoinTable ExecHashTableCreate(Hash *node, List *hashOperators);
extern void ExecHashTableDestroy(HashJoinTable hashtable);
extern void ExecHashTableInsert(HashJoinTable hashtable,
					ExprContext *econtext,
					List *hashkeys);
extern int ExecHashGetBucket(HashJoinTable hashtable,
				  ExprContext *econtext,
				  List *hashkeys);
extern int	ExecHashGetBatch(int bucketno, HashJoinTable hashtable);
extern HeapTuple ExecScanHashBucket(HashJoinState *hjstate, List *hjclauses,
				   ExprContext *econtext);
extern void ExecHashTableReset(HashJoinTable hashtable, long ntuples);
extern void ExecChooseHashTableSize(double ntuples, int tupwidth,
						int *virtualbuckets,
						int *physicalbuckets,
						int *numbatches);
/*Bloom Filter Hash Functions*/
extern int wang_hash(int a);
extern int three_shift_hash(int a);
extern int java_hashmap_hash(int h);
extern int half_avalanche_hash(int a);
extern int full_avalanche_hash( int a);

extern int normalizeHashValue(int hashValue);

extern int (*BloomHashFunctions[NUMHASHFUNCTIONS])(int a);

//Bit Array Functions
#define BIT8 0x01
#define BIT7 0x02
#define BIT6 0x04
#define BIT5 0x08
#define BIT4 0x10
#define BIT3 0x20
#define BIT2 0x40
#define BIT1 0x80

extern void insertIntoBitArray(char * eightBitArray, int bucketNumber);

#endif   /* NODEHASH_H */
