#ifndef ULA_H_
#define ULA_H_

typedef struct {
    PALAVRA rAC;
    PALAVRA rEQ;
    PALAVRA rMBR;
} ULA;

ULA *ULA_criar(void);
void ULA_ativar(/* input1, input2, controle */);

#endif