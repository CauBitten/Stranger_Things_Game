#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_vazia(int size, char sala[size][size]) {
  for (int l = 0; l < size; l++) {
    for (int c = 0; c < size; c++) {
      sala[l][c] = '_';
    }
  }
}

void imprimir(int size, char sala[size][size]) {
  for (int l = 0; l < size; l++) {
    for (int c = 0; c < size; c++) {

      // Para os demondogs ficarem invisíveis
      if (sala[l][c] == 'D') {

        printf("_   ");
      } else {

        printf("%c   ", sala[l][c]);
      }
    }
    printf("\n\n");
  }
}

void i_personagem(int size, char sala[size][size], char personagem, int l,
                  int c) {
  for (int i = 1; i <= 1;) {

    if (sala[l][c] == '_') {
      sala[l][c] = personagem;

      i++;
    }
  }
}

void i_objeto(int size, char sala[size][size], char objeto, int quantidade) {
  for (int o = 1; o <= quantidade;) {

    int l = rand() % size;
    int c = rand() % size;

    if (sala[l][c] == '_') {

      sala[l][c] = objeto;
      o++;
    }
  }
}

void i_objeto_in_range(int size, char matriz[size][size], int l_centro,
                       int c_centro, int raio) {

  // Se chegar a 8, é a ultima posição que pode spawnar inimigo
  int contador = 0;

  for (int i = 1; i < 3;) {
    contador++;

    int l_demon = rand() % size;
    int c_demon = rand() % size;

    int priFracao = pow((l_demon - l_centro), 2);
    int segFracao = pow((c_demon - c_centro), 2);

    int distanciaEntrePontos = sqrt(priFracao + segFracao);

    if (distanciaEntrePontos <= raio) {

      if (matriz[l_demon][c_demon] == '_') {

        matriz[l_demon][c_demon] = 'D';
        i++;

        // Se for a ultima posição e não estiver disponível, não spawna D
      } else if (contador == 8 && matriz[l_demon][c_demon] != '_' && i == 1) {
        i += 2;

        // Se for a ultima posição e não estiver disponível, não spawna D
      } else if (contador == 8 && matriz[l_demon][c_demon] != '_' && i == 2) {
        i++;
      }
    }
  }
}

int init_portal(int *vida) {
  int taxa_de_raiva = 0;

  do {

    taxa_de_raiva = rand() % 101;

    if (taxa_de_raiva >= 60) {

      printf("Vida Eleven: %i\tTaxa de Raiva: %i\n\n", *vida, taxa_de_raiva);
      printf("Eleven conseguiu criar o portal\n\n");
      return 1;

    } else {

      *vida -= 20;
    }

    printf("Vida Eleven: %i\tTaxa de Raiva: %i\n\n", *vida, taxa_de_raiva);

  } while (*vida > 0);

  if (vida == 0) {
    printf("Eleven morreu ao tentar criar o portal\n\n");
  }

  return 0;
}

int main(void) {

  srand(time(NULL));

  char sala[3][3];
  char mundo_invertido[10][10];

  // Iniciando as matrizes com espaços disponíveis
  init_vazia(3, sala);
  init_vazia(10, mundo_invertido);
  //

  // Iniciando os objetos
  i_objeto(10, mundo_invertido, '@', 10); // 10 Árvores
  i_objeto(10, mundo_invertido, 'C', 5);  // 5 Carros
  i_objeto(10, mundo_invertido, 'A', 5);  // 5 Casas Abandonadas
  i_objeto(10, mundo_invertido, 'D', 4);  // 4 Demondogs
  i_objeto(10, mundo_invertido, '.', 10); // 10 Panquecas
  //

  // Iniciando o Will
  int l_Will = rand() % 10;
  int c_Will = rand() % 10;
  i_personagem(10, mundo_invertido, 'W', l_Will, c_Will);
  //

  // Variáveis da Eleven
  int vida_eleven = 100;
  int *v_eleven = &vida_eleven;
  int l_eleven = rand() % 3, c_eleven = rand() % 3;
  //

  // Inicialização do portal se der certo a taxa de raiva
  int portal = init_portal(v_eleven);

  int l_portal = rand() % 3, c_portal = rand() % 3;

  if (portal == 1) {

    sala[l_portal][c_portal] = 'O';
    mundo_invertido[l_portal][c_portal] = 'O';
  }
  //

  // Iniciando a Eleven
  i_personagem(3, sala, 'E', l_eleven, c_eleven);
  //

  // Imprimindo a primeira matriz - Escola -
  imprimir(3, sala);
  //

  // Variável Raio para a distância entre Will e Eleven
  int r;

  // Váriável para ser o tamanho da matriz
  int size;

  // Variável para controle do portal
  int entrou_portal = 0;

  // Variável para controle se Eleven está com Will
  int eleven_estacom_will = 0;

  // Variável para saber se Eleven saiu do Mundo Invertido
  int escapou = 0;

  // V. para controle da movimentação do Will
  int will_stop = 0;

  // V. para movimentação
  char mov;

  // Jogo
  do {

    printf("\n\n> ");
    scanf("%c", &mov);
    getchar();

    system("cls");

    // Na sala
    if (entrou_portal == 0) {
      printf("Vida Eleven: %i\n\n", *v_eleven);

      size = 3;

      // Movimentação na sala 3x3
      switch (mov) {
      case 'w':
        // Para não sair do sala
        if (l_eleven - 1 >= 0) {

          // Próxima posição sendo o portal
          if (sala[l_eleven - 1][c_eleven] == 'O') {
            sala[l_eleven][c_eleven] = '_';

            l_eleven--;

            entrou_portal = 1;
            break;

            // Novas posiçoes sendo _
          } else {
            sala[l_eleven][c_eleven] = '_';

            l_eleven--;
            i_personagem(size, sala, 'E', l_eleven, c_eleven);
          }
        }
        break;
      case 'a':
        // Para não sair do sala
        if (c_eleven - 1 >= 0) {

          // Próxima posição sendo o portal
          if (sala[l_eleven][c_eleven - 1] == 'O') {
            sala[l_eleven][c_eleven] = '_';

            c_eleven--;

            entrou_portal = 1;
            break;

            // Novas posiçoes sendo _
          } else {
            sala[l_eleven][c_eleven] = '_';

            c_eleven--;
            i_personagem(size, sala, 'E', l_eleven, c_eleven);
          }
        }
        break;
      case 's':
        // Para não sair do sala
        if (l_eleven + 1 < size) {

          // Próxima posição sendo o portal
          if (sala[l_eleven + 1][c_eleven] == 'O') {
            sala[l_eleven][c_eleven] = '_';

            l_eleven++;

            entrou_portal = 1;
            break;

            // Novas posiçoes sendo _
          } else {
            sala[l_eleven][c_eleven] = '_';

            l_eleven++;
            i_personagem(size, sala, 'E', l_eleven, c_eleven);
          }
        }
        break;
      case 'd':
        // Para não sair do sala
        if (c_eleven + 1 < size) {

          // Próxima posição sendo o portal
          if (sala[l_eleven][c_eleven + 1] == 'O') {
            sala[l_eleven][c_eleven] = '_';

            c_eleven++;

            entrou_portal = 1;
            break;

            // Novas posiçoes sendo _
          } else {
            sala[l_eleven][c_eleven] = '_';

            c_eleven++;
            i_personagem(size, sala, 'E', l_eleven, c_eleven);
          }
        }
        break;
      }

      imprimir(size, sala);
    }
    //

    // No Mundo Invertido
    if (entrou_portal) {
      system("cls");

      size = 10;

      if (eleven_estacom_will == 0 && will_stop == 0) {
        // Movimentação Aleatória do Will
        for (int i = 1; i <= 1;) {
          int aleatorio = rand() % 4 + 1;

          // W
          if (aleatorio == 1) {

            if (l_Will - 1 >= 0) {

              if (mundo_invertido[l_Will - 1][c_Will] != '@' &&
                  mundo_invertido[l_Will - 1][c_Will] != 'A' &&
                  mundo_invertido[l_Will - 1][c_Will] != 'C' &&
                  mundo_invertido[l_Will - 1][c_Will] != 'O' &&
                  mundo_invertido[l_Will - 1][c_Will] != 'D') {

                if (mundo_invertido[l_Will - 1][c_Will] == '_') {

                  mundo_invertido[l_Will][c_Will] = '_';

                  l_Will--;
                  mundo_invertido[l_Will][c_Will] = 'W';
                  i++;
                }
              }
            }
          }

          // S
          if (aleatorio == 2) {

            if (l_Will + 1 < size) {

              if (mundo_invertido[l_Will + 1][c_Will] != '@' &&
                  mundo_invertido[l_Will + 1][c_Will] != 'A' &&
                  mundo_invertido[l_Will + 1][c_Will] != 'C' &&
                  mundo_invertido[l_Will + 1][c_Will] != 'O' &&
                  mundo_invertido[l_Will + 1][c_Will] != 'D') {

                if (mundo_invertido[l_Will + 1][c_Will] == '_') {

                  mundo_invertido[l_Will][c_Will] = '_';

                  l_Will++;
                  mundo_invertido[l_Will][c_Will] = 'W';
                  i++;
                }
              }
            }
          }

          // A
          if (aleatorio == 3) {

            if (c_Will - 1 >= 0) {

              if (mundo_invertido[l_Will][c_Will - 1] != '@' &&
                  mundo_invertido[l_Will][c_Will - 1] != 'A' &&
                  mundo_invertido[l_Will][c_Will - 1] != 'C' &&
                  mundo_invertido[l_Will][c_Will - 1] != 'O' &&
                  mundo_invertido[l_Will][c_Will - 1] != 'D') {

                if (mundo_invertido[l_Will][c_Will - 1] == '_') {

                  mundo_invertido[l_Will][c_Will] = '_';

                  c_Will--;
                  mundo_invertido[l_Will][c_Will] = 'W';
                  i++;
                }
              }
            }
          }

          // D
          if (aleatorio == 4) {

            if (c_Will + 1 < size) {

              if (mundo_invertido[l_Will][c_Will + 1] != '@' &&
                  mundo_invertido[l_Will][c_Will + 1] != 'A' &&
                  mundo_invertido[l_Will][c_Will + 1] != 'C' &&
                  mundo_invertido[l_Will][c_Will + 1] != 'O' &&
                  mundo_invertido[l_Will][c_Will + 1] != 'D') {

                if (mundo_invertido[l_Will][c_Will + 1] == '_') {

                  mundo_invertido[l_Will][c_Will] = '_';

                  c_Will++;
                  mundo_invertido[l_Will][c_Will] = 'W';
                  i++;
                }
              }
            }
          }
        }
        //
      }

      // Movimentação no Mundo Invertido
      switch (mov) {
      case 'w':
        // Para não sair do sala
        if (l_eleven - 1 >= 0) {

          // Verifica se nova posição não é um obstáculo
          if (mundo_invertido[l_eleven - 1][c_eleven] != '@' &&
              mundo_invertido[l_eleven - 1][c_eleven] != 'A' &&
              mundo_invertido[l_eleven - 1][c_eleven] != 'C') {

            // Verificar se a nova p é um demondog
            if (mundo_invertido[l_eleven - 1][c_eleven] == 'D') {
              *v_eleven -= 10;

              printf("Eleven encontrou um inimigo!\n\n");

              if (eleven_estacom_will) {

                l_Will = l_eleven;
                c_Will = c_eleven;

                mundo_invertido[l_Will][c_Will] = 'W';

                l_eleven--;
                mundo_invertido[l_eleven][c_eleven] = 'E';

                eleven_estacom_will = 0;

              } else {

                mundo_invertido[l_eleven][c_eleven] = '_';

                l_eleven--;
                mundo_invertido[l_eleven][c_eleven] = 'E';
              }

              // Verificar se a nova p é uma panqueca
            } else if (mundo_invertido[l_eleven - 1][c_eleven] == '.') {

              if (*v_eleven > 95) {
                *v_eleven = 100;
              } else if (*v_eleven <= 95) {
                *v_eleven += 5;
              }

              mundo_invertido[l_eleven][c_eleven] = '_';

              l_eleven--;
              mundo_invertido[l_eleven][c_eleven] = 'E';

              // Próxima posição sendo o Will
            } else if (mundo_invertido[l_eleven - 1][c_eleven] == 'W') {

              mundo_invertido[l_eleven][c_eleven] = '_';

              l_eleven--;
              mundo_invertido[l_eleven][c_eleven] = 'E';

              eleven_estacom_will = 1;

              printf("Eleven pegou Will!\n\n");

              // Próxima posição sendo o portal
            } else if (mundo_invertido[l_eleven - 1][c_eleven] == 'O' &&
                       eleven_estacom_will == 1) {
              mundo_invertido[l_eleven][c_eleven] = '_';

              escapou = 1;

              // Se Eleven tentar entrar no portal sem Will
            } else if (mundo_invertido[l_eleven - 1][c_eleven] == 'O' &&
                       eleven_estacom_will == 0) {

              mundo_invertido[l_eleven][c_eleven] = 'E';

              printf("Você precisa escapar com Will!\n\n");

              // Para o portal não sumir
            } else if (mundo_invertido[l_eleven][c_eleven] == 'O') {

              mundo_invertido[l_eleven][c_eleven] = 'O';

              l_eleven--;
              i_personagem(size, mundo_invertido, 'E', l_eleven, c_eleven);

              // Novas posiçoes sendo _
            } else {
              mundo_invertido[l_eleven][c_eleven] = '_';

              l_eleven--;
              i_personagem(size, mundo_invertido, 'E', l_eleven, c_eleven);
            }
          }
        }
        break;
      case 'a':
        // Para não sair do sala
        if (c_eleven - 1 >= 0) {

          // Verifica se nova posição não é um obstáculo
          if (mundo_invertido[l_eleven][c_eleven - 1] != '@' &&
              mundo_invertido[l_eleven][c_eleven - 1] != 'A' &&
              mundo_invertido[l_eleven][c_eleven - 1] != 'C') {

            // Verificar se a nova p é um demondog
            if (mundo_invertido[l_eleven][c_eleven - 1] == 'D') {
              *v_eleven -= 10;

              printf("Eleven encontrou um inimigo!\n\n");

              if (eleven_estacom_will) {

                l_Will = l_eleven;
                c_Will = c_eleven;

                mundo_invertido[l_Will][c_Will] = 'W';

                c_eleven--;
                mundo_invertido[l_eleven][c_eleven] = 'E';

                eleven_estacom_will = 0;

              } else {

                mundo_invertido[l_eleven][c_eleven] = '_';

                c_eleven--;
                mundo_invertido[l_eleven][c_eleven] = 'E';
              }

              // Verificar se a nova p é uma panqueca
            } else if (mundo_invertido[l_eleven][c_eleven - 1] == '.') {

              if (*v_eleven > 95) {
                *v_eleven = 100;
              } else if (*v_eleven <= 95) {
                *v_eleven += 5;
              }

              mundo_invertido[l_eleven][c_eleven] = '_';

              c_eleven--;
              mundo_invertido[l_eleven][c_eleven] = 'E';

              // Próxima posição sendo o Will
            } else if (mundo_invertido[l_eleven][c_eleven - 1] == 'W') {

              mundo_invertido[l_eleven][c_eleven] = '_';

              c_eleven--;
              mundo_invertido[l_eleven][c_eleven] = 'E';

              eleven_estacom_will = 1;

              printf("Eleven pegou Will!\n\n");

              // Próxima posição sendo o portal
            } else if (mundo_invertido[l_eleven][c_eleven - 1] == 'O' &&
                       eleven_estacom_will == 1) {
              mundo_invertido[l_eleven][c_eleven] = '_';

              escapou = 1;

              // Se Eleven tentar entrar no portal sem Will
            } else if (mundo_invertido[l_eleven][c_eleven - 1] == 'O' &&
                       eleven_estacom_will == 0) {

              mundo_invertido[l_eleven][c_eleven] = 'E';

              printf("Você precisa escapar com Will!\n\n");

              // Para o portal não sumir
            } else if (mundo_invertido[l_eleven][c_eleven] == 'O') {

              mundo_invertido[l_eleven][c_eleven] = 'O';

              c_eleven--;
              i_personagem(size, mundo_invertido, 'E', l_eleven, c_eleven);

              // Novas posiçoes sendo _
            } else {
              mundo_invertido[l_eleven][c_eleven] = '_';

              c_eleven--;
              i_personagem(size, mundo_invertido, 'E', l_eleven, c_eleven);
            }
          }
        }
        break;
      case 's':
        // Para não sair do sala
        if (l_eleven + 1 < size) {

          // Verifica se nova posição não é um obstáculo
          if (mundo_invertido[l_eleven + 1][c_eleven] != '@' &&
              mundo_invertido[l_eleven + 1][c_eleven] != 'A' &&
              mundo_invertido[l_eleven + 1][c_eleven] != 'C') {

            // Verificar se a nova p é um demondog
            if (mundo_invertido[l_eleven + 1][c_eleven] == 'D') {
              *v_eleven -= 10;

              printf("Eleven encontrou um inimigo!\n\n");

              if (eleven_estacom_will) {

                l_Will = l_eleven;
                c_Will = c_eleven;

                mundo_invertido[l_Will][c_Will] = 'W';

                l_eleven++;
                mundo_invertido[l_eleven][c_eleven] = 'E';

                eleven_estacom_will = 0;

              } else {

                mundo_invertido[l_eleven][c_eleven] = '_';

                l_eleven++;
                mundo_invertido[l_eleven][c_eleven] = 'E';
              }

              // Verificar se a nova p é uma panqueca
            } else if (mundo_invertido[l_eleven + 1][c_eleven] == '.') {

              if (*v_eleven > 95) {
                *v_eleven = 100;
              } else if (*v_eleven <= 95) {
                *v_eleven += 5;
              }

              mundo_invertido[l_eleven][c_eleven] = '_';

              l_eleven++;
              mundo_invertido[l_eleven][c_eleven] = 'E';

              // Próxima posição sendo o Will
            } else if (mundo_invertido[l_eleven + 1][c_eleven] == 'W') {

              mundo_invertido[l_eleven][c_eleven] = '_';

              l_eleven++;
              mundo_invertido[l_eleven][c_eleven] = 'E';

              eleven_estacom_will = 1;

              printf("Eleven pegou Will!\n\n");

              // Próxima posição sendo um portal
            } else if (mundo_invertido[l_eleven + 1][c_eleven] == 'O' &&
                       eleven_estacom_will == 1) {
              mundo_invertido[l_eleven][c_eleven] = '_';

              escapou = 1;

              // Se Eleven tentar escapar sem o Will
            } else if (mundo_invertido[l_eleven + 1][c_eleven] == 'O' &&
                       eleven_estacom_will == 0) {

              mundo_invertido[l_eleven][c_eleven] = 'E';

              printf("Você precisa escapar com Will!\n\n");

              // Para o portal não sumir
            } else if (mundo_invertido[l_eleven][c_eleven] == 'O') {

              mundo_invertido[l_eleven][c_eleven] = 'O';

              l_eleven++;
              i_personagem(size, mundo_invertido, 'E', l_eleven, c_eleven);

              // Novas posiçoes sendo _
            } else {
              mundo_invertido[l_eleven][c_eleven] = '_';

              l_eleven++;
              i_personagem(size, mundo_invertido, 'E', l_eleven, c_eleven);
            }
          }
        }
        break;
      case 'd':
        // Para não sair do sala
        if (c_eleven + 1 < size) {

          // Verifica se nova posição não é um obstáculo
          if (mundo_invertido[l_eleven][c_eleven + 1] != '@' &&
              mundo_invertido[l_eleven][c_eleven + 1] != 'A' &&
              mundo_invertido[l_eleven][c_eleven + 1] != 'C') {

            // Verificar se a nova p é um demondog
            if (mundo_invertido[l_eleven][c_eleven + 1] == 'D') {
              *v_eleven -= 10;

              printf("Eleven encontrou um inimigo!\n\n");

              if (eleven_estacom_will) {

                l_Will = l_eleven;
                c_Will = c_eleven;

                mundo_invertido[l_Will][c_Will] = 'W';

                c_eleven++;
                mundo_invertido[l_eleven][c_eleven] = 'E';

                eleven_estacom_will = 0;

              } else {

                mundo_invertido[l_eleven][c_eleven] = '_';

                c_eleven++;
                mundo_invertido[l_eleven][c_eleven] = 'E';
              }

              // Verificar se a nova p é uma panqueca
            } else if (mundo_invertido[l_eleven][c_eleven + 1] == '.') {

              if (*v_eleven > 95) {
                *v_eleven = 100;
              } else if (*v_eleven <= 95) {
                *v_eleven += 5;
              }

              mundo_invertido[l_eleven][c_eleven] = '_';

              c_eleven++;
              mundo_invertido[l_eleven][c_eleven] = 'E';

              // Próxima posição sendo o Will
            } else if (mundo_invertido[l_eleven][c_eleven + 1] == 'W') {

              mundo_invertido[l_eleven][c_eleven] = '_';

              c_eleven++;
              mundo_invertido[l_eleven][c_eleven] = 'E';

              eleven_estacom_will = 1;

              printf("Eleven pegou Will!\n\n");

              // Próxima posição sendo um portal
            } else if (mundo_invertido[l_eleven][c_eleven + 1] == 'O' &&
                       eleven_estacom_will == 1) {
              mundo_invertido[l_eleven][c_eleven] = '_';

              escapou = 1;

              // Se Eleven tentar escapar sem o Will
            } else if (mundo_invertido[l_eleven][c_eleven + 1] == 'O' &&
                       eleven_estacom_will == 0) {

              mundo_invertido[l_eleven][c_eleven] = 'E';

              printf("Você precisa escapar com Will!\n\n");

              // Para o portal não sumir
            } else if (mundo_invertido[l_eleven][c_eleven] == 'O') {

              mundo_invertido[l_eleven][c_eleven] = 'O';

              c_eleven++;
              i_personagem(size, mundo_invertido, 'E', l_eleven, c_eleven);

              // Novas posiçoes sendo _
            } else {
              mundo_invertido[l_eleven][c_eleven] = '_';

              c_eleven++;
              i_personagem(size, mundo_invertido, 'E', l_eleven, c_eleven);
            }
          }
        }
        break;
      }

      // Verificar distância de Eleven e Will
      if (eleven_estacom_will == 0) {
        r = 2;

        int priFracao = pow((l_Will - l_eleven), 2);
        int segFracao = pow((c_Will - c_eleven), 2);

        int distanciaEntrePontos = sqrt(priFracao + segFracao);

        if (distanciaEntrePontos <= r) {
          i_objeto_in_range(size, mundo_invertido, l_eleven, c_eleven, 1);
        }
      }
      //

      // Se Eleven chegar a uma casa de pegar Will, ele para
      if (mundo_invertido[l_Will - 1][c_Will] == 'E' ||
          mundo_invertido[l_Will + 1][c_Will] == 'E' ||
          mundo_invertido[l_Will][c_Will - 1] == 'E' ||
          mundo_invertido[l_Will][c_Will + 1] == 'E') {

        will_stop = 1;
      }
      //

      // Para se o portal sumir, ele volta
      if (mundo_invertido[l_portal][c_portal] != 'O') {

        mundo_invertido[l_portal][c_portal] = 'O';
      }
      //

      printf("Vida Eleven: %i\n\n", *v_eleven);

      imprimir(size, mundo_invertido);
    }

    // Se entrou no portal de volta
    if (escapou == 1) {
      break;
    }

  } while (mov != 'x' && *v_eleven > 0 && portal == 1);
  //

  system("cls");

  if (escapou == 1) {
    printf("Eleven escapou com Will!\n\n");

    i_objeto(3, sala, 'E', 1);
    i_objeto(3, sala, 'W', 1);

    imprimir(3, sala);
  } else if (escapou == 0 && vida_eleven <= 0) {

    printf("Eleven morreu ao tentar resgatar Will!\n\n");
  }

  return 0;
}