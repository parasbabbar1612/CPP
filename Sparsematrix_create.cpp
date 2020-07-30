#include<iostream>
#include<vector>

using namespace std;

class Element {
public:
    int row_num;
    int col_num;
    int val;
    Element(){}
};

class sparsematrix {
public:
    int rows;
    int cols;
    int non_zero;
    vector<Element> matrix;
    sparsematrix(){}
    void create();
    void display();
    sparsematrix add(sparsematrix& s1,sparsematrix& s2);

};

ostream& operator<<(ostream& str, const Element& e) {
    str << e.row_num << " " << e.col_num << " " << e.val << endl;
    return str;
}

void sparsematrix::create() {
    cout << "Enter number of rows in matrix" << endl;
    cin >> this->rows;
    cout << "Enter number of columns in matrix" << endl;
    cin >> this->cols;
    cout << "Enter number of non-zero elements in matrix" << endl;
    cin >> this->non_zero;
    cout << "Enter row number,column number and value of each element" << endl;
    for (int i = 0; i < this->non_zero; i++)
    {
        Element obj;
        cin >> obj.row_num >> obj.col_num >> obj.val;
        this->matrix.emplace_back(obj);
    }
}

sparsematrix sparsematrix::add(sparsematrix &s1, sparsematrix &s2)
{
    sparsematrix add_m;
    if (s1.rows != s2.rows || s1.cols != s2.cols) return add_m;
    add_m.rows = s1.rows;
    add_m.cols = s1.cols;
    int i = 0, j = 0;
    while (i < s1.non_zero && j < s2.non_zero) {
        if (s1.matrix[i].row_num < s2.matrix[j].row_num) {
            add_m.matrix.push_back(s1.matrix[i++]);
        }
        else if(s1.matrix[i].row_num > s2.matrix[j].row_num) {
            add_m.matrix.push_back(s2.matrix[j++]);
        }
        else {
            if (s1.matrix[i].col_num < s2.matrix[j].col_num) {
                add_m.matrix.push_back(s1.matrix[i++]);
            }
            else if (s1.matrix[i].col_num > s2.matrix[j].col_num) {
                add_m.matrix.push_back(s2.matrix[j++]);
            }
            else {
                add_m.matrix.push_back(s1.matrix[i++]);
                add_m.matrix.back().val += s2.matrix[j++].val;
            }
        }
    }
    while (i<s1.non_zero)
    {
        add_m.matrix.push_back(s1.matrix[i++]);
    }
    while (j < s2.non_zero)
    {
        add_m.matrix.push_back(s2.matrix[j++]);
    }
    add_m.non_zero = add_m.matrix.size();
    return add_m;
}

void sparsematrix::display() {
    vector<vector<int>> m(this->rows, vector<int>(this->cols));
    for (auto i : this->matrix) {
        if (i.row_num >= this->rows || i.col_num >= this->cols) {
            cout << "Invalid element encountered" << endl;
        }
        else  m[i.row_num][i.col_num] = i.val;
    }
    for (auto i : m) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

int main() {
    sparsematrix newmatrix1,newmatrix2,addition;
    newmatrix1.create();
    newmatrix1.display();
    newmatrix2.create();
    newmatrix2.display();
    cout << endl;
    addition=newmatrix1.add(newmatrix1, newmatrix2);
    if (addition.matrix.size() == 0) cout << "Matrixes doesn't have same dimensions" << endl;
    else addition.display();
    return 0;
}