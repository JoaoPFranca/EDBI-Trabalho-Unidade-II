#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
using namespace std::chrono;

#include <vector>

// 5. Implemente um dos algoritmos de ordenação por distribuição: escolha entre o counting sort e o radix sort. Eu escolhi o counting sort.
vector<int> countingSort(vector<int> vetor) {
  vector<int> vetorFinal(vetor.size());

  int maiorValor = 0;
  for (int i = 0; i < vetor.size(); i++) {
    if (vetor[i] > maiorValor) {
      maiorValor = vetor[i];
    }
  }

  vector<int> vetorContagem(maiorValor + 1);

  for (int i = 0; i < vetor.size(); i++) {
    int posicaoASerAumentada = vetor[i];
    vetorContagem[posicaoASerAumentada] += 1;
  }

  for (int i = 1; i <= vetorContagem.size(); i++) {
    vetorContagem[i] += vetorContagem[(i - 1)];
  }

  for (int i = vetor.size() - 1; i >= 0; i--) {
    vetorFinal[vetorContagem[vetor[i]] - 1] = vetor[i];
    vetorContagem[vetor[i]]--;
  }
  return vetorFinal;
}

//A função de merging para o Merge Sort.
void merge(vector<int> &vetor, int esq, int meio, int dir) {
  vector<int> vetorEsq(meio - esq + 1);
  vector<int> vetorDir(dir - meio);

  for (int i = 0; i < vetorEsq.size(); i++) {
    vetorEsq[i] = vetor[esq + i];
  }

  for (int i = 0; i < vetorDir.size(); i++) {
    vetorDir[i] = vetor[meio + 1 + i];
  }

  int iesq = 0;
  int idir = 0;
  int icomp = esq;
  while (iesq < vetorEsq.size() && idir < vetorDir.size()) {
    if (vetorEsq[iesq] <= vetorDir[idir]) {
      vetor[icomp] = vetorEsq[iesq];
      iesq++;
    } else {
      vetor[icomp] = vetorDir[idir];
      idir++;
    }
    icomp++;
  }

  while (iesq < vetorEsq.size()) {
    vetor[icomp] = vetorEsq[iesq];
    iesq++;
    icomp++;
  }

  while (idir < vetorEsq.size()) {
    vetor[icomp] = vetorDir[idir];
    idir++;
    icomp++;
  }
}

// 4. Implemente um dos algoritmos de complexidade O(nlogn): escolha entre o algoritmo merge sort e o insertion sort. Eu escolhi o merge sort.

// Ao invés de retornar um vector<int> como as outras funções, fiz apenas com a mudança do vector original o passando como referência. Tal técnica foi utilizada para evitar a criação da cópia de um novo vetor a cada recursão, o que, nos testes feitos, mostrou-se uma otimização necessária.
void mergeSort(vector<int> &vetor, int esq, int dir) {
  if (esq < dir) {
    int meio = esq + (dir - esq) / 2;

    mergeSort(vetor, esq, meio);
    mergeSort(vetor, meio + 1, dir);

    merge(vetor, esq, meio, dir);
  }
}

// 3. Implemente um dos algoritmos de complexidade O(n²): escolha entre o algoritmo insertion sort e o selection sort. Eu escolhi o selection sort.
vector<int> selectionSort(vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    int minimoSemOrd = i;
    for (int j = i + 1; j < vetor.size(); j++) {
      if (vetor[j] < vetor[minimoSemOrd]) {
        minimoSemOrd = j;
      }
    }
    if (minimoSemOrd != i) {
      int auxiliar = vetor[i];
      vetor[i] = vetor[minimoSemOrd];
      vetor[minimoSemOrd] = auxiliar;
    }
  }
  return vetor;
}

// 2. Implemente um algoritmo que dado um vetor de entrada A, retorne
// verdadeiro em caso do vetor está ordenado e falso caso contrário.
int verificacaoVetor(vector<int> vetor) {
  for (int i = 0; i <= vetor.size(); i++) {
    if (vetor[i] > vetor[i + 1]) {
      return 1;
    }
  }
  return 0;
}

// Extra: Função feita para printar o vetor e facilitar a visualização da ordenação.
void printarVetor(vector<int> vetor) {
  cout << "[";
  for (int i = 0; i < vetor.size(); i++) {
    if (i < (vetor.size() - 1)) {
      cout << vetor[i] << ", ";
    } else {
      cout << vetor[i];
    }
  }
  cout << "]";
}

int main() {
  int tamanhoVetor;
  vector<int> vetor;
  cout << "Qual vai ser o tamanho do vetor?\n";
  cin >> tamanhoVetor;
  srand(time(NULL));
  for (int i = 0; i < tamanhoVetor; i++) {
    int numeroAleatorio = rand() % (tamanhoVetor + 1);
    vetor.push_back(numeroAleatorio);
  }
  
  cout << "\n";
  cout << "----------------------------------------\n";
  cout << "|                                      |\n";
  cout << "|      Escolha a operação desejada:    |\n";
  cout << "|                                      |\n";
  cout << "----------------------------------------\n";
  cout << "|                                      |\n";
  cout << "| 1 - Algoritmo O(n²): Selection Sort  |\n";
  cout << "| 2 - Algoritmo O(nlogn): Merge Sort   |\n";
  cout << "| 3 - Ord. por dist.: Counting Sort    |\n";
  cout << "|                                      |\n";
  cout << "----------------------------------------\n";
  
  int opcao;
  cin >> opcao;
  
  vector<int> vetorOrdenado;
  
  if (opcao == 1) {
    auto start = steady_clock::now();
    vetorOrdenado = selectionSort(vetor);
    auto end = steady_clock::now();
    auto tempoExec = duration_cast<nanoseconds>(end - start);
    cout << "\n";
    cout << "Tempo do selection sort com o vetor de tamanho indicado:";
    cout << tempoExec.count() << "ns\n";
  }
  if (opcao == 2) {
    int maximoEsquerdo = 0;
    int maximoDireito = vetor.size();
    auto start = steady_clock::now();
    mergeSort(vetor, maximoEsquerdo, maximoDireito);
    vetorOrdenado = vetor;
    auto end = steady_clock::now();
    auto tempoExec = duration_cast<nanoseconds>(end - start);
    cout << "\n";
    cout << "Tempo do merge sort com o vetor de tamanho indicado:";
    cout << tempoExec.count() << "ns\n";
  }
  if (opcao == 3) {
    auto start = steady_clock::now();
    vetorOrdenado = countingSort(vetor);
    auto end = steady_clock::now();
    auto tempoExec = duration_cast<nanoseconds>(end - start);
    cout << "\n";
    cout << "Tempo do counting sort com o vetor de tamanho indicado:";
    cout << tempoExec.count() << "ns\n";
  }
   
  cout << "----------------------------------------\n";
  cout << "|                                      |\n";
  cout << "|     Deseja verificar a ordenação?    |\n";
  cout << "|                                      |\n";
  cout << "|           1 - Sim, 2 - Não           |\n";
  cout << "----------------------------------------\n";
  
  int verificar;
  cin >> verificar;
  if (verificar == 1) {
    cout << "O vetor foi ordenado? ";
    if (verificacaoVetor(vetorOrdenado)) {
      cout << "Sim\n";
    } else {
      cout << "Não\n";
    }
  }
  
  cout << "----------------------------------------\n";
  cout << "|                                      |\n";
  cout << "|      Deseja ver o vetor ordenado?    |\n";
  cout << "|                                      |\n";
  cout << "|           1 - Sim, 2 - Não           |\n";
  cout << "----------------------------------------\n";
  
  int ordenado;
  cin >> ordenado;
  if (ordenado == 1) {
    cout << "Vetor ordenado: ";
    printarVetor(vetorOrdenado);
  }
  
}