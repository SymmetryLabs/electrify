#include "catch/catch.hpp"

#include "project_test_data.h"
#include "engine.h"
#include "rasterization_thread.h"
#include "output.h"

SCENARIO("typical engine/rasterization thread usage") {
    GIVEN("An engine and rasterization thread") {
        Engine engine;
        auto project = projectTestData();
        engine.loadProject(std::move(project));
        auto& rasterizationThread = engine.getRasterizationThread();
        engine.init();
        rasterizationThread.init();

        WHEN("the rasterization thread performs 1 update") {
            rasterizationThread.performFrameUpdate();
            rasterizationThread.performRasterization();
            THEN("The output is 1") {
                std::vector<Color> out{1};
                rasterizationThread.copyColorBuffer(out);
                REQUIRE(out[0] == Color(0x1));
            }
        }

        WHEN("the rasterization thread performs 2 updates") {
            rasterizationThread.performFrameUpdate();
            rasterizationThread.performFrameUpdate();
            rasterizationThread.performRasterization();
            THEN("The output is 1") {
                std::vector<Color> out{1};
                rasterizationThread.copyColorBuffer(out);
                REQUIRE(out[0] == Color(0x2));
            }
        }

        GIVEN("an output") {
            auto output = std::make_shared<Output>();
            engine.registerOutput(output);

            WHEN("the rasterization thread performs 1 update") {
                rasterizationThread.performFrameUpdate();
                rasterizationThread.performRasterization();
                output->populateFrame();
                THEN("The output is 1") {
                    REQUIRE(output->getColorBuffer().size() == 1);
                    REQUIRE(output->getColorBuffer()[0] == Color(0x1));
                }
                WHEN("the rasterization thread performs another update") {
                    rasterizationThread.performFrameUpdate();
                    rasterizationThread.performRasterization();
                    output->populateFrame();
                    THEN("The output is 2") {
                        REQUIRE(output->getColorBuffer().size() == 1);
                        REQUIRE(output->getColorBuffer()[0] == Color(0x2));
                    }
                }
            }

            WHEN("the rasterization thread performs 2 updates") {
                rasterizationThread.performFrameUpdate();
                rasterizationThread.performFrameUpdate();
                rasterizationThread.performRasterization();
                output->populateFrame();
                THEN("The output is 1") {
                    REQUIRE(output->getColorBuffer().size() == 1);
                    REQUIRE(output->getColorBuffer()[0] == Color(0x2));
                }
            }
        }
    }
}

SCENARIO("Model changes while the rasterization thread is running") {
    GIVEN("An engine, rasterization thread, and output") {
        Engine engine;
        auto project = projectTestData();
        auto& model = project->getModel();
        engine.loadProject(std::move(project));
        auto output = std::make_shared<Output>();
        engine.registerOutput(output);
        auto& rasterizationThread = engine.getRasterizationThread();
        engine.init();
        rasterizationThread.init();
        auto& mainRelay = engine.getDataRelay();

        GIVEN("I make a change to the model") {
            REQUIRE(output->getModel().pixels.size() == 1);
            REQUIRE(output->getModel().pixels.sizeVar == 1);
            REQUIRE(rasterizationThread.getModel().pixels.size() == 1);
            model.pixels.push_back(std::make_shared<Pixel>());
            WHEN("I don't commit the transaction") {
                THEN("It doesn't show up on either the rasterization thread or the output") {
                    REQUIRE(rasterizationThread.getModel().pixels.size() == 1);
                    REQUIRE(output->getModel().pixels.size() == 1);
                }
            }
            WHEN("I commit the transaction") {
                mainRelay.commitOutgoingTransaction();
                THEN("It doesn't show up on either the rasterization thread or the output at first") {
                    REQUIRE(rasterizationThread.getModel().pixels.size() == 1);
                    REQUIRE(output->getModel().pixels.size() == 1);
                }
                WHEN("I perform rasterization") {
                    rasterizationThread.performRasterization();
                    THEN("It doesn't show up on either the rasterization thread or the output at first") {
                        REQUIRE(rasterizationThread.getModel().pixels.size() == 1);
                        REQUIRE(output->getModel().pixels.size() == 1);
                    }
                }
                WHEN("I perform a frame update") {
                    rasterizationThread.performFrameUpdate();
                    THEN("it shows up on the rasterization thread but not the output") {
                        REQUIRE(rasterizationThread.getModel().pixels.size() == 2);
                        REQUIRE(output->getModel().pixels.size() == 1);
                    }
                    WHEN("The output populates the frame") {
                        output->populateFrame();
                        THEN("it still doesn't show up on the output") {
                            REQUIRE(output->getModel().pixels.size() == 1);
                        }
                    }
                    GIVEN("it's rasterized") {
                        rasterizationThread.performRasterization();
                        WHEN("output populates the frame") {
                            output->populateFrame();
                            THEN("it has the correct last frame id") {
                                REQUIRE(output->getLastFrameId() == 1);
                            }
                            THEN("it shows up on the output") {
                                REQUIRE(output->getModel().pixels.size() == 2);
                            }
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Dyanamic project loading") {
    GIVEN("An engine, rasterization thread") {
        Engine engine;
        auto& mainRelay = engine.getDataRelay();
        engine.loadProject(projectTestData());

        auto& rasterizationThread = engine.getRasterizationThread();
        rasterizationThread.getModel().pixels[0]->x = 10;
        engine.init();
        rasterizationThread.init();
        
        mainRelay.commitOutgoingTransaction();
        rasterizationThread.performFrameUpdate();
        rasterizationThread.performRasterization();

        GIVEN("a frame is rasterized") {
            rasterizationThread.performFrameUpdate();
            rasterizationThread.performRasterization();
        }

        GIVEN("a new project has been loaded") {
            engine.loadProject(projectTestData());
            THEN("the rasterization thread's model stays intact") {
                REQUIRE(rasterizationThread.getModel().pixels[0]->x == 10);
            }
            WHEN("the frame is rasterized again") {
                rasterizationThread.performRasterization();
            }
            WHEN("the frame is updated") {
                rasterizationThread.performFrameUpdate();
                THEN("the rasterization thread's model stays intact") {
                    REQUIRE(rasterizationThread.getModel().pixels[0]->x == 10);
                }
                WHEN("another frame is rasterized") {
                    rasterizationThread.performRasterization();
                }
            }
        }

        GIVEN("a new project has been loaded but not committed") {
            auto& oldRenderable = rasterizationThread.getRenderable();
            engine.loadProject(projectTestData());
            WHEN("a frame is rasterized") {
                rasterizationThread.performFrameUpdate();
                rasterizationThread.performRasterization();
                THEN("The renderable doesn't change") {
                    REQUIRE(&oldRenderable == &rasterizationThread.getRenderable());
                }
            }
        }

        GIVEN("a new project has been loaded and committed") {
            auto& oldRenderable = rasterizationThread.getRenderable();
            auto newProject = projectTestData();
            auto& blueprint = newProject->getBlueprint();
            engine.loadProject(std::move(newProject));
            mainRelay.commitOutgoingTransaction();
            THEN("The renderable hasn't changed yet") {
                REQUIRE(&oldRenderable == &rasterizationThread.getRenderable());
            }
            GIVEN("another frame is rasterized") {
                rasterizationThread.performFrameUpdate();
                rasterizationThread.performRasterization();
                auto renderable = dynamic_cast<BlueprintRenderable*>(&rasterizationThread.getRenderable());
                REQUIRE(renderable);
                auto& blueprintNode = renderable->getBlueprintNode();
                THEN("The renderable has changed yet") {
                    REQUIRE(&oldRenderable != &rasterizationThread.getRenderable());
                }
                THEN("the rasterization thread should have the updates to the node network") {
                    REQUIRE(blueprintNode.getNumSubnodes() == 1);
                }
                GIVEN("The node network has a node removed") {
                    REQUIRE(blueprint.subnodes.size() == 1);
                    blueprint.removeSubnode(*blueprint.subnodes.at(0));
                    mainRelay.commitOutgoingTransaction();
                    REQUIRE(blueprint.subnodes.size() == 0);
                    THEN("the rasterization thread node network doesn't have the change") {
                        REQUIRE(blueprintNode.getNumSubnodes() == 1);
                    }
                    GIVEN("another frame is rasterized") {
                        rasterizationThread.performFrameUpdate();
                        rasterizationThread.performRasterization();
                        THEN("the rasterization thread node network has the change") {
                            REQUIRE(blueprintNode.getNumSubnodes() == 0);
                        }
                    }
                }
            }
        }
    }
}

#include "project_serializer.h"

SCENARIO("Dyanamic project loading of a serialized project") {
    GIVEN("An engine, rasterization thread") {
        Engine engine;
        auto& mainRelay = engine.getDataRelay();
        engine.loadProject(projectTestData());

        auto& rasterizationThread = engine.getRasterizationThread();
        engine.init();
        rasterizationThread.init();
        
        mainRelay.commitOutgoingTransaction();
        rasterizationThread.performFrameUpdate();
        rasterizationThread.performRasterization();

        GIVEN("the project is serialized and unserialized") {
            auto& session = engine.getSession();
            auto str = ProjectSerializer::serialize(session.getProject());
            auto deserializedProject = ProjectSerializer::deserialize(str);
            auto& blueprint = dynamic_cast<BlueprintProject&>(*deserializedProject).getBlueprint();
            engine.loadProject(std::move(deserializedProject));
            mainRelay.commitOutgoingTransaction();
            rasterizationThread.performFrameUpdate();
            rasterizationThread.performRasterization();
            auto renderable = dynamic_cast<BlueprintRenderable*>(&rasterizationThread.getRenderable());
            auto& blueprintNode = renderable->getBlueprintNode();
            THEN("the rasterization thread node network has the initial setup") {
                REQUIRE(blueprintNode.getNumSubnodes() == 1);
            }
            WHEN("The node network has a node removed") {
                REQUIRE(blueprint.subnodes.size() == 1);
                blueprint.removeSubnode(*blueprint.subnodes.at(0));
                mainRelay.commitOutgoingTransaction();
                REQUIRE(blueprint.subnodes.size() == 0);
                THEN("the rasterization thread node network doesn't have the change") {
                    REQUIRE(blueprintNode.getNumSubnodes() == 1);
                }
                GIVEN("another frame is rasterized") {
                    rasterizationThread.performFrameUpdate();
                    rasterizationThread.performRasterization();
                    THEN("the rasterization thread node network has the change") {
                        REQUIRE(blueprintNode.getNumSubnodes() == 0);
                    }
                }
            }
        }
    }
}
