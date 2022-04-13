#include "SpriteAtlas.h"

void SpriteAtlas::SetFilePath(FilePath fullpath)
{
	filePath = fullpath;
}

void SpriteAtlas::SetFileDir(std::string dir)
{
	filePath.SetFileDir(dir);
}

void SpriteAtlas::SetFileName(std::string name)
{
	filePath.SetFileName(name);
}

void SpriteAtlas::LoadSpriteSheet()
{
	if (!filePath.IsEmpty()) // fullpath not empty
	{
		resManager.LoadTexture(filePath.GetFileName(), filePath.GetFilePath());
	}
	else if (filePath.GetFileDir() != "" && filePath.GetFileName() != "")
	{
		resManager.LoadTexture(filePath.GetFileName(), filePath.GetFileDir() + filePath.GetFileName());
	}
}

FilePath SpriteAtlas::GetFilePath()
{
	return filePath;
}

sf::Texture& SpriteAtlas::GetTexture() {
	return *resManager.GetTexture(filePath.GetFileName());
}
