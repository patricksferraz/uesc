#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void cifrar(int, char *); 

int main(int argc, char *argv[])
{
	FILE *f_in;
	FILE *f_out;
	int key;
    char c;

	if (argc != 3)
	{
		printf("Quantidade de argumentos invalidos, favor digitar somente a chave entre 1-25 e o nome do arquivo para cifrar\n");
	}
	else 
	{
		key = atoi(argv[1]);
		
        if (key < 1 || key > 25)
		{
			printf("Chave invalida, favor digitar a chave entre 1-25\n");
            exit(0);
		}
		else
		{
			if (f_in = fopen(argv[2], "r"))
            {
                if (f_out = fopen("file-cdjc.txt", "w"))
                {
                    while (!feof(f_in))
                    {
                        c = fgetc(f_in);
                        cifrar(key, &c);
                        fputc(c, f_out);                        
                    }
                    printf("Arquivo cifrado com sucesso!\n");
                }
                else
                {
                    printf("Erro ao criar arquivo cifrado\n");
                    exit(0);                    
                }
            }
            else
            {
                printf("O arquivo escolhido para cifrar nao existe\n");
                exit(0);
            }
		}
		
		fclose(f_in);
        fclose(f_out);
	}

	return 0;
}

void cifrar(int key, char *c)
{
    char t;
    
    if (isalpha(*c))
    {
        t = *c + key;
        
        if ((isupper(*c) && !isupper(t)) || !isalpha(t))
        {
            *c = t - 26;
        }
        else
        {
            *c = t;
        }
    }
}
