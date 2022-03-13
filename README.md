# Trabalho Prático - Máquina de Busca Avançada

Uma máquina de busca é composta principalmente por três componentes: crawler, que realiza a coleta dos documentos; indexador, que lê os documentos e constrói o índice invertido; e processador de consultas, que consulta o índice e ordena os documentos de acordo com a relevância com a consulta. O índice invertido é uma estrutura simples que mapeia um conjunto de palavras aos documentos onde elas estão presentes

Para realizar as consultas tipo máquina de busca é utilizado o cálculo de similaridade proposto por Zobet et Al (2006), onde é calculado o grau de similaridade entre q e cada um dos documentos do corpus, depois ordenados, gerando um ranking de documentos por similaridade. A fórmula para esse cálculo é dada abaixo:
<p align = "center">
	<img src = "https://latex.codecogs.com/svg.image?%5Cdpi%7B110%7D%5Cbg%7Bwhite%7Dsim(d_%7Bj%7D,q)=%20%5Csum_%7Bi%20=%201%7D%5E%7BN%7D%5Cfrac%7Bw_%7Bi,j%7D%5Cast%20w_%7Bi,q%7D%7D%7BW_%7Bd%7D%7D">
</p>

<p align = "center">
	<img src = "https://latex.codecogs.com/svg.image?%5Cdpi%7B110%7D%5Cbg%7Bwhite%7DW_%7Bd%7D%20=%20%5Csqrt%7B%5Csum_%7Bt%7Dw_%7Bd,t%7D%5E%7B2%7D%7D">
</p>

Onde W<sub> d </sub> normaliza o produto interno dos vetores de pesos em função do tamanho do documento. Esta normalização dispensa percorrer novamente todo o corpus a cada consulta e, neste trabalho, W<sub> d </sub> será a raiz quadrada do número de termos distintos no documento. A normalização em função da consulta é desconsiderada por ser constante para todos os documentos.

O peso do termo é comumente computado baseado na função tf.idf (Salton, 1988). Assim o peso do termo t no documento d, w<sub> t,d </sub> é computado da seguinte forma:
<p align = "center">
	<img src = "https://latex.codecogs.com/svg.image?%5Cbg%7Bwhite%7DW_%7Bt,d%7D%20=%20f_%7Bt,d%7D%20%5Cast%20log%5Cfrac%7B%5Cleft%7C%20D%20%5Cright%7C%7D%7Bf_%7Bt%7D%7D">
	</p>
Onde f <sub> t,d </sub> é a frequência do termo t no documento d, f <sub> t </sub> é número de documentos na base que possuem o termo t e |D| é o número total de documentos na base.

O segundo fator na equação corresponde à raridade do termo, que seria o inverso da frequência nos documentos da base (idf: inverse document frequency). O valor do idf tende a ser muito alto quando o termo é bastante raro, e por isto é amortizado com a função log

Já o valor de w<sub> i,q </sub> é um vetor binário, onde a posição recebe valor 1 se o termo ocorre na consulta e valor 0 caso contrário. A máquina de busca trata de consultas de mais de um termo usando o operador OU, ou seja, a consulta retorna todos os documentos que possuem um ou outro termo.

Neste trabalho prático foi desenvolvido um indexador em memória e um processador de consultas. O indexador percorre os documentos da base (corpus) e, para cada termo, relaciona os documentos em que eles aparecem e com que frequência, criando o índice invertido. O processador de consultas calcula a similaridade de cada consulta com cada documento do corpus, retornando os 10 documentos mais similares à consulta. Logo, a entrada será um arquivo texto contendo a consulta na primeira linha. A saída será uma lista ordenada com os IDs dos 10 documentos mais relevantes.

A base com documentos (corpus) será uma pasta onde os arquivos contidos correspondem aos seus documentos, e o nome de cada arquivo corresponde ao ID do documento. 

Além disso, algumas palavras são muito frequentes e carregam pouca informação (tais como artigos, conjunções, sujeitos ,etc), e são conhecidas como stopwords. Estas palavras são descartadas na indexação e na consulta, e lidas do arquivo stopwords.txt - uma palavra por linha.

A documentação completa de implementação e instruções para compilação e uso estão presentes no arquivo Documentação.pdf, ou [Aqui](https://l.linklyhq.com/l/lZx4)
