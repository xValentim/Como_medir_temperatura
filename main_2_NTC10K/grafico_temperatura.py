import numpy as np
import matplotlib.pyplot as plt
import pandas as pd 

# Comando para abrir o arquivo .csv utilizando o pandas
tabela = pd.read_csv('data.csv')

# Nesse passo, abra o arquivo data.csv e veja que a primeira linha representa as colunas

# Guarda a coluna do tempo em uma lista de tempo
lista_t = tabela['Tempo']

# Guarda a coluna da temperatura com media e sem media do ntc1 em uma lista
T_medio_ntc1 = tabela['Tntc1 medio']
T_ntc1 = tabela['Tntc1']

# Guarda a coluna da temperatura com media e sem media do ntc1 em uma lista
T_medio_ntc2 = tabela['Tntc2 medio']
T_ntc2 = tabela['Tntc2']

# Plota agora o gráfico de temperatura x tempo
plt.plot(lista_t, T_ntc1, label='Sem medias')
plt.plot(lista_t, T_medio_ntc1, label='Com medias')
plt.axis([-10, 300, 28, 32])
plt.xlabel('Tempo')
plt.ylabel('Temperatura')
plt.grid(True)
plt.legend()
plt.show()