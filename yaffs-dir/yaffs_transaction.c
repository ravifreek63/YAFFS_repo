#include "global.h"

extern struct transaction_list transactionList_Global;

void transaction_list_init()
{
 transactionList_Global.size = 0;
 transactionList_Global.list_head = NULL;
}

struct transaction_node *transaction_list_find(struct transaction_struct * tx_struct)
{
 struct transaction_node *req_tx_node = NULL;
 if (transactionList_Global.list_head == NULL || transactionList_Global.size == 0)
 {
	return req_tx_node;
 }
 else 
 {
  struct transaction_node * current_node = transactionList_Global.list_head;
  while (current_node != NULL)
  {
    if (current_node->transaction_struct_ptr == tx_struct)
    {
	return current_node;
    }
   else
    {
	current_node = current_node->next_node;
    }
  }
 }
 return req_tx_node; 
}

struct transaction_node *transaction_list_find_byID(int txn_id)
{
 struct transaction_node *req_tx_node = NULL;
 if (transactionList_Global.list_head == NULL || transactionList_Global.size == 0)
 {
	return req_tx_node;
 }
 else 
 {
  struct transaction_node * current_node = transactionList_Global.list_head;
  while (current_node != NULL)
  {
    if ((current_node->transaction_struct_ptr)->transaction_id == txn_id)
    {
	return current_node;
    }
   else
    {
	current_node = current_node->next_node;
    }
  }
 }
 return req_tx_node; 
}

struct transaction_node *transaction_list_end(void)
{
  struct transaction_node *current_node = transactionList_Global.list_head;
  while (current_node->next_node != NULL)
  {
   	current_node = current_node->next_node;   
  }
 return current_node;
}

bool is_transaction_list_empty (void)
{
 return (transactionList_Global.size == 0);
}
 
void transaction_list_add(struct transaction_struct * tx_struct)
{
struct transaction_node * last_node;
struct transaction_node txn_node;
if (is_transaction_list_empty())
	{

	transactionList_Global.list_head = &(txn_node);
	txn_node.transaction_struct_ptr = tx_struct;
	txn_node.next_node = NULL;
	transactionList_Global.size = 1;
	return; 
	}
/* 
Checking if the transaction already exists in the list 
*/
if (transaction_list_find(tx_struct) == NULL)
	{
	  last_node = transaction_list_end();
	  
	  last_node->next_node = &(txn_node);
	  txn_node.transaction_struct_ptr = tx_struct;
	  txn_node.next_node = NULL;
	  transactionList_Global.size++;
	  return;
	}
}

void transaction_list_del(struct transaction_struct *txn_struct)
{

 struct transaction_node * prev_txn_node;
 struct transaction_node * old_node;

 if (is_transaction_list_empty()) return;
 prev_txn_node = transactionList_Global.list_head;
 if (prev_txn_node->transaction_struct_ptr == txn_struct)
 {
	transactionList_Global.list_head = prev_txn_node->next_node;
        transactionList_Global.size--;
        return;
 }
 else
 {    
    while (prev_txn_node->next_node != NULL)
    {
      if ((prev_txn_node->next_node)->transaction_struct_ptr == txn_struct)
      {
 	old_node = prev_txn_node->next_node;
	prev_txn_node->next_node = (prev_txn_node->next_node)->next_node;
/*
	TODO free the old node that has been deleted from the list
	free (old_node);	
*/
	transactionList_Global.size--;
 	return;
      }
    }
 }
}






