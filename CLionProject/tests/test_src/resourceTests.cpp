//
// Created by diego on 25/05/18.
//

#include <gtest/gtest.h>
#include "../../src/Resources/Texture.h"


TEST(TextureTest, existingFileLoaded) {
	Texture texture(0);
	std::string path = "test.png";
	texture.load(path);
	
	ASSERT_EQ(texture.isValidResource(), true);
	
}

TEST(TextureTest, nonexistingFileLoaded) {
	Texture texture(0);
	std::string path = "testfalso.png";
	texture.load(path);

	ASSERT_EQ(texture.isValidResource(), false);
}

