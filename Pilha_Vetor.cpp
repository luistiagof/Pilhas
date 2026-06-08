#include <iostream>
#include <climits>
#include <string>
#include <sstream>

using namespace std;

#define CAPACIDADE 30

// Nome: Luis Tiago

struct PilhaVetor {
    int tamanho;
    int dados[CAPACIDADE];
};

PilhaVetor* criarPilha() {
    PilhaVetor* p = new PilhaVetor();
    p->tamanho = 0;
    return p;
}

bool pilhaVazia(PilhaVetor* p) {
    return (p->tamanho == 0);
}

void empilhar(PilhaVetor* p, int valor) {
    if (p->tamanho < CAPACIDADE) {
        p->dados[p->tamanho] = valor;
        p->tamanho++;
    }
}

int desempilhar(PilhaVetor* p) {
    if (pilhaVazia(p)) return -1;
    
    p->tamanho--;
    return p->dados[p->tamanho];
}

int espiarTopo(PilhaVetor* p) {
    if (pilhaVazia(p)) return INT_MIN;
    return p->dados[p->tamanho - 1];
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    
    PilhaVetor* pares = criarPilha();
    PilhaVetor* impares = criarPilha();
    
    int ultimoInserido = INT_MIN;

    cout << "--- Digite " << CAPACIDADE << " números em ordem estritamente crescente ---\n\n";

    for (int i = 0; i < CAPACIDADE; i++) {
        int numeroDigitado;
        string entrada;

        while (true) {
            if (ultimoInserido != INT_MIN) {
                cout << "[Último número digitado: " << ultimoInserido << "]\n";
            }
            cout << "Digite o " << (i + 1) << "º número: ";
            getline(cin, entrada);

            stringstream ss(entrada);
            if (!(ss >> numeroDigitado) || !(ss.eof())) {
                cout << "Erro: Entrada inválida. Digite apenas números inteiros.\n\n";
                continue;
            }

            if (numeroDigitado <= ultimoInserido) {
                cout << "Erro: O número deve ser MAIOR que o anterior (" << ultimoInserido << ").\n\n";
                continue;
            }

            break;
        }

        if (numeroDigitado % 2 == 0) {
            empilhar(pares, numeroDigitado);
        } else {
            empilhar(impares, numeroDigitado);
        }

        ultimoInserido = numeroDigitado;
        cout << "Número aceito com sucesso!\n\n";
    }

    cout << "\n========================================\n";
    cout << "Exibindo os valores em ordem decrescente:\n";
    cout << "========================================\n";

    while (!pilhaVazia(pares) && !pilhaVazia(impares)) {
        if (espiarTopo(pares) > espiarTopo(impares)) {
            cout << desempilhar(pares) << " ";
        } else {
            cout << desempilhar(impares) << " ";
        }
    }

    while (!pilhaVazia(pares)) {
        cout << desempilhar(pares) << " ";
    }
    while (!pilhaVazia(impares)) {
        cout << desempilhar(impares) << " ";
    }

    cout << "\n\nPrograma finalizado.\n";

    delete pares;
    delete impares;

    return 0;
}
