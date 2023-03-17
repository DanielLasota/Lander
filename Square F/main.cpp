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
    const int width = 800; // szerokoœæ okna graficznego
    const int height = 600; // wysokoœæ okna graficznego
    const int n = 200; // liczba punktów na wykresie
    const float thickness = 2.0f; // gruboœæ linii wykresu

    // pobieranie wartoœci wspó³czynników a, b i c
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

    //############################################VV
    //################# GRID #####################VV
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
    //################# GRID #####################^^
    //############################################^^ 

    
    //############################################VV
    //################# F Gr #####################VV
     
    // function graph

    VertexArray plot(LineStrip, n);
    for (int i = 0; i < n; i++)
    {
        x = static_cast<float>(i - n / 2) / static_cast<float>(n) * 20.0f;
        y = a * x * x + b * x + c;
        plot[i].position = Vector2f(x * static_cast<float>(width) / 20.0f + static_cast<float>(width / 2), -y * static_cast<float>(height) / 20.0f + static_cast<float>(height / 2));
        plot[i].color = Color::Red;
    }

    //################# F Gr #####################^^
    //############################################^^

    // coursor initialize
    View view(FloatRect(0, 0, width, height));
    window.setView(view);

    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Devxd\\Desktop\\EurostileExtended.ttf")) {
        cout << "Unable to read .ttf file... ";
        // obs³uga b³êdu - czcionka nie zosta³a wczytana
    }

    sf::Text zeros;
    zeros.setFont(font);
    zeros.setCharacterSize(25);
    zeros.setFillColor(sf::Color::Black);
    std::stringstream oss;
    oss << "Pierwsze miejsce: " << x1 << ", drugie miejsce: " << x2;
    zeros.setString(oss.str());
    zeros.setPosition(-500, 0);
    //window.draw(zeros); // narysowanie tekstu na ekranie

    Vector2f previousMousePos; // zmienna przechowuj¹ca poprzednie po³o¿enie kursora myszy
    bool isDragging = false;
    sf::Vector2i lastPosition;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // obs³uga zamkniêcia okna
            if (event.type == sf::Event::Closed)
                window.close();
            // obs³uga przesuwania wykresu myszk¹
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // zapisanie pozycji kursora w momencie naciœniêcia przycisku myszy
                lastPosition = sf::Mouse::getPosition(window);
            }
            else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // wyznaczenie ró¿nicy pomiêdzy aktualn¹ pozycj¹ kursora a pozycj¹ pocz¹tkow¹
                sf::Vector2i delta = sf::Mouse::getPosition(window) - lastPosition;
                // regulacja prêdkoœci przesuwania w zale¿noœci od wartoœci skali
                float zoomLevel = view.getSize().x / window.getSize().x;
                float speed = 1.0f;
                if (zoomLevel > 1.0f) {
                    speed = 1.0f / zoomLevel;
                }
                view.move(-delta.x * speed, -delta.y * speed);
                window.setView(view);
                lastPosition = sf::Mouse::getPosition(window);
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    // zoom speed adjustment
                    float zoomLevel = view.getSize().x / window.getSize().x;
                    float speed = 0.1f;
                    if (zoomLevel > 1.0f) {
                        speed = 0.1f / zoomLevel;
                    }
                    view.zoom(1 - event.mouseWheelScroll.delta * speed);
                    window.setView(view);
                }
            }
        }

        window.clear(Color::White);
        window.draw(grid1x1);
        window.draw(axes);
        window.draw(plot);
        window.draw(zeros);
        window.display();
    }


    //while (window.isOpen())
    //{
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        // obs³uga zamkniêcia okna
    //        if (event.type == sf::Event::Closed)
    //            window.close();
    //        // obs³uga przesuwania wykresu myszk¹
    //        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    //        {
    //            // zapisanie pozycji kursora w momencie naciœniêcia przycisku myszy
    //            lastPosition = sf::Mouse::getPosition(window);
    //        }
    //        else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    //        {
    //            // wyznaczenie ró¿nicy pomiêdzy aktualn¹ pozycj¹ kursora a pozycj¹ pocz¹tkow¹
    //            sf::Vector2i delta = sf::Mouse::getPosition(window) - lastPosition;

    //            // przesuniêcie wykresu o odpowiedni¹ wartoœæ
    //            view.move(-delta.x, -delta.y);
    //            window.setView(view);

    //            // zapisanie aktualnej pozycji kursora jako pozycji pocz¹tkowej
    //            lastPosition = sf::Mouse::getPosition(window);
    //        }
    //        if (event.type == sf::Event::MouseWheelScrolled)
    //        {
    //            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    //            {
    //                view.zoom(1 - event.mouseWheelScroll.delta / 10.0f);
    //                window.setView(view);
    //            }
    //        }
    //    }





    //    window.clear(Color::White); // czyszczenie ekranu
    //    //window.draw(grid);
    //    window.draw(grid1x1);
    //    window.draw(axes);  // rysowanie osi uk³adu wspó³rzêdnych
    //    window.draw(plot);  // rysowanie wykresu funkcji kwadratowe   
    //    window.draw(zeros);
    //    window.display(); // wyœwietlanie okna graficznego

    //}

    return 0;
}