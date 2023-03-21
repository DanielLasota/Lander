#ifndef f_formulas_hpp
#define f_formulas_hpp

using namespace std;

std::string replace(string str) {
    string pattern1 = "--";
    string pattern2 = "- -";
    string pattern3 = "+ -";
    string pattern4 = "+-";
    string replaceWith = "+";
    string replaceWith2 = "-";

    size_t pos = 0;
    while ((pos = str.find(pattern1, pos)) != string::npos) {
        str.replace(pos, pattern1.length(), replaceWith);
        pos += replaceWith.length();
    }

    pos = 0;
    while ((pos = str.find(pattern2, pos)) != string::npos) {
        str.replace(pos, pattern2.length(), replaceWith);
        pos += replaceWith.length();
    }

    pos = 0;
    while ((pos = str.find(pattern3, pos)) != string::npos) {
        str.replace(pos, pattern3.length(), replaceWith2);
        pos += replaceWith2.length();
    }

    pos = 0;
    while ((pos = str.find(pattern4, pos)) != string::npos) {
        str.replace(pos, pattern4.length(), replaceWith2);
        pos += replaceWith2.length();
    }

    return str;
}

std::string del0s(double x) //removes unnecessarry zeros after fraction coma, returns string
{
    if (x == 0)
        return "0";
    string aux = to_string(x);
    for (int i = aux.length(); i >= 0; i--)
    {
        if (aux[i - 1] == '0' || aux[i - 1] == '.')
            aux.erase(i - 1, 1);
        else
            break;
    }
    return aux;
}

std::string generalf(double a, double b, double c) {

    string general_form = " f(x) = ";
    if (a > 0)
    {
        if (a == 1)
            general_form += "x^2 ";
        else
            general_form += "+ " + del0s(a) + "x^2 ";
    }
    if (a < 0)
    {
        if (a == -1)
            general_form += "-x^2";
        else
            general_form += " " + del0s(a) + "x^2 ";
    }
    if (b > 0)
    {
        if (b == 1)
            general_form += " + x";
        else
            general_form += "+ " + del0s(b) + "x ";
    }
    if (b < 0)
    {
        if (b == -1)
            general_form += " - x";
        else
            general_form += " " + del0s(b) + "x ";
    }
    if (c > 0)
        general_form += " + " + del0s(c);
    else if (c <= 0)
        general_form += del0s(c);

    return general_form;
}

std::string productf(double a, double b, double c) {

    string product_form = "f(x) = ";
    double delta = b * b - 4 * a * c;
    double x1 = (-b - sqrt(delta)) / (2 * a);
    double x2 = (-b + sqrt(delta)) / (2 * a);
    double p = -b / (2.0 * a);

    x1 = (x1 == -0.0) ? 0.0 : x1;
    x2 = (x2 == -0.0) ? 0.0 : x2;
    p = (p == -0.0) ? 0.0 : p;


    if (delta == 0) {
        if (a == 1) {
            product_form += "(x^2";
        }
        else {
            product_form += del0s(a) + "(x^2";
        }
        if (p > 0)
            product_form += " + " + del0s(p) + " x)^2";
        else if (p < 0)
            product_form += del0s(p) + " x)^2";
    }
    else if (delta > 0) {
        if (a == 1)
            product_form += "(x - " + del0s(x1) + ")(x - " + del0s(x2) + ")";
        else
            product_form += del0s(a) + "(x - " + del0s(x1) + ")(x - " + del0s(x2) + ")";
    }
    else
        return generalf(a, b, c);


    return replace(product_form);
}

std::string vertexf(double a, double b, double c) {

    string vertex_form = "f(x) = ";
    double delta = b * b - 4 * a * c;
    double q_vertex = -(delta) / (4 * a);
    double p = -b / (2.0 * a);

    delta = (delta == -0.0) ? 0.0 : delta;
    q_vertex = (q_vertex == -0.0) ? 0.0 : q_vertex;
    p = (p == -0.0) ? 0.0 : p;

    if (a == 1) {
        if (p != 0)
            vertex_form += "(x - " + del0s(p) + ")^2";
        else
            vertex_form += "x^2";
    }
    else if (a != 1) {
        if (p != 0)
            vertex_form += del0s(a) + "(x^2 - " + del0s(p) + ")";
        else
            vertex_form += del0s(a) + "x^2";
    }
    if (q_vertex != 0)
        vertex_form += " + " + del0s(q_vertex);

    return replace(vertex_form);
}

#endif