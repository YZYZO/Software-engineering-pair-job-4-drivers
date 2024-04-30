#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>  // �������þ���

using namespace std;

// �Զ���� double �� string ��ת������
string toString(double value) {
    ostringstream oss;
    oss << fixed << setprecision(2) << value;  // �������ΪС�������λ
    return oss.str();
}

// ������ʽ���
double calculate_result(double num1, double num2, char op) {
    switch (op) {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    case '/': return num2 != 0 ? num1 / num2 : 0;  // ���������
    default:  return 0;
    }
}

// ����һ�������Ŀ
string generate_problem(double& answer, int max_value, const vector<char>& operators, bool include_decimal, bool include_parentheses) {
    double num1 = (rand() % (max_value + 1)) + (include_decimal ? (rand() % 100) / 100.0 : 0);
    double num2 = (rand() % (max_value + 1)) + (include_decimal ? (rand() % 100) / 100.0 : 0);
    char op = operators[rand() % operators.size()];

    string expr;
    if (include_parentheses && rand() % 2) {
        expr = "(" + toString(num1) + " " + op + " " + toString(num2) + ")";
    }
    else {
        expr = toString(num1) + " " + op + " " + toString(num2);
    }

    answer = calculate_result(num1, num2, op);
    return expr;
}

int main() {
    srand(time(NULL));

    int num_problems, max_value;
    bool include_decimal, include_parentheses;
    vector<char> operators;
    string output_type;

    cout << "��������Ŀ����: ";
    cin >> num_problems;
    cout << "���������ֵ����ֵ: ";
    cin >> max_value;
    cout << "�Ƿ����С���� (1 for yes, 0 for no): ";
    cin >> include_decimal;
    cout << "�Ƿ�������ţ� (1 for yes, 0 for no): ";
    cin >> include_parentheses;
    cout << "��������������(+, -, *, /)����q��β: ";

    char temp_op;
    while (cin >> temp_op && temp_op != 'q') {
        operators.push_back(temp_op);
    }

    cout << "ѡ�������ʽ������̨���ļ�(console/file): ";
    cin >> output_type;

    vector<string> problems;
    vector<double> answers;

    ofstream file;
    if (output_type == "file") {
        file.open("problems.txt");
    }

    for (int i = 0; i < num_problems; ++i) {
        double answer;
        string problem = generate_problem(answer, max_value, operators, include_decimal, include_parentheses);
        problems.push_back(problem + " = ?");
        answers.push_back(answer);
    }

    // ���������Ŀ
    for (int i = 0; i < num_problems; ++i) {
        if (output_type == "console") {
            cout << "Problem " << (i + 1) << ": " << problems[i] << endl;
        }
        else if (output_type == "file") {
            file << "Problem " << (i + 1) << ": " << problems[i] << endl;
        }
    }

    // ���ʮ�пհ�
    for (int j = 0; j < 10; ++j) {
        if (output_type == "console") {
            cout << endl;
        }
        else if (output_type == "file") {
            file << endl;
        }
    }

    // ������д�
    for (int i = 0; i < num_problems; ++i) {
        if (output_type == "console") {
            cout << "Answer " << (i + 1) << ": " << toString(answers[i]) << endl;
        }
        else if (output_type == "file") {
            file << "Answer " << (i + 1) << ": " << toString(answers[i]) << endl;
        }
    }

    if (file.is_open()) {
        file.close();
    }

    return 0;
}
