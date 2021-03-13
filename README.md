# NeuroComp

Computational Neuroscience Codes
<a href="https://github.com/limadlp/NeuroComp/tree/main/Cpp" target="blank">**Classes em C++**</a>

Para facilitar a utilização e reutilização de vários modelos de neurônios, desenvolvi uma interface computacional com diferentes modelos de redes, dinâmicas neuronais e sinapses.
O núcleo da interface se divide em duas classes: 
* “rede.h”, contendo estruturas de redes; 
* “dinamica.h”, contendo modelos de dinâmica neuronais e sinapses; 


<a href="https://github.com/limadlp/NeuroComp/tree/main/Cpp" target="blank">Aqui</a>, temos um esquema exemplos de códigos para as classes da interface:

Na classe “rede.h” temos a rede unidimensional, a rede quadrada e um tipo de rede modular hierárquica. 
Na classe “dinamica.h” temos o modelo de integra-dispara simples, o modelo de Izhikevich. e o modelo de Levina-Herrmann-Geisel simplificado. 

**<a href="https://github.com/limadlp/NeuroComp/tree/main/Julia" target="blank">Modelos de neurônios em Julia</a>**

Alguns modelos de neurônios em linguagem Julia:
  * <a href="https://github.com/limadlp/NeuroComp/blob/main/Julia/LeakyIF.ipynb" target="blank">Leaky integrate and fire </a>
  * <a href="https://github.com/limadlp/NeuroComp/blob/main/Julia/ExpoIF.ipynb" target="blank">Exponential integrate and fire </a>
  * <a href="https://github.com/limadlp/NeuroComp/blob/main/Julia/HxHuxley.ipynb" target="blank">Hodkin-Huxley </a>


**<a href="https://github.com/limadlp/NeuroComp/blob/main/DataScience/Avalanche.ipynb" target="blank">Avalanches Neuronais - Análise de dados</a>**

<a href="https://github.com/limadlp/NeuroComp/blob/main/DataScience/Avalanche.ipynb" target="blank">Aqui,</a> um breve exemplo de análise utilizando Python. 

Os dados são de uma simulação de 1024 neurônios (modelo leaky integrate and fire) numa rede quadrada. 
A partir dos dados, é obtidada o histograma da distribuição de avalanches neuronais, bem como verifica-se um comportamento de lei de potência a partir do gráfico log-log.
