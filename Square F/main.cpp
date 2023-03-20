#include <iostream>
#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace sf;

int main()
{
    double a, b, c, y, x, delta;
    const int width = 800;                      
    const int height = 600;                     
    const int n = 200;                          // n of points on chart
    const float thickness = 2.0f;

    cout << "Podaj wspolczynniki a, b i c dla funkcji kwadratowej: ";
    cin >> a >> b >> c;

   
    
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Devxd\\Desktop\\EurostileExtended.ttf")) {
        cout << "Unable to read .ttf file... ";
        // error deal
    }


    // delta, zeros etc 
    delta = b * b - 4 * a * c;
    double x1 = (-b - sqrt(delta)) / (2 * a);
    double x2 = (-b + sqrt(delta)) / (2 * a);
    double v1 = -b / a;
    double v2 = c / a;
    double p = -b / (2.0 * a);
    double q = a * p * p + b * p + c;
    double r = a * (p + 1.0 / (4.0 * a)) * (p + 1.0 / (4.0 * a)) + q - 1.0 / (4.0 * a);
    double q_vertex = -(delta) / (4 * a);

    delta = (delta == -0.0) ? 0.0 : delta;
    x1 = (x1 == -0.0) ? 0.0 : x1;
    x2 = (x2 == -0.0) ? 0.0 : x2;
    p = (p == -0.0) ? 0.0 : p;
    q = (q == -0.0) ? 0.0 : q;
    r = (r == -0.0) ? 0.0 : r;
    v1 = (v1 == -0.0) ? 0.0 : v1;
    v2 = (v2 == -0.0) ? 0.0 : v2;
    q_vertex = (q_vertex == -0.0) ? 0.0 : q_vertex;

    // Function formulas

    //general formVVVVV
    //general formVVVVV
    string general_form = "f(x) = ";
    if (a == 1)                 //a
        general_form += "x^2";
    else
        general_form += to_string(a) + "x^2";
    
    if (b == 1)                 //b
        general_form += " + x";
    if (b == -1)
        general_form += " - x";
    if (b < 0 && b != -1)
        general_form += " " + to_string(b) + "x";
    if (b > 1 && b != 1)
        general_form += " + " + to_string(b) + "x";
    
    if(c<0)                     //c
        general_form += " " + to_string(c);
    if (c > 0)
        general_form += " + " + to_string(c);

    //Product form VVVVVV
    //Product form VVVVVV

    string product_form = "f(x) = ";

    if (delta == 0) {
        if (a == 1) {
            if (p == 0)
                product_form += "x^2";
            else
                product_form += "(x - " + to_string(p) + ")^2";
        }
        else {
            if (p == 0)
                product_form += to_string(a) + "x^2";
            else
                product_form += to_string(a) + "(x - " + to_string(p) + ")^2";
        }

    }
    else if (delta > 0) {
        if (a == 1)
            product_form += "(x - " + to_string(x1) + ")(x - " + to_string(x2) + ")";
        else
            product_form += to_string(a) + "(x - " + to_string(x1) + ")(x - " + to_string(x2) + ")";
    }
    else {
        if (a == 1)
            product_form += "(x - " + to_string(p) + ")^2";
        else
            product_form += to_string(a) + "(x - " + to_string(p) + ")^2";
    }

    //VERTEX FORM VVVVVVVV
    //VERTEX FORM VVVVVVVV

    string vertex_form = "f(x) = ";
    if (a == 1) { 
        if (p != 0)
            vertex_form += "(x - " + to_string(p) + ")^2";
        else
            vertex_form += "x^2";
    }
    else if(a!=1) {
        if(p != 0)
            vertex_form += to_string(a) + "(x^2 - " + to_string(p) + ")";
        else
            vertex_form += to_string(a) + "x^2";
    }

    if (q_vertex != 0)
        vertex_form += " + " + to_string(q_vertex);

    std::cout << "General form: " << general_form << std::endl;
    std::cout << "Product form: " << product_form << std::endl;
    std::cout << "Vertex form: " << vertex_form << std::endl;
    //console chech-out
    cout << "a=" << a << endl << "b=" << b << endl << "c=" << c << endl
        << "p= " << p << endl << "q=" << q << endl << "r= " << r << endl
        << "x1= " << x1 << endl << "x2=" << x2 << endl
        << "v1=" << v1 << endl << "v2=" << v2;
    // axes

    RenderWindow window(VideoMode(width, height), "Funkcja kwadratowa", sf::Style::None);


    VertexArray axes(Lines, 4);
    axes[0].position = Vector2f(static_cast<float>(width / 2), 0.0f);
    axes[1].position = Vector2f(static_cast<float>(width / 2), static_cast<float>(height));
    axes[2].position = Vector2f(0.0f, static_cast<float>(height / 2));
    axes[3].position = Vector2f(static_cast<float>(width), static_cast<float>(height / 2));
    axes[0].color = Color::Black;
    axes[1].color = Color::Black;
    axes[2].color = Color::Black;
    axes[3].color = Color::Black;

    //############################################VV
    //################# GRID #####################VV
    VertexArray grid/*MESH*/(Lines, (width + height) * 2);
    int index = 0;
    for (int i = -width / 2; i <= width / 2; i++) {
        if (i != 0) {
            grid[index].position = Vector2f(static_cast<float>(width / 2 + i), 0.0f);
            grid[index + 1].position = Vector2f(static_cast<float>(width / 2 + i), static_cast<float>(height));
            grid[index].color = Color(200, 200, 200, 100);
            grid[index + 1].color = Color(200, 200, 200, 100);
            index += 2;
        }
    }
    for (int i = -height / 2; i <= height / 2; i++) {
        if (i != 0) {
            grid[index].position = Vector2f(0.0f, static_cast<float>(height / 2 + i));
            grid[index + 1].position = Vector2f(static_cast<float>(width), static_cast<float>(height / 2 + i));
            grid[index].color = Color(200, 200, 200, 100);
            grid[index + 1].color = Color(200, 200, 200, 100);
            index += 2;
        }
    }



    //################# AX PTRS #####################VV
    //################# AX PTRS #####################VV
        

    VertexArray grid1x1(Lines, (width + height) * 2); // AXIS POINTERS

    sf::Text axis_ptrs_numbers;
    axis_ptrs_numbers.setFont(font);
    axis_ptrs_numbers.setCharacterSize(12);
    axis_ptrs_numbers.setFillColor(sf::Color::Black);
    std::stringstream oss_axis_ptrs_numbers;



    index = 0;
    // Axes numerating protootype ADD HERE CAREFULYYY

    for (int i = -width / 2; i <= width / 2; i++) {
        if (i % 40 == 0) {

            grid1x1[index].position = Vector2f(static_cast<float>(width / 2 + i), static_cast<float>(height / 2) - 0.5f);
            grid1x1[index + 1].position = Vector2f(static_cast<float>(width / 2 + i), static_cast<float>(height / 2) + 0.5f);
            grid1x1[index].color = Color(0, 0, 0, 100);
            grid1x1[index + 1].color = Color(0, 0, 0, 100);
            oss_axis_ptrs_numbers << i/40;
            
            axis_ptrs_numbers.setPosition(Vector2f(static_cast<float>(-width / 2 + i), static_cast<float>(height / 2) - 0.5f));
            axis_ptrs_numbers.setString(oss_axis_ptrs_numbers.str());
            index += 2;
            oss_axis_ptrs_numbers.str("");
        }
    }
    for (int i = -height / 2; i <= height / 2; i++) {
        if (i % 40 == 0) {
            grid1x1[index].position = Vector2f(static_cast<float>(width / 2) - 0.5f, static_cast<float>(height / 2 + i));
            grid1x1[index + 1].position = Vector2f(static_cast<float>(width / 2) + 0.5f, static_cast<float>(height / 2 + i));
            grid1x1[index].color = Color(0, 0, 0, 100);
            grid1x1[index + 1].color = Color(0, 0, 0, 100);
            index += 2;
        }
    }
    //################# AX PTRS #####################^^
    //###############################################^^





    //############################################VV
    //############### F Graph ####################VV
    VertexArray plot(LineStrip, n);
    for (int i = 0; i < n; i++)
    {   
        x = static_cast<float>(i - n / 2) / static_cast<float>(n) * 20.0f;
        y = a * x * x + b * x + c;
        plot[i].position = Vector2f(x * static_cast<float>(width) / 20.0f + static_cast<float>(width / 2), -y * static_cast<float>(height) / 20.0f + static_cast<float>(height / 2));
        plot[i].color = Color::Red;
    }
    //############### F Graph ####################^^
    //############################################^^

    View view(FloatRect(0, 0, width, height));  //main layer with moveable & zoomable graph
    window.setView(view);

    //############################################VV
    //################# text #####################VV
    sf::View textView(sf::FloatRect(0, 0, width, height)); // data text layer

    //sf::Font font;
    //if (!font.loadFromFile("C:\\Users\\Devxd\\Desktop\\EurostileExtended.ttf")) {
    //    cout << "Unable to read .ttf file... ";
    //    // error deal
    //}
    sf::Text fdata;
    fdata.setFont(font);
    fdata.setCharacterSize(10);
    fdata.setFillColor(sf::Color::Black);
    std::stringstream oss;

    oss << "General form: " << general_form << endl
        << "Product form: " << product_form << endl
        << "Vertex form: " << vertex_form << endl << endl
        << "Delta: " << delta << endl;
    if (delta == 0)
        oss << "Function' zero: " << p << endl << endl;
    else if (delta > 0)
        oss << "First zero: " << x1 << ", Second zero: " << x2 << endl << endl;
    else
        oss << "Function has no zeros..." << endl << endl;
    oss << "Vieta's formulas: " << endl << "x1 + x2 = " << v1 << endl << "x1 * x2 = " << v2 << endl << endl
        << "Vertex coordinates V(p,q) = (" << p << "," << q_vertex << ")"
        << endl << endl;
 
    fdata.setString(oss.str());


    //zeros.setPosition(-500, 0); // uncomment to get text fixed to graph

    //################# text #####################^^
    //############################################^^

    Vector2f previousMousePos;
    bool isDragging = false;
    sf::Vector2i lastPosition;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //graph move service
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                lastPosition = sf::Mouse::getPosition(window);
            }
            else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // actual & last coursor position difference
                sf::Vector2i delta = sf::Mouse::getPosition(window) - lastPosition;

                // graph move
                view.move(-delta.x, -delta.y);
                window.setView(view);

                lastPosition = sf::Mouse::getPosition(window);
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    view.zoom(1 - event.mouseWheelScroll.delta / 10.0f);
                    window.setView(view);
                }
            }
        }

        window.clear(Color::White);
        //window.draw(grid);
        window.draw(grid1x1);
        window.draw(axes);
        window.draw(axis_ptrs_numbers);
        window.draw(plot);

        window.setView(textView);
        sf::Vector2f textPosition = window.mapPixelToCoords(sf::Vector2i(20, 20));     //delete to get text fixed to graph
        fdata.setPosition(textPosition);
        window.draw(fdata);

        window.setView(view);

        window.display();
    }

    return 0;
}