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

// grid
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

// draw everything
window.draw(grid);
window.draw(grid1x1);
window.draw(axes);
window.draw(plot);