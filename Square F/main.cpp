#include <iostream>
#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>

using namespace std;
using namespace sf;

int main()
{
    double a, b, c, y, x, delta;
    const int width = 800; // szeroko�� okna graficznego
    const int height = 600; // wysoko�� okna graficznego
    const int n = 200; // liczba punkt�w na wykresie
    const float thickness = 2.0f; // grubo�� linii wykresu

    // pobieranie warto�ci wsp�czynnik�w a, b i c
    cout << "Podaj wspolczynniki a, b i c dla funkcji kwadratowej: ";
    cin >> a >> b >> c;

    // tworzenie okna graficznego
    RenderWindow window(VideoMode(width, height), "Funkcja kwadratowa");

    // delta, zero and others
    delta = b * b - 4 * a * c;
    double x1 = (-b - sqrt(delta)) / (2 * a);
    double x2 = (-b + sqrt(delta)) / (2 * a);
    double p = -b / (2.0 * a);
    double q = a * p * p + b * p + c;
    double r = a * (p + 1.0 / (4.0 * a)) * (p + 1.0 / (4.0 * a)) + q - 1.0 / (4.0 * a);

    cout << "a=" << a << endl << "b=" << b << endl << "c=" << c << endl;

    // axes
    VertexArray axes(Lines, 4);
    axes[0].position = Vector2f(static_cast<float>(width / 2), 0.0f);
    axes[1].position = Vector2f(static_cast<float>(width / 2), static_cast<float>(height));
    axes[2].position = Vector2f(0.0f, static_cast<float>(height / 2));
    axes[3].position = Vector2f(static_cast<float>(width), static_cast<float>(height / 2));
    axes[0].color = Color::Black;
    axes[1].color = Color::Black;
    axes[2].color = Color::Black;
    axes[3].color = Color::Black;

    //############################################
    //################# GRID #####################
    VertexArray grid(Lines, (width + height) * 2);
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
    // additional grid for 1x1 spacing
    VertexArray grid1x1(Lines, (width + height) * 2);
    index = 0;
    for (int i = -width / 2; i <= width / 2; i++) {
        if (i % 10 == 0) {
            grid1x1[index].position = Vector2f(static_cast<float>(width / 2 + i), static_cast<float>(height / 2) - 0.5f);
            grid1x1[index + 1].position = Vector2f(static_cast<float>(width / 2 + i), static_cast<float>(height / 2) + 0.5f);
            grid1x1[index].color = Color(0, 0, 0, 100);
            grid1x1[index + 1].color = Color(0, 0, 0, 100);
            index += 2;
        }
    }
    for (int i = -height / 2; i <= height / 2; i++) {
        if (i % 10 == 0) {
            grid1x1[index].position = Vector2f(static_cast<float>(width / 2) - 0.5f, static_cast<float>(height / 2 + i));
            grid1x1[index + 1].position = Vector2f(static_cast<float>(width / 2) + 0.5f, static_cast<float>(height / 2 + i));
            grid1x1[index].color = Color(0, 0, 0, 100);
            grid1x1[index + 1].color = Color(0, 0, 0, 100);
            index += 2;
        }
    }
    //############################################
    //############################################

    // function graph
    VertexArray plot(LineStrip, n);
    for (int i = 0; i < n; i++)
    {
        x = static_cast<float>(i - n / 2) / static_cast<float>(n) * 20.0f;
        y = a * x * x + b * x + c;
        plot[i].position = Vector2f(x * static_cast<float>(width) / 20.0f + static_cast<float>(width / 2), -y * static_cast<float>(height) / 20.0f + static_cast<float>(height / 2));
        //plot[i].position = Vector2f((x - p) * static_cast<float>(width) / 20.0f + static_cast<float>(width / 2), -(y - q) * static_cast<float>(height) / 20.0f + static_cast<float>(height / 2));
        plot[i].color = Color::Red;
    }


    // tworzenie kursora pozwalaj�cego na przybli�anie i oddalanie wykresu
    View view(FloatRect(0, 0, width, height));
    window.setView(view);

    // tworzenie obiektu klasy Text
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Devxd\\Desktop\\EurostileExtended.ttf")) {
        cout << "Unable to read .ttf file... ";
        // obs�uga b��du - czcionka nie zosta�a wczytana
        // mo�na wy�wietli� informacj� o b��dzie lub przerwa� program
    }

    sf::Text zeros; // ustawienie czcionki dla tekstu
    zeros.setFont(font);
    zeros.setCharacterSize(25); // ustawienie rozmiaru tekstu domy�lnej czcionki
    zeros.setFillColor(sf::Color::Black); // ustawienie koloru tekstu

    // ustawienie tre�ci tekstu na podstawie miejsc zerowych funkcji
    std::stringstream oss;
    oss << "Pierwsze miejsce: " << x1 << ", drugie miejsce: " << x2;
    zeros.setString(oss.str());

    // wy�wietlenie tekstu w oknie graficznym
    zeros.setPosition(-500, 0); // ustawienie pozycji tekstu
    //window.draw(zeros); // narysowanie tekstu na ekranie

    Vector2f previousMousePos; // zmienna przechowuj�ca poprzednie po�o�enie kursora myszy
    bool isDragging = false;
    sf::Vector2i lastPosition;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // obs�uga zamkni�cia okna
            if (event.type == sf::Event::Closed)
                window.close();
            // obs�uga przesuwania wykresu myszk�
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // zapisanie pozycji kursora w momencie naci�ni�cia przycisku myszy
                lastPosition = sf::Mouse::getPosition(window);
            }
            else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // wyznaczenie r�nicy pomi�dzy aktualn� pozycj� kursora a pozycj� pocz�tkow�
                sf::Vector2i delta = sf::Mouse::getPosition(window) - lastPosition;

                // przesuni�cie wykresu o odpowiedni� warto��
                view.move(-delta.x, -delta.y);
                window.setView(view);

                // zapisanie aktualnej pozycji kursora jako pozycji pocz�tkowej
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





        window.clear(Color::White); // czyszczenie ekranu
        //window.draw(grid);
        window.draw(grid1x1);
        window.draw(axes);  // rysowanie osi uk�adu wsp�rz�dnych
        window.draw(plot);  // rysowanie wykresu funkcji kwadratowe   
        window.draw(zeros);
        window.display(); // wy�wietlanie okna graficznego

    }

    return 0;
}