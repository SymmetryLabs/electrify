#pragma once

string serializedProject = R"({
    "value0": {
        "polymorphic_id": 2147483649,
        "polymorphic_name": "BlueprintProject",
        "ptr_wrapper": {
            "valid": 1,
            "data": {
                "Project": {
                    "model": {
                        "ptr_wrapper": {
                            "valid": 1,
                            "data": {
                                "pixels": [
                                    {
                                        "ptr_wrapper": {
                                            "id": 2147483649,
                                            "data": {
                                                "x": 0,
                                                "y": 0,
                                                "z": 0
                                            }
                                        }
                                    }
                                ]
                            }
                        }
                    }
                },
                "blueprint": {
                    "polymorphic_id": 1073741824,
                    "ptr_wrapper": {
                        "id": 2147483650,
                        "data": {
                            "CompoundNodeHandle": {
                                "NodeHandle": {
                                    "DataStorage": {
                                        "value0": []
                                    },
                                    "uuid": "19d8d99f-8e40-4bb1-a75c-d475a2fca077",
                                    "nodeName": "BlueprintNode",
                                    "name": "Blueprint"
                                },
                                "subnodes": [
                                    {
                                        "polymorphic_id": 2147483650,
                                        "polymorphic_name": "CompoundNodeHandle",
                                        "ptr_wrapper": {
                                            "id": 2147483651,
                                            "data": {
                                                "NodeHandle": {
                                                    "DataStorage": {
                                                        "value0": []
                                                    },
                                                    "uuid": "7863d8d3-e0eb-469a-897f-8d0d415728e0",
                                                    "nodeName": "CompoundNode",
                                                    "name": "Compound node"
                                                },
                                                "subnodes": [
                                                    {
                                                        "polymorphic_id": 1073741824,
                                                        "ptr_wrapper": {
                                                            "id": 2147483652,
                                                            "data": {
                                                                "DataStorage": {
                                                                    "value0": []
                                                                },
                                                                "uuid": "dca4689a-71ad-4756-8506-23c15d479bd6",
                                                                "nodeName": "ConstantColorNode",
                                                                "name": "Constant color"
                                                            }
                                                        }
                                                    },
                                                    {
                                                        "polymorphic_id": 1073741824,
                                                        "ptr_wrapper": {
                                                            "id": 2147483653,
                                                            "data": {
                                                                "DataStorage": {
                                                                    "value0": []
                                                                },
                                                                "uuid": "066f5133-5659-49c6-8c6d-cf5e7acaf665",
                                                                "nodeName": "TranslateNode",
                                                                "name": "Translate"
                                                            }
                                                        }
                                                    }
                                                ],
                                                "nodeWires": [
                                                    {
                                                        "ptr_wrapper": {
                                                            "id": 2147483654,
                                                            "data": {
                                                                "sourceHandle": {
                                                                    "locked_ptr": {
                                                                        "polymorphic_id": 1073741824,
                                                                        "ptr_wrapper": {
                                                                            "id": 4
                                                                        }
                                                                    }
                                                                },
                                                                "sourceName": "output",
                                                                "destinationHandle": {
                                                                    "locked_ptr": {
                                                                        "polymorphic_id": 1073741824,
                                                                        "ptr_wrapper": {
                                                                            "id": 5
                                                                        }
                                                                    }
                                                                },
                                                                "destinationName": "ContextModifierNode"
                                                            }
                                                        }
                                                    },
                                                    {
                                                        "ptr_wrapper": {
                                                            "id": 2147483655,
                                                            "data": {
                                                                "sourceHandle": {
                                                                    "locked_ptr": {
                                                                        "polymorphic_id": 1073741824,
                                                                        "ptr_wrapper": {
                                                                            "id": 5
                                                                        }
                                                                    }
                                                                },
                                                                "sourceName": "ContextModifierNode",
                                                                "destinationHandle": {
                                                                    "locked_ptr": {
                                                                        "polymorphic_id": 2,
                                                                        "ptr_wrapper": {
                                                                            "id": 3
                                                                        }
                                                                    }
                                                                },
                                                                "destinationName": "color"
                                                            }
                                                        }
                                                    }
                                                ]
                                            }
                                        }
                                    }
                                ],
                                "nodeWires": [
                                    {
                                        "ptr_wrapper": {
                                            "id": 2147483656,
                                            "data": {
                                                "sourceHandle": {
                                                    "locked_ptr": {
                                                        "polymorphic_id": 2,
                                                        "ptr_wrapper": {
                                                            "id": 3
                                                        }
                                                    }
                                                },
                                                "sourceName": "color",
                                                "destinationHandle": {
                                                    "locked_ptr": {
                                                        "polymorphic_id": 2147483651,
                                                        "polymorphic_name": "Blueprint",
                                                        "ptr_wrapper": {
                                                            "id": 2
                                                        }
                                                    }
                                                },
                                                "destinationName": "color"
                                            }
                                        }
                                    }
                                ]
                            }
                        }
                    }
                }
            }
        }
    }
})";
