#include "catch/catch.hpp"

#include "project_test_data.h"
#include "engine.h"
#include "rasterization_thread.h"
#include "output.h"

SCENARIO("Using Output") {
    GIVEN("An engine with a project and an output") {
        Engine engine;
        auto& mainRelay = engine.getDataRelay();
        engine.loadProject(projectTestData());
        auto output = std::make_shared<Output>();
        int calls = 0;
        output->getModelObservable().observe([&] (const shared_ptr<Model>& model) {
            calls++;
        });
        THEN("it starts with no model callbacks") {
            REQUIRE(calls == 0);
        }

        WHEN("I register the output") {
            engine.registerOutput(output);
            THEN("the output has a renderer") {
                REQUIRE(output->hasRenderer());
            }
            THEN("the output has a model") {
                REQUIRE(output->hasModel());
            }
            THEN("the output's model has pixels") {
                REQUIRE(output->getModel().getNumPixels() == 1);
                REQUIRE(output->getModel().pixels[0]);
            }
            THEN("there is a model callback") {
                REQUIRE(calls == 1);
            }
            THEN("I can observe the modelObservable") {
                int calls2 = 0;
                output->getModelObservable().observe([&] (const shared_ptr<Model>& model) {
                    calls2++;
                });
                REQUIRE(calls2 == 1);
            }
        }
        GIVEN("I start the engine") {
            auto& rasterizationThread = engine.getRasterizationThread();
            engine.init();
            rasterizationThread.init();

            WHEN("I register the output") {
                engine.registerOutput(output);
                THEN("the output has a renderer") {
                    REQUIRE(output->hasRenderer());
                }
                THEN("the output doesn't have a model") {
                    REQUIRE(!output->hasModel());
                }
                WHEN("the changes are committed") {
                    mainRelay.commitOutgoingTransaction();
                    THEN("the main relay incremented the frame id") {
                        REQUIRE(mainRelay.getLastFrameId() == 1);
                    }
                    rasterizationThread.performFrameUpdate();
                    THEN("the rasterization thread received the correct frame id") {
                        REQUIRE(rasterizationThread.getDataRelayId() == 1);
                    }
                    REQUIRE(rasterizationThread.getDataRelay().getLastFrameId() == 1);
                    rasterizationThread.performRasterization();
                    REQUIRE(output->getLastFrameId() == -1);
                    output->populateFrame();
                    THEN("it has the new frame id") {
                        REQUIRE(output->getLastFrameId() == 1);
                    }
                    THEN("the output has a model") {
                        std::vector<Color> v;
                        REQUIRE(rasterizationThread.copyColorBuffer(0, v) == 1);
                        REQUIRE(output->hasModel());
                    }
                    THEN("the output's model has pixels") {
                        REQUIRE(output->getModel().getNumPixels() == 1);
                        REQUIRE(output->getModel().pixels[0]);
                    }
                    THEN("there is a model callback") {
                        REQUIRE(calls == 1);
                    }
                    THEN("I can observe the modelObservable") {
                        int calls2 = 0;
                        output->getModelObservable().observe([&] (const shared_ptr<Model>& model) {
                            calls2++;
                        });
                        REQUIRE(calls2 == 1);
                    }
                }
            }
        }
    }
    GIVEN("An engine, rasterization thread, and output") {
        Engine engine;
        auto& mainRelay = engine.getDataRelay();
        engine.loadProject(projectTestData());

        auto output = std::make_shared<Output>();
        engine.registerOutput(output);

        auto& rasterizationThread = engine.getRasterizationThread();
        rasterizationThread.getModel().pixels[0]->x = 10;
        engine.init();
        rasterizationThread.init();
    }
}

SCENARIO("Dyanamic project loading with an output") {
    GIVEN("An engine, rasterization thread, and output") {
        Engine engine;
        auto& mainRelay = engine.getDataRelay();
        engine.loadProject(projectTestData());

        auto output = std::make_shared<Output>();
        engine.registerOutput(output);

        auto& rasterizationThread = engine.getRasterizationThread();
        rasterizationThread.getModel().pixels[0]->x = 10;
        engine.init();
        rasterizationThread.init();

        GIVEN("a new project has been loaded") {
            engine.loadProject(projectTestData());
            THEN("the rasterization thread's model stays intact") {
                REQUIRE(rasterizationThread.getModel().pixels[0]->x == 10);
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

        GIVEN("a new project has been loaded and committed") {
            engine.loadProject(projectTestData());
            mainRelay.commitOutgoingTransaction();
            WHEN("another frame is rasterized") {
                rasterizationThread.performFrameUpdate();
                rasterizationThread.performRasterization();
            }
        }
    }
}

SCENARIO("observing model changes on an output") {
    GIVEN("an output") {
        auto output = std::make_shared<Output>();
        int calls = 0;
        output->getModelObservable().observe([&] (const shared_ptr<Model>& model) {
            calls++;
        });
        THEN("it starts with no model callbacks") {
            REQUIRE(calls == 0);
        }
        WHEN("I set the model on the output") {
            auto model = make_shared<Model>();
            output->setModel(model);
            THEN("the output has a model") {
                REQUIRE(output->hasModel());
            }
            THEN("there is a model callback") {
                REQUIRE(calls == 1);
            }
            THEN("I can observe the modelObservable") {
                int calls2 = 0;
                output->getModelObservable().observe([&] (const shared_ptr<Model>& model) {
                    calls2++;
                });
                REQUIRE(calls2 == 1);
            }
        }
    }
}
