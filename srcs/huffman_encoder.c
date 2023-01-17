/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_encoder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:17:32 by harndt            #+#    #+#             */
/*   Updated: 2023/01/15 12:06:17 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_compressor.h"

/**
 * @brief Compress a file using the Huffman Algoritm.
 * 
 * @param input_file File to compress.
 * @param output_file Result from the file compression.
 */
static void	compressFile(const char *input_file, const char *output_file)
{
	clock_t	start;
	clock_t	end;
	double	runtime;
	
	start = clock();

	unsigned	listBytes[256] = {0};

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

	getByteFrequency(input, listBytes);

	// Builds  binary tree using priority queue.
	nodeTree *root = buildHuffmanTree(listBytes);

	// Stores the priority queue at the beginning of the 'output' file.
	fwrite(listBytes, 256, sizeof(listBytes[0]), output);
	
	// Moves the cursor to the end of an unsigned int.
	fseek(output, sizeof(unsigned int), SEEK_CUR);

	byte	c;
	unsigned	size = 0;
	byte	aux = 0;


	// Reads 1 block of memory with 1 byte size from 'input' file and saves it in 'c'.
	while (fread(&c, 1, 1, input) >= 1)
	{
		// Creates an empty buffer.
		char	buffer[1024] = {0};

		// Search for the the 'c' in the tree starting by its root.
		getCode(root, c, buffer, 0);

		// Travels the buffer.
		for (char *i = buffer; *i; i++)
		{
			if (*i == '1')
			{
				// aux = aux + pow(2, size % 8)
				aux = aux | (1 << (size % 8));
			}

			size++;

			// Writes the byte into the 'output' file.
			if (size % 8 == 0)
			{
				fwrite(&aux, 1, 1, output);
				aux = 0;
			}
		}
	}

	fwrite(&aux, 1, 1, output);

	// Moves the cursor to 256 * the size of an unsigned int using SEEK_SET.
	fseek(output, 256 * sizeof(unsigned int), SEEK_SET);
	
	// Stores the value o 'size' into 'output' file.
	fwrite(&size, 1, sizeof(unsigned), output);

	end = clock();
	runtime = (double)(end - start) / CLOCKS_PER_SEC;

	// Calculates the size of each file.
	fseek(input, 0L, SEEK_END);
	double	input_size = ftell(input);

	fseek(output, 0L, SEEK_END);
	double	output_size = ftell(output);

	freeHuffmanTree(root);
	printf("%s█ ENCODER ██████████████████████████████████████████████████████████████████████%s\n", byellow, eof);
	printf("%sArquivo de entrada:%s\t|%s|\t(%g bytes)\n", yellow, eof, input_file, input_size / 1000);
	printf("%sArquivo de saída:%s\t|%s|\t(%g bytes)\n", yellow, eof, output_file, output_size / 1000);
	printf("%sTempo gasto:%s\t\t%gs\n", yellow, eof, runtime);
	printf("%sTaxa de compressão:%s\t%d%%\n", yellow, eof, (int)((100 * output_size / input_size)));

	fclose(input);
	fclose(output);
}

int main(int argc, char *argv[])
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
	
	// Creates '.huff' file.
	strcpy(filename_out, filename);
	strcat(filename_out, ".huff");
	fp = fopen(filename_out, "w");
	
	if (!fp)
	{
		printf("%sERROR:%s output file not created.\n", bired, eof);
		exit(0);
	}
	
	fclose(fp);
	compressFile(filename, filename_out);
	return (0);
}
