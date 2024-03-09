import os

instrucoes = [
    ("op_lsh", "OP_LSH"),
    ("op_rsh", "OP_RSH"),
    ("op_load", "OP_LOAD"),
    ("op_stor", "OP_STOR"),
    ("op_load_menos", "OP_LOAD_MENOS"),
    ("op_load_mod", "OP_LOAD_MOD"),
    ("op_load_menos_mod", "OP_LOAD_MENOS_MOD"),
    ("op_load_mq", "OP_LOAD_MQ"),
    ("op_load_mq_m", "OP_LOAD_MQ_M"),
    ("op_jump_l", "OP_JUMP_L"),
    ("op_jump_r", "OP_JUMP_R"),
    ("op_jump_cond_l", "OP_JUMP_COND_L"),
    ("op_jump_cond_r", "OP_JUMP_COND_R"),
    ("op_add", "OP_ADD"),
    ("op_add_mod", "OP_ADD_MOD"),
    ("op_sub", "OP_SUB"),
    ("op_sub_mod", "OP_SUB_MOD"),
    ("op_mul", "OP_MUL"),
    ("op_div", "OP_DIV"),
    ("op_stor_l", "OP_STOR_L"),
    ("op_stor_r", "OP_STOR_R"),
    ("op_exit", "OP_EXIT"),
]

pasta_exemplo = "./src/instrucoes/EXAMPLE/"
pasta = "./src/instrucoes/"

conteudo: dict[str, str | None] = {
    ".c": None,
    ".h": None
}


def main():
    global instrucoes, conteudo

    files: set[str] = set(map(lambda f: f.rstrip(".c").rstrip(".h"), os.listdir(pasta)))
    inst_a_criar: list[tuple[str]] = list(filter(lambda val: val[1] not in files, instrucoes))

    with open(pasta_exemplo + "EXAMPLE.c") as c_ex, open(pasta_exemplo + "EXAMPLE.h") as h_ex:
        conteudo[".c"] = c_ex.read()
        conteudo[".h"] = h_ex.read()

    for nome, NOME in inst_a_criar:
        with open(pasta + NOME + ".c", "w") as c_file, open(pasta + NOME + ".h", "w") as h_file:
            c_file.write(
                conteudo[".c"].replace("<nome_da_operacao>", nome)
                              .replace("<NOME_DA_OPERACAO>", NOME)
            )

            h_file.write(
                conteudo[".h"].replace("<nome_da_operacao>", nome)
                              .replace("<NOME_DA_OPERACAO>", NOME)
            )

    print(conteudo)


if __name__ == "__main__":
    main()
