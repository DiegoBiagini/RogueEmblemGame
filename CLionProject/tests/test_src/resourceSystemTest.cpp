//
// Created by diego on 26/05/18.
//
#include <gtest/gtest.h>
#include "../../src/Systems/ResourceSystem.h"

class ResourceSystemTest : public ::testing::Test {

protected:
	virtual void TearDown() {
		resourceSystem.shutdown();
	}

	virtual void SetUp() {
		resourceSystem.startup();
	}

	ResourceSystem resourceSystem;
};

TEST_F(ResourceSystemTest, LoadNonExistingImage) {
	int id = resourceSystem.enqueueRequest();
	ASSERT_FALSE(id == 0);

	std::string fakePath("fakeee.fk");
	std::shared_ptr<ResourceMessage> msg {new ResourceMessage};

	msg->type = ResourceMessage::Type::LOAD_TEXTURE;
	msg->path = fakePath;


	resourceSystem.handleMsg(std::move(msg));

	//Get it back and see if it is null
	ASSERT_EQ(resourceSystem.getResourceById(id), nullptr);
}

TEST_F(ResourceSystemTest, Load2Images) {
	int id1 = resourceSystem.enqueueRequest();
	int id2 = resourceSystem.enqueueRequest();
	//Check that the ids are saved correctly
	ASSERT_FALSE(id1 == 0);
	ASSERT_FALSE(id2 == 0);
	ASSERT_EQ(id2 , id1 + 1);


	std::string path1("test.png");
	std::string path2("test2.png");

	std::shared_ptr<ResourceMessage> msg1 {new ResourceMessage};
	msg1->type = ResourceMessage::Type::LOAD_TEXTURE;
	msg1->path = path1;

	resourceSystem.handleMsg(std::move(msg1));

	std::shared_ptr<ResourceMessage> msg2 {new ResourceMessage};
	msg2->type = ResourceMessage::Type::LOAD_TEXTURE;
	msg2->path = path2;

	resourceSystem.handleMsg(std::move(msg2));

	//Get it back and see if it is null
	ASSERT_NE(resourceSystem.getResourceById(id1), nullptr);
	ASSERT_NE(resourceSystem.getResourceById(id2), nullptr);
	ASSERT_NE(resourceSystem.getResourceById(id1), resourceSystem.getResourceById(id2));

	//Chech that paths are saved correctly
	ASSERT_EQ(id1, resourceSystem.getIdByPath(path1));
	ASSERT_EQ(id2, resourceSystem.getIdByPath(path2));
}

TEST_F(ResourceSystemTest, LoadAndFreeResource) {
	int id = resourceSystem.enqueueRequest();
	ASSERT_FALSE(id == 0);

	std::string path("test.png");
	std::shared_ptr<ResourceMessage> msg {new ResourceMessage};

	msg->type = ResourceMessage::Type::LOAD_TEXTURE;
	msg->path = path;

	resourceSystem.handleMsg(std::move(msg));

	//Get it back and see if it is null
	ASSERT_NE(resourceSystem.getResourceById(id), nullptr);

	//Check that freeing is successful
	ASSERT_NO_THROW(resourceSystem.freeResourceById(id));
	ASSERT_EQ(resourceSystem.getResourceById(id), nullptr);
}