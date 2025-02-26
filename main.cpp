#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Funcion para comprobar si un numero es primo
bool esPrimo(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Funcion que devuelve la parte "restante" y el ultimo digito de un numero (en forma de string)
pair<string, int> removeLastDigit(const string &s) {
    int last = s.back() - '0';
    string rest = s.substr(0, s.size() - 1);
    if (rest.empty()) rest = "0";
    return {rest, last};
}

// Funcion que resta un entero pequeno (x) a un numero grande representado como string.
string subtractInt(const string &s, int x) {
    string sx = to_string(x);
    if (s.size() < sx.size() || (s.size() == sx.size() && s < sx)) {
        int s_val = stoi(s);
        int diff = x - s_val;
        return "-" + to_string(diff);
    }

    int carry = x;
    string result = s;
    for (int i = result.size() - 1; i >= 0 && carry > 0; i--) {
        int digit = result[i] - '0';
        if (digit < carry) {
            int new_digit = (10 + digit - carry);
            result[i] = char('0' + new_digit);
            carry = 1;
        } else {
            int new_digit = digit - carry;
            result[i] = char('0' + new_digit);
            carry = 0;
        }
    }
    int pos = 0;
    while (pos < result.size() - 1 && result[pos] == '0')
        pos++;
    return result.substr(pos);
}

// Funcion que devuelve el valor absoluto (en forma de string) de un numero que puede tener signo
string absString(const string &s) {
    if (!s.empty() && s[0] == '-')
        return s.substr(1);
    return s;
}

// Funcion que compara si el valor absoluto (en forma de string) es mayor que 100
bool greaterThan100(const string &s) {
    if (s.size() > 3)
        return true;
    if (s.size() < 3)
        return false;
    return s > "100";
}

// Funcion que, aplicando iterativamente el criterio de divisibilidad, reduce el numero
// y determina si es divisible por el numero primo dado.
bool esDivisiblePorN(string n, int primo) {
    n = absString(n);
    while (greaterThan100(n)) {
        auto pr = removeLastDigit(n);
        string rest = pr.first;
        int last = pr.second;
        int toSubtract = 2 * last;
        n = subtractInt(rest, toSubtract);
        n = absString(n);
    }
    int value = stoi(n);
    return (value % primo == 0);
}

int main() {
    int opcion, primo;
    do {
        cout << "\n----- MENU -----\n";
        cout << "1. Elegir un numero primo para comprobar divisibilidad\n";
        cout << "2. Verificar divisibilidad de un numero por el primo elegido\n";
        cout << "3. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            cout << "Ingrese un numero primo: ";
            cin >> primo;
            if (esPrimo(primo)) {
                cout << "El numero " << primo << " es primo.\n";
            } else {
                cout << "El numero ingresado no es primo.\n";
                primo = 0;
            }
        } else if (opcion == 2) {
            if (primo == 0) {
                cout << "Primero debe elegir un numero primo.\n";
            } else {
                cout << "Ingrese un numero (sin limite de cifras): ";
                string numero;
                getline(cin, numero);
                if (esDivisiblePorN(numero, primo))
                    cout << "El numero es divisible por " << primo << ".\n";
                else
                    cout << "El numero no es divisible por " << primo << ".\n";
            }
        } else if (opcion != 3) {
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 3);

    cout << "Hasta luego!\n";
    return 0;
}
