/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_compressor.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:50:22 by harndt            #+#    #+#             */
/*   Updated: 2023/01/15 11:55:34 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_COMPRESSOR_H
# define DATA_COMPRESSOR_H

// =============================================================================
// STANDARTS LIBRARIES
// =============================================================================

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

// =============================================================================
// LOCAL LIBRARIES
// =============================================================================

# include "colors.h"

// =============================================================================
// STRUCTS
// =============================================================================

/**
 * @brief Unsigned is used to store the gap between 0 and 255.
 * 
 */
typedef unsigned char	byte;

/**
 * @brief Binary tree struct.
 * 
 */
typedef struct nodeTree
{
	int					freq;
	byte				c;
	struct	nodeTree	*left;
	struct	nodeTree	*right;
}	nodeTree;

/**
 * @brief Simple list to use as priority queue
 * 
 */
typedef struct nodeList
{
	nodeTree		*node;
	struct nodeList	*next;
}	nodeList;

typedef struct list
{
	nodeList	*head;
	int			elements;
}	list;

// =============================================================================
// UTILS FUNCTIONS
// =============================================================================

int			generateBit(FILE *input, int position, byte *aux);
void		getByteFrequency(FILE *input, unsigned int *listBytes);
bool		getCode(nodeTree *node, byte c, char *buffer, int size);

// =============================================================================
// HUFFMAN FUNCTIONS
// =============================================================================

nodeTree	*popMinList(list *list);
nodeList	*newNodeList(nodeTree *nTree);
void		freeHuffmanTree(nodeTree *node);
void		insertList(nodeList	*node, list	*list);
nodeTree	*buildHuffmanTree(unsigned *listBytes);
nodeTree	*newNodeTree(byte c, int freq, nodeTree *left, nodeTree *right);

#endif