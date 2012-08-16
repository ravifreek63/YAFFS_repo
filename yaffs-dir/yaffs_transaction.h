#ifndef __YAFFS_TRANSACTION_H__
#define __YAFFS_TRANSACTION_H__

#include "global.h"

// This defines the transaction's current state of action 
enum transaction_state
{
  TX_COMMIT, // A Committed Transaction
  TX_ABORT,  // Transaction that has aborted 
  TX_RUNNING // Transaction that is currently running
};

struct transaction_struct
{
  enum transaction_state tx_state; 
/*
 This is the structure that stores the transaction state
*/
  struct yaffs_obj * yaffs_object;
 /*
    This is the pointer to the object on which the transaction is currently acting. 
    We assume that each transaction spans over only a single object.
 */
  int transaction_id;
};

struct transaction_node
{
 struct transaction_struct * transaction_struct_ptr;
 struct transaction_node * next_node; 
};

struct transaction_list
{
  struct transaction_node* list_head;
  int size;
};

struct transaction_list transactionList_Global;
void transaction_list_init(void);
/*
Adding a transaction to the list
*/
void transaction_list_add(struct transaction_struct *);
/*
Removing a transaction from the list
*/
void transaction_list_del(struct transaction_struct *);
/*
Searching the transaction list by transaction structure pointer
*/
struct transaction_node *transaction_list_find(struct transaction_struct *);
/*
Searching the transaction list by transaction id
*/
struct transaction_node *transaction_list_find_byID(int);

#endif
