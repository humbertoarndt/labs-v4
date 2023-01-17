/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:35:39 by harndt            #+#    #+#             */
/*   Updated: 2023/01/15 11:58:14 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_compressor.h"

/**
 * @brief Allocates memory and treats the single pointer in the Simple Tree.
 * 
 * @param nTree A node from the tree.
 * @return nodeList* The new node.
 */
nodeList	*newNodeList(nodeTree *nTree)
{
	nodeList *new;
	
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->node = nTree;
	new->next = NULL;
	return (new);
}


/**
 * @brief Allocates memory and treats the single pointer in the Tree.
 * 
 * @param c Byte to sotre in the node.
 * @param freq Frquency to store in the node.
 * @param left Pointer to the left child node.
 * @param right Pointer to the right child node.
 * @return nodeTree* The new node.
 */
nodeTree	*newNodeTree(byte c, int freq, nodeTree *left, nodeTree *right)
{
	nodeTree	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->c = c;
	new->freq = freq;
	new->left = left;
	new->right = right;
	return (new);
}

/**
 * @brief Insert a new node into the priority queue.
 * 
 * @param node A node preivous created.
 * @param list The list to insert.
 */
void	insertList(nodeList	*node, list	*list)
{
	if (!list->head)
	{
		list->head = node;
	}
	else if (node->node->freq < list->head->node->freq)
	{
		node->next = list->head;
		list->head = node;
	}
	else
	{
		nodeList	*aux = list->head->next;
		nodeList	*aux2 = list->head;

		while (aux && aux->node->freq <= node->node->freq)
		{
			aux2 = aux;
			aux = aux2->next;
		}
		aux2->next = node;
		node->next = aux;
	}
	list->elements++;
}

/**
 * @brief Removes the 'head' from the priority queue (less frequency).
 * 
 * @param list A simple list.
 * @return nodeTree* 
 */
nodeTree	*popMinList(list *list)
{
	nodeList	*aux = list->head;
	nodeTree	*aux2 = aux->node;
	list->head = aux->next;
	free(aux);
	aux = NULL;
	list->elements--;
	return (aux2);
}

/**
 * @brief Builds the Huffman Tree.
 * 
 * @param listBytes The priority queue.
 * @return nodeTree* 
 */
nodeTree	*buildHuffmanTree(unsigned *listBytes)
{
	// Head pointing to NULL, and 0 elements.
	list	list = {NULL, 0};

	// Populates by using the priority queue.
	for (int i = 0; i < 256; i++)
	{
		if (listBytes[i])
		{
			insertList(newNodeList(newNodeTree(i, listBytes[i], NULL, NULL)), &list);
		}
	}

	while (list.elements > 1)
	{
		// Left node gets the small frequency.
		nodeTree	*nodeLeft = popMinList(&list);

		// Right node gets the next small frequency.
		nodeTree	*nodeRight = popMinList(&list);

		// Fills 'c' with '#' into the tree.
		// Fills the 'frequency' with the sum from left and right.
		// Add the left and right pointer in the tree.
		nodeTree	*sum = newNodeTree('#', nodeLeft->freq + nodeRight->freq, nodeLeft, nodeRight);
		
		// // Adds sum into the list.
		insertList(newNodeList(sum), &list);
	}
	return (popMinList(&list));
}

/**
 * @brief Frees the memory used by the Huffman Tree.
 * 
 * @param node Node from a (sub)Tree.
 */
void	freeHuffmanTree(nodeTree *node)
{
	if (!node)
		return ;
	else
	{
		nodeTree	*left = node->left;
		nodeTree	*right = node->right;
		free(node);
		freeHuffmanTree(left);
		freeHuffmanTree(right);
	}
}
