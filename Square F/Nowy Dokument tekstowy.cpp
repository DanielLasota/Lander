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
            // przesuniêcie wykresu o odpowiedni¹ wartoœæ z uwzglêdnieniem prêdkoœci
            view.move(-delta.x * speed, -delta.y * speed);
            window.setView(view);

            // zapisanie aktualnej pozycji kursora jako pozycji pocz¹tkowej
            lastPosition = sf::Mouse::getPosition(window);
        }
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                // regulacja prêdkoœci przybli¿ania w zale¿noœci od wartoœci skali
                float zoomLevel = view.getSize().x / window.getSize().x;
                float speed = 0.1f;
                if (zoomLevel > 1.0f) {
                    speed = 0.1f / zoomlevel;
            }
            // przybli¿anie z uwzglêdnieniem prêdkoœci
            view.zoom(1 - event.mouseWheelScroll.delta * speed);
            window.setView(view);
        }
    }
}

window.clear(Color::White); // czyszczenie ekranu
//window.draw(grid);
window.draw(grid1x1);
window.draw(axes);  // rysowanie osi uk³adu wspó³rzêdnych
window.draw(plot);  // rysowanie wykresu funkcji kwadratowe   
window.draw(zeros);
window.display(); // wyœwietlanie okna graficznego
}




float moveScale = 0.1f; // skala przesuwania
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
            // regulacja prêdkoœci przesuwania
            delta *= moveScale;
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

sf::Vector2f delta = sf::Vector2f(event.mouseMove.x - lastMousePos.x, event.mouseMove.y - lastMousePos.y);
float zoomLevel = view.getSize().x / window.getSize().x;
float moveScale = zoomLevel * 10.0f; // tu mo¿esz dostosowaæ wartoœæ
delta *= moveScale;
lastMousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);






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
            previousMousePos = window.mapPixelToCoords(lastPosition); // dodane
            isDragging = true; // dodane
        }
        else if (event.type == sf::Event::MouseMoved && isDragging) // zmienione
        {
            // wyznaczenie ró¿nicy pomiêdzy aktualn¹ pozycj¹ kursora a pozycj¹ pocz¹tkow¹
            sf::Vector2i delta = sf::Mouse::getPosition(window) - lastPosition;

            // przesuniêcie wykresu o odpowiedni¹ wartoœæ
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            view.move(previousMousePos - mousePos);
            previousMousePos = mousePos;

            window.setView(view);

            // zapisanie aktualnej pozycji kursora jako pozycji pocz¹tkowej
            lastPosition = sf::Mouse::getPosition(window);
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) // dodane
        {
            isDragging = false;
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
    window.draw(axes);  // rysowanie osi uk³adu wspó³rzêdnych
    window.draw(plot);  // rysowanie wykresu funkcji kwadratowe   
    window.draw(zeros);
    window.display(); // wyœwietlanie okna graficznego

}



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
    double v1 = -b / a;
    double v2 = c / a;
    double p = -b / (2.0 * a);
    double q = a * p * p + b * p + c;
    double r = a * (p + 1.0 / (4.0 * a)) * (p + 1.0 / (4.0 * a)) + q - 1.0 / (4.0 * a);

    delta = (delta == -0.0) ? 0.0
// Function formulas
std::string general_form = "f(x) = ";
if (a != 0) {
    general_form += std::to_string(a) + "x^2";
}
if (b != 0) {
    if (a != 0) {
        general_form += " + ";
    }
    general_form += std::to_string(b) + "x";
}
if (c != 0) {
    if (a != 0 || b != 0) {
        general_form += " + ";
    }
    general_form += std::to_string(c);
}
std::string product_form = "f(x) = ";
if (a != 0) {
    product_form += std::to_string(a) + "(x - " + std::to_string(x1) + ")(x - " + std::to_string(x2) + ")";
}
else {
    product_form += "0";
}

std::string vertex_form = "f(x) = ";
if (a != 0) {
    vertex_form += std::to_string(a) + "(x - " + std::to_string(p) + ")^2 + " + std::to_string(q);
}
else {
    vertex_form += std::to_string(q);
}

std::cout << "General form: " << general_form << std::endl;
std::cout << "Product form: " << product_form << std::endl;
std::cout << "Vertex form: " << vertex_form << std::endl;

//...