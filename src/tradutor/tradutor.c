#include "./tradutor.h"

typedef enum {
    OPERACAO,
    NUMERO,

    MEMORIA,
    VIRGULA,
    PIPE,
    PAREN_OPEN,
    PAREN_CLOSE,
    MENOS,
    DOIS_PONTOS,
    VAZIO,
    MAIS
} SimbolosEnum;

typedef struct {
    SimbolosEnum tipo;
    char valor[128];
} Simbolo;

typedef enum {
    MULTIVALORADO,
    UNICO
} FuncaoMemoriaEnum;

typedef struct {
    FuncaoMemoriaEnum tipo;
    int valor;
    char posicao;
} ResultadoParseMemoria;

static Simbolo proximo_simbolo(char **linha);
static Simbolo peek_simbolo(char *linha);
static bool e_numero(char *str);
static Simbolo except_proximo_simbolo(char **linha, SimbolosEnum tipo, int num_linha);
static void compilar_linha_configuracao(char *linha, CPU *cpu, int num_linha) ;
static void compilar_linha(char *linha, Memoria *mem, int num_linha);
static void compilar_secao_configuracao(FILE *in, CPU *cpu);
static void compilar_secao_dados(FILE *in, Memoria *mem);
static void compilar_secao_programa(FILE *in, Memoria *mem);
static long parse_numero(char **linha, int num_linha);
static char parse_range(char **linha, int num_linha);
static ResultadoParseMemoria parse_memoria(char **linha, int num_linha);
static ResultadoParseMemoria except_memoria(char **linha, int num_linha, FuncaoMemoriaEnum tipo);
static ResultadoParseMemoria except_memoria_MOD(char **linha, int num_linha);

static char charhigh(char c);
static char fpeek(FILE *f);

//-Funcoes-------------------------------------------------------------------------------------------------------------------

void compilar_para_arquivo(char *in, char *out, int tamanho, int tamanho_dados) {
    FILE *f = fopen(in, "r");
    if (!f) RAISE("Arquivo '%s' não encontrado", in);
    FILE *f_out = fopen(out, "w");
    if (!f_out) RAISE("Arquivo '%s' não encontrado", out);

    Memoria *mem = memoria_criar(tamanho, tamanho_dados);

    compilar_para_memoria(f, mem);
    memoria_para_arquivo(f_out, mem);

    fclose(f);
    fclose(f_out);
}

void compilar_para_memoria(FILE *in, Memoria *mem) {
    if (mem == NULL) RAISE("Memoria não pode ser nula");

    compilar_secao_dados(in, mem);
    compilar_secao_programa(in, mem);
}

void compilar_para_IAS(FILE *in, IAS *ias) {
    if (ias == NULL) RAISE("IAS não pode ser nulo");
    if (ias->memoria == NULL) RAISE("Memoria não pode ser nula");
    if (ias->cpu == NULL) RAISE("cpu não pode ser nula");

    compilar_secao_configuracao(in, ias->cpu);
    compilar_secao_dados(in, ias->memoria);
    compilar_secao_programa(in, ias->memoria);
}

//-Funcoes estaticas---------------------------------------------------------------------------------------------------------

static void compilar_secao_configuracao(FILE *in, CPU *cpu) {
    char linha[128] = "\0";
    int n = 0;

    while (n < NUM_INSTRUCOES) {
        linha[0] = fpeek(in);
        linha[1] = '\0';
        if (e_numero(linha)) break;
        
        fgets(linha, 128, in);
        compilar_linha_configuracao(linha, cpu, n);

        n++;
    }
}

static void compilar_secao_dados(FILE *in, Memoria *mem) {
    for (int i = 0; i < mem->tamanho_dados; i++) {
        int64_t dado = 0;
        if (fscanf(in, "%li", &dado) == EOF) RAISE("Erro ao ler dado na posição %d", i);
        
        bool negativo = dado < 0;
        dado = llabs(dado);
        dado &= (MASK >> 1);
        dado |= (negativo ? (1ll << 39): 0);

        memoria_escrever(mem, i, dado);

        if (fpeek(in) != '\n') break;
    }    
}

static void compilar_secao_programa(FILE *in, Memoria *mem) {
    char linha[128] = "\0";
    int op_len = 0;
    char c = '\0';
    int i = mem->tamanho_dados;
    bool fim = false;

    while (!fim) {
        c = charhigh(fgetc(in));
        
        if (c == '\n' || c == EOF) {
            if (c == EOF) fim = true;

            compilar_linha(linha, mem, i++);
            op_len = 0;
        } else if (c == ' ') {
            if (op_len > 0 && linha[op_len - 1] != ' ') {
                linha[op_len++] = ' ';
            }
        } else {
            linha[op_len++] = c;
        }

        linha[op_len] = '\0';
    }
}

static void compilar_linha_configuracao(char *linha, CPU *cpu, int num_linha) {
    char *nome_operacao = except_proximo_simbolo(&linha, OPERACAO, num_linha).valor;
    except_proximo_simbolo(&linha, DOIS_PONTOS, num_linha);
    long num = parse_numero(&linha, num_linha);

    if (strcmp(nome_operacao, "ADD") == 0) {
        CPU_inserir_configuracao(linha, OP_ADD, num);
    }
}

static void compilar_linha(char *linha, Memoria *mem, int num_linha) {
    char *nome_operacao = except_proximo_simbolo(&linha, OPERACAO, num_linha).valor;    
    num_linha = (num_linha - mem->tamanho_dados) / 2 + mem->tamanho_dados;

    if (strcmp(nome_operacao, "LSH") == 0 || strcmp(nome_operacao, "RSH") == 0 || strcmp(nome_operacao, "EXIT") == 0) {
        if (nome_operacao[0] == 'L')
            memoria_adicionar_instrucao(mem, OP_LSH, 0, num_linha);
        else if (nome_operacao[0] == 'R')
            memoria_adicionar_instrucao(mem, OP_RSH, 0, num_linha);
        else
            memoria_adicionar_instrucao(mem, OP_EXIT, 0, num_linha);
    }

    if (strcmp(nome_operacao, "LOAD") == 0) {
        Simbolo simbolo_a_seguir = peek_simbolo(linha);

        if (simbolo_a_seguir.tipo == OPERACAO && strcmp(simbolo_a_seguir.valor, "MQ") == 0) {
            proximo_simbolo(&linha);
            Simbolo outro_argumento = proximo_simbolo(&linha);
            
            if (outro_argumento.tipo == VIRGULA) {
                ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);

                memoria_adicionar_instrucao(mem, OP_LOAD_MQ_M, memoria.valor, num_linha);
            } else if (outro_argumento.tipo == VAZIO) {    
                memoria_adicionar_instrucao(mem, OP_LOAD_MQ, 0, num_linha);
            } else {
                RAISE("Argumento do tipo '%i' nao e permitido em 'load mq'", outro_argumento.tipo);
            }
        } else if (simbolo_a_seguir.tipo == MENOS) {
            except_proximo_simbolo(&linha, MENOS, num_linha);

            Simbolo outro_argumento = peek_simbolo(linha);
            
            if (outro_argumento.tipo == PIPE) {
                ResultadoParseMemoria memoria = except_memoria_MOD(&linha, num_linha);
                
                memoria_adicionar_instrucao(mem, OP_LOAD_MENOS_MOD, memoria.valor, num_linha);
            } else if (outro_argumento.tipo == MEMORIA) {
                ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);
                
                memoria_adicionar_instrucao(mem, OP_LOAD_MENOS, memoria.valor, num_linha);
            } else {
                RAISE("Argumento do tipo '%i' nao e permitido em 'load -'", outro_argumento.tipo);
            }
        } else if (simbolo_a_seguir.tipo == PIPE) {
            ResultadoParseMemoria memoria = except_memoria_MOD(&linha, num_linha);
            
            memoria_adicionar_instrucao(mem, OP_LOAD_MOD, memoria.valor, num_linha);
        } else if (simbolo_a_seguir.tipo == MEMORIA) {
            ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);
            
            memoria_adicionar_instrucao(mem, OP_LOAD, memoria.valor, num_linha);
        }
    }

    if (strcmp(nome_operacao, "STOR") == 0) {
        ResultadoParseMemoria memoria = parse_memoria(&linha, num_linha);
            
        if (memoria.tipo == MULTIVALORADO) {
            if (memoria.posicao == 'L') 
                memoria_adicionar_instrucao(mem, OP_STOR_L, memoria.valor, num_linha);
            else if (memoria.posicao == 'R')
                memoria_adicionar_instrucao(mem, OP_STOR_R, memoria.valor, num_linha);
            else
                RAISE("posicionamento invalido para STOR");
        } else {
            memoria_adicionar_instrucao(mem, OP_STOR, memoria.valor, num_linha);
        }
    }

    if (strcmp(nome_operacao, "JUMP") == 0) {
        Simbolo simbolo_a_seguir = peek_simbolo(linha);

        if (simbolo_a_seguir.tipo == MAIS) {
            proximo_simbolo(&linha);

            ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, MULTIVALORADO);
            
            if (memoria.posicao == 'l')
                memoria_adicionar_instrucao(mem, OP_JUMP_COND_L, memoria.valor, num_linha);
            else
                memoria_adicionar_instrucao(mem, OP_JUMP_COND_R, memoria.valor, num_linha);
        } else {
            ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, MULTIVALORADO);
            
            if (memoria.posicao == 'l')
                memoria_adicionar_instrucao(mem, OP_JUMP_L, memoria.valor, num_linha);
            else
                memoria_adicionar_instrucao(mem, OP_JUMP_R, memoria.valor, num_linha);
        }
    }

    if (strcmp(nome_operacao, "ADD") == 0) {
        Simbolo simbolo_a_seguir = peek_simbolo(linha);

        if (simbolo_a_seguir.tipo == MEMORIA) {
            ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);

            memoria_adicionar_instrucao(mem, OP_ADD, memoria.valor, num_linha);
        } else if (simbolo_a_seguir.tipo == PIPE) {
            ResultadoParseMemoria memoria = except_memoria_MOD(&linha, num_linha);

            memoria_adicionar_instrucao(mem, OP_ADD_MOD, memoria.valor, num_linha);    
        } else {
            RAISE("Argumento do tipo '%i' nao e permitido em 'add'", simbolo_a_seguir.tipo);
        }
    }

    if (strcmp(nome_operacao, "SUB") == 0) {
        Simbolo simbolo_a_seguir = peek_simbolo(linha);

        if (simbolo_a_seguir.tipo == MEMORIA) {
            ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);

            memoria_adicionar_instrucao(mem, OP_SUB, memoria.valor, num_linha);
        } else if (simbolo_a_seguir.tipo == PIPE) {
            ResultadoParseMemoria memoria = except_memoria_MOD(&linha, num_linha);

            memoria_adicionar_instrucao(mem, OP_SUB_MOD, memoria.valor, num_linha);    
        } else {
            RAISE("Argumento do tipo '%i' nao e permitido em 'add'", simbolo_a_seguir.tipo);
        }
    }

    if (strcmp(nome_operacao, "MUL") == 0) {
        ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);
            
        memoria_adicionar_instrucao(mem, OP_MUL, memoria.valor, num_linha);
    }

    if (strcmp(nome_operacao, "DIV") == 0) {
        ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);
            
        memoria_adicionar_instrucao(mem, OP_DIV, memoria.valor, num_linha);
    }

    except_proximo_simbolo(&linha, VAZIO, num_linha);
}    

static Simbolo proximo_simbolo(char **linha) {
    Simbolo s = {0};
    int i = 0;

    for (; **linha == ' '; (*linha)++);

    for (; 
            **linha != ' '  &&
            **linha != '\n' &&
            **linha != '\0' &&
            **linha != ','  &&
            **linha != '|'  &&
            **linha != '('  &&
            **linha != ')'  &&
            **linha != '-'  &&
            **linha != ':'  &&
            **linha != '+'  ; 
            (*linha)++
        ) {
        s.valor[i] = **linha;
        s.valor[i+1] = '\0';
        i++;
    }

    if (i == 0) {
        switch (**linha) {
            case ',':
                s.tipo = VIRGULA;
                break;
            case '|':
                s.tipo = PIPE;
                break;
            case '(':
                s.tipo = PAREN_OPEN;
                break;
            case ')':
                s.tipo = PAREN_CLOSE;
                break;
            case '-':
                s.tipo = MENOS;
                break;
            case ':':
                s.tipo = DOIS_PONTOS;
                break;
            case '+':
                s.tipo = MAIS;
                break;
            default:
                s.tipo = VAZIO;
                break;
        }
        s.valor[0] = **linha;
        s.valor[1] = '\0';
        (*linha)++;
        return s;
    }

    if (strcmp(s.valor, "M") == 0) {
        s.tipo = MEMORIA;
        return s;
    }

    if (e_numero(s.valor)) s.tipo = NUMERO;
    else s.tipo = OPERACAO;

    return s;
}

static Simbolo peek_simbolo(char *linha) {
    return proximo_simbolo(&linha);
}

static bool e_numero(char *str) {
    size_t i = 0;
    for (i = 0; str[i] >= 48 && str[i] <= 57; i++);
    return i == strlen(str);
}

static Simbolo except_proximo_simbolo(char **linha, SimbolosEnum tipo, int num_linha) {
    Simbolo s = proximo_simbolo(linha);

    if (s.tipo != tipo) 
        RAISE("na linha '%i': Um simbolo deveria ser %i mas é %i", num_linha, tipo, s.tipo);

    return s;
}

static long parse_numero(char **linha, int num_linha) {
    return atol(except_proximo_simbolo(linha, NUMERO, num_linha).valor);
}

static char parse_range(char **linha, int num_linha) {
    ARGUMENTO num_inicio = parse_numero(linha, num_linha) & ARGUMENTO_MASK;
    except_proximo_simbolo(linha, DOIS_PONTOS, num_linha);
    ARGUMENTO num_final = parse_numero(linha, num_linha) & ARGUMENTO_MASK;

    if (num_inicio == 0 && num_final == 19) return 'l';
    if (num_inicio == 8 && num_final == 19) return 'L';
    if (num_inicio == 20 && num_final == 39) return 'r';
    if (num_inicio == 28 && num_final == 39) return 'R';

    RAISE("'%i:%i' nao e um range valido!", num_inicio, num_final);
}

static ResultadoParseMemoria parse_memoria(char **linha, int num_linha) {
    except_proximo_simbolo(linha, MEMORIA, num_linha);
    except_proximo_simbolo(linha, PAREN_OPEN, num_linha);

    ARGUMENTO arg = parse_numero(linha, num_linha) & ARGUMENTO_MASK;

    Simbolo proximo = proximo_simbolo(linha);
    if (proximo.tipo == VIRGULA) {
        char range = parse_range(linha, num_linha);
        except_proximo_simbolo(linha, PAREN_CLOSE, num_linha);

        return (ResultadoParseMemoria){
            .tipo = MULTIVALORADO,
            .valor = arg,
            .posicao = range
        };
    } else if (proximo.tipo == PAREN_CLOSE) {
        return (ResultadoParseMemoria){
            .tipo = UNICO,
            .valor = arg,
            .posicao = 0
        };
    }
    
    RAISE("Declaracao invalida de funcao de memoria");
}

static ResultadoParseMemoria except_memoria(char **linha, int num_linha, FuncaoMemoriaEnum tipo) {
    ResultadoParseMemoria mem = parse_memoria(linha, num_linha);

    if (mem.tipo != tipo)
        RAISE("memoria do tipo errada passada");

    return mem;
}

static ResultadoParseMemoria except_memoria_MOD(char **linha, int num_linha) {
    except_proximo_simbolo(linha, PIPE, num_linha);
    ResultadoParseMemoria mem = except_memoria(linha, num_linha, UNICO);
    except_proximo_simbolo(linha, PIPE, num_linha);

    return mem;
}

static char charhigh(char c) {
    return c >= 'a' && c <= 'z' ? c - 32 : c;  
}

static char fpeek(FILE *f) {
    char c;

    c = fgetc(f);
    ungetc(c, f);

    return c;
}