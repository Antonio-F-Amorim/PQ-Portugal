byte tamanho[2] = {13,13};
byte esquerda[13]={7,8,9,25,26,27,43,44,45,61,62,63,79};
byte direita[13]={2,3,4,9,10,11,16,17,18,23,24,25,30};
byte* linhas[2]={esquerda,direita};
uint16_t pins[2]={9,7};

Masc Telma(2,pins,linhas,tamanho);