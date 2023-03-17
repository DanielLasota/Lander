#include <iostream>
#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace std;
using namespace sf;

int main()
{
    double a, b, c, y, x, delta;
    const int width = 800; // szerokoœæ okna graficznego
    const int height = 600; // wysokoœæ okna graficznego
    const int n = 200; // liczba punktów na wykresie
    const float thickness = 2.0f; // gruboœæ linii wykresu

    // pobieranie wartoœci wspó³czynników a, b i c
    cout << "Podaj wspolczynniki a, b i c dla funkcji kwadratowej: ";
    cin >> a >> b >> c;

    // tworzenie okna graficznego
    RenderWindow window(VideoMode(width, height), "Funkcja kwadratowa");

    // tworzenie obiektu klasy Text
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Devxd\\Desktop\\EurostileExtended.ttf")) {
        cout << "Unable to read .ttf file... ";
        // obs³uga b³êdu - czcionka nie zosta³a wczytana
        // mo¿na wyœwietliæ informacjê o b³êdzie lub przerwaæ program
    }
    
    sf::Text zeros; // ustawienie czcionki dla tekstu
    zeros.setFont(font);
    zeros.setCharacterSize(20); // ustawienie rozmiaru tekstu domyœlnej czcionki
    zeros.setFillColor(sf::Color::Black); // ustawienie koloru tekstu

    // delta, zero and others
    delta = b * b - 4 * a * c;
    double x1 = (-b - sqrt(delta)) / (2 * a);
    double x2 = (-b + sqrt(delta)) / (2 * a);
    double p = -b / (2.0 * a);
    double q = a * p * p + b * p + c;
    double r = a * (p + 1.0 / (4.0 * a)) * (p + 1.0 / (4.0 * a)) + q - 1.0 / (4.0 * a);

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

    
    // function graph
    VertexArray plot(LineStrip, n);
    for (int i = 0; i < n; i++)
    {
        //x = static_cast<float>(i - n / 2) / n * 20.0f;
        x = static_cast<float>(i - n / 2) / static_cast<float>(n) * 20.0f;
        y = a * x * x + b * x + c;
        plot[i].position = Vector2f((x - p) * static_cast<float>(width) / 20.0f + static_cast<float>(width / 2), -(y - q) * static_cast<float>(height) / 20.0f + static_cast<float>(height / 2));
        plot[i].color = Color::Red;
    }


    // tworzenie kursora pozwalaj¹cego na przybli¿anie i oddalanie wykresu
    View view(FloatRect(0, 0, width, height));
    window.setView(view);

    std::ostringstream oss;
    oss << "Miejsca zerowe: x1 = " << x1 << ", x2 = " << x2;
    std::string text = oss.str();
    zeros.setString(text);

    // loop for displ
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel)
                {
                    view.zoom(1 - event.mouseWheelScroll.delta / 10.0f);
                    window.setView(view);
                }
            }
        }

        window.clear(Color::White); // czyszczenie ekranu
        window.draw(axes);  // rysowanie osi uk³adu wspó³rzêdnych
        window.draw(plot);  // rysowanie wykresu funkcji kwadratowe    
        window.display(); // wyœwietlanie okna graficznego
    }





    return 0;
}