from collections import defaultdict

# estruturas usadas:
# dicionário: armazena as produções
# conjuntos(set): armazena os terminais e não-terminais
# defaultdict: armazena os conjuntos FIRST e FOLLOW, onde a chave é o símbolo e o valor é um conjunto de símbolos


# Definição da gramática
# aqui é usado um dicionário onde a chave é o não-terminal e o valor é uma lista de produções a qual esse não terminal pode gerar
# cada produção é uma lista de símbolos
productions = {
    "S'": [["S", "$"]],
    "S": [["(", "L", ")"], ["x"]],
    "L": [["S"], ["L", ",", "S"]]
}

terminals = {"(", ")", ",", "x", "$"}
# armazena os terminais em um conjunto
non_terminals = set(productions.keys())
# productions.keys() retorna uma lista com as chaves do dicionário, ou seja, os não-terminais, já o set cria um conjunto com esses não-terminais.
# Esse conjunto retorna {"S'", "S", "L"}, é mais indicado usar o set pois não há repetição de elementos e é mais eficiente para operações de busca e comparação,
# além de ser mais fácil de representar coleções de símbolos únicos.

# defaultdict é uma subclasse do dicionário padrão do Python, que fornece um valor padrão para chaves que não existem no dicionário.
# está sendo criado 3 dicionários que não precisam ser inicializados com valores, pois o defaultdict cria automaticamente um conjunto vazio para cada chave que não existe.
FIRST = defaultdict(set)
FOLLOW = defaultdict(set)
nullable = defaultdict(bool)

# FIRST de terminais é o próprio terminal
for t in terminals:
    FIRST[t].add(t)

# Símbolo inicial
start_symbol = "S'"
FOLLOW[start_symbol].add("$")

changed = True
while changed:
    changed = False
    for head, bodies in productions.items():
        for body in bodies:
            # Verifica se é anulável
            if all(symbol in nullable and nullable[symbol] for symbol in body) or not body:
                if not nullable[head]:
                    nullable[head] = True
                    changed = True

            # Atualiza FIRST
            for i in range(len(body)):
                prefix = body[:i]
                if all(nullable[s] for s in prefix) or i == 0:
                    before = len(FIRST[head])
                    FIRST[head].update(FIRST[body[i]])
                    if len(FIRST[head]) > before:
                        changed = True

            # Atualiza FOLLOW
            k = len(body)
            for i in range(k):
                for j in range(i + 1, k + 1):
                    prefix = body[i+1:j]
                    if all(nullable[s] for s in prefix) or i+1 == j:
                        # FOLLOW[Yᵢ] ← FOLLOW[Yᵢ] ∪ FIRST[Yⱼ]
                        if j < k:
                            before = len(FOLLOW[body[i]])
                            FOLLOW[body[i]].update(FIRST[body[j]])
                            if len(FOLLOW[body[i]]) > before:
                                changed = True
                        # FOLLOW[Yᵢ] ← FOLLOW[Yᵢ] ∪ FOLLOW[X]
                        elif j == k:
                            before = len(FOLLOW[body[i]])
                            FOLLOW[body[i]].update(FOLLOW[head])
                            if len(FOLLOW[body[i]]) > before:
                                changed = True

def print_sets(name, sets):
    print(f"\n{name} sets:")
    for symbol in sorted(sets):
        print(f"{symbol}: {sorted(sets[symbol])}")

# Exibe resultados
print_sets("FIRST", FIRST)
print_sets("FOLLOW", FOLLOW)
