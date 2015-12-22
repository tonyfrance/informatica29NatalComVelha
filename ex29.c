/* Fazer um jogo da velha */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

#define TAMTAB 3 /*tamanho da tabela para o jogo*/

/* Bordas UTF 8 */

#define WUL L'\u2518' /* ^VU2518 ┘ */
#define WDL L'\u2510' /* ^VU2510 ┐ */
#define WDR L'\u250c' /* ^VU250c ┌ */
#define WUR L'\u2514' /* ^VU2514 └ */
#define WVH L'\u253c' /* ^VU253c ┼ */
#define WHH L'\u2500' /* ^VU2500 ─ */
#define WVR L'\u251c' /* ^VU251c ├ */
#define WVL L'\u2524' /* ^VU2524 ┤ */
#define WUH L'\u2534' /* ^VU2534 ┴ */
#define WDF L'\u252c' /* ^VU252c ┬ */
#define WVV L'\u2502' /* ^VU2502 │ */
#define WGL L'\u2571' /* ^VU2571 ╱ */
#define WGR L'\u2572' /* ^VU2572 ╲ */
#define WGX L'\u2573' /* ^VU2573 ╳ */
#define PRINTGRAF_ON ;
#define PRINTGRAF_OFF ;

typedef struct
{
    int tab[3][3];  posicoes dos elementos do mapa 
    int nivel;  nivel de dificuldade 
}dados;

dados d;


/* Prototipos */
int inicio(void); /* escolha de nivel */
int nivelfacil(int tab[3][3],int vez); /* funcao do nivel facil */
int nivelmedio(int tab[3][3],int vez); /* funcao do nivel medio */
int niveldificil(int tab[3][3],int vez); /* funcao do nivel dificil */
int imprimetab(void); /* imprime tabuleiro de jogo da velha */
int imprimemenu(void); /* imprime o menu de selecao de nivel */

int main(void)
{
    imprimetab();
    imprimemenu();
    return EXIT_SUCCESS;
}

int inicio(void)
{
    int i,j;

    for(i=0,i<TAMTAB,i++)      /*faz todas as casas receberem 0 para deixar o tabuleiro em branco */
        for(j=0,j<TAMTAB,j++)
            d.tab[i][j]=0;
    return 0;
}

int imprimemenu(void)
{
    int nivel;
    printf("Escolha um nivel de dificuldade: \n");
    printf("1-facil \n2-medio \n3-dificil");
    scanf("%d", &nivel);
    switch(nivel)
    {
        case 1:
            nivelfacil();
            break;
        case 2:
            nivelmedio();
            break;
        case 3:
            niveldificil();
            break;
        default:
            printf("ERRO.\nObrigado por jogar");
            break;
    }
    return nivel;
}

int imprimetab(void)
{
    return 0;
}

int entrada(int vez)
{
    int numero;
    do
    {
        printf("Escolha valores entre 0 e 8");
        scanf("%d",&numero);
        switch(numero);
        {
            case 1:
                d.tab[0][0]=vez;               
                break;
            case 2:
                d.tab[0][1]=vez;
                break;
            case 3:
                d.tab[0][2]=vez;
                break;
            case 4:
                d.tab[1][0]=vez;
                break;
            case 5:
                d.tab[1][1]=vez;
                break;
            case 6:
                d.tab[1][2]=vez;
                break;
            case 7:
                d.tab[2][0]=vez;
                break;
            case 8:
                d.tab[2][1]=vez;
                break;
            case 9:
                d.tab[2][2]=vez;
                break;
            default:
                printf("Opcao invalida...escolha uma opcao valida!!!");
                break;
        }          
    }while(numero < 0 || numero > 9);
}

int humanojoga(void)
{
    int numero;
    do
    {
        imprimetab();
        numero=entrada();
    }

}

