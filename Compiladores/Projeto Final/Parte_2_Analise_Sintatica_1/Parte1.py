
#Entrada inicial, onde vai ser inserido o simbolo inicial (que possui $ no final), e suas produções
class Gramatica:
    def __init__(self, producoes, simbolo_inicial):
        self.producoes = producoes  # dicionário: não-terminal -> lista de produções (listas de símbolos)
        self.simbolo_inicial = simbolo_inicial
    
    #Exemplo de entrada do init: (Dicionário)
    #producoes = {
    #    "S": [["a", "A"], ["b"]],
    #    "A": [["c"]]
    #}
    #gramatica = Gramatica(producoes, "S")

    #Retorna o simbolo inicial porém com o simbolo de linha
    def simbolo_inicial_estendido(self):
        return self.simbolo_inicial + "'"

    def simbolos(self):
            simbolos = set() # isso esta criando um conjunto, inicialmente vazio, para evitar duplicatas no for posterior
            for cabeca, corpos in self.producoes.items(): #isso aqui é para usar o dicionário para pegar a chave (cabeça) e o conteúdo (corpos)
                simbolos.add(cabeca) #adiciona a cabeça ao começo do conjunto
                for corpo in corpos: #adiciona todos os corpos daquela cabeça
                    simbolos.update(corpo) #chama toda a lista (da tupla do dicionário) de uma vez daquele corpo
            return simbolos

class AutomatoLR0:
    def __init__(self, gramatica): #Inicializa o autômato passando a gramática para ele
        self.gramatica = gramatica
        self.estados = []
        self.transicoes = {}

    def fecho(self, itens): 
        conjunto_fecho = set(itens) # Vai pegar todos as tuplas no estilo (Cabeça, corpo, posição atual do ponto)
        mudou = True #só pra fazer uma verificação de "entrou um não terminal"

        while mudou:
            mudou = False #falseia a condição
            novos_itens = set() #Cria um conjunto vazio para caso precise adicionar novos corpos (caso entre um não terminal)

            for (cabeca, corpo, pos_ponto) in conjunto_fecho: 
                if pos_ponto < len(corpo): #Vê se o ponto atual não está no final do corpo
                    simbolo_apos_ponto = corpo[pos_ponto] #pega o simbolo que está justamente depois do ponto, por exemplo S -> a.A , o ponto está em 1 ou seja, o A será pego.
                    if simbolo_apos_ponto in self.gramatica.producoes: #verifica se o simbolo que foi pego acima é um não terminal, se for, ele vai incluir suas produções também.
                        for producao in self.gramatica.producoes[simbolo_apos_ponto]:
                            novo_item = (simbolo_apos_ponto, tuple(producao), 0)
                            if novo_item not in conjunto_fecho:
                                novos_itens.add(novo_item)
                                mudou = True

            conjunto_fecho.update(novos_itens)

        return conjunto_fecho
    
    def ir_para(self, itens, simbolo):
        """
        Retorna o fecho do conjunto de itens que resulta ao mover o ponto sobre o símbolo especificado.
        """
        itens_mover_ponto = set()#Conjunto de itens

        for (cabeca, corpo, pos_ponto) in itens:
            # Verifica se o ponto ainda pode avançar e se o símbolo após o ponto é o símbolo desejado
            if pos_ponto < len(corpo) and corpo[pos_ponto] == simbolo:
                # Avança o ponto (pos_ponto + 1)
                novo_item = (cabeca, corpo, pos_ponto + 1)
                itens_mover_ponto.add(novo_item)

        # Aplica o fecho sobre os itens resultantes
        return self.fecho(itens_mover_ponto)

    def construir_estados(self):
        # Item inicial: S' → • S $
        item_inicial = (self.gramatica.simbolo_inicial_estendido(), 
                        tuple(self.gramatica.producoes[self.gramatica.simbolo_inicial_estendido()][0]), 0) # Cria o não terminal inicial extendido (S'), passando ele como incial.
    
        estado_inicial = self.fecho({item_inicial}) # cria o primeiro estado com base no fecho do não terminal inicial
        self.estados.append(estado_inicial)# adiciona o estado inicial com todos o fecho do S' no final da lita "estados"

        fila = [estado_inicial] # vai ser usado como uma espécie de contador pra saber quando parar
        visitados = [estado_inicial]  # usado para evitar repetição

        while fila:
            estado_atual = fila.pop(0)

            for simbolo in self.gramatica.simbolos(): # Vai dar os passos procurando novos estados
                novo_estado = self.ir_para(estado_atual, simbolo)
                if not novo_estado:
                    continue

                if novo_estado not in self.estados: #achou um estado novo
                    self.estados.append(novo_estado) #adiciona o novo estado na lista
                    fila.append(novo_estado) #adiciona o estado novo na fila

                self.transicoes[(frozenset(estado_atual), simbolo)] = frozenset(novo_estado) #Usa frozenset para garantir que o conjunto de itens seja "hashable"
    
    def gerar_dicionario_estados(self):
        """
        Retorna um dicionário com os estados indexados por número
        e transições com origem numérica, facilitando o uso no parser.
        """
        #Criando os dicionários que vão guardar os estados e as transicoes
        estados_dict = {}
        transicoes_dict = {}

        for i, estado in enumerate(self.estados): #Associa um numero a cada estado
            estados_dict[i] = estado #guarda esse numero no dict

        #Constrói as transições com índices numéricos
        for (estado_orig, simbolo), estado_dest in self.transicoes.items():
            id_origem = self.estados.index(set(estado_orig))
            id_destino = self.estados.index(set(estado_dest))
            transicoes_dict[(id_origem, simbolo)] = id_destino

        return {
            "estados": estados_dict,
            "transicoes": transicoes_dict
        }











# Definindo uma gramática de exemplo
"""producoes = {
    "S": [["a", "A"]],
    "A": [["c"]]
}"""
producoes = {
    "S'": [["S", "$"]],
    "S": [["(", "L", ")"], ["x"]],
    "L": [["S"], ["L", ",", "S"]]
}

# Criando a gramática
gramatica = Gramatica(producoes, "S")

# Criando o autômato com essa gramática
automato = AutomatoLR0(gramatica)

# Item inicial para testar o fecho
# Representa: S → • a A
"""item_inicial = ("S", ("a", "A"), 0)"""
# Item inicial: S' → • S $
item_inicial = ("S", ("(", "L",")"), 1)


# Chamando o método fecho com o item inicial

# Construindo todos os estados do autômato LR(0)
automato.construir_estados()

dados = automato.gerar_dicionario_estados()

print("\nDicionario organizado para o parser:")
print("Estados:")
for id_estado, itens in dados["estados"].items():
    print(f"I{id_estado}:")
    for item in itens:
        print("  ", item)

print("\nTransicoes:")
for (origem, simbolo), destino in dados["transicoes"].items():
    print(f"I{origem} -- {simbolo} --> I{destino}")