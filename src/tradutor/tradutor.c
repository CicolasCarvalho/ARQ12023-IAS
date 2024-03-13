#include "./tradutor.h"

#define MOD_PIPE    (char)0b0001
#define MOD_MENOS   (char)0b0010
#define MOD_M       (char)0b0100
#define MOD_MAIS    (char)0b1000

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
static void processar_modificador(char **linha, char *modificadores, SimbolosEnum simb, char tipo_mod);

static char charhigh(char c);
static char fpeek(FILE *f);
static char *simtoa(SimbolosEnum simb);

//-Funcoes-------------------------------------------------------------------------------------------------------------------

void compilar_para_arquivo(char *in, char *out, int tamanho, int tamanho_dados) {
    FILE *f = fopen(in, "r");
    if (!f) {
        RAISE("Arquivo '%s' não encontrado", in);
    }
    FILE *f_out = fopen(out, "w");
    if (!f_out) {
        RAISE("Arquivo '%s' não encontrado", out);
    }

    Memoria *mem = memoria_criar(tamanho, tamanho_dados);

    PRINT("COMPILAR PARA MEMORIA INICIADO!");
    compilar_para_memoria(f, mem);
    memoria_para_arquivo(f_out, mem);

    memoria_free(mem);
    fclose(f);
    fclose(f_out);
}

void compilar_para_memoria(FILE *in, Memoria *mem) {
    if (mem == NULL) {
        RAISE("Memoria não pode ser nula");
    }

    compilar_secao_configuracao(in, NULL);
    compilar_secao_dados(in, mem);
    compilar_secao_programa(in, mem);
}

void compilar_para_IAS(FILE *in, IAS *ias) {
    if (ias == NULL) {
        RAISE("IAS não pode ser nulo");
    }
    if (ias->memoria == NULL) {
        RAISE("Memoria não pode ser nula");
    }
    if (ias->cpu == NULL) {
        RAISE("cpu não pode ser nula");
    }

    compilar_secao_configuracao(in, ias->cpu);
    compilar_secao_dados(in, ias->memoria);
    compilar_secao_programa(in, ias->memoria);
}

//-Funcoes estaticas---------------------------------------------------------------------------------------------------------

static void compilar_secao_configuracao(FILE *in, CPU *cpu) {
    char linha[128] = "\0";
    int n = 0;
    int op_len = 0;
    char c;
    bool fim = false;

    while (!fim && n < NUM_INSTRUCOES) {
        c = charhigh((char)fgetc(in));
        
        if (c == '\n' || c == EOF) {
            fim = (bool)(c == EOF);
            
            compilar_linha_configuracao(linha, cpu, n++);
            op_len = 0;

            linha[0] = fpeek(in);
            linha[1] = '\0';

            if (e_numero(linha)) break;
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

static void compilar_secao_dados(FILE *in, Memoria *mem) {
    for (int i = 0; i < mem->tamanho_dados; i++) {
        int64_t dado = 0;
        if (fscanf(in, "%li", &dado) == EOF) {
            RAISE("Erro ao ler dado na posição %d", i);
        }

        PALAVRA dadoi40 = i64toi40(dado);

        memoria_escrever(mem, (int16_t)i, dadoi40, MASK);

        if (fpeek(in) != '\n') break;
        else fgetc(in);
    }
}

static void compilar_secao_programa(FILE *in, Memoria *mem) {
    char linha[128] = "\0";
    int op_len = 0;
    char c;
    int i = mem->tamanho_dados;
    bool fim = false;

    while (!fim) {
        c = charhigh((char)fgetc(in));
        
        if (c == '\n' || c == EOF) {
            fim = (bool)(c == EOF);

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
    char modificadores = 0,
          num;
    INSTRUCAO operacao = 0;

    processar_modificador(&linha, &modificadores, MAIS, MOD_MAIS);
    processar_modificador(&linha, &modificadores, MENOS, MOD_MENOS);
    processar_modificador(&linha, &modificadores, PIPE, MOD_PIPE);
    processar_modificador(&linha, &modificadores, MEMORIA, MOD_M);
    
    if (strcmp(nome_operacao, "LSH") == 0) {
        operacao = OP_LSH;
    
    } else if (strcmp(nome_operacao, "RSH") == 0) {
        operacao = OP_RSH;
    
    } else if (strcmp(nome_operacao, "LOADM") == 0) {
        operacao = OP_LOAD_MQ;

    } else if (strcmp(nome_operacao, "LOADMM") == 0) {
        operacao = OP_LOAD_MQ_M;
    
    } else if (strcmp(nome_operacao, "LOAD") == 0) {
        if (modificadores & MOD_M) {
            modificadores &= ~MOD_M;

            if (modificadores & MOD_MENOS && modificadores & MOD_PIPE) {
                modificadores &= ~MOD_MENOS;
                modificadores &= ~MOD_PIPE;
                
                operacao = OP_LOAD_MENOS_MOD;
            } else if (modificadores & MOD_PIPE){
                modificadores &= ~MOD_PIPE;
              
                operacao = OP_LOAD_MOD;
            } else if (modificadores & MOD_MENOS) {
                modificadores &= ~MOD_MENOS;
               
                operacao = OP_LOAD_MENOS;
            } else {
                RAISE("operacao inválida ou modificadores inválidos em '%s' (mod: %i)", nome_operacao, modificadores);
            }
        } else if (modificadores == 0) {
            operacao = OP_LOAD;
        } else {
            RAISE("combinacao de modificadores (%i) inválida em 'LOAD'", modificadores);
        }
    } else if (strcmp(nome_operacao, "STOR") == 0) {
        operacao = OP_STOR;
    
    }  else if (strcmp(nome_operacao, "STORM") == 0) {
        operacao = OP_STOR_L;
    
    } else if (strcmp(nome_operacao, "JUMP") == 0) {
        if (modificadores & MOD_MAIS) {
            modificadores &= ~MOD_MAIS;

            operacao = OP_JUMP_COND_L;
        } else if (modificadores == 0) {
            operacao = OP_JUMP_L;
        }
    
    } else if (strcmp(nome_operacao, "ADD") == 0) {
        if (modificadores & MOD_PIPE) {
            modificadores &= ~MOD_PIPE;

            operacao = OP_ADD_MOD;
        } else if (modificadores == 0) {
            operacao = OP_ADD;
        }   
    } else if (strcmp(nome_operacao, "SUB") == 0) {
        if (modificadores & MOD_PIPE) {
            modificadores &= ~MOD_PIPE;

            operacao = OP_SUB_MOD;
        } else if (modificadores == 0) {
            operacao = OP_SUB;
        }
    } else if (strcmp(nome_operacao, "MUL") == 0) {
        operacao = OP_MUL;
    } else if (strcmp(nome_operacao, "DIV") == 0) {
        operacao = OP_DIV;
    } else if (strcmp(nome_operacao, "EXIT") == 0) {
        operacao = OP_EXIT;
    }

    if (operacao == 0) {
        RAISE("operacao inválida '%s' (mod: %i)", nome_operacao, modificadores);
    }
    if (modificadores != 0) {
        RAISE("operacao inválida ou modificadores inválidos em '%s' (mod: %i)", nome_operacao, modificadores);
    }

    except_proximo_simbolo(&linha, DOIS_PONTOS, num_linha);
    num = (char)parse_numero(&linha, num_linha);

    if(cpu == NULL) {
        WARN("CPU e NULL, isso so deve acontecer caso esteja usando a flag '-t'");
        return;
    }

    PRINT("configuracao: '%s'", optoa(operacao));

    pipeline_inserir_tempo_operacao(&cpu->uc->pipeline, operacao, num);
}

static void compilar_linha(char *linha, Memoria *mem, int num_linha) {
    char *nome_operacao = except_proximo_simbolo(&linha, OPERACAO, num_linha).valor;    
    int num_mem = (num_linha - mem->tamanho_dados) / 2 + mem->tamanho_dados;

    PRINT("%i: %s", num_linha, nome_operacao);
    
    if (strcmp(nome_operacao, "LSH") == 0 || strcmp(nome_operacao, "RSH") == 0 || strcmp(nome_operacao, "EXIT") == 0) {
        if (nome_operacao[0] == 'L')
            memoria_adicionar_instrucao(mem, OP_LSH, 0, num_mem);
        else if (nome_operacao[0] == 'R')
            memoria_adicionar_instrucao(mem, OP_RSH, 0, num_mem);
        else
            memoria_adicionar_instrucao(mem, OP_EXIT, 0, num_mem);
    }

    if (strcmp(nome_operacao, "LOAD") == 0) {
        Simbolo simbolo_a_seguir = peek_simbolo(linha);

        if (simbolo_a_seguir.tipo == OPERACAO && strcmp(simbolo_a_seguir.valor, "MQ") == 0) {
            proximo_simbolo(&linha);
            Simbolo outro_argumento = peek_simbolo(linha);
            
            if (outro_argumento.tipo == VIRGULA) {
                proximo_simbolo(&linha);
                ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);

                memoria_adicionar_instrucao(mem, OP_LOAD_MQ_M, memoria.valor, num_mem);
            } else if (outro_argumento.tipo == VAZIO) {
                memoria_adicionar_instrucao(mem, OP_LOAD_MQ, 0, num_mem);
            } else {
                RAISE("Argumento do tipo '%i' nao e permitido em 'load mq'", outro_argumento.tipo);
            }
        } else if (simbolo_a_seguir.tipo == MENOS) {
            except_proximo_simbolo(&linha, MENOS, num_linha);

            Simbolo outro_argumento = peek_simbolo(linha);
            
            if (outro_argumento.tipo == PIPE) {
                ResultadoParseMemoria memoria = except_memoria_MOD(&linha, num_linha);
                
                memoria_adicionar_instrucao(mem, OP_LOAD_MENOS_MOD, memoria.valor, num_mem);
            } else if (outro_argumento.tipo == MEMORIA) {
                ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);
                
                memoria_adicionar_instrucao(mem, OP_LOAD_MENOS, memoria.valor, num_mem);
            } else {
                RAISE("Argumento do tipo '%i' nao e permitido em 'load -'", outro_argumento.tipo);
            }
        } else if (simbolo_a_seguir.tipo == PIPE) {
            ResultadoParseMemoria memoria = except_memoria_MOD(&linha, num_linha);
            
            memoria_adicionar_instrucao(mem, OP_LOAD_MOD, memoria.valor, num_mem);
        } else if (simbolo_a_seguir.tipo == MEMORIA) {
            ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);
            
            memoria_adicionar_instrucao(mem, OP_LOAD, memoria.valor, num_mem);
        }
    }

    if (strcmp(nome_operacao, "STOR") == 0) {
        ResultadoParseMemoria memoria = parse_memoria(&linha, num_linha);
            
        if (memoria.tipo == MULTIVALORADO) {
            if (memoria.posicao == 'L') {
                memoria_adicionar_instrucao(mem, OP_STOR_L, memoria.valor, num_mem);
            }
            else if (memoria.posicao == 'R') {
                memoria_adicionar_instrucao(mem, OP_STOR_R, memoria.valor, num_mem);
            } else {
                RAISE("posicionamento invalido para STOR");
            }
        } else {
            memoria_adicionar_instrucao(mem, OP_STOR, memoria.valor, num_mem);
        }
    }

    if (strcmp(nome_operacao, "JUMP") == 0) {
        Simbolo simbolo_a_seguir = peek_simbolo(linha);

        if (simbolo_a_seguir.tipo == MAIS) {
            proximo_simbolo(&linha);

            ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, MULTIVALORADO);
            
            if (memoria.posicao == 'l')
                memoria_adicionar_instrucao(mem, OP_JUMP_COND_L, memoria.valor, num_mem);
            else
                memoria_adicionar_instrucao(mem, OP_JUMP_COND_R, memoria.valor, num_mem);
        } else {
            ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, MULTIVALORADO);
            
            if (memoria.posicao == 'l')
                memoria_adicionar_instrucao(mem, OP_JUMP_L, memoria.valor, num_mem);
            else
                memoria_adicionar_instrucao(mem, OP_JUMP_R, memoria.valor, num_mem);
        }
    }

    if (strcmp(nome_operacao, "ADD") == 0) {
        Simbolo simbolo_a_seguir = peek_simbolo(linha);

        if (simbolo_a_seguir.tipo == MEMORIA) {
            ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);

            memoria_adicionar_instrucao(mem, OP_ADD, memoria.valor, num_mem);
        } else if (simbolo_a_seguir.tipo == PIPE) {
            ResultadoParseMemoria memoria = except_memoria_MOD(&linha, num_linha);

            memoria_adicionar_instrucao(mem, OP_ADD_MOD, memoria.valor, num_mem);
        } else {
            RAISE("Argumento do tipo '%i' nao e permitido em 'add'", simbolo_a_seguir.tipo);
        }
    }

    if (strcmp(nome_operacao, "SUB") == 0) {
        Simbolo simbolo_a_seguir = peek_simbolo(linha);

        if (simbolo_a_seguir.tipo == MEMORIA) {
            ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);

            memoria_adicionar_instrucao(mem, OP_SUB, memoria.valor, num_mem);
        } else if (simbolo_a_seguir.tipo == PIPE) {
            ResultadoParseMemoria memoria = except_memoria_MOD(&linha, num_linha);

            memoria_adicionar_instrucao(mem, OP_SUB_MOD, memoria.valor, num_mem);
        } else {
            RAISE("Argumento do tipo '%i' nao e permitido em 'add'", simbolo_a_seguir.tipo);
        }
    }

    if (strcmp(nome_operacao, "MUL") == 0) {
        ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);
            
        memoria_adicionar_instrucao(mem, OP_MUL, memoria.valor, num_mem);
    }

    if (strcmp(nome_operacao, "DIV") == 0) {
        ResultadoParseMemoria memoria = except_memoria(&linha, num_linha, UNICO);
            
        memoria_adicionar_instrucao(mem, OP_DIV, memoria.valor, num_mem);
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
    size_t i;
    for (i = 0; (str[i] >= 48 && str[i] <= 57) || str[i] == '-'; i++);
    return (bool)(i == strlen(str));
}

static Simbolo except_proximo_simbolo(char **linha, SimbolosEnum tipo, int num_linha) {
    Simbolo s = proximo_simbolo(linha);

    // PRINT("%s / %s", s.valor, *linha);

    if (s.tipo != tipo) {
        RAISE("na linha '%i': Um simbolo deveria ser '%s' mas e '%s'", num_linha, simtoa(tipo), simtoa(s.tipo));
    }

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

    if (mem.tipo != tipo) {
        RAISE("memoria do tipo errada passada");
    }

    return mem;
}

static ResultadoParseMemoria except_memoria_MOD(char **linha, int num_linha) {
    except_proximo_simbolo(linha, PIPE, num_linha);
    ResultadoParseMemoria mem = except_memoria(linha, num_linha, UNICO);
    except_proximo_simbolo(linha, PIPE, num_linha);

    return mem;
}

static char charhigh(char c) {
    return c >= 'a' && c <= 'z' ? c - 32 : c; // NOLINT(*-narrowing-conversions)
}

static char fpeek(FILE *f) {
    char c;

    c = (char)fgetc(f);
    ungetc(c, f);

    return c;
}

static char *simtoa(SimbolosEnum simb) {
    switch(simb) {
        case OPERACAO:
            return "OPERACAO";
        case NUMERO:
            return "NUMERO";
        case MEMORIA:
            return "MEMORIA";
        case VIRGULA:
            return "VIRGULA";
        case PIPE:
            return "PIPE";
        case PAREN_OPEN:
            return "PAREN_OPEN";
        case PAREN_CLOSE:
            return "PAREN_CLOSE";
        case MENOS:
            return "MENOS";
        case DOIS_PONTOS:
            return "DOIS_PONTOS";
        case VAZIO:
            return "VAZIO";
        case MAIS:
            return "MAIS";
        default:
            return "Unknown";
    }
}

static void processar_modificador(char **linha, char *modificadores, SimbolosEnum simb, char tipo_mod) {
    Simbolo simbolo_a_seguir = peek_simbolo(*linha);
    
    if (simbolo_a_seguir.tipo == simb) {
        proximo_simbolo(linha);
        *modificadores |= tipo_mod; // NOLINT(*-narrowing-conversions)
    }
}