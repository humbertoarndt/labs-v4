/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_decoder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:33:30 by harndt            #+#    #+#             */
/*   Updated: 2023/01/15 12:06:24 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_compressor.h"

/**
 * @brief Decompress a file using the Huffman Algoritm.
 * 
 * @param input_file File to decompress.
 * @param output_file Result from the file decompression.
 */
static void	decompressFile(const char *input_file, const char *output_file)
{
	clock_t	start;
	clock_t	end;
	double	runtime;

	start = clock();

	unsigned listBytes[256] = {0};

	// Open 'input' file as "rb".
	FILE	*input = fopen(input_file, "rb");
	if (!input)
	{
		printf("%sERROR:%s input file not found.\n", bired, eof);
		exit (0);
	}

	// Open 'output' file as "wb".
	FILE	*output = fopen(output_file, "wb");
	if (!output)
	{
		printf("%sERROR:%s output file not found.\n", bired, eof);
		exit (0);
	}

	// Reads the priority queue stored in the first 265 bytes from 'input' file.
	fread(listBytes, 256, sizeof(listBytes[0]), input);

	// Builds tree.
	nodeTree *root = buildHuffmanTree(listBytes);

	// Reads the size stored in 'input' file.
	unsigned	size;
	fread(&size, 1, sizeof(size), input);

	unsigned	position = 0;
	byte aux = 0;

	while (position < size)
	{
		nodeTree *nodeCurrent = root;
		
		while (nodeCurrent->left || nodeCurrent->right)
		{
			if (generateBit(input, position++, &aux))
				nodeCurrent = nodeCurrent->right;
			else
				nodeCurrent = nodeCurrent->left;
		}
		fwrite(&(nodeCurrent->c), 1, 1, output);
	}

	freeHuffmanTree(root);

	end = clock();
	runtime = (double)(end - start) / CLOCKS_PER_SEC;

	// Calculates the size of each file.
	fseek(input, 0L, SEEK_END);
	double	input_size = ftell(input);

	fseek(output, 0L, SEEK_END);
	double	output_size = ftell(output);

	printf("%s█ DECODER ██████████████████████████████████████████████████████████████████████%s\n", byellow, eof);
	printf("%sArquivo de entrada:%s\t|%s|\t(%g bytes)\n", yellow, eof, input_file, input_size / 1000);
	printf("%sArquivo de saída:%s\t|%s|\t(%g bytes)\n", yellow, eof, output_file, output_size / 1000);
	printf("%sTempo gasto:%s\t\t%gs\n", yellow, eof, runtime);
	printf("%sTaxa de descompressão:%s %d%%\n", yellow, eof, (int)((100*output_size) / input_size));

	fclose(input);
	fclose(output);
}

int	main(int argc, char *argv[])
{
	char	filename[42] = {0};
	char	filename_out[84] = {0};
	FILE	*fp;
	
	if (argc == 2)
		strcpy(filename, argv[1]);
	else if (argc > 2)
	{
		printf("%sERROR:%s too many arguments.\n", bired, eof);
		exit (0);
	}
	else
	{
		printf("%sUSAGE:%s ./encoder <file>\n", bired, eof);
		exit (0);
	}

	// Creates the '_copy' file.
	strncpy(filename_out, filename, (strlen(filename) - 5));
	strcat(filename_out, "_copy");
	fp = fopen(filename_out, "w");
	
	if (!fp)
	{
		printf("%sERROR:%s output file not created.\n", bired, eof);
		exit(0);
	}
	
	fclose(fp);
	decompressFile(filename, filename_out);
	return (0);
}
