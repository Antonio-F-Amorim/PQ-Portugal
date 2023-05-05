 byte tamanho[4]={61,1,1,1};
byte tecto[68]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
byte esquerda[1]={255};
byte direita[1]={255};
byte frente[1]={255};


byte* linhas[4]={tecto,esquerda,direita,frente};
uint16_t pins[4]={6,5,10,9};

Masc Beco(4,pins,linhas,tamanho);



byte tam[1]={3};
byte dir[3]={20,21,25};
byte* lis[1]={dir};
uint16_t pis[1]={10};

Masc Coracao(1,pis,lis,tam);