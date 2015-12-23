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
    int tab[3][3]; /* posicoes dos elementos do mapa */
    int nivel; /*  nivel de dificuldade */
}dados;

int vez,opt;
dados d;


/* Prototipos */
int inicio(void); /* escolha de nivel */
int nivelfacil(int tab[3][3]); /* funcao do nivel facil */
int nivelmedio(int tab[3][3]); /* funcao do nivel medio */
int niveldificil(int tab[3][3]); /* funcao do nivel dificil */
int imprimetab(void); /* imprime tabuleiro de jogo da velha */
int imprimemenunivel(void); /* imprime o menu de selecao de nivel */
int imprimemenu(void); /* imprime o menu principal */
int humanoVShumano(void); /*chama a funcao multiplayer*/
int humanoVSpc(void); /*chama a funcao humano contra o computador*/
int pcVSpc(void); /*chama a funcao computador contra o computador*/
int vence(void);/*chama a funcao q determinara o final do jogo*/
int entrada(void);/*chama a funcao de entrada de dados do usuario(jogador)*/
char start(void);/*chama a funcao qm ira fazer a primeira jogada*/
int geradordenumeros(void);

int main(void)
{
    int jogada=0,x;
    vez=-1;
    imprimemenu();
    imprimetab();

    do
    {
        vez*=-1;
        if(vez==1)
        {
            switch(opt)
            {
                case 1:
                    humanoVShumano();
                    break;
                case 2:
                    humanoVSpc();
                    break;
                case 3:
                    pcVSpc();
                    break;
                default:
                    printf("ERRO. Obrigado por jogar!\n");
                    return 0;
            }
            jogada++;
            x=vence();
            if(x==1)
                vez++;
        }
        if(vez==-1)
        {
            switch(opt)
            {
                case 1:
                    humanoVShumano();
                    break;
                case 2:
                    humanoVSpc();
                    break;
                case 3:
                    pcVSpc();
                    break;
                default:
                    printf("ERRO. Obrigado por jogar!\n");
                    return 0;
            }
            jogada++;
            x=vence();
            if(x==1)
                vez++;
        }
        if(jogada==9 && x==0) /* se o contador de jogadas for 9, sai do laço e testa empate */
            vez=3;
    }while(vez==1 || vez==-1);

    switch(vez)
    {
        case 0:
            printf("O ganhou\n");
            break;
        case 2:
            printf("X ganhou\n");
            break;
        case 3:
            printf("DEU VELHA\n");
            break;
        default:
            break;
    }
    printf("Obrigado por jogar o Jogo da Velha\n");


    return EXIT_SUCCESS;
}

int inicio(void)
{
    int i,j;

    for(i=0;i<TAMTAB;i++)      /*faz todas as casas receberem 0 para deixar o tabuleiro em branco */
        for(j=0;j<TAMTAB;j++)
            d.tab[i][j]=0;
    return 0;
}

int imprimemenunivel(void)
{
    int nivel;
    printf("Escolha um nivel de dificuldade: \n");
    printf("1-facil \n2-medio \n3-dificil\n");
    scanf("%d", &d.nivel);
    switch(d.nivel)
    {
        case 1:
            printf("nivel facil\n");
            /*nivelfacil();*/
            break;
        case 2:
            printf("nivel medio\n");
            /*nivelmedio();*/
            break;
        case 3:
            printf("nivel dificil\n");
            /*niveldificil();*/
            break;
        default:
            printf("ERRO.\nObrigado por jogar\n");
            break;
    }

    return 0;
}


int imprimetab(void)
{
    /* Lembrar de implementar UTF-8 depois */
    int linha, coluna;
    putchar('\n');

    for(linha=0; linha<TAMTAB; linha++)
    {
        for(coluna=0; coluna<TAMTAB; coluna++)
        {
            if(d.tab[linha][coluna] == 0)
                printf("    ");
            else
                if(d.tab[linha][coluna] == 1)
                    printf("  X ");
                else
                    printf("  O ");

            if(coluna!=(TAMTAB-1))
                printf("|");
        }
        putchar('\n');
        if(linha<TAMTAB-1)
            printf(" ---+----+---\n");
    }
    putchar('\n');
    return 0;
}
int vence(void)/*Determina como finalizara o jogo*/
{
    int n1;
    for(n1=0; n1<3; n1++)/* Analisa se tem linha completa */
    {
        if((d.tab[n1][0] == vez && d.tab[n1][1] == vez) && d.tab[n1][2] == vez)
            return 1;
    }
    for(n1=0; n1<3; n1++)/* Analisa se tem coluna completa */
    {
        if((d.tab[0][n1] == vez && d.tab[1][n1] == vez) && d.tab[2][n1] == vez)
            return 1;  
    }
    if((d.tab[0][0] == vez && d.tab[1][1] == vez) && d.tab[2][2])
        return 1;
    else if((d.tab[0][2] == vez && d.tab[1][1] == vez) && d.tab[2][0])
        return 1;
    return 0;
}

int entrada(void)/*Determina a entrada de dados do jogador por tecla para cada espaço livre no #*/
{
    int numero;
    do
    {
        printf("Escolha valores entre 0 e 8\n");
        scanf("%d",&numero);
        switch(numero)
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
                printf("Opcao invalida...escolha uma opcao valida!!!\n");
                break;
        }          
    }while(numero>0 || numero<10);
}

/*int humanojoga(void)
{
    int numero, vez;
    do
    {
        imprimetab();
        numero=entrada();
    }while(0==0); coloque uma condicao aqui

}*/

int imprimemenu(void)/*imprime menu*/
{
    int opt;
    printf("Bem vindo ao jogo da velha de NATAL!\n");
    printf("Escolha seu tipo de jogo: ");
    printf("\n1-Player vs Player \n2-Player vs PC \n3-PC vs PC\n");
    scanf("%d", &opt);
    switch(opt)/*opcoes para modo de jogo*/
    {
        case 1:
            printf("Player vs Player\n")
                break;
        case 2:
            printf("Player vs PC\n");
            break;
        case 3:
            printf("PC vs PC\n");
            break;
        default:
            printf("ERRO. Obrigado por jogar!\n");
            return 0;
    }
    return 0;
}

char start(void)/*Seleciona qm ira fazer a primeira jogada*/
{
    char r;

    printf("\nVoce quer começar jogando?\n s-sim\nn-nao\n");
    do
    {
        r=getchar();       
    }while(r=='\n' || (r!= 's' && r!='n'));

    return r;
}

int humanoVShumano(void)
{
    printf("O primeiro Player sera X e o segundo Player sera O\n");
}

int humanoVSpc(void)
{
    imprimemenunivel();
    start();
    printf("O primeiro Player sera X e o segundo Player sera O\n");    
}

int pcVSpc(void)/*modo de jogo pc vs pc*/
{
    int x,y,r=1,jogada=0;

    imprimemenunivel();
    printf("O primeiro Player sera X e o segundo Player sera O\n");

    do
    {
        if(vez==1)
        {
            printf("\nJogador 1:\n");
            x=geradordenumeros();
            y=geradordenumeros();
            if(d.tab[x][y]==0)
                d.tab[x][y] = 1;
            jogada=jogada+1;
        }
        else
        {
            printf("\nJogador 2:\n");
            x=geradordenumeros();
            y=geradordenumeros();
            if(d.tab[x][y]==0)
                d.tab[x][y] = 2;
            jogada=jogada+1;
        }
        vez=vez*-1;
        imprimetab();

    }while(jogada<9);

    return 0;
}

int geradordenumeros(void)
{
    int x;

    x = rand()%3;

    return x;
}


