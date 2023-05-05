# Programa para monitorização ECG

## Prévia
![Prévia do ECG](./img/p.png)

**Representação simples para análise do ECG:**
![Representação simples para análise do ECG](./img/R.png)

- Em alguns casos, é comum ver ondas P precedentes, que leva ao quadro de extrassístole ventricular, o que é nada a se preocupar, é apenas uma situação adrenérgica que pode ser controlada por betabloqueadores.
- Também é comum encontrar uma repolarização ventricular, nada fora da normalidade.

![Segundo exemplo simples para análise de ECG](./img/R2.png)

## Hardware usado:

- Sensor de ECG AD8232

- Arduino UNO R3

- Alguma ProtoBoard


## Conexões


| Board Labal | Pin Function |Arduino |
|---|---|---| 
| GND | Ground | GND |
|3.3v|3.3v Power Supply| 3.3v |
|Output|Output Sgnal| A0|
|LO-|Leads-off Detect -| 11 |
|LO+| Leads-off Detect +|10|
|SDN|Shutdown|Not used|


## Posições dos eletrodos:

(as conexões não seguem o padrão hospitalar por ser um equipamento simples)

- Vermelho -> RA
- Amarelo -> LA
- Verde -> RL

## Representação das conexões

![Representação das conexões](./img/figura-1.png)
