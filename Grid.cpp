#include "Grid.h"

Grid::Grid(int in_cellSize, sf::Vector2i in_gridSize, Camera& camera)
	:
	cellSize(in_cellSize),
	gridSize(in_gridSize),
	camera(camera)
{
	hLine.setSize({ (float)cellSize * (float)gridSize.x, 2.f });
	vLine.setSize({ 2.f, (float)cellSize * (float)gridSize.y });
	SetColor(sf::Color::White);
}

void Grid::Upadate()
{	
	sf::Vector2f scaledCellSize = (sf::Vector2f)camera.MapWorldToScreen({ (float)cellSize,(float)cellSize });
	sf::Vector2f scaledLineWidth = camera.MapScreenToWorld({ 2, 2 });
	hLine.setSize({ (float)cellSize * (float)gridSize.x, scaledLineWidth.y });
	vLine.setSize({ scaledLineWidth.x, (float)cellSize * (float)gridSize.y });
}

void Grid::Draw(tgui::CanvasSFML& canvas)
{
	for (int x = 0; x <= gridSize.x; x++)
	{
		sf::Vector2f worldPos = camera.MapScreenToWorld({ x * cellSize, 0 });
		vLine.setPosition({ (float)x * (float)cellSize, 0 });
		canvas.draw(vLine);
	}
	for (int y = 0; y <= gridSize.y; y++)
	{
		sf::Vector2f worldPos = camera.MapScreenToWorld({ 0, y * cellSize });
		hLine.setPosition({ 0, (float)y * (float)cellSize });
		canvas.draw(hLine);
	}
}

void Grid::Draw(sf::RenderTexture& rt)
{
	for (int x = 0; x <= gridSize.x; x++)
	{
		sf::Vector2f worldPos = camera.MapScreenToWorld({ x * cellSize, 0 });
		vLine.setPosition({ (float)x * (float)cellSize, 0 });
		rt.draw(vLine);
	}
	for (int y = 0; y <= gridSize.y; y++)
	{
		sf::Vector2f worldPos = camera.MapScreenToWorld({ 0, y * cellSize });
		hLine.setPosition({ 0, (float)y * (float)cellSize });
		rt.draw(hLine);
	}
}

std::string Grid::GetDebugSStream()
{
	return ss.str();
}

int Grid::GetClickedOnCellIndex(const sf::Vector2i& mousePos)
{
	sf::Vector2f pos = camera.MapScreenToWorld(mousePos);
	sf::Vector2f offset = camera.GetOffset();
	sf::Vector2f worldPos = pos - offset;
	
	int xLoc = (worldPos.x) / (cellSize); /// camera.GetZoomLevel()
	int yLoc = (worldPos.y) / (cellSize);

	int index = yLoc * gridSize.y + xLoc;
	
	if (!ss.str().empty())
	{
		ss.str("");
	}
	
	ss << " !mousePos: " << mousePos.x << " " << mousePos.y << '\n'
		<< " worldPos1: " << worldPos.x << " " << worldPos.y << '\n'
		<< " zoomLevel: " << camera.GetZoomLevel() << '\n'
		<< " Index: " << index << '\n'
		<< " offset: " << offset.x << " " << offset.y << '\n'
		<< " vCenter: " << camera.GetView().getCenter().x << " " << camera.GetView().getCenter().y << '\n';
	


	return index;
}

void Grid::SetHorizontalLength(float length)
{
	hLine.setSize({ length, 1.f });
}

void Grid::SetVerticalLength(float length)
{
	vLine.setSize({ 1.f, length });
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
