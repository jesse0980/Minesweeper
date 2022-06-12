#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string filename) {
	string path = "images/";
	path += filename + ".png";

	textures[filename].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string texturename) {
	if (textures.find(texturename) == textures.end()) {
		LoadTexture(texturename);
	}

	return textures[texturename];
}

void TextureManager::Clear() {
	textures.clear(); //get rid of all stored objects
}

