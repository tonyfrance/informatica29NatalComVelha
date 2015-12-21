/* Fazer um jogo da velha */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

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
    int tabuleiro[3][3]; /* posicoes dos elementos do mapa */
    int nivel; /* nivel de dificuldade */
}dados;

dados d;

/* Prototipos */
int inicio(void); /* escolha de nivel */
int nivelfacil(int tab[3][3],int vez); /* funcao do nivel facil */
int nivelmedio(int tab[3][3],int vez); /* funcao do nivel medio */
int niveldificil(int tab[3][3],int vez); /* funcao do nivel dificil */
int imprimetab(void); /* imprime tabuleiro de jogo da velha */

int main(void)
{
    imprimetab();
    inicio();
    return EXIT_SUCCESS;
}

