#include <iostream>
#include <climits>
#include <string>
#include <sstream>

using namespace std;

// Nome: Luis Tiago

struct Elemento {
    int valor;
    Elemento* abaixo;
};

struct EstruturaPilha {
    Elemento* topo;
};

EstruturaPilha* criarPilha() {
    EstruturaPilha* p = new EstruturaPilha();
    p->topo = nullptr;
    return p;
}

bool pilhaVazia(EstruturaPilha* p) {
    return (p->topo == nullptr);
}

int contarElementos(EstruturaPilha* p) {
    int total = 0;
    Elemento* atual = p->topo;
    while (atual != nullptr) {
        total++;
        atual = atual->abaixo;
    }
    return total;
}

void empilhar(EstruturaPilha* p, int num) {
    Elemento* novo = new Elemento();
    novo->valor = num;
    novo->abaixo = p->topo;
    p->topo = novo;
}

int desempilhar(EstruturaPilha* p) {
    if (pilhaVazia(p)) return -1;
    
    Elemento* auxiliar = p->topo;
    int valorRetorno = auxiliar->valor;
    p->topo = auxiliar->abaixo;
    delete auxiliar;
    
    return valorRetorno;
}

int espiarTopo(EstruturaPilha* p) {
    if (pilhaVazia(p)) return INT_MIN; // Evita crash se a pilha estiver vazia
    return p->topo->valor;
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    
    EstruturaPilha* pares = criarPilha();
    EstruturaPilha* impares = criarPilha();
    
    int ultimoInserido = INT_MIN;
    const int TOTAL_NUMEROS = 30;

    cout << "--- Digite " << TOTAL_NUMEROS << " números em ordem estritamente crescente ---\n\n";

    for (int i = 0; i < TOTAL_NUMEROS; i++) {
        int numeroDigitado;
        string entrada;

        while (true) {
            if (ultimoInserido != INT_MIN) {
                cout << "[Último número digitado: " << ultimoInserido << "]\n";
            }
            cout << "Digite o " << (i + 1) << "º número: ";
            getline(cin, entrada);

            // Validação usando stringstream (muda totalmente o estilo do João)
            stringstream ss(entrada);
            if (!(ss >> numeroDigitado) || !(ss.eof())) {
                cout << "Erro: Entrada inválida. Digite apenas números inteiros.\n\n";
                continue;
            }

            if (numeroDigitado <= ultimoInserido) {
                cout << "Erro: O número deve ser MAIOR que o anterior (" << ultimoInserido << ").\n\n";
                continue;
            }

            break; // Entrada válida e maior que a anterior
        }

        // Separação par ou ímpar
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

    // Mesclagem decrescente das duas pilhas
    while (!pilhaVazia(pares) && !pilhaVazia(impares)) {
        if (espiarTopo(pares) > espiarTopo(impares)) {
            cout << desempilhar(pares) << " ";
        } else {
            cout << desempilhar(impares) << " ";
        }
    }

    // Esvazia o que sobrou
    while (!pilhaVazia(pares)) {
        cout << desempilhar(pares) << " ";
    }
    while (!pilhaVazia(impares)) {
        cout << desempilhar(impares) << " ";
    }

    cout << "\n\nPrograma finalizado.\n";

    // Liberando a memória dos ponteiros das pilhas
    delete pares;
    delete impares;

    return 0;
}
