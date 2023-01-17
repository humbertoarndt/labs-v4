/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:24:43 by harndt            #+#    #+#             */
/*   Updated: 2023/01/15 11:58:31 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_compressor.h"

/**
 * @brief Counts the frequency from bytes in a file.
 * 
 * @param input The file to read.
 * @param listBytes Bytes list.
 */
void	getByteFrequency(FILE *input, unsigned int *listBytes)
{
	byte c;

	while (fread(&c, 1, 1, input) >= 1)
	{
		listBytes[(byte)c]++;
	}
	rewind (input);
}

/**
 * @brief Recursive function to travel the Huffman Tree and stops when found 'c'
 * 
 * @param node Node to start the search.
 * @param c Byte to look for.
 * @param buffer Buffer to store the nodes travelled.
 * @param size Prosition to wright.
 * @return true 
 * @return false 
 */
bool	getCode(nodeTree *node, byte c, char *buffer, int size)
{
	// Rescursion base case:
	// If leaf node and its value are searched, puts the char into buffer and ends.
	if (!(node->left || node->right) && node->c == c)
	{
		buffer[size] = '\0';
		return (true);
	}
	else
	{
		bool	found = false;

		if (node->left)
		{
			buffer[size] = '0';
			found = getCode(node->left, c, buffer, size + 1);
		}
		if (!found && node->right)
		{
			buffer[size] = '1';
			found = getCode(node->right, c, buffer, size + 1);
		}
		if (!found)
		{
			buffer[size] = '\0';
		}
		return (found);
	}
}

/**
 * @brief Bitmasks the read node.
 * 
 * @param input File to read.
 * @param position Position to mask the byte.
 * @param aux Byte to check.
 * @return int 1 or 0.
 */
int	generateBit(FILE *input, int position, byte *aux)
{
	if (position % 8 == 0)
	{
		fread(aux, 1, 1, input);
	}
	// Double exclamation point converts to (1) if not (0). Else maintains (0).
	// Travels the binary tree (left to rigth).
	return (!!((*aux) & (1 << (position % 8))));
}
