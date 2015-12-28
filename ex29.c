/*ex29 - Jogo da Velha 
AUTORES:
Antonio Francelino
Hericles Escoteiro
Priscila de Sousa Silva
Thiago Rodrigo

ORIENTADOR:
Prof. Ruben Carlo Benante
OBS: Esse programa e protegido pela GNU LICENSE V2.0, para maiores informacoes consulte o arquivo LICENSE*/


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <time.h>

#define TAMTAB 3 /*tamanho da tabela para o jogo*/
#define BOLA  -1 /* referente a bola */
#define XIS    1 /* referente a xis  */
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

/* Prototipos */
void entrada(int tab[TAMTAB][TAMTAB], int vez);/*chama a funcao de entrada de dados do usuario(jogador)*/
void inicio(int tab[TAMTAB][TAMTAB]); /* zera o tabuleiro */
void jogarnovamente(void); /* roda o programa novamente caso o usuario queira usa-lo novamente */
void vezpcmedio(int tab[TAMTAB][TAMTAB], int vez);
void vezpcdificil(int tab[TAMTAB][TAMTAB], int vez);

int nivelfacil(int tab[TAMTAB][TAMTAB], int vez); /* funcao do nivel facil */
int humanonivel(int tab[TAMTAB][TAMTAB], int vez);
int nivelmedio(int tab[TAMTAB][TAMTAB], int vez); /* funcao do nivel medio */
int niveldificil(int tab[TAMTAB][TAMTAB], int vez); /* funcao do nivel dificil */
int imprimetab(int tab[TAMTAB][TAMTAB]); /* imprime tabuleiro de jogo da velha */
int tabaux(int tab[TAMTAB][TAMTAB]); /* auxiliar para a funcao imprimetab */
int imprimemenunivel(int [TAMTAB][TAMTAB], int vez); /* imprime o menu de selecao de nivel */
int imprimemenu(int tab[TAMTAB][TAMTAB], int vez); /* imprime o menu principal */
int humanoVShumano(int tab[TAMTAB][TAMTAB]); /*chama a funcao multiplayer*/
int humanoVSpc(int tab[TAMTAB][TAMTAB], int vez); /*chama a funcao humano contra o computador*/
int pcVSpc(int tab[TAMTAB][TAMTAB], int vez); /*chama a funcao computador contra o computador*/
int vence(int tab[TAMTAB][TAMTAB],int vez);/*chama a funcao q determinara o final do jogo*/
int humanojoga(int tab[TAMTAB][TAMTAB], int vez);
int vezhumano(int tab[TAMTAB][TAMTAB], int vez);
int vezpc(int tab[TAMTAB][TAMTAB], int vez);
int vezhumanomedio(int tab[TAMTAB][TAMTAB], int vez);
int vezhumanodificil(int tab[TAMTAB][TAMTAB], int vez);


char start(void);/*chama a funcao qm ira fazer a primeira jogada*/

int main(void)
{
    int tab[TAMTAB][TAMTAB], jogada=0, x, nivel, vez=-1;

    srand(time(NULL));
    inicio(tab);
    imprimemenu(tab, vez);
    imprimetab(tab);

    return EXIT_SUCCESS;
}
void jogarnovamente(void)
{
    int parada;

    printf("deseja jogar novamente?\n1-sim\n0-nao\n");
    scanf("%d",&parada);
    if(parada==1)
        main();
    if(parada==0)
    {
        printf("Obrigado por jogar o Jogo da Velha\n");
        exit(0);
    }
}


void inicio(int tab[TAMTAB][TAMTAB])
{
    int i,j;

    for(i=0;i<TAMTAB;i++)      /*faz todas as casas receberem 0 para deixar o tabuleiro em branco */
        for(j=0;j<TAMTAB;j++)
            tab[i][j]=0;
}

int imprimemenu(int tab[TAMTAB][TAMTAB], int vez)/*imprime menu*/
{
    int opt;
    printf("Bem vindo ao jogo da velha de NATAL!\n");
    printf("Escolha seu tipo de jogo: ");
    printf("\n1-Player vs Player \n2-Player vs PC \n3-PC vs PC\n");
    scanf("%d", &opt);
    switch(opt)/*opcoes para modo de jogo*/
    {
        case 1:
            printf("Player vs Player\n");
            humanoVShumano(tab);
            break;
        case 2:
            printf("Player vs PC\n");
            humanoVSpc(tab, vez);
            break;
        case 3:
            printf("PC vs PC\n");
            pcVSpc(tab, vez);
            break;
        default:
            printf("ERRO. Obrigado por jogar!\n");

    }
    return 0;
}
int imprimetab(int tab[TAMTAB][TAMTAB])
{
    setlocale(LC_ALL, ""); /* para caracteres UTF-8 */
    int linha, coluna;
    tabaux(tab);
    putchar('\n');

    for(linha=0; linha<TAMTAB; linha++)
    {
        for(coluna=0; coluna<TAMTAB; coluna++)
        {
            if(tab[linha][coluna] == 0)
                printf("   ");
            else
                if(tab[linha][coluna] == 1)
                    printf(" X ");
                else
                    printf(" O ");

            if(coluna!=(TAMTAB-1))
                printf("%lc",WVV);
        }
        putchar('\n');
        if(linha<TAMTAB-1)
            printf("%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n", WHH, WHH, WHH, WVH, WHH, WHH, WHH, WVH, WHH, WHH, WHH);
    }
    putchar('\n');
    return 0;
}

int tabaux(int tab[TAMTAB][TAMTAB])  /*auxiliar para a funcao imprimetab para mostrar a localizacao de cada casa */
{
    setlocale(LC_ALL, ""); /* para caracteres UTF-8 */
    int linha, coluna, x=0;
    putchar('\n');

    for(linha=0; linha<TAMTAB; linha++)
    {
        for(coluna=0; coluna<TAMTAB; coluna++)
        {
            x++;
            printf(" %d ", x);

            if(coluna!=(TAMTAB-1))
                printf("%lc",WVV);
        }
        putchar('\n');
        if(linha<TAMTAB-1)
            printf("%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n", WHH, WHH, WHH, WVH, WHH, WHH, WHH, WVH, WHH, WHH, WHH);
    }
    putchar('\n');
    return 0;
}


int imprimemenunivel(int tab[TAMTAB][TAMTAB], int vez)
{

    int nivel;

    printf("Escolha um nivel de dificuldade: \n");
    printf("1-facil \n2-medio \n3-dificil\n");
    scanf("%d", &nivel);
    switch(nivel)
    {
        case 1:
            printf("nivel facil\n");
            nivelfacil(tab, vez);
            break;
        case 2:
            printf("nivel medio\n");
            nivelmedio(tab, vez);
            break;
        case 3:
            printf("nivel dificil\n");
            niveldificil(tab, vez);
            break;
        default:
            printf("ERRO.\nObrigado por jogar\n");
            break;
    }

    return 0;
}

int humanonivel(int tab[TAMTAB][TAMTAB], int vez)
{

    int nivel;

    printf("Escolha um nivel de dificuldade: \n");
    printf("1-facil \n2-medio \n3-dificil\n");
    scanf("%d", &nivel);
    switch(nivel)
    {
        case 1:
            {
                int jogar;

                printf("nivel facil\n");
                printf("voce quer comecar jogando?: 1-s\t0-n\n");
                scanf("%d",&jogar);
                vez*=-1; 
                if(jogar==1)
                {   
                    vezhumano(tab, vez);
                    vez=1;
                }   
                else if(jogar==0)
                {
                    vezpc(tab, vez);
                    vez=1;
                }
                //humanofacil(tab, vez);
                //facilhumano(tab, vez);
            }
            break;
        case 2:
            {
                int jogar;

                printf("nivel medio\n");
                printf("voce quer comecar jogando?: 1-s\t0-n\n");
                scanf("%d",&jogar);
                vez*=-1; 
                if(jogar==1)
                {   
                    vezhumanomedio(tab, vez);
                    vez=1;
                }   
                else if(jogar==0)
                {
                    vezpcmedio(tab, vez);
                    vez=1;
                }
            }
            break;
        case 3:
            {

                int jogar;

                printf("nivel dificil\n");
                printf("voce quer comecar jogando?: 1-s\t0-n\n");
                scanf("%d",&jogar);
                vez*=-1;
                if(jogar==1)
                {
                    vezhumanodificil(tab, vez);
                    vez=1;
                }
                else if(jogar==0)
                {
                    vezpcdificil(tab, vez);
                    vez=1;
                }
            }
            break;
        default:
            printf("ERRO.\nÉ DE 1 ATÉ 3\nObrigado por jogar\n");
            break;
    }

    return 0;
}
int vence(int tab[TAMTAB][TAMTAB],int vez)/*Determina como finalizara o jogo*/
{
    /*linhas X*/
    if(tab[0][0]==1 && tab[0][1]==1 && tab[0][2]==1)
    {
        imprimetab(tab);
        printf("Jogador 'X' ganhou\n");
        jogarnovamente();
    }
    if(tab[1][0]==1 && tab[1][1]==1 && tab[1][2]==1)
    {
        imprimetab(tab);
        printf("Jogador 'X' ganhou\n");
        jogarnovamente();
    }
    if(tab[2][0]==1 && tab[2][1]==1 && tab[2][2]==1)
    {
        imprimetab(tab);
        printf("Jogador 'X' ganhou\n");
        jogarnovamente();
    }
    /*colunas X*/
    if(tab[0][0]==1 && tab[1][0]==1 && tab[2][0]==1)
    {
        imprimetab(tab);
        printf("Jogador 'X' ganhou\n");
        jogarnovamente();
    }
    if(tab[0][1]==1 && tab[1][1]==1 && tab[2][1]==1)
    {
        imprimetab(tab);
        printf("Jogador 'X' ganhou\n");
        jogarnovamente();
    }
    if(tab[0][2]==1 && tab[1][2]==1 && tab[2][2]==1)
    {
        imprimetab(tab);
        printf("Jogador 'X' ganhou\n");
        jogarnovamente();
    }
    /*linhas O*/
    if(tab[0][0]==-1 && tab[0][1]==-1 && tab[0][2]==-1)
    {
        imprimetab(tab);
        printf("Jogador 'O' ganhou\n");
        jogarnovamente();
    }
    if(tab[1][0]==-1 && tab[1][1]==-1 && tab[1][2]==-1)
    {
        imprimetab(tab);
        printf("Jogador 'O' ganhou\n");
        jogarnovamente();
    }
    if(tab[2][0]==-1 && tab[2][1]==-1 && tab[2][2]==-1)
    {
        imprimetab(tab);
        printf("Jogador 'O' ganhou\n");
        jogarnovamente();
    }
    /*colunas O*/
    if(tab[0][0]==-1 && tab[1][0]==-1 && tab[2][0]==-1)
    {
        imprimetab(tab);
        printf("Jogador 'O' ganhou\n");
        jogarnovamente();
    }
    if(tab[0][1]==-1 && tab[1][1]==-1 && tab[2][1]==-1)
    {
        imprimetab(tab);
        printf("Jogador 'O' ganhou\n");
        jogarnovamente();
    }
    if(tab[0][2]==-1 && tab[1][2]==-1 && tab[2][2]==-1)
    {
        imprimetab(tab);
        printf("Jogador 'O' ganhou\n");
        jogarnovamente();
    }
    /*diagonais*/
    /*-----------------*/
    if(tab[0][0]==1 && tab[1][1]==1 && tab[2][2]==1)
    {
        imprimetab(tab);
        printf("Jogador 'X' ganhou\n");
        jogarnovamente();
    }
    if(tab[0][0]==-1 && tab[1][1]==-1 && tab[2][2]==-1)
    {   
        imprimetab(tab);
        printf("Jogador 'O' ganhou\n");
        jogarnovamente();
    }
    if(tab[0][2]==1 && tab[1][1]==1 && tab[2][0]==1)
    {   
        imprimetab(tab);
        printf("Jogador 'X' ganhou\n");
        jogarnovamente();
    }
    if(tab[0][2]==-1 && tab[1][1]==-1 && tab[2][0]==-1)
    {
        imprimetab(tab);
        printf("Jogador 'O' ganhou\n");
        jogarnovamente();
    }
    //return 0;
}

void entrada(int tab[TAMTAB][TAMTAB], int vez)/*Determina a entrada de dados do jogador por tecla para cada espaço livre no #*/
{
    int numero,linha,coluna,x,jogada=0;
    do
    {
        imprimetab(tab);
        if(vez==1)
            printf("jogador 'X': ");
        if(vez==-1)
            printf("jogador 'O': ");
        printf("Escolha valores entre 1 e 9\n");

        scanf("%d",&numero);
        switch(numero)
        {
            case 1:
                if(tab[0][0]==0)
                {
                    tab[0][0]=vez;
                    vez*=-1;
                    jogada++;
                }
                else
                    printf("Opcao invalida.. Faca outro movimento \n");
                break;
            case 2:
                if(tab[0][1]==0)
                {
                    tab[0][1]=vez;
                    vez*=-1;
                    jogada++;
                }
                else
                    printf("Opcao invalida.. Faca outro movimento \n");
                break;
            case 3:
                if(tab[0][2]==0)
                {
                    tab[0][2]=vez;
                    vez*=-1;
                    jogada++;
                }
                else
                    printf("Opcao invalida.. Faca outro movimento \n");
                break;
            case 4:
                if(tab[1][0]==0)
                {
                    tab[1][0]=vez;
                    vez*=-1;
                    jogada++;
                }
                else
                    printf("Opcao invalida.. Faca outro movimento \n");
                break;
            case 5:
                if(tab[1][1]==0)
                {
                    tab[1][1]=vez;
                    vez*=-1;
                    jogada++;
                }
                else
                    printf("Opcao invalida.. Faca outro movimento \n");
                break;
            case 6:
                if(tab[1][2]==0)
                {
                    tab[1][2]=vez;
                    vez*=-1;
                    jogada++;
                }
                else
                    printf("Opcao invalida.. Faca outro movimento \n");
                break;
            case 7:
                if(tab[2][0]==0)
                {
                    tab[2][0]=vez;
                    vez*=-1;
                    jogada++;
                }
                else
                    printf("Opcao invalida.. Faca outro movimento \n");
                break;
            case 8:
                if(tab[2][1]==0)
                {
                    tab[2][1]=vez;
                    vez*=-1;
                    jogada++;
                }
                else
                    printf("Opcao invalida.. Faca outro movimento \n");
                break;
            case 9:
                if(tab[2][2]==0)
                {
                    tab[2][2]=vez;
                    vez*=-1;
                    jogada++;
                }
                else
                    printf("Opcao invalida.. Faca outro movimento \n");
                break;
            default:
                printf("Opcao invalida...escolha uma opcao valida!!!\n");
                break;
        }
        vence(tab, vez);
        if(jogada==9)
        {
            imprimetab(tab);
            printf("Vishhhhhh...deu velha...vamos jogar novamente!\n");
            jogarnovamente();
            exit(0);
        }
    }while(numero>0 && numero<10);
}

int humanojoga(int tab[TAMTAB][TAMTAB], int vez)
{ 
    int artificio;
    entrada(tab, vez);
    /*imprimetab(); caso for usar tem que entrar com a tabela como argumento ou seja imprimetab(tab);*/
    artificio = vence(tab, vez);
    if(artificio == 1)
        return 1;
    else
        return 0;
}

char start(void)/*Seleciona qm ira fazer a primeira jogada*/
{
    char r,x;

    printf("\nVoce quer começar jogando?\n s-sim\nn-nao\n");
    do
    {
        r=getchar();
        if(r=='s')
            x=3;
        else if(r=='n')
            x=3;
        else               
            x=2;
    }while(x==2);

    return r;
}

int humanoVShumano(int tab[3][3])
{
    int parada=0, vez = XIS;
    printf("O primeiro Player sera X e o segundo Player sera O.\n");
    while(parada != 1)
    {
        parada = humanojoga(tab, vez);      
        vez = vez *(-1);
    }
    vez = vez*(-1); /* Para anular o mesmo comando anterior 
                       if( vez == XIS )
                       printf(" Parabens jogador xis voce venceu! \n");
                       if( vez == BOLA)
                       printf(" Parabens jogador bola voce venceu! \n");*/
    return 0;
}

int humanoVSpc(int tab[TAMTAB][TAMTAB], int vez)
{
    humanonivel(tab,vez);
}
int pcVSpc(int tab[TAMTAB][TAMTAB], int vez)/*modo de jogo pc vs pc*/
{
    imprimemenunivel(tab,vez);
}
int nivelfacil(int tab[TAMTAB][TAMTAB], int vez)/*modo de jogo pc vs pc*/
{
    int x,y,r=1,jogada=0;

    printf("O primeiro Player sera X e o segundo Player sera O\n");

    do
    {
        if(vez==-1)
        {
            x=rand()%3;
            y=rand()%3;
            if(tab[x][y]==0)
            {
                printf("\nJogador 1:\n");
                tab[x][y] = 1;
                jogada++;
                vez*=-1;
                imprimetab(tab);
            }
        }
        else
        {
            x=rand()%3;
            y=rand()%3;
            if(tab[x][y]==0)
            {
                printf("\nJogador 2:\n");
                tab[x][y] = -1;
                jogada++;
                vez*=-1;
                imprimetab(tab);
            }
        }

        vence(tab, vez);

    }while(jogada<9);

    return 0;
}

int vezhumano(int tab[TAMTAB][TAMTAB],int vez)
{
    int tc, parada=0;

    do
    {
        imprimetab(tab);
        printf("Escolha de 1 a 9\n");
        scanf("%d",&tc);
        switch(tc)
        {
            case 1:
                if(tab[0][0]==0)
                {
                    tab[0][0]=vez;
                    vez*=-1;
                    vezpc(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;

            case 2:
                if(tab[0][1]==0)
                {
                    tab[0][1]=vez;
                    vez*=-1;
                    vezpc(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;

            case 3:
                if(tab[0][2]==0)
                {
                    tab[0][2]=vez;
                    vez*=-1;
                    vezpc(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 4:
                if(tab[1][0]==0)
                {
                    tab[1][0]=vez;
                    vez*=-1;
                    vezpc(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 5:
                if(tab[1][1]==0)
                {
                    tab[1][1]=vez;
                    vez*=-1;
                    vezpc(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 6:
                if(tab[1][2]==0)
                {
                    tab[1][2]=vez;
                    vez*=-1;
                    vezpc(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 7:
                if(tab[2][0]==0)
                {
                    tab[2][0]=vez;
                    vez*=-1;
                    vezpc(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 8:
                if(tab[2][1]==0)
                {
                    tab[2][1]=vez;
                    vez*=-1;
                    vezpc(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 9:
                if(tab[2][2]==0)
                {
                    tab[2][2]=vez;
                    vez*=-1;
                    vezpc(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            default:
                printf("valor invalido\n");
                break;
        }
        vence(tab, vez);
    }while(tc>0 && tc<10);
}

int vezpc(int tab[TAMTAB][TAMTAB], int vez)
{
    int x,y, parada=0;
    //vez=-1;

    imprimetab(tab);
    do
    {
        x=rand()%3;
        y=rand()%3;
        if(tab[x][y]==0)
        {
            tab[x][y]=vez;
            imprimetab(tab);
            parada=1;
            //vezhumano(tab, vez);
        }
    }while(parada==0);
    vence(tab, vez);
    vez*=-1;
    vezhumano(tab, vez);
}

void vezpcmedio(int tab[TAMTAB][TAMTAB], int vez)
{
    int n1,n2,x,y, parada=0;

    do
    {
        imprimetab(tab);
        for(n1=0;n1<TAMTAB;n1++)
        {
            if((tab[n1][0] == vez && tab[n1][1] == vez) && tab[n1][2]==0)
            {

                tab[n1][2] = vez;
                parada=1;
            }
            else if((tab[n1][0] == vez && tab[n1][2] == vez) && tab[n1][0]==0)
            {
                tab[n1][1] = vez;
                parada=1;
            }
            else  if((tab[n1][1] == vez && tab[n1][2] == vez) && tab[n1][0]==0)
            {
                tab[n1][0] = vez;
                parada=1;

            }
            if((tab[0][n1] == vez && tab[1][n1] == vez) && tab[2][n1]==0)
            {
                tab[2][n1] = vez;
                parada=1;

            }
            else if((tab[0][n1] == vez && tab[2][n1] == vez) && tab[1][n1]==0)
            {
                tab[1][n1] = vez;
                parada=1;

            }
            else  if((tab[1][n1] == vez && tab[2][n1] == vez) && tab[0][n1]==0)
            {
                tab[0][n1] = vez;
                parada=1;

            }
            if((tab[0][0] == vez && tab[1][1] == vez) && tab[2][2]==0)
            {
                tab[2][2] = vez;
                parada=1;

            }
            else if((tab[0][0] == vez && tab[2][2] == vez) && tab[1][1]==0)
            {
                tab[1][1] = vez;
                parada=1;

            }
            else if((tab[2][2] == vez && tab[1][1] == vez) && tab[0][0]==0)
            {
                tab[0][0] = vez;
                parada=1;

            }
            if((tab[0][2] == vez && tab[1][1] == vez) && tab[2][0]==0)
            {
                tab[2][0] = vez;
                parada=1;

            }
            else if((tab[0][2] == vez && tab[2][0] == vez) && tab[1][1]==0)

            {
                tab[1][1] = vez;
                parada=1;
            }
            else if((tab[2][0] == vez && tab[1][1] == vez) && tab[0][2]==0)
            {
                tab[0][2] = vez;
                parada=1;

            }
        }
        x=rand()%3;
        y=rand()%3;
        if(tab[x][y]==0)
        {
            tab[x][y]=vez;
            imprimetab(tab);
            parada=1;
        }
    }while(parada==0);
    imprimetab(tab);
    vence(tab, vez);
    vez*=-1;
    vezhumanomedio(tab, vez);

}

int vezhumanomedio(int tab[TAMTAB][TAMTAB],int vez)
{
    int tc, parada=0;

    do
    {
        imprimetab(tab);
        printf("Escolha de 1 a 9\n");
        scanf("%d",&tc);
        switch(tc)
        {
            case 1:
                if(tab[0][0]==0)
                {
                    tab[0][0]=vez;
                    vence(tab, vez);
                    vez*=-1;
                    vezpcmedio(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;

            case 2:
                if(tab[0][1]==0)
                {
                    tab[0][1]=vez;
                    vence(tab, vez);
                    vez*=-1;
                    vezpcmedio(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;

            case 3:
                if(tab[0][2]==0)
                {
                    tab[0][2]=vez;
                    vence(tab, vez);
                    vez*=-1;
                    vezpcmedio(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 4:
                if(tab[1][0]==0)
                {
                    tab[1][0]=vez;
                    vence(tab, vez);
                    vez*=-1;
                    vezpcmedio(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 5:
                if(tab[1][1]==0)
                {
                    tab[1][1]=vez;
                    vence(tab, vez);
                    vez*=-1;
                    vezpcmedio(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 6:
                if(tab[1][2]==0)
                {
                    tab[1][2]=vez;
                    vence(tab, vez);
                    vez*=-1;
                    vezpcmedio(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 7:
                if(tab[2][0]==0)
                {
                    tab[2][0]=vez;
                    vence(tab, vez);
                    vez*=-1;
                    vezpcmedio(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 8:
                if(tab[2][1]==0)
                {
                    tab[2][1]=vez;
                    vence(tab, vez);
                    vez*=-1;
                    vezpcmedio(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 9:
                if(tab[2][2]==0)
                {
                    tab[2][2]=vez;
                    vence(tab, vez);
                    vez*=-1;
                    vezpcmedio(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            default:
                printf("valor invalido\n");
                break;
        }
        vence(tab, vez);
    }while(tc>0 && tc<10);
}

void vezpcdificil(int tab[TAMTAB][TAMTAB], int vez)
{
    int parada=0;
    int n1,x,y;

    do
    {
        for(n1=0;n1<TAMTAB;n1++)
        {
            if((tab[n1][0] == (vez*-1) && tab[n1][1] == (vez*-1)) && tab[n1][2]==0)
            {

                tab[n1][2] = vez;
                parada=1;
            }
            else if((tab[n1][0] == (vez*-1) && tab[n1][2] == (vez*-1)) && tab[n1][0]==0)
            {
                tab[n1][1] = vez;
                parada=1;
            }
            else  if((tab[n1][1] == (vez*-1) && tab[n1][2] == (vez*-1)) && tab[n1][0]==0)
            {
                tab[n1][0] = vez;
                parada=1;

            }
            if((tab[0][n1] == (vez*-1) && tab[1][n1] == (vez*-1)) && tab[2][n1]==0)
            {
                tab[2][n1] = vez;
                parada=1;

            }
            else if((tab[0][n1] == (vez*-1) && tab[2][n1] == (vez*-1)) && tab[1][n1]==0)
            {
                tab[1][n1] = vez;
                parada=1;

            }
            else  if((tab[1][n1] == (vez*-1) && tab[2][n1] == (vez*-1)) && tab[0][n1]==0)
            {
                tab[0][n1] = vez;
                parada=1;

            }
            if((tab[0][0] == (vez*-1) && tab[1][1] == (vez*-1)) && tab[2][2]==0)
            {
                tab[2][2] = vez;
                parada=1;

            }
            else if((tab[0][0] == (vez*-1) && tab[2][2] == (vez*-1)) && tab[1][1]==0)
            {
                tab[1][1] = vez;
                parada=1;

            }
            else if((tab[2][2] == (vez*-1) && tab[1][1] == (vez*-1)) && tab[0][0]==0)
            {
                tab[0][0] = vez;
                parada=1;

            }
            if((tab[0][2] == (vez*-1) && tab[1][1] == (vez*-1)) && tab[2][0]==0)
            {
                tab[2][0] = vez;
                parada=1;

            }
            else if((tab[0][2] == (vez*-1) && tab[2][0] == (vez*-1)) && tab[1][1]==0)

            {
                tab[1][1] = vez;
                parada=1;
            }
            else if((tab[2][0] == (vez*-1) && tab[1][1] == (vez*-1)) && tab[0][2]==0)
            {
                tab[0][2] = vez;
                parada=1;

            }
        }
        
        x=rand()%3;
        y=rand()%3;
        if(tab[x][y]==0)
        {
            tab[x][y]=vez;
            //imprimetab(tab);
            parada=1;
        }
    }while(parada==0);
    imprimetab(tab);
    vence(tab, vez);
    vez*=-1;
    vezhumanomedio(tab, vez);
}

int vezhumanodificil(int tab[TAMTAB][TAMTAB],int vez)
{
    int tc, parada=0;

    do
    {
        imprimetab(tab);
        printf("Escolha de 1 a 9\n");
        scanf("%d",&tc);
        switch(tc)
        {
            case 1:
                if(tab[0][0]==0)
                {
                    tab[0][0]=vez;
                    imprimetab(tab);
                    vez*=-1;
                    vezpcdificil(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;

            case 2:
                if(tab[0][1]==0)
                {
                    tab[0][1]=vez;
                    imprimetab(tab);
                    vez*=-1;
                    vezpcdificil(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;

            case 3:
                if(tab[0][2]==0)
                {
                    tab[0][2]=vez;
                    imprimetab(tab);
                    vez*=-1;
                    vezpcdificil(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 4:
                if(tab[1][0]==0)
                {
                    tab[1][0]=vez;
                    imprimetab(tab);
                    vez*=-1;
                    vezpcdificil(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 5:
                if(tab[1][1]==0)
                {
                    tab[1][1]=vez;
                    imprimetab(tab);
                    vez*=-1;
                    vezpcdificil(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 6:
                if(tab[1][2]==0)
                {
                    tab[1][2]=vez;
                    imprimetab(tab);
                    vez*=-1;
                    vezpcdificil(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 7:
                if(tab[2][0]==0)
                {
                    tab[2][0]=vez;
                    imprimetab(tab);
                    vez*=-1;
                    vezpcdificil(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 8:
                if(tab[2][1]==0)
                {
                    tab[2][1]=vez;
                    imprimetab(tab);
                    vez*=-1;
                    vezpcdificil(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            case 9:
                if(tab[2][2]==0)
                {
                    tab[2][2]=vez;
                    imprimetab(tab);
                    vez*=-1;
                    vezpcdificil(tab, vez);
                }
                else
                {
                    printf("Opcao invalida.. Faca outro movimento \n");
                }
                break;
            default:
                printf("valor invalido\n");
                break;
        }
        vence(tab, vez);
    }while(tc>0 && tc<10);
}

int nivelmedio(int tab[TAMTAB][TAMTAB], int vez) /* funcao do nivel medio */
{
    int n1,n2,x,y, parada=0;

    do
    {
        imprimetab(tab);
        for(n1=0;n1<TAMTAB;n1++)
        {
            if((tab[n1][0] == vez && tab[n1][1] == vez) && tab[n1][2]==0)
            {

                tab[n1][2] = vez;
                parada=1;
            }
            else if((tab[n1][0] == vez && tab[n1][2] == vez) && tab[n1][0]==0)
            {
                tab[n1][1] = vez;
                parada=1;
            }
            else  if((tab[n1][1] == vez && tab[n1][2] == vez) && tab[n1][0]==0)
            {
                tab[n1][0] = vez;
                parada=1;

            }
            if((tab[0][n1] == vez && tab[1][n1] == vez) && tab[2][n1]==0)
            {
                tab[2][n1] = vez;
                parada=1;

            }
            else if((tab[0][n1] == vez && tab[2][n1] == vez) && tab[1][n1]==0)
            {
                tab[1][n1] = vez;
                parada=1;

            }
            else  if((tab[1][n1] == vez && tab[2][n1] == vez) && tab[0][n1]==0)
            {
                tab[0][n1] = vez;
                parada=1;

            }
            if((tab[0][0] == vez && tab[1][1] == vez) && tab[2][2]==0)
            {
                tab[2][2] = vez;
                parada=1;

            }
            else if((tab[0][0] == vez && tab[2][2] == vez) && tab[1][1]==0)
            {
                tab[1][1] = vez;
                parada=1;

            }
            else if((tab[2][2] == vez && tab[1][1] == vez) && tab[0][0]==0)
            {
                tab[0][0] = vez;
                parada=1;

            }
            if((tab[0][2] == vez && tab[1][1] == vez) && tab[2][0]==0)
            {
                tab[2][0] = vez;
                parada=1;

            }
            else if((tab[0][2] == vez && tab[2][0] == vez) && tab[1][1]==0)

            {
                tab[1][1] = vez;
                parada=1;
            }
            else if((tab[2][0] == vez && tab[1][1] == vez) && tab[0][2]==0)
            {
                tab[0][2] = vez;
                parada=1;

            }
        }
        x=rand()%3;
        y=rand()%3;
        if(tab[x][y]==0)
        {
            tab[x][y]=vez;
            imprimetab(tab);
            parada=1;
        }
    }while(parada==0);
    imprimetab(tab);
    vence(tab, vez);
    vez*=-1;
    nivelmedio(tab, vez);

}

int niveldificil(int tab[TAMTAB][TAMTAB], int vez) /* funcao do nivel dificil */
{
    int parada=0,jogada=0;
    int n1,x,y;

    do
    {
        for(n1=0;n1<TAMTAB;n1++)
        {
            if((tab[n1][0] == (vez*-1) && tab[n1][1] == (vez*-1)) && tab[n1][2]==0)
            {

                tab[n1][2] = vez;
                parada=1;
            }
            else if((tab[n1][0] == (vez*-1) && tab[n1][2] == (vez*-1)) && tab[n1][0]==0)
            {
                tab[n1][1] = vez;
                parada=1;
            }
            else  if((tab[n1][1] == (vez*-1) && tab[n1][2] == (vez*-1)) && tab[n1][0]==0)
            {
                tab[n1][0] = vez;
                parada=1;

            }
            if((tab[0][n1] == (vez*-1) && tab[1][n1] == (vez*-1)) && tab[2][n1]==0)
            {
                tab[2][n1] = vez;
                parada=1;

            }
            else if((tab[0][n1] == (vez*-1) && tab[2][n1] == (vez*-1)) && tab[1][n1]==0)
            {
                tab[1][n1] = vez;
                parada=1;

            }
            else  if((tab[1][n1] == (vez*-1) && tab[2][n1] == (vez*-1)) && tab[0][n1]==0)
            {
                tab[0][n1] = vez;
                parada=1;

            }
            if((tab[0][0] == (vez*-1) && tab[1][1] == (vez*-1)) && tab[2][2]==0)
            {
                tab[2][2] = vez;
                parada=1;

            }
            else if((tab[0][0] == (vez*-1) && tab[2][2] == (vez*-1)) && tab[1][1]==0)
            {
                tab[1][1] = vez;
                parada=1;

            }
            else if((tab[2][2] == (vez*-1) && tab[1][1] == (vez*-1)) && tab[0][0]==0)
            {
                tab[0][0] = vez;
                parada=1;

            }
            if((tab[0][2] == (vez*-1) && tab[1][1] == (vez*-1)) && tab[2][0]==0)
            {
                tab[2][0] = vez;
                parada=1;

            }
            else if((tab[0][2] == (vez*-1) && tab[2][0] == (vez*-1)) && tab[1][1]==0)

            {
                tab[1][1] = vez;
                parada=1;
            }
            else if((tab[2][0] == (vez*-1) && tab[1][1] == (vez*-1)) && tab[0][2]==0)
            {
                tab[0][2] = vez;
                parada=1;

            }
        }
        
        x=rand()%3;
        y=rand()%3;
        if(tab[x][y]==0)
        {
            tab[x][y]=vez;
            //imprimetab(tab);
            parada=1;
        }
    }while(parada==0);
    imprimetab(tab);
    vence(tab, vez);
    jogada++;
    if(jogada==9)
    {
        printf("DEU VELHA!! VAMOS NOVAMENTE\n");
        jogarnovamente();
    }
    vez*=-1;
    niveldificil(tab, vez);
}

