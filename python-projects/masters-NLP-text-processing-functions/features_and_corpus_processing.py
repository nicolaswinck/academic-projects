# -*- coding: utf-8 -*-
"""estudo_de_conjunções_new_features.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/1YHbvUtJJNP74q__aTOS6KESN-bu8rHV6
"""

import nltk
nltk.download('punkt')
from nltk import tokenize
sent_tokenizer = nltk.data.load('tokenizers/punkt/portuguese.pickle')

import itertools

# Commented out IPython magic to ensure Python compatibility.
import nltk.tokenize.punkt as pkt

class CustomLanguageVars(pkt.PunktLanguageVars):

    _period_context_fmt = r"""
        \S*                          # some word material
#         %(SentEndChars)s             # a potential sentence ending
        \s*                       #  <-- THIS is what I changed
        (?=(?P<after_tok>
#             %(NonWord)s              # either other punctuation
            |
            (?P<next_tok>\S+)     #  <-- Normally you would have \s+ here
        ))"""

custom_tknzr = pkt.PunktSentenceTokenizer(lang_vars=CustomLanguageVars())

# FONTE: https://stackoverflow.com/questions/33139531/preserve-empty-lines-with-nltks-punkt-tokenizer Hugo Mailhlot

def ler(nome_arq):
    arq = open(nome_arq, 'r', encoding='UTF-8')
    corpus = arq.read()
    arq.close()

    return corpus


def tokenizar(s):
    return custom_tknzr.tokenize(s)


def achatar(lista):
    return list(itertools.chain(*lista))


def pipeline(txt):
    texto = ler(txt)
    sentencas = tokenizar(texto)
    paragrafos = [i.replace('\n\n', ' FIM_DE_PARAGRAFO ').replace(',','').replace(';','').replace(':','').strip() for i in sentencas]
    sentencas_de_tokens = [tokenize.word_tokenize(i, language='portuguese') for i in paragrafos]

    return sentencas_de_tokens

# Nova biblioteca: permite buscar facilmente nomes de arquivos no drive (HD ou virtual)
import glob

# Descompacta (no drive do Colab) o arquivo zipado
!unzip 'red_temas_1_24_1' -d 'red_temas_1_24_1'

# Recebe uma lista dos nomes de arquivos que foram descompactados na pasta 'red_tema1'
arqs = glob.glob('red_temas_1_24_1/*.txt')

# Cria uma (grande) lista dos tokens de todas as redações
lst_tokens = list()
for arquivo in arqs:
    print(f'Processando {arquivo}...')
    tokens_da_redacao = pipeline(arquivo)
    lst_tokens.append(tokens_da_redacao)

# Até aqui, lst_tokens é uma lista de sublistas (cada lista é uma redação).
# Será preciso transformá-la numa lista única, unidimensional:
lst_tokens_unica = achatar(lst_tokens)

'''Função que recebe uma redação (lista) e devolve apenas as notas por
competência.'''

def notas_competencias(lst_tokens_item):
  lista_suja = lst_tokens_item[-1]
  sujeira = [':', ',', '</s>']
  lista_limpa = [i for i in lista_suja if i not in sujeira]
  lista_limpa = lista_limpa[1::2]
  lista_int = [int(i) for i in lista_limpa]

  return lista_int


'''Função que recebe diversas redações (range) e devolve as notas por
competência, por redação.'''

def notas_competencias_conjunto(lst_tokens_itens):
  lista_completa_notas_competencias = [i[-1] for i in lst_tokens_itens]
  notas_achatada = [notas_competencias(i) for i in lista_completa_notas_competencias]

  return notas_achatada


'''Função que recebe uma redação (lista) e devolve a quantidade de períodos
(sentenças).'''

def contar_periodos(red_lst):
  quant_fins_red = [i for i in red_lst if i == '.']
  quant_periodos_red = len(quant_fins_red) - 1

  return quant_periodos_red


'''Função que recebe uma redação (lista) e devolve uma lista com sublistas que
consistem nos períodos do texto. Esta função retira as notas por competência, ao
 fim da redação.'''

def separar_periodos(red_lst):
  periodos_red_lst = [i for i in red_lst]
  periodos_limpo = [i for i in periodos_red_lst]

  return periodos_limpo[:-1]


'''Função que recebe uma redação dividida em sentenças (lista de listas) e
devolve uma lista de tuplas, em que cada tupla tem dois itens:
[0] é o índice da palavra na sentença;
[1] é a palavra em si (string)'''

def indexar_palavras(red_lst_sents):

  indices_palavras = list()

  for i in red_lst_sents:
    for p,item in enumerate(i, start=1):
      indices_palavras.append((p,item))

  return indices_palavras


'''Função que recebe uma redação dividida em sentenças (lista de listas) e
devolve um número, que corresponde à quantidade de parágrafos do texto.'''

def contar_paragrafos(red_lst_sents):
  contagem = list()
  extração = [contagem.append(i) for i in red_lst_sents if 'FIM_DE_PARAGRAFO' in i]

  return len(contagem)


'''Função que recebe uma redação dividida em sentenças (lista de listas) e
devolve uma lista (texto) com listas (parágrafos) de listas (sentenças),
contendo palavras.
OBSERVAÇÃO: o último item da maior lista é o quadro de notas por competência.'''

def indexar_paragrafos(red_lst_sents):
  nao_tem_fim = list()
  tem_fim = list()
  texto = list()
  cont = 0
  contsemfim = 0
  contfim = 0

  while cont < len(red_lst_sents):

    if 'FIM_DE_PARAGRAFO' not in red_lst_sents[cont]:
      nao_tem_fim.append(red_lst_sents[cont])
      cont += 1
      contsemfim += 1

    else:
      if contsemfim != 0:
        par = nao_tem_fim[0:] + [red_lst_sents[cont]]
        texto.append(par)
        del nao_tem_fim[:]
        tem_fim.append(red_lst_sents[cont])
        cont += 1
        contfim += 1

      else:
        par = nao_tem_fim[contsemfim - cont:cont] + [red_lst_sents[cont]]
        texto.append(par)
        cont += 1
        contfim += 1

  return texto + [[i.upper() for i in red_lst_sents[-1]]]

# Importando o módulo com o etiquetador.

import joblib
from nltk import word_tokenize

folder = 'trained_POS_taggers/'
tagger = joblib.load('POS_tagger_trigram.pkl')

# Testando o etiquetador com uma frase qualquer.

frase = 'quando se tem certeza, no entanto, parece difícil'
tagger.tag(word_tokenize(frase))

'''Função que recebe uma redação (lista) e devolve uma lista com tuplas contendo
 cada palavra e sua respectiva classificação.'''

def etiquetar(red_lst):
  lista_etiquetas = list()

  for i in red_lst:
    lista_etiquetas.append(tagger.tag(i))

  return achatar(lista_etiquetas)

'''Função que recebe uma redação (lista) e devolve uma lista com as conjunções
e pronomes que existem no texto.'''
# 'KC' é conjunção coordenativa e 'KS' é conjunção subordinativa.
# 'PROSUB' é pronome substantivo e 'PRO-KS-REL' é pronome relativo.
# 'ADV' é advérbio, 'PDEN' é palavra denotativa e PCP é particípio.

def operadores(red_lst):
  red_etiquetas = etiquetar(red_lst)
  red_conjuncoes = [i[0].lower() for i in red_etiquetas if i[1] == 'KS'
                    or i[1] == 'KC']
  red_pronomes = [i[0].lower() for i in red_etiquetas if i[1] == 'PROSUB'
                  or i[1] == 'PRO-KS-REL' or i[1] == 'PDEN']
  red_outros = [i[0].lower() for i in red_etiquetas if[1] == 'ADV'
                or i[1] == 'PCP']

  return red_conjuncoes + red_pronomes

def etiquetar_paragrafos(red_lst_lst):
  lista_etiquetas = list()

  for i in red_lst_lst:
    lista_etiquetas.append(etiquetar(i))

  '''A função devolve a lista sem o último item, pois este consiste em notas por
  competência.'''

  return lista_etiquetas[:-1]

def operadores_paragrafos(red_lst_lst):
  return [operadores(i) for i in red_lst_lst]

def textos_indexados(lst_redacoes):
  return [indexar_paragrafos(i) for i in lst_redacoes]

# Listona formatada de redações (com sublistas).

indexados = textos_indexados(lst_tokens)

'''Esta função recebe a lista formatada de redações (com sublistas) e devolve o
índice de cada uma (opcional) com uma lista das notas por competência.'''

def notas_indexados(lst_lsts):
  lista = list()

  for i in lst_lsts:
     # lista.append([lst_lsts.index(i), notas_competencias(i)]) <-- com índice (opcional)
     lista.append(notas_competencias(i))

  return lista

'''Esta função aplica etiquetas em uma unidade de redação dividida em listas de
parágrafos, com listas de períodos, que são listas de palavras.'''

def etiquetar_dividido(red_dividida):
  taggeado = list()

  for i in red_dividida:
    taggeado.append(tagger.tag(i))

  return taggeado

'''Esta função recebe a lista de redações dividida em listas de parágrafos,
divididos em listas de períodos, organizados em listas de palavras e devolve
uma lista com a mesma formatação de dados, mas com etiquetas.'''

def etiquetar_final(lst_reds_divididas):
  geral = list()

  for c in lst_reds_divididas:
    idx = 0
    guardados = list()

    while idx < (len(c) - 1):
      guardados.append(etiquetar_dividido(c[idx]))

      if idx == (len(c) - 2):
        geral.append(guardados)

      idx += 1

  return geral

# Listona formatada de redações (com sublistas), COM TAGS.

corpus_tags = etiquetar_final(indexados)

indexados[11]

len(corpus_tags)

"""ABAIXO: cálculo de porcentagem de textos, em determinados níveis, que apresentam um certo número de sentenças por parágrafo (média por texto)."""

def porcentagem_textos_sentencas(redacoes):
    count_valid = 0
    count_total = 0

    for redacao in redacoes:
        # Extrair o quadro de notas
        quadro_notas = redacao[-1]

        # Verificar a nota em COMPETÊNCIA4
        indice_competencia4 = quadro_notas.index('COMPETÊNCIA4') + 1
        nota_competencia4 = int(quadro_notas[indice_competencia4])

        if nota_competencia4 in [200]:
            count_total += 1
            num_paragrafos = len(redacao) - 1
            total_sentencas = sum(len(paragrafo) for paragrafo in redacao[:-1])

            if num_paragrafos > 0:
                media_sentencas_por_paragrafo = total_sentencas / num_paragrafos
                if media_sentencas_por_paragrafo >= 2:
                    count_valid += 1

    if count_total == 0:
        return 0.0
    return (count_valid / count_total) * 100

resultado = porcentagem_textos_sentencas(indexados)
print(resultado)

'''Função que recebe o corpus taggeado e devolve uma lista com os endereços dos
operadores argumentativos.

Output:
[índice do parágrafo no texto, índice da sentença no parágrafo, índice da
palavra na sentença, (palavra, classe)].'''

def enderecos(corpus):
  general = list()
  classes = ['KC', 'KS', 'ADV', 'PROSUB', 'PRO-KS-REL', 'ADV-KS-REL', 'PDEN', \
             'PROADJ', 'PRO-KS', 'PCP']

  for essay in corpus:
    address = list()

    for par in essay:
      for sent in par:
        for word in sent:

          if word[1] in classes:
            vec = [essay.index(par), par.index(sent), sent.index(word), word]

            if vec not in address:
               address.append(vec)

    general.append(address)

  return general

'''Esta função é um teste que analisa ocorrências de casos pontuais.
Na presente aplicação, ela verifica:
1. gerúndio (1ª conjugação) iniciando sentença
2. uso específico de "o mesmo", indicado como ruim pela correção.'''

def pron_o_mesmo(lst_lsts):
  # Esta lista armazena os endereços das sentenças com as expressões.
  general = list()

  target_prob2 = ['mesmo', 'mesmos', 'mesma', 'mesmas']
  expressions_art = ['o', 'os', 'a', 'as']
  expressions_preced = ['PREP', 'PRO-KS-REL']
  expressions_succeed = ['PREP', 'ADV']

  idx_essay = 0
  while idx_essay < len(lst_lsts):
    idx_par = 0
    coordinate = list()
    prob1_count = 0
    prob2_count = 0
    while idx_par < len(lst_lsts[idx_essay]):
      idx_sent = 0
      while idx_sent < len(lst_lsts[idx_essay][idx_par]):
        idx_word = 0
        while idx_word < len(lst_lsts[idx_essay][idx_par][idx_sent]):
          if 'ando' in lst_lsts[idx_essay][idx_par][idx_sent][idx_word][0].lower() \
              and idx_word == 0 \
              and lst_lsts[idx_essay][idx_par][idx_sent][idx_word][1] != 'KS':
              prob1_count += 1
              idx_word += 1
          elif lst_lsts[idx_essay][idx_par][idx_sent][idx_word][0] in target_prob2:
            if lst_lsts[idx_essay][idx_par][idx_sent][idx_word - 1][0] in expressions_art:
              if lst_lsts[idx_essay][idx_par][idx_sent][idx_word + 1][1] == 'V' \
              or (lst_lsts[idx_essay][idx_par][idx_sent][idx_word + 1][1] in expressions_succeed \
                  and lst_lsts[idx_essay][idx_par][idx_sent][idx_word + 2][1] == 'V')\
              or (lst_lsts[idx_essay][idx_par][idx_sent][idx_word + 1][0] == '.' \
                  and lst_lsts[idx_essay][idx_par][idx_sent][idx_word - 2][1] in expressions_preced):
                prob2_count += 1
                idx_word += 1
              idx_word += 1
            idx_word += 1
          idx_word += 1
        idx_sent += 1
      idx_par += 1
    idx_essay += 1
    coordinate = round(prob1_count + prob2_count / idx_par, 1)
    general.append(coordinate)

  return general

len(corpus_tags[1])

'''Lista com as coordenadas de cada palavra-alvo em cada texto do corpus.'''

corpus_enderecos = enderecos(corpus_tags)

# Listas com operadores interparágrafo adequados a parágrafos específicos.
# https://www.todamateria.com.br/conectivos/ Daniela Diana

conectivos_par2 = ['em primeiro lugar',
                         'em primeira análise',
                         'em primeiro plano',
                         'em um primeiro plano',
                         'em uma primeira análise',
                         'em um primeiro momento',
                         'a princípio',
                         'de início',
                         'para começar',
                         'antes de mais nada',
                         'antes de tudo',
                         'em princípio',
                         'primeiramente',
                         'acima de tudo',
                         'principalmente',
                         'primordialmente',
                         'sobretudo',
                         'a priori',
                         'a posteriori',
                         'precipuamente']

conectivos_par3 = ['então',
                   'além disso',
                   'sob esse viés',
                   'em paralelo',
                   'paralelamente',
                   'outro ',
                   'outra ',
                   'além da',
                   'além do',
                   'além de',
                   'mormente',
                   'em segundo lugar',
                   'secundariamente',
                   'ademais',
                   'outrossim',
                   'ainda mais',
                   'por outro lado',
                   'também',
                   'não só',
                   'não apenas',
                   'bem como'
                   'por conseguinte',
                   'logo depois',
                   'posteriormente',
                   'agora',
                   'já']

conectivos_comparacao = ['igualmente',
                         'da mesma forma',
                         'assim também',
                         'do mesmo modo',
                         'similarmente',
                         'semelhantemente',
                         'analogamente',
                         'por analogia',
                         'de maneira idêntica',
                         'de conformidade com',
                         'de acordo com',
                         'segundo',
                         'conforme',
                         'sob o mesmo ponto de vista',
                         'tal qual',
                         'tanto quanto',
                         'como',
                         'assim como',
                         'como se',
                         'bem como']

conectivos_adicao = ['além disso',
                     'em segundo lugar',
                     'ademais',
                     'outrossim',
                     'ainda mais',
                     'por outro lado',
                     'também',
                     'e',
                     'nem',
                     'não só',
                     'como também',
                     'não apenas',
                     'bem como']

conectivos_esclarecimento = ['por exemplo',
                             'isto é',
                             'ou seja',
                             'aliás']

conectivos_finalidade = ['com o fim de',
                         'a fim de',
                         'como propósito de',
                         'com a finalidade de',
                         'com o intuito de',
                         'para que',
                         'a fim de que',
                         'para',
                         'ao propósito']

conectivos_conclusao = ['em suma',
                        'conclui-se',
                        'diante disso',
                        'diante do exposto',
                        'diante do que foi exposto',
                        'por fim',
                        'finalmente',
                        'em conclusão',
                        'concluindo',
                        'em síntese',
                        'enfim',
                        'em resumo',
                        'portanto',
                        'assim',
                        'dessa forma',
                        'dessa maneira',
                        'desse modo',
                        'logo',
                        'pois',
                        'assim sendo',
                        'nesse sentido']

# FEATURE 1: COUNT PARAGRAPHS
'''Função que conta parágrafos (devolve um valor entre 0 e 1).'''

def count_paragraphs(lst_lsts):
    results = []

    for paragraphs in lst_lsts:
        if len(paragraphs) > 4:
            count = 4
        else:
            count = len(paragraphs)

        # Normalização e arredondamento
        normalized_count = round((count - 1) / 3, 1)
        results.append(normalized_count)

    return results

# FEATURE 2: PARAGRAPH STARTS WITH LINKING WORDS
'''Função que calcula o score de OPERADORES INTERPARÁGRAFO (devolve
um valor decimal suavizado entre 0 e 1).
Considera-se uma janela de palavras de índices 0 a 3 (4 palavras).'''

def score_start_lnk_wrds(red_addresses, lst_lsts):
    idx_red = 0
    scores = []

    while idx_red < len(lst_lsts):
        score_red = 0.0  # Inicializando como float

        # Definir índice do parágrafo, começando com o segundo parágrafo (index 1).
        idx_par = 1
        idx_par_max = len(lst_lsts[idx_red])

        while idx_par < idx_par_max:
            idx_wrd = 0
            idx_wrd_max = 3
            score_par = 0.0  # Inicializando como float

            while idx_wrd < idx_wrd_max:
                found = 0.0  # Inicializando como float

                for address in red_addresses[idx_red]:
                    if [idx_par, 0, idx_wrd] == address[0:3]:
                        found = 1.0  # Marcando como float
                        score_par = found

                idx_wrd += 1

            score_red += score_par
            idx_par += 1

        # Verificação para evitar divisão por zero
        num_paragraphs = len(lst_lsts[idx_red])
        if num_paragraphs == 1:
            score_red = round(score_red, 1)
        else:
            score_red = round(score_red / (num_paragraphs - 1), 1)

        scores.append(score_red)
        idx_red += 1

    return scores

# FEATURE 3: FIRST SENTENCE HAS LINKING WORDS
'''Função que calcula o score de OPERADORES NA PRIMEIRA SENTENÇA (devolve
um valor decimal suavizado entre 0 e 1).
Considera-se uma janela de palavras de índices 4 a n.'''

def sent1_has_lnk_wrds(red_addresses, lst_lsts):
    idx_red = 0
    scores = []

    while idx_red < len(lst_lsts):
        score_red = 0.0  # Inicializando como float

        # Definir índice do parágrafo, começando com o segundo parágrafo (index 1).
        idx_par = 1
        idx_par_max = len(lst_lsts[idx_red])

        while idx_par < idx_par_max:

            # Definir índice de palavras, começando com a quinta palavra (index 4).
            idx_wrd = 4
            idx_wrd_max = len(lst_lsts[idx_red][idx_par][0])
            score_par = 0.0  # Inicializando como float

            while idx_wrd < idx_wrd_max:
                found = 0.0  # Inicializando como float

                for address in red_addresses[idx_red]:
                    if [idx_par, 0, idx_wrd] == address[0:3]:
                        found = 1.0  # Marcando como float
                        score_par = found

                idx_wrd += 1

            score_red += score_par
            idx_par += 1

        # Verificação para evitar divisão por zero
        num_paragraphs = len(lst_lsts[idx_red])
        if num_paragraphs == 1:
            score_red = round(score_red, 1)
        else:
            score_red = round(score_red / (num_paragraphs - 1), 1)

        scores.append(score_red)
        idx_red += 1

    return scores

# FEATURE 4: START LINKING WORDS QUALITY
'''Função que avalia e conta os conectivos iniciais dos parágrafos, segundo uma
lista previamente preparada de acordo com os critérios do ENEM (devolve um valor
decimal suavizado entre 0 e 1).'''

def lnk_wrds_quality(lst_lsts):
    idx_red = 0
    scores = []
    palavras = []

    while idx_red < len(lst_lsts):
        idx_par = 1
        score_red = 0
        palavras_red = []

        while idx_par < len(lst_lsts[idx_red]):
            temp_sent = ' '.join(lst_lsts[idx_red][idx_par][0][0:6]).lower()

            if idx_par == 1:
                for conect in conectivos_par2:
                    if conect in temp_sent:
                        score_red += 1
                        palavras_red.append(conect)

            if idx_par == 2:
                for conect in conectivos_par3:
                    if conect in temp_sent:
                        score_red += 1
                        palavras_red.append(conect)

            if idx_par == 3 or idx_par > 3:
                for conect in conectivos_conclusao:
                    if conect in temp_sent:
                        score_red += 1
                        palavras_red.append(conect)

            idx_par += 1

        # Verificação para evitar divisão por zero
        num_paragraphs = len(lst_lsts[idx_red])
        if num_paragraphs == 1:
            score_red = round(score_red, 1)
        elif num_paragraphs == 2:
            score_red = round(score_red / (num_paragraphs - 1), 1)
        else:
            score_red = round(score_red / (num_paragraphs - 2), 1)

        if score_red > 1.0:
            score_red = 1.0

        scores.append(score_red)
        palavras.append(palavras_red)
        idx_red += 1

    return scores

  # conectivos_prioridade conectivos_continuidade conectivos_comparacao conectivos_adicao conectivos_esclarecimento conectivos_finalidade conectivos_conclusao

# FEATURE 5: ONE-SENTENCED PARAGRAPH
'''Função que verifica a quantidade de parágrafos com apenas uma sentença
em uma redação (devolve um valor suavizado entre 0 e 1).'''

def par_one_sent(lst_lsts):
  results = list()
  idx_red = 0

  while idx_red < len(lst_lsts):
    score_red = 0
    idx_par = 0
    while idx_par < len(lst_lsts[idx_red]):
      if len(lst_lsts[idx_red][idx_par]) > 1:
        score_red += 1

      idx_par += 1

    if len(lst_lsts[idx_red]) > 1:
      score_red = round((score_red / (len(lst_lsts[idx_red]))), 1)

    else:
      score_red = round((score_red / (len(lst_lsts[idx_red]) - 2)), 1)

    if score_red < 0:
      score_red = 0.0

    results.append(score_red)
    idx_red += 1

  return results

# FEATURE 6: sentence average length
'''Função que verifica o tamanho médio de sentença por redação. (devolve um
valor suavizado entre 0 e 1).'''

def tamanho_medio_sent(lst_lsts):
  general = list()
  result = list()
  i = 0

  for red in lst_lsts:
    sizes_per_red = list()
    for par in red:
      sizes_per_par = list()
      for sent in par:
        sizes_per_par.append(len(sent))
        # Tamanho médio de sentença por parágrafo.
      sizes_per_red.append(round(sum(sizes_per_par) / len(sizes_per_par), 1))
      # Tamanho médio de sentença por redação.
      if round((((sum(sizes_per_red) / len(sizes_per_red)) * 0.1) / 10), 1) > 1.0:
        general.append(1.0)
      else:
        general.append(round((((sum(sizes_per_red) / len(sizes_per_red)) * 0.1) / 10), 1))

  return general

def palavras_totais_texto(lst_lsts):
  total_palavras = 0

  # Percorrer todos os textos
  for texto in lst_lsts:
      # Percorrer todos os parágrafos (exceto o último, que é o quadro de notas)
      for paragrafo in texto[:-1]:
          # Percorrer todas as sentenças em cada parágrafo
          for sentenca in paragrafo:
              # Somar a quantidade de palavras em cada sentença
              total_palavras += len(sentenca)

  return total_palavras

# FEATURE 7: counting repeated tokens
'''Função que verifica a quantidade de repetições no texto e cria uma proporção
entre esse valor e a quantidade total de palavras (devolve um valor suavizado
entre 0 e 1).'''

from collections import defaultdict, Counter
import string

def limpar_palavra(palavra):
    # Remove sinais gráficos e preposições (adicione outras preposições conforme necessário)
    sinais_graficos = set(".,;:!?'\"()[]{}")
    preposicoes = {"a", "o", "de", "em", "para", "com", "por", "sobre", "entre",
                   "sem", "até", "desde", "antes", "após"}
    palavra = palavra.lower()
    palavra = ''.join(char for char in palavra if char not in sinais_graficos)
    if palavra in preposicoes:
        return None
    return palavra

def contar_proporcao_palavras_repetidas(lst_lsts):
    results = []

    for texto in lst_lsts:
        contador_geral = defaultdict(list)
        total_palavras_texto = 0

        # Contar palavras e registrar suas posições
        for paragrafo_idx, paragrafo in enumerate(texto[:-1]):  # Excluir o quadro de notas
            for sentenca in paragrafo:
                for pos, palavra in enumerate(sentenca):
                    palavra = limpar_palavra(palavra)
                    if palavra:
                        contador_geral[palavra].append((paragrafo_idx, pos))
                        total_palavras_texto += 1

        # Filtrar palavras que ocorrem mais de uma vez
        palavras_repetidas = {}
        for palavra, posicoes in contador_geral.items():
            if len(posicoes) > 1:
                # Verificar se as palavras estão no mesmo parágrafo ou se a distância entre elas é menor que 15 palavras
                palavras_repetidas[palavra] = 0
                for i in range(len(posicoes)):
                    for j in range(i + 1, len(posicoes)):
                        par1, pos1 = posicoes[i]
                        par2, pos2 = posicoes[j]
                        if par1 == par2 or abs(pos1 - pos2) < 15:
                            palavras_repetidas[palavra] += 1
                            break

        total_repetidas_texto = sum(palavras_repetidas.values())

        # Calcular a proporção suavizada
        if total_palavras_texto > 0:
            proporcao = total_repetidas_texto / total_palavras_texto
        else:
            proporcao = 0.0

        # Suavizar a proporção entre 0 e 1
        resultado_suavizado = round(proporcao, 1)
        results.append(resultado_suavizado)

    return results

# FEATURE 8:

def semantica_conectivos(lst_lsts):
    conectivos_par2 = ['em primeiro lugar', 'em primeira análise', 'em primeiro plano', 'em um primeiro plano',
                       'em uma primeira análise', 'em um primeiro momento', 'a princípio', 'de início',
                       'para começar', 'antes de mais nada', 'antes de tudo', 'em princípio',
                       'primeiramente', 'acima de tudo', 'principalmente', 'primordialmente',
                       'sobretudo', 'a priori', 'a posteriori', 'precipuamente']

    conectivos_par3 = ['então', 'além disso', 'sob esse viés', 'em paralelo', 'paralelamente', 'outro ',
                       'outra ', 'além da', 'além do', 'além de', 'mormente', 'em segundo lugar',
                       'secundariamente', 'ademais', 'outrossim', 'ainda mais', 'por outro lado',
                       'também', 'não só', 'não apenas', 'bem como', 'por conseguinte', 'logo depois',
                       'posteriormente', 'agora', 'já']

    conectivos_finalidade = ['com o fim de', 'a fim de', 'como propósito de', 'com a finalidade de',
                             'com o intuito de', 'para que', 'a fim de que', 'para', 'ao propósito']

    conectivos_conclusao = ['em suma', 'conclui-se', 'diante disso', 'diante do exposto',
                            'diante do que foi exposto', 'por fim', 'finalmente', 'em conclusão',
                            'concluindo', 'em síntese', 'enfim', 'em resumo', 'portanto', 'assim',
                            'dessa forma', 'dessa maneira', 'desse modo', 'logo', 'pois',
                            'assim sendo', 'nesse sentido']

    conectivos_por_paragrafo = {
        1: conectivos_par2,
        2: conectivos_par3,
        3: conectivos_finalidade + conectivos_conclusao
    }

    resultados = []

    for texto in lst_lsts:
        total_conectivos = 0
        paragrafo_relevantes = 0

        for idx_par, paragrafo in enumerate(texto[:-1], start=1):
            if idx_par in conectivos_por_paragrafo:
                paragrafo_relevantes += 1
                conectivos = conectivos_por_paragrafo[idx_par]
                paragrafo_texto = ' '.join([' '.join(sentenca) for sentenca in paragrafo]).lower()

                paragrafo_texto = ''.join(char for char in paragrafo_texto if char.isalnum() or char.isspace())

                for conectivo in conectivos:
                    conectivo = conectivo.lower().strip()
                    if conectivo in paragrafo_texto:
                        total_conectivos += 1

        max_conectivos = sum(len(conectivos_por_paragrafo[idx_par]) for idx_par in conectivos_por_paragrafo)

        # Aplicando suavização
        if max_conectivos > 0:
            proporcao = total_conectivos / max_conectivos
            resultado_suavizado = round(min(proporcao, 1.0) * 10, 1)
        else:
            resultado_suavizado = 0.0

        resultados.append(resultado_suavizado)

    return resultados

lnk_wrds_quality(indexados)[1]

semantica_conectivos(indexados)[1]

notas_competencias(indexados[27])[3]

'''Lista com os valores relativos ao atributo 1 (monobloco).'''

feature1 = count_paragraphs(corpus_tags)

'''Lista com os valores relativos ao atributo 2 (interparágrafos).'''

feature2 = score_start_lnk_wrds(corpus_enderecos, corpus_tags)

'''Lista com os valores relativos ao atributo 3 (operadores da sent 1).'''

feature3 = sent1_has_lnk_wrds(corpus_enderecos, corpus_tags)

'''Lista com os valores relativos ao atributo 4 (qualidade de operadores
na sent 1).'''

feature4 = lnk_wrds_quality(indexados)

'''Lista com os valores relativos ao atributo 5 (quantidade de parágrafos com
apenas uma sentença).'''

feature5 = par_one_sent(corpus_tags)

'''Lista com os valores relativos ao atributo 6 (tamanho médio de sentença por
redação).'''

feature6 = tamanho_medio_sent(corpus_tags)

'''Lista com os valores relativos ao atributo 7 (repetição de palavras por
tamanho do texto).'''

feature7 = contar_proporcao_palavras_repetidas(indexados)

feature8 = semantica_conectivos(indexados)

# VECTOR GENERATOR
'''Função que chama todas as funções com os atributos e as executa.
Recebe dois argumentos:
1. a lista com os endereços (função enderecos())
2. a lista com as redações tokenizadas (parágrafos, períodos...)'''

def create_vec(feat1, feat2, feat3, feat4, feat5, feat6, feat7, feat8):
  vec_list = list()
  i = 0

  while i < len(feat1):
    temp_list = list()

    # atributo1: [CHECAR INTERDEPENDÊNCIA]"quantidade" de parágrafos.
    temp_list.append(feat1[i])

    # atributo2: [ELIMINAR?] existe palavra-alvo no início do parágrafo.
    temp_list.append(feat2[i])

    # atributo3: [ELIMINAR?] existe palavra-alvo em primeira sentença de parágrafo.
    temp_list.append(feat3[i])

    # atributo4: a palavra-alvo no primeira sentença do parágrafo é adequada.
    temp_list.append(feat4[i])

    # atributo5: parágrafos com apenas uma sentença.
    temp_list.append(feat5[i])

    # atributo6: tamanho médio de sentença (por redação).
    temp_list.append(feat6[i])

    # atributo7: repetição absoluta de palavras / tamanho do texto.
    temp_list.append(feat7[i])

    # atributo8:
    temp_list.append(feat8[i])

    vec_list.append(temp_list)
    i += 1

  return vec_list

vetores = create_vec(feature1, feature2, feature3, feature4, feature5, feature6, feature7, feature8)

i = 0

while i < len(vetores):
  if vetores[i][0] == 1:
    print(i)
    i += 1
  i += 1

selecao1 = notas_indexados(indexados)

def selecao_corpus(lst_lsts):
  selection = list()
  i = 0
  class1 = 0
  class2 = 0
  class3 = 0
  class4 = 0
  class5 = 0
  class6 = 0

  while i < len(lst_lsts):
    while class1 < 20 or \
    class2 < 20 or \
    class3 < 20 or \
    class4 < 20 or \
    class5 < 20 or \
    class6 < 20:
      if lst_lsts[i][3] == 0:
        selection.append(i)
        class1 += 1
      if lst_lsts[i][3] == 40:
        selection.append(i)
        class2 += 1
      if lst_lsts[i][3] == 80:
        selection.append(i)
        class3 += 1
      if lst_lsts[i][3] == 120:
        selection.append(i)
        class4 += 1
      if lst_lsts[i][3] == 160:
        selection.append(i)
        class5 += 1
      if lst_lsts[i][3] == 200:
        selection.append(i)
        class6 += 1
    i += 1

  return selection

#selecao_corpus(selecao1)

notas_indexados(indexados)[5]

vetores[16]

# VETORES COM TODOS OS ATRIBUTOS ATUALIZADOS.

vetores[:765]

# VETORES SEM A CONTAGEM DE PARÁGRAFOS (acurácia de ~2,5% maior com multinomial NB).

indices_desejados = [0, 1, 2, 3, 4, 5, 6, 7]

i = 0
while i < len(vetores):
    # Selecionar e imprimir os itens nos índices desejados
    print([vetores[i][j] for j in indices_desejados], '\b,')
    i += 1

# Classes na comp. 4 (por nível).

textos_classe1 = len([notas_indexados(indexados).index(i) \
                          for i in notas_indexados(indexados) if i[3] == 0])
textos_classe2 = len([notas_indexados(indexados).index(i) \
                          for i in notas_indexados(indexados) if i[3] == 40])
textos_classe3 = len([notas_indexados(indexados).index(i) \
                          for i in notas_indexados(indexados) if i[3] == 80])
textos_classe4 = len([notas_indexados(indexados).index(i) \
                          for i in notas_indexados(indexados) if i[3] == 120])
textos_classe5 = len([notas_indexados(indexados).index(i) \
                          for i in notas_indexados(indexados) if i[3] == 160])
textos_classe6 = len([notas_indexados(indexados).index(i) \
                          for i in notas_indexados(indexados) if i[3] == 200])

# Procurando textos que não estejam dentro das notas das classes selecionadas.

textos_classe_und = len([notas_indexados(indexados).index(i) \
                          for i in notas_indexados(indexados) \
                         if i[3] != 0 and i[3] != 40 and i[3] != 80 \
                         and i[3] != 120 and i[3] != 160 and i[3] != 200])

print(f'{textos_classe1} textos com nota 0 na comp. 4')
print(f'{textos_classe2} textos com nota 40 na comp. 4')
print(f'{textos_classe3} textos com nota 80 na comp. 4')
print(f'{textos_classe4} textos com nota 120 na comp. 4')
print(f'{textos_classe5} textos com nota 160 na comp. 4')
print(f'{textos_classe6} textos com nota 200 na comp. 4')
print(f'{textos_classe_und} textos com nota ? na comp. 4')

# Lista com todas as 6 classes.

i = 0
todas_classes_lista = list()

while i < len(notas_indexados(indexados)):
    todas_classes_lista.append(notas_indexados(indexados)[i][3])
    i += 1

todas_classes_lista[:]

# [TESTE] Lista com apenas 3 classes: 120, 160, 200.

i = 0
suaves = list()

while i < len(notas_indexados(indexados)):
  if notas_indexados(indexados)[i][3] in [0, 40, 80]:
    suaves.append(80)
    i += 1
  else:
    suaves.append(notas_indexados(indexados)[i][3])
    i += 1

suaves[:765]

# Looking for scores other than the classes'.

i = 0
gen_class_list = [0, 40, 80, 120, 160, 200]

while i < len(notas_indexados(indexados)):
  if notas_indexados(indexados)[i][3] not in gen_class_list:
    print(i)
    i += 1
  i += 1

i = 0

while i < len(notas_indexados(indexados)):
  if notas_indexados(indexados)[i][3] == 0:
    print(i)
    i += 1
  i += 1

i = 0

while i < 200:
  if notas_indexados(indexados)[i][3] == 0:
    print('\'class1\' \b,')
  elif notas_indexados(indexados)[i][3] == 40:
    print('\'class2\' \b,')
  elif notas_indexados(indexados)[i][3] == 80:
    print('\'class3\' \b,')
  elif notas_indexados(indexados)[i][3] == 120:
    print('\'class4\' \b,')
  elif notas_indexados(indexados)[i][3] == 160:
    print('\'class5\' \b,')
  elif notas_indexados(indexados)[i][3] == 200:
    print('\'class6\' \b,')
  i += 1

# Listas com algumas conjunções.

adversativas = ['mas', 'porém', 'contudo', 'todavia', 'entretanto', 'no entanto', 'entanto', 'não obstante']
explicativas = ['porque', 'porquanto', 'pois', 'visto que', 'já que']
conclusivas = ['logo', 'portanto', 'assim', 'então', 'por isso', 'por conseguinte', 'por consequência', 'consequentemente', 'de modo que', 'desse modo', 'dessarte', 'destarte']
alternativas = ['ou', 'ora', 'quer', 'seja', 'nem']
condicionais = ['se', 'caso', 'contanto que', 'desde que', 'salvo se', 'sem que', 'a não ser que', 'a menos que', 'dado que']
aditivas = ['e', 'nem', 'bem como']