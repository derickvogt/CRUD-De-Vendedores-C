#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura de um vendedor
struct Vendedor
{
    //Atributos de Vendedor
    char nome[101];
    unsigned long int matricula;
    float salario;
    float venda1;
    float venda2;
    float venda3;
    float venda4;
    float totalVendasMes;
    int faltas;
    char nivelHierarquico[7];
    int frequencia;
    FILE *arquivo;
};

//Declaração das Funções

void atualizarDadosVendedor(struct Vendedor *array, int matricula, int ultimaPosicao, FILE *reg);
int cadastrarVendedor(struct Vendedor *array, int tamanhoArray, int ultimaPosicao, FILE *reg);
int faltas();
int indexOf(int matricula, int ultimaPosicao, struct Vendedor *array);
void linha(int quantidade, int bool);
void listarUmMembro(struct Vendedor *array, int i);
int listarVendedores(struct Vendedor *array, int ultimaPosicao);
int listarVendedoresFrequenciaMaior(struct Vendedor *array, int ultimaPosicao, int frequencia, char *hierarquia);
int listarVendedoresFrequenciaMenor(struct Vendedor *array, int ultimaPosicao, int frequencia, char *hierarquia);
int removerVendedor(int matricula, struct Vendedor *array, int ultimaPosicao, int tamanhoArray, FILE *reg);
void salarioHierarquiaFrequencia(struct Vendedor *array, int index);
void consultarDadosVendedor(struct Vendedor *array, int matricula, int ultimaPosicao);
void mensagem(char *texto);
void limparTela(void);
char menuPrincipal(void);
void limparBuffer(void);
void gerarArquivo(struct Vendedor *array, int index, FILE *reg);
int verificarQuantidadeArquivos(FILE *reg);
void sobrescreverReg(struct Vendedor *array, int ultimaPosicao, FILE *reg);
int lerArquivos(struct Vendedor *array, int ultimaPosicao, FILE *reg);
float faixaPorcentagem(char *hierarqia);
void removerArquivo(struct Vendedor *array, int index);

//Declaração de Variaveis Globais
float salario = 1540;
float porcentagemSenior = 0.15;
float porcentagemPleno = 0.1;
float porcentagemJunior = 0.05;

int main()
{

    //Atributos

    const FILE *reg;
    unsigned long int entradaMatricula = 0;
    int contador = 0;
    int tamanhoArray = verificarQuantidadeArquivos(reg) + 15;

    struct Vendedor vendedores[tamanhoArray];
    int ultimaPosicao = lerArquivos(vendedores, ultimaPosicao, reg);

    printf("\n\n");

    while (1)
    {

        switch (menuPrincipal())
        {

        case 'A':
        {
            //Cadastrar Vendedor
            linha(50, 1);
            ultimaPosicao = cadastrarVendedor(vendedores, tamanhoArray, ultimaPosicao, reg);
            linha(50, 1);
            break;
        }

        case 'B':
        {
            //Remover Vendedor
            linha(50, 1);
            printf("Informe a matricula: ");
            scanf("%lu", &entradaMatricula);
            ultimaPosicao = removerVendedor(entradaMatricula, vendedores, ultimaPosicao, tamanhoArray, reg);
            entradaMatricula = 0;
            linha(50, 1);
            break;
        }

        case 'C':
        {
            //Atualizar Dados Vendedor
            printf("Informe a matricula do vendedor: \n");
            scanf("%lu", &entradaMatricula);

            limparTela();
            linha(50, 1);

            atualizarDadosVendedor(vendedores, entradaMatricula, ultimaPosicao, reg);
            entradaMatricula = 0;
            linha(50, 1);
            limparTela();
            break;
        }

        case 'D':
        {
            //Consultar Dados Vendedor
            printf("Informe a matricula do vendedor: ");
            scanf("%lu", &entradaMatricula);

            limparTela();
            linha(50, 1);
            consultarDadosVendedor(vendedores, entradaMatricula, ultimaPosicao);
            linha(50, 1);

            entradaMatricula = 0;
            break;
        }

        case 'M':
        {
            //Listar Vendedores
            linha(50, 1);
            contador = listarVendedores(vendedores, ultimaPosicao);

            if (contador == 0)
            {
                mensagem("Nao Tem Vendedores Cadastrados");
            }
            contador = 0;
            linha(50, 1);
            break;
        }

        case 'N':
        {
            //Listar todos os vendedores Senior
            linha(50, 1);
            contador = listarVendedoresFrequenciaMenor(vendedores, ultimaPosicao, 101, "Senior");

            if (contador == 0)
            {
                mensagem("Nao Tem Vendedores Senior Cadastrados");
            }
            contador = 0;
            linha(50, 1);
            break;
        }

        case 'O':
        {
            //Listar todos os vendedores Pleno
            linha(50, 1);
            contador = listarVendedoresFrequenciaMenor(vendedores, ultimaPosicao, 101, "Pleno");
            if (contador == 0)
            {
                mensagem("Nao Tem Vendedores Pleno Cadastrados");
            }
            contador = 0;
            linha(50, 1);

            break;
        }

        case 'P':
        {
            //Listar todos os vendedores Junior
            linha(50, 1);
            contador = listarVendedoresFrequenciaMenor(vendedores, ultimaPosicao, 101, "Junior");

            if (contador == 0)
            {
                mensagem("Nao Tem Vendedores Junior Cadastrados");
            }
            contador = 0;
            linha(50, 1);
            break;
        }

        case 'Q':
        {
            //Listar todos os vendedores maiores que 80%
            linha(50, 1);
            contador = listarVendedoresFrequenciaMaior(vendedores, ultimaPosicao, 80, "Senior");
            contador += listarVendedoresFrequenciaMaior(vendedores, ultimaPosicao, 80, "Pleno");
            contador += listarVendedoresFrequenciaMaior(vendedores, ultimaPosicao, 80, "Junior");

            if (contador == 0)
            {
                mensagem("Nao Tem Vendedores Com a Frequencia Menor que 80%");
            }
            contador = 0;
            linha(50, 1);
            break;
        }

        case 'R':
        {
            //Listar todos os vendedores com a frequencia menor que 60%

            linha(50, 1);
            if (ultimaPosicao == -1)
            {
                mensagem("Nao tem vendedores cadastrados");
            }
            else
            {
                contador = listarVendedoresFrequenciaMenor(vendedores, ultimaPosicao, 60, "Junior");
                contador += listarVendedoresFrequenciaMenor(vendedores, ultimaPosicao, 60, "Pleno");
                contador += listarVendedoresFrequenciaMenor(vendedores, ultimaPosicao, 60, "Senior");

                if (contador == 0)
                {
                    mensagem("Nao Tem Vendedores com a Frequencia Menor que 60%");
                }
            }
            linha(50, 1);
            contador = 0;
            break;
        }
        }
    }
}

//Cadastra um vendedor se o numero de matricula nao estiver sido cadastrada
//anteriormente
int cadastrarVendedor(struct Vendedor *array, int tamanhoArray, int ultimaPosicao, FILE *reg)
{

    unsigned long int matricula = 0;

    if (ultimaPosicao + 1 < tamanhoArray)
    {

        //Validação do numero de matricula
        printf("\nInforme a matricula do Vendedor: ");
        scanf("%lu", &matricula);

        if (indexOf(matricula, ultimaPosicao, array) != -1)
        {
            mensagem("Vendedor Ja Cadastrado, Operacao Encerrada");
            return ultimaPosicao;
        }
        ultimaPosicao++;

        array[ultimaPosicao].matricula = matricula;

        printf("\nInforme o nome do vendedor: ");
        limparBuffer();
        gets(array[ultimaPosicao].nome);
        printf("Informe as vendas da primeira semana: ");
        scanf("%f", &array[ultimaPosicao].venda1);

        printf("Informe as vendas da segunda semana: ");
        scanf("%f", &array[ultimaPosicao].venda2);

        printf("Informe as vendas da terceira semana: ");
        scanf("%f", &array[ultimaPosicao].venda3);

        printf("Informe as vendas da quarta semana: ");
        scanf("%f", &array[ultimaPosicao].venda4);

        //Validação das faltas
        array[ultimaPosicao].faltas = faltas();

        salarioHierarquiaFrequencia(array, ultimaPosicao);

        gerarArquivo(array, ultimaPosicao, reg);
        mensagem("Vendedor Cadastrado com Sucesso!");
        return ultimaPosicao;
    }
    else
    {
        limparTela();
        mensagem("Espaco Cheio! Vendedor nao Cadastrado!");
    }
}

//Remove um vendedor baseado em sua matricula e realoca os outros vendedores para liberar espaço
int removerVendedor(int matricula, struct Vendedor *array, int ultimaPosicao, int tamanhoArray, FILE *reg)
{
    int i = indexOf(matricula, ultimaPosicao, array);
    int entrada = 0; // recebe a entrada do usuario
    //lista vazia
    if (ultimaPosicao == -1)
    {
        mensagem("Nao Tem Vendedores Cadastrados");
        return ultimaPosicao;
    }

    //Matricula nao encontrada
    if (i == -1)
    {
        mensagem("Vendedor Nao Cadastrado!");
        return ultimaPosicao;
    }
    else
    {
        //O elemento existe
        do
        {
            listarUmMembro(array, i);
            printf("\n\nTem certeza que deseja excluir o vendedor?\n\n");
            printf("1 - Sim\n");
            printf("2 - Nao\n");
            printf("\nOpcao: ");

            scanf("%d", &entrada);

            switch (entrada)
            {
            case 1:
            {

                //O elemento esta no fim
                if (i == tamanhoArray - 1)
                {
                    sobrescreverReg(array, ultimaPosicao, reg);
                    ultimaPosicao--;
                    removerArquivo(array, i);

                    mensagem("O Vendedor foi Removido com Sucesso!");

                    return ultimaPosicao;
                }

                //o elemento nao esta no inicio e nem no fim
                if (i != tamanhoArray - 1)
                {
                    removerArquivo(array, i);
                    for (i; i < ultimaPosicao; i++)
                    {
                        array[i] = array[i + 1];
                    }
                    sobrescreverReg(array, ultimaPosicao, reg);
                    ultimaPosicao--;
                    mensagem("O Vendedor foi Removido com Sucesso!");
                    return ultimaPosicao;
                }
            }

            case 2:
            {
                return ultimaPosicao;
            }

            default:
            {
                printf("Opcao invalida\n");
            }
            }
        } while (entrada != 1 || entrada != 2);
    } //Fim do else
}

//Altera os dados de um vendedor a partir de sua matricula
void atualizarDadosVendedor(struct Vendedor *array, int matricula, int ultimaPosicao, FILE *reg)
{
    int i = indexOf(matricula, ultimaPosicao, array);
    int entrada = 0; //variável que receberá as entradas de stdin
    if (i != -1)
    {

        do
        {

            listarUmMembro(array, i);

            printf("\n");

            printf("\nO que deseja fazer?\n\n");
            printf("1 -  > Alterar o nome do Vendedor\n");
            printf("2 -  > Alterar o valor das vendas da primeira semana\n");
            printf("3 -  > Alterar o valor das vendas da segunda semana\n");
            printf("4 -  > Alterar o valor das vendas da terceira semana\n");
            printf("5 -  > Alterar o valor das vendas da quarta semana\n");
            printf("6 -  > Alterar o numero de faltas\n");
            printf("0 -  > Voltar ao menu\n");
            printf("\nOpcao: ");
            scanf("%d", &entrada);

            switch (entrada)
            {
            case 0:
            {

                break;
            }
            case 1:
            {
                //Alterar nome do vendedor
                printf("\nInforme o novo nome do Vendedor: ");
                limparBuffer();
                gets(array[i].nome);
                limparTela();
                mensagem("O Nome do Vendedor Foi Alterado Com Sucesso!");
                break;
            }
            case 2:
            {
                //Alterar vendas da primeira semana
                printf("\nInforme o novo valor das vendas da primeira semana: ");
                scanf("%f", &array[i].venda1);
                limparTela();
                mensagem("As Vendas da Primeira Semana Foi Alterada Com Sucesso");
                break;
            }
            case 3:
            {
                //alterar dados da segunda semana
                printf("\nInforme o novo valor das vendas da segunda semana: ");
                scanf("%f", &array[i].venda2);
                limparTela();
                mensagem("As Vendas da Segunda Semana Foi Alterada Com Sucesso!");
                break;
            }
            case 4:
            {
                //alterar dados da terceira semana
                printf("\nInforme o novo valor das vendas da terceira semana: ");
                scanf("%f", &array[i].venda3);
                limparTela();
                mensagem("As Vendas da Terceira Semana Foi Alterada Com Sucesso!");
                break;
            }
            case 5:
            {
                //alterar dados da quarta semana
                printf("\nInforme o novo valor das vendas da quarta semana: ");
                scanf("%f", &array[i].venda4);
                limparTela();
                mensagem("As Vendas da Quarta Semana Foi Alterada Com Sucesso!");
                break;
            }
            case 6:
            {
                //altera o número de faltas
                array[i].faltas = faltas();
                limparTela();
                mensagem("Faltas Alteradas Com Sucesso!");
                break;
            }

            default:
            {
                printf("Opcao Invalida");
            }
            }
            salarioHierarquiaFrequencia(array, i);
            gerarArquivo(array, i, reg);
        } while (entrada != 0);
    }
    else
    {
        limparTela();
        mensagem("Vendedor Nao Cadastrado!");
    }
}

void consultarDadosVendedor(struct Vendedor *array, int matricula, int ultimaPosicao)
{
    int i = indexOf(matricula, ultimaPosicao, array);

    if (i != -1)
    {
        listarUmMembro(array, i);
    }
    else
    {
        mensagem("O Vendedor Nao Esta Cadastrado!");
    }
}

//Lista todos os vendedores usando um for
int listarVendedores(struct Vendedor *array, int ultimaPosicao)
{
    int contador = 0;
    int i;

    for (i = 0; i <= ultimaPosicao; i++)
    {
        listarUmMembro(array, i);
        contador++;
    }

    return contador;
}

//Lista os vendedores baseado no tipo de vendedor (junior, pleno e senior) com a frequencia menor do que a especificada
int listarVendedoresFrequenciaMenor(struct Vendedor *array, int ultimaPosicao, int frequencia, char *hierarquia)
{
    int i;
    int contador = 0;

    for (i = 0; i <= ultimaPosicao; i++)
    {
        if (strcmp(array[i].nivelHierarquico, hierarquia) == 0 && array[i].frequencia < frequencia)
        {
            printf("\n");
            listarUmMembro(array, i);
            contador++;
        }
    }
    return contador;
}

int listarVendedoresFrequenciaMaior(struct Vendedor *array, int ultimaPosicao, int frequencia, char *hierarquia)
{
    int i;
    int contador = 0;
    for (i = 0; i <= ultimaPosicao; i++)
    {
        if (strcmp(array[i].nivelHierarquico, hierarquia) == 0 && array[i].frequencia > frequencia)
        {

            listarUmMembro(array, i);

            contador++;
        }
    }
    return contador;
}

//Procura se existe uma matricula passada no array de vendedores
int indexOf(int matricula, int ultimaPosicao, struct Vendedor *array)
{
    int i;
    for (i = 0; i <= ultimaPosicao; i++)
    {
        if (matricula == array[i].matricula)
        {
            return i;
        }
    }
    return -1;
}

//cria linhas
void linha(int quantidade, int bool)
{
    if (bool)
    {
        printf("\n\n");
    }

    for (int i = 0; i < quantidade; i++)
    {
        printf("-");
    }

    if (bool)
    {
        printf("\n\n");
    }
}

//Atribui um quantidade faltas válida a um vendedor
int faltas()
{
    int faltas = 0;
    do
    {
        printf("Informe a quantidade de faltas do vendedor: ");
        scanf("%d", &faltas);
        if (faltas < 0 || faltas > 26)
        {
            printf("\nEntrada invalida, informe o numero de faltas entre 0 e 26\n\n");
        }
    } while (faltas < 0 || faltas > 26);

    return faltas;
}

//Calcula o salario, a frequencia e aplica a hierarquia do vendedor
void salarioHierarquiaFrequencia(struct Vendedor *array, int index)
{
    int soma = 0;

    soma = (array[index].venda1 + array[index].venda2 +
            array[index].venda3 + array[index].venda4);

    if (soma > 10000)
    {
        strcpy(array[index].nivelHierarquico, "Senior");
        array[index].salario = salario + porcentagemSenior * (soma / 4);
    }
    else if (soma >= 5000 && soma <= 10000)
    {
        strcpy(array[index].nivelHierarquico, "Pleno");
        array[index].salario = salario + porcentagemPleno * (soma / 4);
    }
    else
    {
        strcpy(array[index].nivelHierarquico, "Junior");
        array[index].salario = salario + porcentagemJunior * (soma / 4);
    }

    array[index].frequencia = (((26 - array[index].faltas) * 100) / 26);
    array[index].totalVendasMes = soma;
}

//Lista apenas 1 vendedor
void listarUmMembro(struct Vendedor *array, int i)
{
    printf("\n");
    printf("\nMatricula: %lu", array[i].matricula);
    printf("\nNome do Vendedor: %s", array[i].nome);
    printf("\nSalario: R$ %.2f", array[i].salario);
    printf("\nVendas da primeira semana: R$ %.2f", array[i].venda1);
    printf("\nVendas da segunda semana: R$ %.2f", array[i].venda2);
    printf("\nVendas da terceira semana: R$ %.2f", array[i].venda3);
    printf("\nVendas da quarta semana: R$ %.2f", array[i].venda4);
    printf("\nTotal de Vendas no Mes R$ %.2f", array[i].totalVendasMes);
    printf("\nFaltas: %d", array[i].faltas);
    printf("\nFrequencia: %d%%", array[i].frequencia);
    printf("\nNivel Hierarquico: %s", array[i].nivelHierarquico);
    printf("\n");
}

void mensagem(char *texto)
{

    int tamanho1 = strlen(texto);
    char *string = (char *)(malloc((tamanho1 + 12) * sizeof(char)));

    //Concatenação da string Texto
    strcpy(string, "| -> ");
    strcat(string, texto);
    strcat(string, " <- |");

    //Impressão
    printf("\n");
    linha(strlen(string), 0);
    printf("\n");
    printf("%s", string);
    printf("\n");
    linha(strlen(string), 0);
    printf("\n");

    free(texto);
    free(string);
}

//Função que limpa a tela
void limparTela(void)
{
    system("clear||cls");
}

//Função que limpa o buffer
void limparBuffer(void)
{
    char caracter;
    while (((caracter = getchar()) != '\n' && caracter != EOF))
    {
    }
}

char menuPrincipal(void)
{
    char letra = "";
    int opcao = 0;

    do
    {

        printf("\nMenu\n\n");
        printf("1 -  > Cadastrar Vendedor\n");
        printf("2 -  > Remover Vendedor\n");
        printf("3 -  > Atualizar Dados do Vendedor\n");
        printf("4 -  > Consultar Dados do Vendedor\n");
        printf("5 -  > Relatorio de Vendas\n");
        printf("0 -  > Sair\n");

        printf("\nOpcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            //Adicionar Vendedor
            return 'A';
        }
        case 2:
        {
            //Remover Vendedor
            return 'B';
        }
        case 3:
        {
            //Atualizar Dados do Vendedor
            return 'C';
        }
        case 4:
        {
            //ConsultarDados do Vendedor
            return 'D';
        }
        case 5:
        {
            do
            {
                if (letra != 'V')
                {
                    limparTela();
                }

                //Relatórios de Vendas
                printf("\nMenu\n\n");
                printf("> 5 - Relatorio de Vendas\n\n");
                printf("    1 -  > Listar Todos os Vendedores Cadastrados\n");
                printf("    2 -  > Listar Todos os Vendedores Senior\n");
                printf("    3 -  > Listar Todos os Vendedores Pleno\n");
                printf("    4 -  > Listar Todos os Vendedores Junior\n");
                printf("    5 -  > Listar Todos os Vendedores com Frequencia Maior que 80%%\n");
                printf("    6 -  > Listar Todos os Vendedores com Frequencia Menor que 60%%\n");
                printf("    0 -  > Voltar ao Menu Anterior");

                printf("\n\nOpcao: ");
                scanf("%d", &opcao);

                switch (opcao)
                {
                case 1:
                {
                    //Listar Todos os Vendedores Cadastrados
                    return 'M';
                }
                case 2:
                    //Listar Todos os Vendedores Senior
                    return 'N';
                    {
                    }
                case 3:
                    //Listar Todos os Vendedores Pleno
                    return 'O';
                    {
                    }
                case 4:
                    //Listar Todos os Vendedores Junior
                    return 'P';
                    {
                    }
                case 5:
                {
                    //Listar Todos os Vendedores com Frequencia Maior que 80%
                    return 'Q';
                }
                case 6:
                {
                    //Listou Todos os Vendedores com Frequencia Menor que 60%%\n");
                    return 'R';
                }
                case 0:
                {
                    limparTela();
                    break;
                }

                default:
                {
                    limparTela();
                    letra = 'V';
                    printf("\nOpcao Invalida\n");
                }
                }

            } while (opcao != 0);

            opcao = -1;

            break;
        }

        case 0:
        {
            printf("\nPrograma Finalizado com Sucesso!\n");
            exit(0);
        }

        default:
        {
            limparTela();
            printf("\n");
            printf("Opcao Invalida\n");
        }
        }

    } while (opcao != 0);
}

//Gera um arquivo com os dados do vendedor
void gerarArquivo(struct Vendedor *array, int index, FILE *reg)
{
    char string[100];
    strcpy(string, "");
    sprintf(string, "%lu", array[index].matricula);
    strcat(string, ".dat");
    array[index].arquivo = fopen(string, "wb");

    if (array[index].arquivo != NULL)
    {
        fwrite(&array[index], sizeof(struct Vendedor), 1, array[index].arquivo);

        fclose(array[index].arquivo);
    }

    reg = fopen("reg.txt", "a");

    if (reg != NULL)
    {
        fprintf(reg, "%lu\n", array[index].matricula);
        fclose(reg);
    }
}

//Apaga um arquivo do sistema
void removerArquivo(struct Vendedor *array, int index)
{
    char string[100];
    strcpy(string, "");
    sprintf(string, "%lu", array[index].matricula);
    strcat(string, ".dat");
    remove(string);
}

//Verifica a quantidade de vendedores salvos.
int verificarQuantidadeArquivos(FILE *reg)
{

    unsigned long int matricula = 0;
    int contador = 0;

    reg = fopen("reg.txt", "r");

    if (reg != NULL)
    {
        while (fscanf(reg, "%lu\n", &matricula) != EOF)
        {
            contador++;
        }
    }

    fclose(reg);
    return contador;
}

void sobrescreverReg(struct Vendedor *array, int ultimaPosicao, FILE *reg)
{
    int matricula = 0;
    char string[100];
    strcpy(string, "");

    //Abrindo reg

    reg = fopen("reg.txt", "w");

    if (reg != NULL)
    {
        for (int i = 0; i < ultimaPosicao; i++)
        {
            fprintf(reg, "%lu\n", array[i].matricula);
        }
        //fechamento de reg
        fclose(reg);
    }
}

int lerArquivos(struct Vendedor *array, int ultimaPosicao, FILE *reg)
{
    ultimaPosicao = 0;
    unsigned int matricula = 0;
    char string[100];
    FILE *arquivo;

    //abrindo reg

    reg = fopen("reg.txt", "r");

    if (reg != NULL)
    {
        while (fscanf(reg, "%d\n", &matricula) != EOF)
        {
            //Transformando o valor de cada linha de reg em uma string
            strcpy(string, "");
            sprintf(string, "%u", matricula);
            strcat(string, ".dat");

            //Abrindo o arquivo que referenciado em reg
            arquivo = fopen(string, "rb");

            //Verificando se o arquivo existe
            if (arquivo != NULL)
            {

                fread(&array[ultimaPosicao], sizeof(struct Vendedor), 1, arquivo);
                fclose(arquivo);
                array[ultimaPosicao].arquivo = arquivo;
                ultimaPosicao++;
            }
        }

        //fechamento do arquivo
        fclose(reg);
        sobrescreverReg(array, ultimaPosicao, reg);
        ultimaPosicao--;
        return ultimaPosicao;
    }
    else
    {
        return -1;
    }
}
