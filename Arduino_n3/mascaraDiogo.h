const byte tamanho[3] = {28,13,7};
const byte esquerda[28]={4,5,6,16,15,14,13,17,18,28,27,26,25,29,30,40,39,38,37,41,42,52,51,50,49,53,54};
const byte direita[13]={4,6,5,15,17,16,26,28,27,37,39,38,47};
byte tecto[7]={16,17,18,19,20,22,21};
byte* linhas[3]={esquerda,direita,tecto};
uint16_t pins[3]={11,8,6};
Masc Diogo(3,pins,linhas,tamanho);