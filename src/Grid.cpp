#include "Grid.h"

Grid::Grid(int in_cellSize, sf::Vector2i in_gridSize, Camera& camera)
	:
	cellSize(in_cellSize),
	gridSize(in_gridSize),
	camera(camera)
{
	hLine.setSize({ (float)cellSize * (float)gridSize.x, 2.f });
	vLine.setSize({ 2.f, (float)cellSize * (float)gridSize.y });
	vLine.setFillColor(sf::Color::White);
	hLine.setFillColor(sf::Color::White);
}

void Grid::Upadate()
{	
	sf::Vector2f scaledLineWidth = camera.MapScreenToWorld({ 2.f, 2.f  }); // resize event * ratio
	hLine.setSize({ (float)cellSize * (float)gridSize.x, scaledLineWidth.y * ratio.y });
	vLine.setSize({ scaledLineWidth.x * ratio.x , (float)cellSize * (float)gridSize.y });
}

void Grid::Draw(tgui::CanvasSFML& canvas)
{
	for (int x = 0; x <= gridSize.x; x++)
	{
		sf::Vector2f worldPos = camera.MapScreenToWorld(sf::Vector2f{ (float)x * (float)cellSize, 0.f });
		vLine.setPosition({ (float)x * (float)cellSize, 0 });
		canvas.draw(vLine);
	}
	for (int y = 0; y <= gridSize.y; y++)
	{
		sf::Vector2f worldPos = camera.MapScreenToWorld(sf::Vector2f{ 0.f,(float)y * (float)cellSize });
		hLine.setPosition({ 0, (float)y * (float)cellSize });
		canvas.draw(hLine);
	}
}

int Grid::GetClickedOnCellIndex(const sf::Vector2i& mousePos)
{
	sf::Vector2f pos = camera.MapScreenToWorld((sf::Vector2f)mousePos);
	sf::Vector2f offset = camera.GetOffset();
	sf::Vector2f worldPos = pos - offset;
	
	int xLoc = (worldPos.x) / (cellSize);
	int yLoc = (worldPos.y) / (cellSize);

	int index = yLoc * gridSize.y + xLoc;
	
	std::cout << index << std::endl;
	return index;
}

void Grid::HandleEvents(sf::Event& event, sf::Vector2f in_ratio)
{
	ratio = in_ratio;
	if (in_ratio.x < 1.f)
	{
		ratio.x = 1.f;
	}
	if (in_ratio.y < 1.f)
	{
		ratio.y = 1.f;
	}
}

void Grid::SetColor(sf::Color c)
{
	vLine.setFillColor(c);
	hLine.setFillColor(c);
}

void Grid::SetCellSize(int size)
{
	cellSize = size;
}

void Grid::SetGridSize(sf::Vector2i size)
{
	gridSize = size;
}
